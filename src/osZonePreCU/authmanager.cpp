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

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>

#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soelayermessages.h>

#include <osZonePreCU/authmanager.h>

using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;

AuthManager::AuthManager()
{}

void AuthManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
	factory->addOpcodeHandler(CMSG_DATA_SES_VER, OpcodeHandlerPtr(GS_NEW OpcodeHandler(
        bind(&AuthManager::handleAuthRequest, this, std::placeholders::_1, std::placeholders::_2))));
}

void AuthManager::handleAuthRequest(gsServer::Session* session, std::shared_ptr<gsNetwork::BinaryPacket> message) const
{
    message->read<uint32_t>();
    uint32_t length = message->read<uint32_t>();

    for (uint32_t i = 0; i < (length-4); ++i)
        message->read<char>();

    session->setAccountId(message->read<uint32_t>());
}

