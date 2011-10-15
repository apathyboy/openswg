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

#ifndef GALAXY_NETWORK_NETWORKMESSAGE
#define GALAXY_NETWORK_NETWORKMESSAGE

#include <cstdint>
#include <memory>
#include <gsNetwork/binarypacket.h>

namespace gsNetwork
{
	class NetworkMessage
	{
	public:
		uint64_t recipientId;

		virtual std::shared_ptr<NetworkMessage> clone() 
		{
			std::shared_ptr<NetworkMessage> clone;
			return clone;
		}

		NetworkMessage();
		virtual ~NetworkMessage();
	
		uint16_t getSequence() { return m_sequence; }
		void setSequence(uint16_t sequence) { m_sequence = sequence; }

		uint8_t getPriority() { return m_priority; }
		void setPriority(uint8_t priority) { m_priority = priority; }

		void setResend(bool resend) { m_resend = resend; }
		bool resend() { return m_resend; }

		void setReschedule(bool reschedule) { m_reschedule = reschedule; }
		bool reschedule() { return m_reschedule; }
		virtual bool canSendScheduled() { return false; }

		uint16_t sendCount;

		virtual std::shared_ptr<BinaryPacket> serialize() = 0;
		virtual void unserialize() = 0;

		bool crc() {return m_crc;}
		void setCrc(bool crc) { m_crc = crc; }
		bool compress() { return m_compress; }
		void setCompress(bool compress) {m_compress = compress; }
		bool encrypt() {return m_encrypt;}
		void setEncrypt(bool encrypt) { m_encrypt = encrypt; }

	protected:
		uint16_t m_sequence;
		uint8_t m_priority;
		uint8_t m_sendCount;
		bool m_resend;
		bool m_compress;
		bool m_crc;
		bool m_reschedule;
		bool m_encrypt;
		std::shared_ptr<BinaryPacket> m_serializedData;
	};

	typedef std::shared_ptr<NetworkMessage> NetworkMessagePtr;
}

#endif // GALAXY_NETWORK_NETWORKMESSAGE