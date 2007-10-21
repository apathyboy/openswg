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

#ifndef GALAXY_NETWORK_GAMESOCKET
#define GALAXY_NETWORK_GAMESOCKET

#include <gsCore/globals.h>
#include <gsCore/macros.h>

#include <Sockets/SocketHandler.h>
#include <Sockets/UdpSocket.h>

#include <gsNetwork/binarypacket.h>
#include <gsNetwork/export.h>
#include <gsNetwork/networkaddress.h>

#include <boost/optional.hpp>

namespace gsNetwork
{
    enum SocketStates
    {
        SOCKET_DISABLED,
        SOCKET_ACTIVE
    };

    class GS_NETWORK_EXPORT GameSocket : public UdpSocket
    {
    public:
        GameSocket(ISocketHandler&);

        static char const * const gkName;

    public:
		virtual void sendServerHeader(std::string serverName, uint32 serverId) {}
		virtual void sendNewConnectionResponse(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address) {}
		virtual void sendPacket(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address);
		virtual void sendPacket(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address, bool encrypt, bool compress, bool crc) {}

        /**
		 * This virtual override allows GameSocket implementations a chance to handle
		 * remote incoming messages before the default RemoteMessage event is triggered.
		 *
		 * Generally the implementation of this method should be lightweight in order
		 * to prevent delays in receiving other remote messages. Ideally the implementation
		 * method will queue the message in an appropriate location to be handled by
		 * the main server thread.
		 */
        virtual bool handleRemoteIncoming(BinaryPacketPtr packet, NetworkAddressPtr address);

	public: // UdpSocket Overrides 
		// @NOTE If the underlying socket library is ever changed this section needs
		// to be replaced with the new libraries equivalent.

        /** This is called whenever an incoming message is received. The
         *  job of this function is to create and trigger a remote_message
         *  event.
         */
        virtual void OnRawData(const char *data, size_t length, sockaddr *sa_from, socklen_t sa_length);
    };
}

#endif // GALAXY_NETWORK_GAMESOCKET

