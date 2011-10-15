/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2011 OpenSWG Team <http://openswg.org>
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

#ifndef GALAXY_NETWORK_NETWORK_ADDRESS_H_
#define GALAXY_NETWORK_NETWORK_ADDRESS_H_

#include <memory>
#include <boost/asio/ip/udp.hpp>

namespace gsNetwork
{
    typedef boost::asio::ip::udp::endpoint NetworkAddress2;
}

#endif  // GALAXY_NETWORK_NETWORK_ADDRESS_H_
