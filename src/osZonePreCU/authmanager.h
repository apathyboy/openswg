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

#ifndef OPENSWG_ZONEPRECU_AUTHMANAGER
#define OPENSWG_ZONEPRECU_AUTHMANAGER

#include <gsNetwork/binarypacket.h>

namespace gsServer
{
	class OpcodeFactory;
	class Session;
}

namespace osZonePreCU
{
	class AuthManager //: public GameManager 
	// @NOTE: Extract common functionality to a GameManager base class.
	{
	public:
		AuthManager();

        bool authenticate(gsServer::Session* session, std::string username, std::string password) const;

	public: // OPCODE HANDLING
		virtual void registerOpcodes(gsServer::OpcodeFactory* factory);

		void handleAuthRequest(gsServer::Session* session, gsNetwork::BinaryPacketPtr packet) const;
	};
}

#endif // OPENSWG_ZONEPRECU_AUTHMANAGER

