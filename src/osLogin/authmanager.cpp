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

#include "osLogin/authmanager.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/sha1.h>
#include <gsCore/md5.h>

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsServer/serverevents.h>

#include <gsCore/datastore.h>

#include <osSOEProtocol/accountversionmessage.h>
#include <osSOEProtocol/stationidentifiermessage.h>
#include <osSOEProtocol/soelayermessages.h>

#include <osSOEProtocol/opcodes.h>

#define AUTH_MD5

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osLogin;

AuthManager::AuthManager()
{}

void AuthManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
	CBFunctor2<Session*, BinaryPacketPtr> handler = makeFunctor((HandlerFunctor)0, *this, &AuthManager::handleAuthRequest);	
	factory->addOpcodeHandler(CMSG_ACCT_VERSION, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
}

void AuthManager::handleAuthRequest(gsServer::Session* session, gsNetwork::BinaryPacketPtr message) const
{
	boost::shared_ptr<AccountVersionMessage> authData(GS_NEW AccountVersionMessage(message));
	authData->unserialize();

    if (authData->version.compare(std::string("20051010-17:00")) == 0)
        session->setClientVersion(SWG_CU);
    else if (authData->version.compare(std::string("20041215-19:26")) == 0)
        session->setClientVersion(SWG_PRECU);

	if (! authenticate(session, authData->username, authData->password))
	{
		// Handle invalid password.
		return;
	}

	session->setAuthenticated(true);
	session->setUsername(std::string("apathy"));

	boost::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);

	boost::shared_ptr<StationIdentifierMessage> identifier(GS_NEW StationIdentifierMessage);
	identifier->session = session;

	session->sendToRemote(identifier);

	safeTriggerEvent(Event_AccountAuthenticated(session));
}

bool AuthManager::authenticate(gsServer::Session* session, std::string username, std::string password) const
{
    try
    {
        mysqlpp::Query q = Datastore::getStationDB().query();

        q << "SELECT * FROM accounts WHERE username = "
          << mysqlpp::quote << username;
		  
        mysqlpp::StoreQueryResult result = q.store();

        if (result)
        {
			std::string dbPassword = (std::string)result[0]["password"];
			std::string salt = (std::string)result[0]["salt"];
			
			md5wrapper wrapper;
			std::string md5 = wrapper.getHashFromString(password);
			std::string md5WithSalt = wrapper.getHashFromString(md5+salt);

			if (dbPassword.compare(md5WithSalt) == 0)
			{
	            session->setAccountId((uint32_t)result[0]["id"]);
            
		        // Set account information in the session ptr here.
			    // return true;
			    session->setUsername(username);

				return true;
			}
        }
    }
    catch (const mysqlpp::Exception& er)
    {
		LOG(ERROR) << "ERROR: " << er.what();
    }
			
    LOG(ERROR) << "Unable to authenticate user: " << username;
    return false;
}

