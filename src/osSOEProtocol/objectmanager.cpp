/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2007 OpenSWG Team <http://www.openswg.com>
 */

// *********************************************************************
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// To read the license please visit http://www.gnu.org/copyleft/gpl.html
// *********************************************************************

#include "osSOEProtocol/objectmanager.h"
#ifdef ERROR
#undef ERROR
#endif

#include <glog/logging.h>

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsServer/sessionevents.h>
#include <gsCore/datastore.h>
#include <osSOEProtocol/opcodes.h>

#include <osSOEProtocol/logincharacterrequest.h>
#include <osSOEProtocol/soelayermessages.h>
#include <osSOEProtocol/loadreadymessage.h>
#include <osSOEProtocol/emotemessage.h>
#include <osSOEProtocol/radialresponsemessage.h>
#include <osSOEProtocol/postureupdatemessage.h>
#include <osSOEProtocol/selfpostureupdatemessage.h>
#include <osSOEProtocol/spatialchatmessage.h>
#include <osSOEProtocol/movementmessage.h>
#include <osSOEProtocol/cellmovementmessage.h>
#include <osSOEProtocol/radialmenumanager.h>
#include <osSOEProtocol/creatureobjectproxy.h>
#include <osSOEProtocol/playercreatureobjectproxy.h>
#include <osSOEProtocol/objectpropertytypes.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

ObjectManager::ObjectManager(ObjectGrid* objectGrid)
: Process(PROC_OBJECTS)
, m_objectGrid(objectGrid)
{
	m_attempt = 0;
	//m_objectGrid = GS_NEW ObjectGrid;
}

boost::optional<ObjectProxyPtr> ObjectManager::findObjectProxyById(uint64_t objectId)
{
	boost::optional<ObjectProxyPtr> object = m_objectGrid->findObjectProxyById(objectId);
	return object;
}

boost::optional<ObjectProxyPtr> ObjectManager::findObjectProxyBySession(Session* session)
{
	boost::optional<ObjectProxyPtr> object = m_objectGrid->findObjectProxyBySession(session);
	return object;
}

void ObjectManager::removeObject(ObjectProxyPtr object)
{
	m_objectGrid->removeObject(object);
}

void ObjectManager::update(const uint64_t updateTimestamp)
{}
        
void ObjectManager::initialize()
{
	// Register the basic events needed to run the server application.
	// Additional events or overrides can be performed from the concrete
	// application instance.	
	EventListenerPtr objectManagerEventListener(GS_NEW ObjectManagerEventListener(this));
	ObjectManagerEventListener::registerEvents(objectManagerEventListener);

	m_radialMenuManager = GS_NEW RadialMenuManager(this);
    buildRadialMenuMap(m_radialMenuMap);
}

void ObjectManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
	CBFunctor2<Session*, std::shared_ptr<BinaryPacket>> handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleLoginCharacter);	
	factory->addOpcodeHandler(CMSG_LOGIN_CHAR, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleObjectPreload);	
	factory->addOpcodeHandler(CMSG_OBJ_PRELOAD, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleUnknown);	
	factory->addOpcodeHandler(0x0f5d5325, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
	
	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleUnknown);	
	factory->addOpcodeHandler(0x4c3d2cfa, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
	
	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleUnknown);	
	factory->addOpcodeHandler(0x48f493c5, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleUnknown);	
	factory->addOpcodeHandler(0xca88fbad, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleCommand);	
	factory->addOpcodeHandler(0x80CE5E46, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
	
	handler = makeFunctor((HandlerFunctor)0, *this, &ObjectManager::handleLoadReady);	
	factory->addOpcodeHandler(CMSG_LOAD_READY, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	m_radialMenuManager->registerOpcodes(factory);
}

void ObjectManager::handleUnknown(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) 
{
	std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);
}

void ObjectManager::handleObjectPreload(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) 
{
	std::shared_ptr<AcknowledgeMessage> ack(GS_NEW AcknowledgeMessage());
	ack->sequence = session->getClientSequence();
	session->sendToRemote(ack);
}

void ObjectManager::handleLoadReady(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) 
{
	std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);

	std::shared_ptr<LoadReadyMessage> loadReady(GS_NEW LoadReadyMessage());
	session->sendToRemote(loadReady);
}

void ObjectManager::handleLoginCharacter(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) 
{
	if (session->isLoggedIn())
		return;

	session->setLoggedIn(true);

	std::shared_ptr<LoginCharacterRequest> loginRequest(GS_NEW LoginCharacterRequest(message));
	loginRequest->unserialize();

	std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);

	PlayerCreatureObjectProxyPtr proxy(GS_NEW PlayerCreatureObjectProxy);
	proxy->loadFromDatabaseId(loginRequest->characterId);
	proxy->setPlayerSession(session);

    LOG(INFO) << "Logging in character: " << proxy->getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue();

	m_objectGrid->insert(proxy);
}

void ObjectManager::handleCommand(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) 
{
    uint32_t header = message->read<uint32_t>();

    switch(header)
    {
    case 0x00000083:
    case 0x00000021:
    case 0x00000023:
        {
            header = message->read<uint32_t>();
            
            switch (header)
            {
            case 0x00000126:
				{					
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);
					
					uint64_t objectId = message->read<uint64_t>();

					boost::optional<ObjectProxyPtr> object = findObjectProxyById(objectId);
					
					if (! object)
						return;

					message->read<uint32_t>();

					uint64_t targetId = message->read<uint64_t>();

					(*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("TargetId"))->setValue(targetId);
					(*object)->notifyInRange(false);
				}
				break;
            case 0x00000146:
                {
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);
					
					printf("In Msg: \n%s\n", message->getLogString().c_str());
                    uint64_t objectId = message->read<uint64_t>();
                    uint32_t errCode = message->read<uint32_t>();
                    uint64_t targetId = message->read<uint64_t>();
                    uint64_t initiatorId = message->read<uint64_t>();

                    RadialMenuMap map;

                    uint32_t radialCount = message->read<uint32_t>();
                    for (uint32_t i = 0; i < radialCount; i++)
                    {
						uint8_t index = message->read<uint8_t>();
						uint8_t parentIndex = message->read<uint8_t>();
                        RadialMenuMap::iterator j = m_radialMenuMap.find(message->read<uint8_t>());

                        RadialOption option;

                        if (j != m_radialMenuMap.end())
                        {
                            option = (*j).second;
							option.index = index; // Index.
							option.parentIndex = parentIndex; // Parent.
                            map[option.id] = option;                           
                        }       

                        message->read<uint8_t>(); // callback
                        message->read<uint32_t>(); // ??
                    }

                    if (map.size() == 0)
                        break;

                    uint8_t defaultOption = message->read<uint8_t>();
					printf("Radial Response: Target: %i Object: %i\n", targetId, objectId);

					std::shared_ptr<RadialResponseMessage> radialResponse(GS_NEW RadialResponseMessage());
					radialResponse->objectId = objectId;
					radialResponse->targetId = targetId;
					radialResponse->radialMap = map;
					radialResponse->defaultOption = defaultOption;
					session->sendToRemote(radialResponse);

					printf("Response: \n%s\n", radialResponse->serialize()->getLogString().c_str());

                    break;
                }
            case 0x00000116:
                {
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);

                    uint64_t target = message->read<uint64_t>();
                    message->read<uint32_t>(); // error 1?
                    uint16_t count = message->read<uint16_t>();
                    uint16_t intcode = message->read<uint16_t>();                
                    uint32_t opcode = message->read<uint32_t>();
               
                    switch (opcode)
                    {
					case 0xB719FA26: // Sit
						{

							boost::optional<ObjectProxyPtr> object = findObjectProxyById(target);
							
							if (! object)
								return;

							(*object)->getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->setValue(8);
							
							std::shared_ptr<SelfPostureUpdateMessage> selfPostureUpdate(GS_NEW SelfPostureUpdateMessage);
							selfPostureUpdate->objectId = target;
							selfPostureUpdate->posture = 8;
							m_objectGrid->sendInRange(target,	selfPostureUpdate);
//
							std::shared_ptr<PostureUpdateMessage> postureUpdate(GS_NEW PostureUpdateMessage);
							postureUpdate->objectId = target;
							postureUpdate->posture = 8;
							m_objectGrid->sendInRange(target, postureUpdate);
						}
						break;
					case 0xA8A25C79: // Stand
						{

							boost::optional<ObjectProxyPtr> object = findObjectProxyById(target);
							
							if (! object)
								return;

							(*object)->getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->setValue(0);
							
							std::shared_ptr<SelfPostureUpdateMessage> selfPostureUpdate(GS_NEW SelfPostureUpdateMessage);
							selfPostureUpdate->objectId = target;
							selfPostureUpdate->posture = 0;
							m_objectGrid->sendInRange(target, selfPostureUpdate);

							std::shared_ptr<PostureUpdateMessage> postureUpdate(GS_NEW PostureUpdateMessage);
							postureUpdate->objectId = target;
							postureUpdate->posture = 0;
							m_objectGrid->sendInRange(target, postureUpdate);
						}
						break;
					case 0x32CF1BEE: // Emote
						{
							message->read<uint64_t>();
							uint32_t size = message->read<uint32_t>();
							std::ostringstream emoteString;
							message->read<uint32_t>();
							for (uint32_t i = 0; i < size; ++i)
							{
								uint8_t tmp = message->read<uint8_t>();

								if (tmp == 32)
									break;
								message->read<uint8_t>();
								emoteString << tmp;
							}

							boost::optional<ObjectProxyPtr> object = findObjectProxyById(target);
							
							if (! object)
								return;

							uint32_t emoteId = atoi(emoteString.str().c_str());
       
							std::shared_ptr<EmoteMessage> emoteMessage(GS_NEW EmoteMessage);
							emoteMessage->objectId = target;
							emoteMessage->targetId = (*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("TargetId"))->getValue();
							emoteMessage->emoteId = emoteId;

							m_objectGrid->sendInRange(target, emoteMessage);

						}
						break;
					case 0x7759f35e: // MOOD
						{
							message->read<uint64_t>();
							uint32_t size = message->read<uint32_t>();
							std::ostringstream moodString;

							for (uint32_t i = 0; i < size; ++i)
							{
								uint8_t tmp = message->read<uint8_t>();

								if (tmp == 0 || tmp == 32)
									break;
								message->read<uint8_t>();
								moodString << tmp;
							}

							uint32_t moodInt = atoi(moodString.str().c_str());
							boost::optional<ObjectProxyPtr> object = findObjectProxyById(target);
							
							if (! object)
								return;

							std::string mood = MoodStr[moodInt];

							(*object)->getPropertyAs<StringObjectProperty*>(std::string("Mood"))->setValue(mood);
							(*object)->notifyInRange(true);
						}
						break;
                    case 0x7C8d63d4: // SPATIAL CHAT
                        {                  
							std::shared_ptr<SpatialChatMessage> spatialChat(GS_NEW SpatialChatMessage);
							                  
                            message->read<uint64_t>();
                            uint32_t size = message->read<uint32_t>();

                            std::vector<uint64_t> moods;
                            
                            char tmp[5][32];
                            memset(tmp[0], 0, 32);
                            memset(tmp[1], 0, 32);
                            memset(tmp[2], 0, 32);
                            memset(tmp[3], 0, 32);
                            memset(tmp[4], 0, 32);

                            uint8_t spaces = 0;
                            uint8_t i = 0;
                            uint8_t remove = 0;            
                            
                            while (spaces<5) {
                                uint8_t data = message->read<uint8_t>();

                                if (data == 32) {
                                    spaces++;
                                    i=0;
                                    continue;
                                }
                                if (data == 0) {
                                    remove++;
                                    continue;
                                }
                                tmp[spaces][i] = data;
                                i++;
                                remove++;
                            }
                            message->read<uint8_t>();
                            remove /= 2;
                            remove += 5;

                            for (int j = 0; j < 5; ++j)
                                spatialChat->moods.push_back((uint64_t)atoi(tmp[j]));
                            
                            size -= remove;
                            std::wstring textMessage;
                            
                            for (uint32_t i = 0; i < size+2; ++i)
                            {
                                wchar_t buf = message->read<wchar_t>();
                                textMessage += buf;
                            }

							spatialChat->message = std::string(textMessage.begin(), textMessage.end());    
							spatialChat->targetId = target;

							m_objectGrid->sendInRange(target, spatialChat);
                            
                            break;
                        }

                    default:
                        {
                            LOG(ERROR) << "Unhandled sub-opcode: " << std::hex << opcode;
                        }
                    }

                    break;
                }
            case 0x00000071:
                {
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);
                    
					std::shared_ptr<MovementMessage> movement(GS_NEW MovementMessage(message));
					movement->unserialize();

					m_objectGrid->moveObject(movement);

					break;
                }
                
            case 0x000000f1:
                {                
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);

					std::shared_ptr<CellMovementMessage> movement(GS_NEW CellMovementMessage(message));
					movement->unserialize();

					m_objectGrid->moveCellObject(movement);

					break;
                }

            default:
                {
					std::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
					ok->sequence = session->getClientSequence();
					session->sendToRemote(ok);
                    LOG(ERROR) << "Unhandled sub-opcode: " << std::hex << header;
                    break;
                }
            }
        }
    }
}



bool ObjectManagerEventListener::handleEvent(Event const & event)
{
    if (_stricmp(event.getType().getStr(), Event_DisconnectRequested::gkName) == 0)
    {
		printf("Object manager handler disconnect\n");
        EventData_DisconnectRequested * eventData = event.getDataPtr<EventData_DisconnectRequested>();		
		
		boost::optional<ObjectProxyPtr> object = m_objectManager->findObjectProxyBySession(eventData->session);
		(*object)->store();

		m_objectManager->removeObject(*object);			
	}

	return false;
}
	
void ObjectManagerEventListener::registerEvents(EventListenerPtr listener)
{
	safeAddListener(listener, EventType(Event_DisconnectRequested::gkName));
}

