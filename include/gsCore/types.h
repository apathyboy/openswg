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

#ifndef GALAXY_CORE_TYPES
#define GALAXY_CORE_TYPES

#ifdef __GNUG__
__extension__
typedef long long   int64;
#else
typedef long long   int64;
#endif
typedef long        int32;
typedef short       int16;
typedef char        int8;

#ifdef __GNUG__
__extension__
typedef unsigned long long  uint64;
#else
typedef unsigned long long  uint64;
#endif
typedef unsigned short      port_t;
typedef unsigned long       uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;
typedef unsigned int        uint;
typedef unsigned short      unicode;

#endif // GALAXY_CORE_TYPES