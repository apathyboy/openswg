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

#include <gsCore/log.h>
#include <gsNetwork/events.h>

#include <Sockets/Utility.h>

using namespace gsCore;
using namespace gsNetwork;

char const * const Event_RemoteConnectionEstablished::gkName = "remote_connection_established";
char const * const Event_RemoteConnectionRequest::gkName     = "remote_connection_request";
char const * const Event_RemoteMessage::gkName               = "remote_message";

PacketLogListener::PacketLogListener()
{
}

PacketLogListener::~PacketLogListener()
{
}

void PacketLogListener::registerEvents(EventListenerPtr listener)
{
    safeAddListener(listener, EventType(gsNetwork::Event_RemoteMessage::gkName));
}

bool PacketLogListener::handleEvent( Event const & event )
{
    if (_stricmp(event.getType().getStr(), Event_RemoteMessage::gkName) == 0)
    {
        EventData_RemoteMessage * eventData = event.getDataPtr<EventData_RemoteMessage>();

        Log::getPacketLog().info("Received Packet\n%s -> %s:%d\n%s\n", 
            eventData->address->getAddressString().c_str(), // From address:port
            Utility::GetLocalAddress().c_str(),         // To address
            eventData->socket->GetPort(),              // To port
            eventData->packet->getLogString().c_str()); 
    }

    return false;
}
