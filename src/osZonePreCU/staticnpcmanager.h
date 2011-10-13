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

#ifndef OPENSWG_ZONEPRECU_STATICNPCMANAGER
#define OPENSWG_ZONEPRECU_STATICNPCMANAGER

#include <gsCore/process.h>
#include <gsCore/timing.h>
#include <gsNetwork/binarypacket.h>
#include <osSOEProtocol/objectgrid.h>
#include <osSOEProtocol/tangibleobjectproxy.h>
#include <osSOEProtocol/creatureobjectproxy.h>
#include <list>
namespace gsServer
{
	class OpcodeFactory;
	class Session;
}

namespace osZonePreCU
{
	class StaticNpcManager : public gsCore::Process //: public GameManager 
	// @NOTE: Extract common functionality to a GameManager base class.
	{
	public:
		StaticNpcManager(osSOEProtocol::ObjectGrid* objectGrid);

	protected:
		osSOEProtocol::ObjectGrid* m_objectGrid;

		void loadStaticNpcs();

		std::list<osSOEProtocol::ObjectProxyPtr> m_staticNpcs;
		
    public: // gsCore::Process virtual overrides
        virtual void update(const uint64_t updateTimestamp);
        virtual void initialize();

	public: // OPCODE HANDLING
		virtual void registerOpcodes(gsServer::OpcodeFactory* factory);
	
	};
}

#endif // OPENSWG_ZONEPRECU_STATICNPCMANAGER

