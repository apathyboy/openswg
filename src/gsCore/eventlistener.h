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

#ifndef GALAXY_CORE_EVENTLISTENER
#define GALAXY_CORE_EVENTLISTENER

#include <gsCore/event.h>

#include <memory>

namespace gsCore
{
    /** IEventListener
     *
     * Base type for all event handler objects, note that this is a
     * C++ interface in the classic sense in that it defines the call
     * sequence but does not provide any functionality nor aggregate
     * any data.
     *
     * Thus, this is suitable for both single-ineritance use and MAY
     * be used safely in a multiple-inheritance construct, neither is
     * imposed or assumed.
     */
    class IEventListener
    {
    public:
        explicit IEventListener()
        {}

        virtual ~IEventListener()
        {}

		
		virtual void initialize() {}

        /** Returns ascii-text name for this listener, used mostly for
         *  debugging.
         */
        virtual char const * getName(void) = 0;

        /** Return 'false' to indicate that this listener did NOT
         *  consume the event, ( and it should continue to be 
         *  propagated )
         *
         *  Return 'true' to indicate that this listener consumed the
         *  event, ( and it should NOT continue to be propagated )
         */
        virtual bool handleEvent(Event const & event) = 0
        {
            // @note: while handleEvent() MUST be implemented in all
            // derivative classes, (as this function is pure-virtual
            // and thus the hook for IEventListener being an 
            // interface definition) a base implementation is 
            // provided here to make it easier to wire up do-nothing
            // stubs that can easily be wired to log the 
            // unhandled-event (once logging is available)

            // handleEvent() functioning shoing be kept as brief as
            // possible as multiple events will need to be evaluated
            // per-advance loop iteration.
            return false;
        }
    };
    
    typedef std::shared_ptr<IEventListener> EventListenerPtr;

    /** Event listener used for snooping ... simply emits event stats
     *  for all processed & known events to runtime log 
     */
     class EventSnooper : public IEventListener
     {
     public:
        explicit EventSnooper();
        virtual ~EventSnooper();
        char const * getName(void) { return "EventSnoop"; }
        bool handleEvent(Event const & event);

		static void registerEvents(EventListenerPtr listener);
     };
}

#endif // GALAXY_CORE_EVENTLISTENER

