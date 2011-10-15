/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2011 OpenSWG Team <http://openswg.org>
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

#ifndef GALAXY_NETWORK_UDP_EVENT_SOCKET_H_
#define GALAXY_NETWORK_UDP_EVENT_SOCKET_H_

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

#include "gsNetwork/binarypacket.h"
#include "gsNetwork/network_address.h"

namespace gsNetwork
{
    class UdpEventSocket
    {
    public:
        static const std::string TYPE_NAME;

        UdpEventSocket(boost::asio::io_service& io_service);

        virtual void sendServerHeader(
            std::string server_name, 
            uint32_t server_id);
        
		virtual void sendNewConnectionResponse(
            std::shared_ptr<BinaryPacket> packet, 
            std::shared_ptr<NetworkAddress2> address);

		virtual void sendPacket(
            std::shared_ptr<BinaryPacket> packet, 
            std::shared_ptr<NetworkAddress2> address);

		virtual void sendPacket(
            std::shared_ptr<BinaryPacket> packet, 
            std::shared_ptr<NetworkAddress2> address, 
            bool encrypt, 
            bool compress, 
            bool crc);

        /**
		 * This virtual override allows GameSocket implementations a chance to 
         * handle remote incoming messages before the default RemoteMessage 
         * event is triggered.
		 *
		 * Generally the implementation of this method should be lightweight in
         * order to prevent delays in receiving other remote messages. Ideally
         * the implementation method will queue the message in an appropriate 
         * location to be handled by the main server thread.
		 */
        virtual bool handleRemoteIncoming(
            std::shared_ptr<BinaryPacket> packet, 
            std::shared_ptr<NetworkAddress2> address);

    private:
        void HandleReceive(
            const boost::system::error_code& error,
            size_t bytes_received);

        void AsyncReceive();
        
        std::vector<uint8_t> buffer_;

        boost::asio::ip::udp::socket socket_;  
        boost::asio::ip::udp::endpoint remote_endpoint_;
        
        uint16_t port_;
    };
}

#endif  // GALAXY_NETWORK_UDP_EVENT_SOCKET_H_
