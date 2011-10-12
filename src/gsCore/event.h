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

#ifndef GALAXY_CORE_EVENT
#define GALAXY_CORE_EVENT

#include <gsCore/eventdata.h>
#include <gsCore/eventtype.h>

#include <boost/shared_ptr.hpp>

#include <strstream>

namespace gsCore
{
    /** Event
     * 
     * Base class that all events inheret from.
     */
    class Event
    {
    public:
        explicit Event(char const * const inEventTypeName,
                       float inTime = 0.f,
                       IEventDataPtr inData = IEventDataPtr((IEventData*)NULL))
            : _type(inEventTypeName)
            , _time(inTime)
            , _userData(inData)
        {}

        Event(Event const & o)
            : _type(o._type)
            , _time(o._time)
            , _userData(o._userData)
        {}

        virtual ~Event()
        {}

        EventType const & getType() const
        {
            return _type;
        }

        float getTime() const
        {
            return _time;
        }

        IEventDataPtr getData() const
        {
            return _userData;
        }

        template<typename _T>
        _T * getDataPtr() const
        {
            return reinterpret_cast<_T *>(_userData.get());
        }

        void setDataPtr(IEventDataPtr userData) { _userData = userData; }
        virtual void serialize(std::ostrstream & out) const {};

    private:

        EventType _type;         // the identified type of the event
        float _time;             // the time at which the event fired
        IEventDataPtr _userData; // the call-time provided associated
                                 // data link ( may be NULL, validly,
                                 // if no associated data )
    };
    
    typedef boost::shared_ptr<Event> EventPtr;
}

#endif // GALAXY_CORE_EVENT

