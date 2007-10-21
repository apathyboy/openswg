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

#ifndef GALAXY_CORE_MACROS
#define GALAXY_CORE_MACROS

// macros.h: System-wide macro definitions. This is based off the 
// system-wide macros by the delta3d team.
//
//////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

// Override the debug new to assist in memory leak checks.
#ifdef _DEBUG
#   define GS_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#   define GS_NEW new
#endif

// Safe deletion of pointers and pointer arrays.
#define SAFE_DELETE(p) { if(p) { delete(p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);    (p)=NULL; } }

//
// The "is-a" macro.  Checks whether the first parameter (a pointer) is an
// instance of the second parameter (a class).
//
// Example usage:
//
//    Base* scene = new Scene();
//
//    if( IS_A(scene, Scene*) )
//    {
//       cout << "Yes, it is." << endl;
//    }
//
#ifdef IS_A
#undef IS_A
#endif
#define IS_A(P, T) (dynamic_cast<T>(P)!=NULL)

// Bit-packing helpers
#ifdef UNSIGNED_BIT
#undef UNSIGNED_BIT
#endif

// Apparently gcc doesn't like this without the cast...
#define UNSIGNED_BIT(a) ((unsigned long)(1L<<(unsigned long)(a)))

#ifdef BIT
#undef BIT
#endif
#define BIT(a) (long(1L<<long(a)))

#ifdef   UNSIGNED_INT_BIT
#undef   UNSIGNED_INT_BIT
#endif
#define  UNSIGNED_INT_BIT(a)   ((unsigned int)(1L<<(unsigned int)(a)))

#endif // GALAXY_CORE_MACROS

