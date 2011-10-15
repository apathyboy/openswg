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

#include <gsCore/timing.h>
#include <gsServer/session.h>
using namespace gsNetwork;
using namespace gsServer;

Session::Session(std::shared_ptr<NetworkAddress> address, GameSocket* socket)
: m_remoteAddress(address)
, m_remoteSocket(socket)
, m_clientSequence(0)
{
	m_isLoggedIn = false;
	m_isValid = false;
	m_remoteMessageQueue = GS_NEW PriorityQueue();
}

bool Session::isValid()
{
	return m_isValid;
}

void Session::setValid(bool valid)
{
	m_isValid = valid;
}

void Session::update()
{
	m_remoteMessageQueue->sendQueue(m_remoteSocket, m_remoteAddress);
	processIncomingQueue();
}

void Session::sendToRemote(NetworkMessagePtr message)
{
	m_remoteMessageQueue->queue(message);
}

void Session::handleIncoming(std::shared_ptr<BinaryPacket> packet)
{
	m_incomingQueue.push_back(packet);
	setLastUpdateTime(gsCore::getTimeInMs());
}

uint64_t Session::getLastUpdateTime()
{
    return m_lastUpdateTime;
}
      
void Session::setLastUpdateTime(uint64_t lastUpdateTime)
{
    m_lastUpdateTime = lastUpdateTime;
}

void Session::setRemoteAddress(std::shared_ptr<NetworkAddress> address)
{
    m_remoteAddress = address;
}

std::shared_ptr<NetworkAddress> Session::getRemoteAddress()
{
    return m_remoteAddress;
}