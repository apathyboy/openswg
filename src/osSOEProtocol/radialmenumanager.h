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

#ifndef OPENSWG_SOEPROTOCOL_RADIALMENUMANAGER
#define OPENSWG_SOEPROTOCOL_RADIALMENUMANAGER

#include <gsNetwork/binarypacket.h>
#include <osSOEProtocol/radialmenu.h>
#include <osSOEProtocol/objectmanager.h>
#include <gsCore/macros.h>
#include <gsCore/globals.h>
#include <list>

namespace gsServer
{
	class OpcodeFactory;
	class Session;
}

namespace osSOEProtocol
{
	class RadialMenuManager //: public GameManager 
	{
	public:
		RadialMenuManager(ObjectManager* objectManager);
		virtual ~RadialMenuManager();

	protected:
		ObjectManager* m_objectManager;
        
	public: // OPCODE HANDLING
		virtual void registerOpcodes(gsServer::OpcodeFactory* factory);
		void handleRadialSelection(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> packet) ;
	};
}

#endif // OPENSWG_SOEPROTOCOL_RADIALMENUMANAGER