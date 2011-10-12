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

#ifndef GALAXY_CORE_GLOBALS
#define GALAXY_CORE_GLOBALS

#include <string>

namespace gsCore 
{
    ///Get the root path to Galaxy (equivalent to the GALAXY_ROOT environment)
    std::string GetGalaxyRootPath();

    ///Convienence method to get the supplied environment
    std::string GetEnvironment(const std::string& env);  
};

struct nulldeleter
{
	void operator() (void const *) const
	{}
};

inline char atoc(unsigned char c)
{
    if( c < ' ' || c > '~' )
	    return '.';
	   
    return (char)c;
}

inline int axtoi(char *hexStg) {
    int n = 0;         // position in string
    int m = 0;         // position in digit[] to shift
    int count;         // loop index
    int intValue = 0;  // integer value of hex string
   	int digit[5];      // hold values to convert
    while (n < 4) {
        if (hexStg[n]=='\0')
	        break;
  
        if (hexStg[n]!='\n'&&hexStg[n]!=' '&&hexStg[n]!='\a') 
        {
            if (hexStg[n] > 0x2f && hexStg[n] < 0x40 ) //if 0 to 9
                digit[n] = hexStg[n] & 0x0f;            //convert to int
            else if (hexStg[n] >='a' && hexStg[n] <= 'f') //if a to f
                digit[n] = (hexStg[n] & 0x0f) + 9;      //convert to int
            else if (hexStg[n] >='A' && hexStg[n] <= 'F') //if A to F
                digit[n] = (hexStg[n] & 0x0f) + 9;      //convert to int
            else break;
        }
		
        n++;
    }
	
    count = n;
    m = n - 1;
    n = 0;
	
    while(n < count) {
        // digit[n] is value of hex digit at position n
        // (m << 2) is the number of positions to shift
        // OR the bits into return value
        intValue = intValue | (digit[n] << (m << 2));
        m--;   // adjust the position to set
        n++;   // next digit to process
    }
  
    return (intValue);
}

#endif // GALAXY_CORE_GLOBALS

