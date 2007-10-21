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

#include <gsCore/types.h>
#include <gsNetwork/binarypacket.h>
#include <gsNetwork/export.h>

namespace gsNetwork
{
	class GS_NETWORK_EXPORT NetworkMessage
	{
	public:
		uint64 recipientId;

		virtual boost::shared_ptr<NetworkMessage> clone() 
		{
			boost::shared_ptr<NetworkMessage> clone;
			return clone;
		}

		NetworkMessage();
		virtual ~NetworkMessage();
	
		uint16 getSequence() { return m_sequence; }
		void setSequence(uint16 sequence) { m_sequence = sequence; }

		uint getPriority() { return m_priority; }
		void setPriority(uint priority) { m_priority = priority; }

		void setResend(bool resend) { m_resend = resend; }
		bool resend() { return m_resend; }

		void setReschedule(bool reschedule) { m_reschedule = reschedule; }
		bool reschedule() { return m_reschedule; }
		virtual bool canSendScheduled() { return false; }

		uint16 sendCount;

		virtual BinaryPacketPtr serialize() = 0;
		virtual void unserialize() = 0;

		bool crc() {return m_crc;}
		void setCrc(bool crc) { m_crc = crc; }
		bool compress() { return m_compress; }
		void setCompress(bool compress) {m_compress = compress; }
		bool encrypt() {return m_encrypt;}
		void setEncrypt(bool encrypt) { m_encrypt = encrypt; }

	protected:
		uint16 m_sequence;
		uint m_priority;
		uint m_sendCount;
		bool m_resend;
		bool m_compress;
		bool m_crc;
		bool m_reschedule;
		bool m_encrypt;
		BinaryPacketPtr m_serializedData;
	};

	typedef boost::shared_ptr<NetworkMessage> NetworkMessagePtr;
}

#endif // GALAXY_NETWORK_NETWORKMESSAGE