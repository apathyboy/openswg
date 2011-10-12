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

#ifndef GALAXY_SERVER_SESSIONMANAGER
#define GALAXY_SERVER_SESSIONMANAGER

#include <cstdint>
#include <list>
#include <map>

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

#include <gsCore/process.h>
#include <gsNetwork/binarypacket.h>
#include <gsNetwork/networkaddress.h>
#include <gsServer/session.h>
#include <gsServer/opcodehandler.h>

namespace gsServer
{
    class SessionManager : public gsCore::Process
    {        

    protected:
        // Map of sessions to their remote addresses (IP + PORT). Only 
        // one remote address can ever exist for a single session, so 
        // this is the best data to use for identifying them.
        typedef std::map<std::string, SessionPtr> SessionMap;

        // A single entry in the session map.
        typedef std::pair<std::string, SessionPtr> SessionMapEnt;

        // Container for the result of an insert into the session map.
        typedef std::pair<SessionMap::iterator, bool> SessionMapIRes;

    public:
        SessionManager();

    public: // gsCore::Process virtual overrides
        virtual void update(const uint64_t updateTimestamp);
        virtual void removeDeadSessions(const uint64_t updateTimestamp);
        virtual void initialize();
		virtual void queueRemoteMessage(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address);

    public:
		virtual uint32_t countSessions() { return m_sessions.size(); }
        void addSession(SessionPtr session);
		virtual void removeSession(SessionMap::iterator i);
        virtual void removeSession(SessionPtr session);
		virtual boost::optional<SessionPtr> createSession(gsNetwork::NetworkMessagePtr message, gsNetwork::NetworkAddressPtr address, gsNetwork::GameSocket* socket);

        boost::optional<SessionPtr> findSession(std::string address);

		void setOpcodeFactory(OpcodeFactory* opcodeFactory) { m_opcodeFactory = opcodeFactory; }
		OpcodeFactory* getOpcodeFactory() { return m_opcodeFactory; }

	protected:

		OpcodeFactory* m_opcodeFactory;
		uint64_t m_lastCleanupTime;
		SessionMap m_sessions;
    };
}

#endif // GALAXY_SERVER_SESSIONMANAGER

