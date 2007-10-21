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

#ifndef GALAXY_NETWORK_PRIORITYQUEUE
#define GALAXY_NETWORK_PRIORITYQUEUE

#include <gsNetwork/export.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/networkaddress.h>
#include <gsNetwork/networkmessage.h>

#include <list>

namespace gsNetwork
{
	class GS_NETWORK_EXPORT PriorityQueue
	{
	public:
		PriorityQueue(uint slots = 1);
		virtual ~PriorityQueue();
	
		virtual void queue(NetworkMessagePtr message);
		virtual void resend(uint16 sequence, GameSocket* socket, NetworkAddressPtr address);
		virtual void sendQueue(GameSocket* socket, NetworkAddressPtr address);

	protected:
		virtual uint16 getNextSequence();
		std::list<NetworkMessagePtr> m_messages;
		
		typedef std::map<uint16, NetworkMessagePtr> SentQueue;
		SentQueue m_sentMessages;

		uint16 m_sequence;

		uint m_slots;
	};
}

#endif // GALAXY_NETWORK_PRIORITYQUEUE

