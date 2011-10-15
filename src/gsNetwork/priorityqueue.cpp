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

#include <gsNetwork/priorityqueue.h>

using namespace gsNetwork;

PriorityQueue::PriorityQueue(uint32_t slots)
: m_slots(slots)
, m_sequence(0)
{}

PriorityQueue::~PriorityQueue()
{}

uint16_t PriorityQueue::getNextSequence()
{
	return m_sequence++;
}

void PriorityQueue::queue(NetworkMessagePtr message)
{
	m_messages.push_back(message);
}

void PriorityQueue::resend(uint16_t sequence, GameSocket* socket, std::shared_ptr<NetworkAddress> address)
{
	SentQueue::iterator i = m_sentMessages.find(sequence);

	if (i != m_sentMessages.end())
	{
		NetworkMessagePtr message = (*i).second;

		message->sendCount++;
		socket->sendPacket(message->serialize(), address);
	}
}

void PriorityQueue::sendQueue(GameSocket* socket, std::shared_ptr<NetworkAddress> address)
{
	if (m_messages.size() < 1) return;

	std::list<NetworkMessagePtr>::iterator i = m_messages.begin();
	for(;i != m_messages.end();)
	{
		NetworkMessagePtr message = *i;

		if (message->reschedule() && (! message->canSendScheduled()))
		{
			++i;
			continue;
		}

		if (message->resend()) //&& (message->sendCount == 0))
		{
			// Get next sequence number.
			uint16_t sequence = getNextSequence();
			message->setSequence(sequence);

			// Insert message into the sent queue here.
			m_sentMessages[sequence] = message;
		}

		message->sendCount++;
		socket->sendPacket(message->serialize(), address, message->encrypt(), message->compress(), message->crc());

		if (! message->reschedule() || message->sendCount > 4)
			i = m_messages.erase(i);
		else
			++i;
	}
}

