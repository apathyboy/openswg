/**
 * log.cpp: A collection of custom logging classes for use with log4cpp.
 *
 * Copyright (C) 2006, 2007 OpenSWG Team <http://www.openswg.com>
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

#include <gsCore/logevents.h>
#include <gsNetwork/events.h>
#include <gsCore/log.h>

#include <Sockets/Utility.h>

using namespace gsCore;
using namespace gsNetwork;

PacketLogListener::PacketLogListener()
{
}

PacketLogListener::~PacketLogListener()
{
}

bool PacketLogListener::handleEvent( Event const & event )
{
    if (!_stricmp(event.getType().getStr(), Event_RemoteMessage::gkName))
    {
        EventData_RemoteMessage * eventData = event.getDataPtr<EventData_RemoteMessage>();

        sPacketLog.info("Received Packet\n%s -> %s:%d\n%s\n", 
            eventData->_address->getAddressString().c_str(), // From address:port
            Utility::GetLocalAddress().c_str(),         // To address
            eventData->_socket->GetPort(),              // To port
            eventData->_packet->getLogString().c_str()); 
    }

    return false;
}