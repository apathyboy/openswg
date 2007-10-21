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

#include <osSOEProtocol/datachannelmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

DataChannelMessage::DataChannelMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

DataChannelMessage::DataChannelMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

DataChannelMessage::~DataChannelMessage()
{}

BinaryPacketPtr DataChannelMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

	return packet;
}

void DataChannelMessage::unserialize()
{
	clientSequence = m_serializedData->read<uint16>();
	delta = m_serializedData->read<uint16>();
		
    if (delta == SOE_MULTI_DATA_CHL)
    {
        for (uint i = 4; i < (m_serializedData->getLength()); ++i)
        {
			uint8 size = m_serializedData->read<uint8>();
			++i;

			if (size == 0xFF)
			{
				uint8 counter = m_serializedData->read<uint8>();
				++i;

				m_serializedData->setReadPosition(m_serializedData->getReadPosition()+counter);
	
				size += m_serializedData->read<uint8>();
				++i;
			}

			else if (size < 6 ) // Minimum datachannel packet size
				return;

			BinaryPacketPtr segment(GS_NEW BinaryPacket);

			uint16 group = m_serializedData->read<uint16>();
			for (uint j = 0; j < (size-(uint)2); ++j)
				segment->append<uint8>(m_serializedData->read<uint8>());

			segments.push_back(segment);

			i+=size;
		}
	}

	else
	{
		BinaryPacketPtr segment(GS_NEW BinaryPacket);

		for (uint i = m_serializedData->getReadPosition(); i < m_serializedData->getLength(); ++i)
			segment->append<char>(m_serializedData->read<char>());
		
		segments.push_back(segment);
	}
}

