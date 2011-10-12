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

#ifndef GALAXY_CORE_BASE
#define GALAXY_CORE_BASE

// base.h: The root of the inheritance hierarchy.
//
//////////////////////////////////////////////////////////////////////

#include <gsCore/export.h>
#include <gsCore/macros.h>

namespace gsCore
{
    ///Base class to support naming and message passing

    /**
     * Set the name of this object instance.
     *
     * @param name the new instance name
     */
    class GS_CORE_EXPORT Base
    {
        DECLARE_MANAGEMENT_LAYER(Base)

    public:

        /**
         * The Base class handles things required by most gsCore classes
         * such as naming.
         */
        Base(const std::string& name = "Base");

        /**
         * Destructor.
         */
        virtual ~Base();

    public:

         /**
          * Constructor.
          *
          * @param name the instance name
          */
        void setName(const std::string& name);

        /**
         * Get the name of this object instance.
         *
         * @return the current instance name
         */
        const std::string& getName() const;

    private:

        std::string m_name;
    };
}

#endif // GALAXY_CORE_BASE

