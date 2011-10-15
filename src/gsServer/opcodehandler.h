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

#ifndef GALAXY_SERVER_OPCODEHANDLER
#define GALAXY_SERVER_OPCODEHANDLER

#include <cstdint>

#include <functional>

#include <gsNetwork/binarypacket.h>

#include <memory>
#include <boost/optional.hpp>

#include <map>

namespace gsServer
{
	class Session;
	typedef std::function<void (Session*, std::shared_ptr<gsNetwork::BinaryPacket>)> HandlerFunctor;

	/** Define our handler function type.
	 */
	class OpcodeHandler
	{
	public:
		OpcodeHandler(const HandlerFunctor &inHandler)
			: m_handler(inHandler)
		{}

		void handle(Session* session, std::shared_ptr<gsNetwork::BinaryPacket> packet)
		{
			m_handler(session, packet);
		}
		
	protected:
		HandlerFunctor m_handler;
	};

	typedef std::shared_ptr<OpcodeHandler> OpcodeHandlerPtr;
	class OpcodeFactory
	{
	public:
		boost::optional< OpcodeHandlerPtr > addOpcodeHandler(uint32_t opcode, OpcodeHandlerPtr opcodeHandler);
		boost::optional< OpcodeHandlerPtr > findOpcodeHandler(uint32_t opcode);

	protected:
		typedef std::map<uint32_t, OpcodeHandlerPtr > OpcodeHandlerMap;
		OpcodeHandlerMap m_opcodeMap;
	};
}

#endif // GALAXY_SERVER_OPCODEHANDLER

