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

#include <gsCore/callback.h>
#include <gsNetwork/binarypacket.h>
#include <gsServer/export.h>

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

#include <map>

namespace gsServer
{
	class Session;
	typedef GS_SERVER_EXPORT CBFunctor2<Session*, gsNetwork::BinaryPacketPtr> *HandlerFunctor;

	/** Define our handler function type.
	 */
	class GS_SERVER_EXPORT OpcodeHandler
	{
	public:
		OpcodeHandler(const CBFunctor2<Session*, gsNetwork::BinaryPacketPtr> &inHandler)
			: m_handler(inHandler)
		{}

		void handle(Session* session, gsNetwork::BinaryPacketPtr packet)
		{
			m_handler(session, packet);
		}
		
	protected:
		CBFunctor2<Session*, gsNetwork::BinaryPacketPtr> m_handler;
	};

	typedef GS_SERVER_EXPORT boost::shared_ptr<OpcodeHandler> OpcodeHandlerPtr;
	class GS_SERVER_EXPORT OpcodeFactory
	{
	public:
		boost::optional< OpcodeHandlerPtr > addOpcodeHandler(uint32 opcode, OpcodeHandlerPtr opcodeHandler);
		boost::optional< OpcodeHandlerPtr > findOpcodeHandler(uint32 opcode);

	protected:
		typedef std::map<uint32, OpcodeHandlerPtr > OpcodeHandlerMap;
		OpcodeHandlerMap m_opcodeMap;
	};
}

#endif // GALAXY_SERVER_OPCODEHANDLER

