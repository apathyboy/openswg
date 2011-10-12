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

#ifndef GALAXY_CORE_EVENTTYPE
#define GALAXY_CORE_EVENTTYPE

#include <boost/shared_ptr.hpp>

namespace gsCore
{
    // Use this event type to register a listener that recieves (but
    // never consumes) all events that pass through the system. It is
    // special in that if the type ident str that is passed in matches
    // this, then the ident value is set to zero.
    char const * const kpWildcardEventType = "*";

    /** Event Type
     *
     * EventType is used as auxillary data during event handler
     * registration, but also provides the translation from internal
     * numeric event type designation to a human readable identifier
     * useful for debugging and logging.
     *
     * @note: During event handler registration, it is wrong code to
     * register an event type that has different text associated with
     * the numeric identifier.
     *
     * The event manager generates a 32-bit numeric identity for this 
     * event type upon registration and that is what is used by the
     * system from that point on.
     */
    class EventType
    {
    public:
        explicit EventType(char const * const identStr)
            : _ident( hash_name(identStr))
            , _identStr(identStr)
        {}

        unsigned long getIdent() const
        {
            return (unsigned long)reinterpret_cast<unsigned long>(_ident);
        }

        char const * const getStr() const
        {
            return _identStr;
        }

        bool operator< (EventType const & o) const
        {
            bool r = (getIdent() < o.getIdent());
            return r;
        }

        bool operator== (EventType const & o) const
        {
            bool r = (getIdent() == o.getIdent());
            return r;
        }

        static
        void * hash_name(char const * identStr);

    private:

        // @note: _ident is stored as a void* not an int, so that in
        // the debugge it will show up as hex-values instead of
        // integer values. This is a bit more representative of what
        // we're doing here and makes it easy to allow external code
        // to assign event types as desired.
        void *       _ident;
        char const * _identStr;
    };
}

#endif // GALAXY_CORE_EVENTTYPE

