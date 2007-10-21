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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTMANAGER
#define OPENSWG_SOEPROTOCOL_OBJECTMANAGER

#include <osSOEProtocol/export.h>
#include <gsCore/eventlistener.h>
#include <gsCore/process.h>
#include <gsNetwork/binarypacket.h>
#include <gsServer/session.h>
#include <osSOEProtocol/objectgrid.h>

namespace gsServer
{
	class OpcodeFactory;
	class Session;
}

namespace osSOEProtocol
{
	class RadialMenuManager;
	class OS_SOEPROTOCOL_EXPORT ObjectManager : public gsCore::Process //: public GameManager 
	// @NOTE: Extract common functionality to a GameManager base class.
	{
		friend class ObjectManagerEventListener;

	public:
		ObjectManager(ObjectGrid* objectGrid);

		boost::optional<ObjectProxyPtr> findObjectProxyById(uint64 objectId);
		boost::optional<ObjectProxyPtr> findObjectProxyBySession(gsServer::Session* session);
		void removeObject(ObjectProxyPtr object);

	protected:
		ObjectGrid* m_objectGrid;
		RadialMenuManager* m_radialMenuManager;
		uint m_attempt;
		
    public: // gsCore::Process virtual overrides
        virtual void update(const uint64 updateTimestamp);
        virtual void initialize();

	public: // OPCODE HANDLING
		virtual void registerOpcodes(gsServer::OpcodeFactory* factory);

		void handleLoginCharacter(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) ;
		void handleObjectPreload(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) ;
		void handleUnknown(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) ;
		void handleLoadReady(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) ;
		void handleCommand(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) ;
	};

	class OS_SOEPROTOCOL_EXPORT ObjectManagerEventListener : public gsCore::IEventListener
	{
    public:
        ObjectManagerEventListener(ObjectManager* objectManager)
			: m_objectManager(objectManager)
		{}

		virtual ~ObjectManagerEventListener() {}
        char const * getName(void) { return "ObjectManagerEventListener"; }
        bool handleEvent(gsCore::Event const & event);

		static void registerEvents(gsCore::EventListenerPtr listener);

	protected:
		ObjectManager* m_objectManager;
	};
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTMANAGER

