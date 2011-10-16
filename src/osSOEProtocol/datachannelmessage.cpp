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

DataChannelMessage::DataChannelMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

DataChannelMessage::~DataChannelMessage()
{}

std::shared_ptr<BinaryPacket> DataChannelMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

	return packet;
}

void DataChannelMessage::unserialize()
{
	clientSequence = m_serializedData->read<uint16_t>();
	delta = m_serializedData->read<uint16_t>();
		
    if (delta == SOE_MULTI_DATA_CHL)
    {
        for (uint32_t i = 4; i < (m_serializedData->getLength()); ++i)
        {
			uint8_t size = m_serializedData->read<uint8_t>();
			++i;

			if (size == 0xFF)
			{
				uint8_t counter = m_serializedData->read<uint8_t>();
				++i;

				m_serializedData->setReadPosition(m_serializedData->getReadPosition()+counter);
	
				size += m_serializedData->read<uint8_t>();
				++i;
			}

			else if (size < 6 ) // Minimum datachannel packet size
				return;

			std::shared_ptr<BinaryPacket> segment(new BinaryPacket);

			uint16_t group = m_serializedData->read<uint16_t>();
			for (uint32_t j = 0; j < (size-(uint32_t)2); ++j)
				segment->append<uint8_t>(m_serializedData->read<uint8_t>());

			segments.push_back(segment);

			i+=size;
		}
	}

	else
	{
		std::shared_ptr<BinaryPacket> segment(new BinaryPacket);

		for (uint32_t i = m_serializedData->getReadPosition(); i < m_serializedData->getLength(); ++i)
			segment->append<char>(m_serializedData->read<char>());
		
		segments.push_back(segment);
	}
}

