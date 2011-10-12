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

#ifndef GALAXY_CORE_EVENTDATA
#define GALAXY_CORE_EVENTDATA

#include <boost/shared_ptr.hpp>

namespace gsCore
{
    /** Event Data
     *
     * Base type for event object hierarchy, may be used itself for
     * simplest event notifications ... aka: those that do not carry
     * additional payload data. If any event needs to propogate with
     * payload data it must be defined separately.
     *
     * The userData parameter is used to propogate access from
     * event-firing code to event-listening code. By using a smart
     * pointer object here we can safely create-and-forget the
     * object at event trigger time, and if there is nothing to
     * associate with the event then simply provide the parameter with
     * EventData(NULL) and away you go ... all nice and safe and
     * zero-memory bleed.
     */
    class IEventData
    {
    public:
        virtual ~IEventData() {}
    };

    template <typename T>
    struct EventData : public IEventData
    {
    public:
        explicit EventData<T>(T n)
        {
            _value = n;
        }

        const T getValue() { return _value; }

    private:
        EventData();                    // disable default construction
        EventData(const EventData &);   // disable copy construction
        T _value;
    };

    typedef EventData<int> EventData_Int;
    typedef boost::shared_ptr<IEventData> IEventDataPtr;
}

#endif // GALAXY_CORE_EVENTDATA

