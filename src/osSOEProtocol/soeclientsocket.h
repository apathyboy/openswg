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

#ifndef OPENSWG_SOEPROTOCOL_SOECLIENTSOCKET
#define OPENSWG_SOEPROTOCOL_SOECLIENTSOCKET

#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsNetwork/clientsocket.h>
#include <gsServer/sessionmanager.h>

#define CompressSize 150

namespace osSOEProtocol
{
    class SOEClientSocket : public gsNetwork::ClientSocket
    {
    public:
		SOEClientSocket(gsServer::SessionManager* sessionManager, ISocketHandler &h);

    public:
        /**
		 * This virtual override queues attempts to queue messages 
		 * in the session associated with the senders address. These 
		 * messages are then processed during the main game loop.
		 */
        virtual bool handleRemoteIncoming(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address);

		void sendPacket(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address, bool encrypt, bool compress, bool crc);

    protected:

		gsServer::SessionManager* m_sessionManager;
    };
}

#endif // OPENSWG_SOEPROTOCOL_SOECLIENTSOCKET

