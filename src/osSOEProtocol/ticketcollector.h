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

#ifndef OPENSWG_SOEPROTOCOL_TICKETCOLLECTOR
#define OPENSWG_SOEPROTOCOL_TICKETCOLLECTOR

#include <osSOEProtocol/export.h>
#include <boost/shared_ptr.hpp>
#include <osSOEProtocol/tangibleobject.h>

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT TicketCollector : public TangibleObject
	{
	public:
		TicketCollector() {}
		virtual ~TicketCollector(){}

	private:
	};

	typedef OS_SOEPROTOCOL_EXPORT std::shared_ptr<TicketCollector> TicketCollectorPtr;
}

#endif // OPENSWG_SOEPROTOCOL_TICKETCOLLECTOR