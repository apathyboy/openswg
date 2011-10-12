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

#include <osSOEProtocol/radialmenumanager.h>
#include <osSOEProtocol/soelayermessages.h>
#include <gsCore/callback.h>
#include <gsNetwork/binarypacket.h>
#include <gsServer/session.h>

using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
		
RadialMenuManager::RadialMenuManager(ObjectManager* objectManager)
: m_objectManager(objectManager)
{}
		
RadialMenuManager::~RadialMenuManager()
{}

void RadialMenuManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
	CBFunctor2<Session*, BinaryPacketPtr> handler = makeFunctor((HandlerFunctor)0, *this, &RadialMenuManager::handleRadialSelection);	
	factory->addOpcodeHandler(0x7ca18726, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
}


void RadialMenuManager::handleRadialSelection(gsServer::Session* session, gsNetwork::BinaryPacketPtr message) 
{
	boost::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);
	
	uint64_t targetId = message->read<uint64_t>();
	uint8_t option = message->read<uint8_t>();

	boost::optional<ObjectProxyPtr> objectProxy = m_objectManager->findObjectProxyById(targetId);
	(*objectProxy)->radialSelection(option, session);
}
