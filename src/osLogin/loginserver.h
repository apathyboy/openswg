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

#ifndef OPENSWG_LOGIN_LOGINSERVER
#define OPENSWG_LOGIN_LOGINSERVER

#include <cstdint>
#include <string>

#include "gsServer/server_application.h"

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsNetwork/binarypacket.h>
#include <osLogin/authmanager.h>


	class LoginServer : public gsServer::ServerApplication
	{
    public:
        LoginServer(std::string serverType, uint32_t serverId);
        virtual ~LoginServer();

        virtual void initialize(const std::string& configFilename);
		//virtual void shutdown();
        //virtual void startNetwork();
		//virtual void run();

	protected:
		osLogin::AuthManager* m_authManager;
	};


#endif // OPENSWG_LOGIN_LOGINSERVER

