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

#include <gsNetwork/networkaddress.h>

using namespace gsNetwork;

NetworkAddress::NetworkAddress(sockaddr *sa_from, socklen_t sa_length)
{
    // Package message and address then trigger a network message event.
    struct sockaddr_in sa;
    memcpy(&sa, sa_from, sa_length);

    ipaddr_t a;
    memcpy(&a,&sa.sin_addr,4);
    
    m_ipv4Address = GS_NEW Ipv4Address(a, ntohs(sa.sin_port));
}

std::string NetworkAddress::getAddressString()
{
    return m_ipv4Address->Convert(true);
}

