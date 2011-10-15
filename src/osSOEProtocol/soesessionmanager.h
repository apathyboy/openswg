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

#ifndef OPENSWG_SOEPROTOCOL_SOESESSIONMANAGER
#define OPENSWG_SOEPROTOCOL_SOESESSIONMANAGER

#include <osSOEProtocol/soesession.h>
#include <gsServer/sessionmanager.h>

#include <boost/optional.hpp>
#include <memory>

#include <list>
#include <map>

namespace osSOEProtocol
{
	class SOESessionManager : public gsServer::SessionManager
    {        
    public:
        SOESessionManager();

    public: // gsCore::Process virtual overrides
		virtual void initialize();
        virtual void update(const uint64_t updateTimestamp);		
		virtual boost::optional<gsServer::SessionPtr> createSession(gsNetwork::NetworkMessagePtr message, std::shared_ptr<gsNetwork::NetworkAddress> address, gsNetwork::GameSocket* socket);

        inline uint32_t generateRandomCrcSeed() {
            uint32_t crcSeed;
            srand((unsigned int)time(0));
            uint16_t *test = GS_NEW uint16_t[2];
            uint16_t randomNum = rand()%65535;
            memcpy(&test[0], &randomNum, 2);
            randomNum = rand()%65535;
            memcpy(&test[1], &randomNum, 2);
            memcpy(&crcSeed, test, 4);
            delete [] test;
            return crcSeed;
        }
    };
}

#endif // OPENSWG_SOEPROTOCOL_SOESESSIONMANAGER

