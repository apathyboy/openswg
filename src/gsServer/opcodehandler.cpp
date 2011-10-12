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

using namespace gsNetwork;
using namespace gsServer;

boost::optional<OpcodeHandlerPtr> OpcodeFactory::addOpcodeHandler(uint32_t opcode, OpcodeHandlerPtr opcodeHandler)
{
	boost::optional<OpcodeHandlerPtr> oldHandler = findOpcodeHandler(opcode);

	m_opcodeMap[opcode] = opcodeHandler;

	return oldHandler;
}
		
boost::optional<OpcodeHandlerPtr> OpcodeFactory::findOpcodeHandler(uint32_t opcode)
{
	OpcodeHandlerMap::iterator i = m_opcodeMap.find(opcode);

	if (i != m_opcodeMap.end())
	{
		return (*i).second;
	}

	return NULL;
}

