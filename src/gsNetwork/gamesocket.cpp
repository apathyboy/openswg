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

#include <gsCore/eventmanager.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/networkaddress.h>
#include <gsNetwork/events.h>

#include <stdio.h>

#include <Sockets/Utility.h>

using namespace gsCore;
using namespace gsNetwork;

char const * const GameSocket::gkName = "game_socket";

GameSocket::GameSocket(ISocketHandler &h)
: UdpSocket(h)
{}


void GameSocket::sendPacket(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address)
{
	SendToBuf(*(address->getRawAddress()), packet->getData(), packet->getLength());
}


bool GameSocket::handleRemoteIncoming(BinaryPacketPtr packet, NetworkAddressPtr address)
{
	// Any processing should be done by concrete game socket implementations.
	return false;
}

void GameSocket::OnRawData(const char *data, size_t length, sockaddr *sa_from, socklen_t sa_length)
{
	// Wrap the raw network data in GSF data structures.
    NetworkAddressPtr address(GS_NEW NetworkAddress(sa_from, sa_length));    
    BinaryPacketPtr   packet(GS_NEW BinaryPacket(data, length));    

    // Only trigger a remote message if the socket hasn't already 
    // handled the message (i.e., it was a low level request such as
    // a session request or resend request, could be potential 
	// mischief as well).
    if (! handleRemoteIncoming(packet, address))
    {
        // Trigger a remote message event which will be read by
        // the simulation layer, which in turn will pass the message
        // along to the intended recipient.
        safeQueueEvent(EventPtr(GS_NEW Event_RemoteMessage(address, packet, this)));
    }
}

