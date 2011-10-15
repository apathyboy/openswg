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

#include "gsNetwork/udp_event_socket.h"

#include "gsCore/eventmanager.h"
#include "gsNetwork/events.h"

using namespace gsCore;
using namespace gsNetwork;
using namespace std;

const string UdpEventSocket::TYPE_NAME = "game_socket";

UdpEventSocket::UdpEventSocket(boost::asio::io_service& io_service)
: socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 111))
{}

void UdpEventSocket::sendServerHeader(
    std::string server_name, 
    uint32_t server_id) 
{}

void UdpEventSocket::sendNewConnectionResponse(
    std::shared_ptr<BinaryPacket> packet, 
    std::shared_ptr<NetworkAddress2> address) 
{}

void UdpEventSocket::sendPacket(
    std::shared_ptr<BinaryPacket> packet, 
    std::shared_ptr<NetworkAddress2> address)
{}

void UdpEventSocket::sendPacket(
    std::shared_ptr<BinaryPacket> packet, 
    std::shared_ptr<NetworkAddress2> address, 
    bool encrypt, 
    bool compress, 
    bool crc) 
{}

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
bool UdpEventSocket::handleRemoteIncoming(
    std::shared_ptr<BinaryPacket> packet, 
    std::shared_ptr<NetworkAddress2> address)
{
    return false;
}

void UdpEventSocket::HandleReceive(
    const boost::system::error_code& error,
    size_t bytes_received)
{
    if (error && error != boost::asio::error::message_size) {
      return;
    }
        
    auto address = make_shared<boost::asio::ip::udp::endpoint>(remote_endpoint_);
    auto packet = make_shared<BinaryPacket>(&buffer_[0], bytes_received);
    
    // Only trigger a remote message if the socket hasn't already 
    // handled the message (i.e., it was a low level request such as
    // a session request or resend request, could be potential 
	// mischief as well).
    //if (! handleRemoteIncoming(packet, address))
    //{
    //    // Trigger a remote message event which will be read by
    //    // the simulation layer, which in turn will pass the message
    //    // along to the intended recipient.
    //    safeQueueEvent(EventPtr(GS_NEW Event_RemoteMessage(address, packet, this)));
    //}

    AsyncReceive();
}

void UdpEventSocket::AsyncReceive()
{}
