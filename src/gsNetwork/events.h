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

#ifndef GALAXY_NETWORK_EVENTS
#define GALAXY_NETWORK_EVENTS

#include <cstdint>

#include <gsCore/eventmanager.h>
#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsNetwork/binarypacket.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/networkaddress.h>

namespace gsNetwork
{
    /**
     * 
     */
    struct EventData_RemoteConnectionRequest : public gsCore::IEventData
    {
        explicit EventData_RemoteConnectionRequest(std::shared_ptr<NetworkAddress> inAddress, 
                                                   GameSocket* inSocket,
                                                   uint32_t inConnectionId)
            : address(inAddress)
            , socket(inSocket)
            , connectionId(inConnectionId)
        {}

        std::shared_ptr<NetworkAddress> address;
        GameSocket* socket;
        uint32_t connectionId; 
    };

    class Event_RemoteConnectionRequest : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_RemoteConnectionRequest(std::shared_ptr<NetworkAddress> address, GameSocket* socket, uint32_t connectionId)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_RemoteConnectionRequest(address, socket, connectionId)))
        {}        
    };

    /**
     * 
     */
    struct EventData_RemoteConnectionEstablished : public gsCore::IEventData
    {
        explicit EventData_RemoteConnectionEstablished(std::string inAddress, 
                                                       GameSocket* inSocket)
            : address(inAddress)
            , socket(inSocket)
        {}

        std::string address;
        GameSocket* socket;
    };

    class Event_RemoteConnectionEstablished : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_RemoteConnectionEstablished(std::string address, GameSocket* socket)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_RemoteConnectionEstablished(address, socket)))
        {}        
    };

    /**
     * Every network message has an incoming address, packet data and a 
     * specific socket that data came in on.
     */
    struct EventData_RemoteMessage : public gsCore::IEventData
    {
        explicit EventData_RemoteMessage(std::shared_ptr<NetworkAddress> inAddress, 
                                         std::shared_ptr<BinaryPacket> inPacket, 
                                         GameSocket* inSocket)
            : address(inAddress)
            , packet(inPacket)
            , socket(inSocket)
        {}

        std::shared_ptr<NetworkAddress> address;
        std::shared_ptr<BinaryPacket> packet;
        GameSocket* socket;
    };

    class Event_RemoteMessage : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_RemoteMessage(std::shared_ptr<NetworkAddress> address, 
                                     std::shared_ptr<BinaryPacket> packet, 
                                     GameSocket* socket)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_RemoteMessage(address, packet, socket)))
        {}        
    };

    
    class PacketLogListener : public gsCore::IEventListener
    {
    public:
        PacketLogListener();
        virtual ~PacketLogListener();
        char const * getName(void) { return "PacketLogListener"; }
        bool handleEvent(gsCore::Event const & event);

		static void registerEvents(gsCore::EventListenerPtr listener);
    };
}

#endif // GALAXY_NETWORK_EVENTS

