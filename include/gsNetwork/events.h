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

#include <gsCore/eventmanager.h>
#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsNetwork/binarypacket.h>
#include <gsNetwork/export.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/networkaddress.h>

namespace gsNetwork
{
    /**
     * 
     */
    struct GS_NETWORK_EXPORT EventData_RemoteConnectionRequest : public gsCore::IEventData
    {
        explicit EventData_RemoteConnectionRequest(NetworkAddressPtr inAddress, 
                                                   GameSocket* inSocket,
                                                   uint32 inConnectionId)
            : address(inAddress)
            , socket(inSocket)
            , connectionId(inConnectionId)
        {}

        NetworkAddressPtr address;
        GameSocket* socket;
        uint32 connectionId; 
    };

    class GS_NETWORK_EXPORT Event_RemoteConnectionRequest : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_RemoteConnectionRequest(NetworkAddressPtr address, GameSocket* socket, uint32 connectionId)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_RemoteConnectionRequest(address, socket, connectionId)))
        {}        
    };

    /**
     * 
     */
    struct GS_NETWORK_EXPORT EventData_RemoteConnectionEstablished : public gsCore::IEventData
    {
        explicit EventData_RemoteConnectionEstablished(std::string inAddress, 
                                                       GameSocket* inSocket)
            : address(inAddress)
            , socket(inSocket)
        {}

        std::string address;
        GameSocket* socket;
    };

    class GS_NETWORK_EXPORT Event_RemoteConnectionEstablished : public gsCore::Event
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
    struct GS_NETWORK_EXPORT EventData_RemoteMessage : public gsCore::IEventData
    {
        explicit EventData_RemoteMessage(NetworkAddressPtr inAddress, 
                                         BinaryPacketPtr inPacket, 
                                         GameSocket* inSocket)
            : address(inAddress)
            , packet(inPacket)
            , socket(inSocket)
        {}

        NetworkAddressPtr address;
        BinaryPacketPtr packet;
        GameSocket* socket;
    };

    class GS_NETWORK_EXPORT Event_RemoteMessage : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_RemoteMessage(NetworkAddressPtr address, 
                                     BinaryPacketPtr packet, 
                                     GameSocket* socket)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_RemoteMessage(address, packet, socket)))
        {}        
    };

    
    class GS_NETWORK_EXPORT PacketLogListener : public gsCore::IEventListener
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

