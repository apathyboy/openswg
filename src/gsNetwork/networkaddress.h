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

#ifndef GALAXY_NETWORK_NETWORKADDRESS
#define GALAXY_NETWORK_NETWORKADDRESS

#include <gsCore/globals.h>
#include <gsCore/macros.h>

#include <Sockets/Ipv4Address.h>
#include <boost/shared_ptr.hpp>

namespace gsNetwork
{
    class NetworkAddress;
    typedef boost::shared_ptr<NetworkAddress> NetworkAddressPtr;

    class NetworkAddress
    {
    public:
        NetworkAddress(sockaddr *sa_from, socklen_t sa_length);

        std::string getAddressString();

		Ipv4Address* getRawAddress() { return m_ipv4Address; }

    private:
        Ipv4Address* m_ipv4Address;
    };
}

#endif // GALAXY_NETWORK_NETWORKADDRESS

