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

#include <osSOEProtocol/multimessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

MultiMessage::MultiMessage()
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(true);
}

MultiMessage::MultiMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

MultiMessage::~MultiMessage()
{}

std::shared_ptr<BinaryPacket> MultiMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

	return packet;
}

void MultiMessage::unserialize()
{
    for (uint32_t i = 2; i < (m_serializedData->getLength()-4); ++i)
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

        else if (size < 1)
            return;

		std::shared_ptr<BinaryPacket> segment(GS_NEW BinaryPacket);

		for (uint32_t j = 0; j < size; ++j)
			segment->append<char>(m_serializedData->read<char>());
		
		segment->setReadPosition(0);
		segments.push_back(segment);

        i += size;
	}
}

