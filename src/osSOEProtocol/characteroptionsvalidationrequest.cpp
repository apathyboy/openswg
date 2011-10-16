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

#include <osSOEProtocol/characteroptionsvalidationrequest.h>
#include <osSOEProtocol/opcodes.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

CharacterOptionsValidationRequest::CharacterOptionsValidationRequest()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

CharacterOptionsValidationRequest::CharacterOptionsValidationRequest(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

CharacterOptionsValidationRequest::~CharacterOptionsValidationRequest()
{}

std::shared_ptr<BinaryPacket> CharacterOptionsValidationRequest::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

	return packet;
}

void CharacterOptionsValidationRequest::unserialize()
{
}

