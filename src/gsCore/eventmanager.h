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

#ifndef GALAXY_CORE_EVENTMANAGER
#define GALAXY_CORE_EVENTMANAGER

#include <cstdint>

#include <gsCore/event.h>
#include <gsCore/eventdata.h>
#include <gsCore/eventlistener.h>
#include <gsCore/eventtype.h>
#include <gsCore/process.h>
#include <gsCore/timing.h>

#include <boost/shared_ptr.hpp>

#include <vector>
#include <set>
#include <list>
#include <map>
#include <tchar.h>

namespace gsCore
{
    /** IEventManager
     * 
     *  This ist he object which maintains the list of registered
     *  events and their listeners.
     *
     *  This is a many-to-many relationship, as both one listener can
     *  be configured to process multiple event types and of course
     *  multiple listeners can be registered to each event type.
     *
     *  The interface to this construct uses smart pointer wrapped
     *  objects, the purpose being to ensure that no object that the
     *  registry is referring to is destroyed before it is removed from
     *  the registry AND to allow for the registry to be the only
     *  place where this list is kept ... the application code does
     *  not need to maintain a second list.
     *
     *  Simply tearing down the registry (e.g.: destroying it) will
     *  automatically clean up all pointed-to objects (so long as
     *  there are no other outstanding references, of course).
     */
    class IEventManager
    {
    public:
        enum eConstants
        {
            kINFINITE = 0xffffffff
        };

        explicit IEventManager(char const * const name, bool setAsGlobal);
        virtual ~IEventManager();

        /** Register a handler for a a specific event type, implicitly
         *  the event type will be added tot he known event types if
         *  not already known.
         *
         *  The function will return false on failure for any reason.
         *  The only really anticipated failure reason is if the
         *  input event type is bad (e.g.: known-ident number with
         *  different signature text, or signature text is empty)
         */
        virtual bool addListener(EventListenerPtr const & inHandler,
                                 EventType const & inType) = 0;

        /** Remove a listener/type pairing from the internal tables.
         *  
         *  Returns false if the pairing was not found.
         */
        virtual bool delListener(EventListenerPtr const & inHandler,
                                 EventType const & inType) = 0;

        /** Fire off event - synchronous - do it NOW kind of thing -
         *  analogous to Win32 SendMessage() API.
         *
         *  Returns true if the event was consumed, false if not. Note
         *  that it is acceptable for all event listeners to act on an
         *  event and not consume it, this return signature exists to
         *  allow complete propogation of that shred of information
         *  from the internals of this system to outside users.
         */
        virtual bool trigger(Event const & inEvent) const = 0;

        /** Fire off event - asynchronous - do it WHEN the event
         *  system tick() method is called, normally at a judicious
         *  time during game-loop processing.
         *
         *  Returns true if the message was added to the processing
         *  queue, false otherwise.
         */
        virtual bool queueEvent(EventPtr const & inEvent) = 0;

        /** Find the next-available instance of the named event type
         *  and remove it from the processing queue.
         *
         *  This may be done up to the point that it is actively being
         *  processed ...  e.g.: is safe to happen during event 
         *  processing itself.
         *
         *  If 'allOfType' is input true, then all events of that type 
         *  are cleared from the input queue.
         *
         *  Returns true if the event was found and removed, false
         *  otherwise.
         */
        virtual bool abortEvent(EventType const & inType,
                                bool allOfType = false) = 0;

        /**
         *  Allow for processing of any queued messages, optionally
         *  specify a processing time limit so that the event
         *  processing does not take too long. Note the danger
         *  of using this artificial limiter is that all messages may
         *  not in fact get processed.
         *
         *  Returns true if all messages ready for processing were
         *  completed, false otherwise (e.g. timeout)
         */
        virtual bool tick(uint64_t deltaMilliseconds = kINFINITE) = 0;

        // --- information lookup functions ---

        /**
         *  Validate an event type, this does NOT add it to the
         *  internal registry, only verifies that it is legal 
         *  (e.g.: eitehr the ident number is not yet assigned, or it is
         *  assigned to matching signature text, and the signature
         *  text is not empty).
         */
        virtual bool validateType(EventType const & inType) const = 0;

    private:
        
        /** Internal use only accessor for the static helper methods to use 
         *  to get the active global instance.
         */
        static IEventManager * get();

        // These methods are declared friends in order to get access to the
        // get() method. Since there is no other private entity declared
        // in this class this does not break encapsulation, but does allow
        // us to do this without requiring macros or other older-style
        // mechanics.
        friend bool safeAddListener(EventListenerPtr const & inHandler,
                                    EventType const & inType);

        friend bool safeDelListener(EventListenerPtr const & inHandler,
                                    EventType const & inType);

        friend bool safeTriggerEvent(Event const & inEvent);

        friend bool safeQueueEvent(EventPtr const & inEvent);

        friend bool safeAbortEvent(EventType const & inType,
                                   bool allOfType = false);

        friend bool safeTickEventManager(unsigned long maxMillis = 
                                    IEventManager::kINFINITE);

        friend bool safeValidateEventType(EventType const & inType);
    };

    typedef std::vector<EventListenerPtr> EventListenerList;
    typedef std::vector<EventType>        EventTypeList;

    /** EventManager is a basic implementation of the event listener registry
     *  defined by IEventManager.
     */
    class EventManager : public IEventManager
    {
    public:
        explicit EventManager(char const * const name, bool setAsGlobal);
        virtual ~EventManager();

        // --- primary use functions ---

        /** Register a listener for a specific event type, implicitly
         *  the event type will be added to the known event types if
         *  not already known.
         *
         *  The function will return false on failure for any
         *  reason. The only really anticipated failure reason is if
         *  the input event type is bad (e.g.: known-ident number
         *  with different signature text, or signature text is empty)
         */
        bool addListener(EventListenerPtr const & inListener,
                         EventType const & inType);

        /** Remove a listener/type pairing from the internal tables.
         *
         *  Returns false if the pairing was not found.
         */
        bool delListener(EventListenerPtr const & inListener,
                         EventType const & inType);

        /** Fire off event - synchronous - do it NOW kind of thing -
         *  analogous to Win32 SendMessage() API.
         *
         *  Returns true if the event was consumed, false if not. Note
         *  that it is acceptable for all event listeners to act on an
         *  event and not consume it, this return signature exists to
         *  allow complete propogation of that shred of information
         *  from the internals of this system to outside users.
         */
        bool trigger(Event const & inEvent) const;

        /** Fire off event - asynchronous - do it WHEN the event
         *  system tick() method is called, normally at a judicious
         *  time during game-loop processing.
         *
         *  Returns true if the message was added to the processing
         *  queue, false otherwise.
         */
        bool queueEvent(EventPtr const & inEvent);

        /** Find the next-available instance of the named event type
         *  and remove it from the processing queue.
         *
         *  This may be done up to the point that it is actively being
         *  processed ...  e.g.: is safe to happen during event 
         *  processing itself.
         *
         *  If 'allOfType' is input true, then all events of that type 
         *  are cleared from the input queue.
         *
         *  Returns true if the event was found and removed, false
         *  otherwise.
         */
        bool abortEvent(EventType const & inType, bool allOfType);

        /**
         *  Allow for processing of any queued messages, optionally
         *  specify a processing time limit so that the event
         *  processing does not take too long. Note the danger
         *  of using this artificial limiter is that all messages may
         *  not in fact get processed.
         *
         *  Returns true if all messages ready for processing were
         *  completed, false otherwise (e.g. timeout)
         */
        bool tick(uint64_t deltaMilliseconds);

        // -- information lookup functions ---

        /**
         *  Validate an event type, this does NOT add it to the
         *  internal registry, only verifies that it is legal 
         *  (e.g.: eitehr the ident number is not yet assigned, or it is
         *  assigned to matching signature text, and the signature
         *  text is not empty).
         */
        bool validateType(EventType const & inType) const;

        /** Get the list of listeners associated with a specific event type.
         */
        EventListenerList getListenerList(EventType const & eventType) const;

        /** Get the list of known event types.
         */
        EventTypeList getTypeList(void) const;

    private:

        // one global instance
        typedef std::set<EventType> EventTypeSet;

        // insert result into event type set
        typedef std::pair<EventTypeSet::iterator, bool> EventTypeSetIRes;

        // one list per event type (stored in the map)
        typedef std::list<EventListenerPtr> EventListenerTable;

        // mapping of event ident to listener list
        typedef std::map<unsigned int, EventListenerTable> EventListenerMap;

        // entry in the event listener map
        typedef std::pair<unsigned int, EventListenerTable> EventListenerMapEnt;

        // insert result into listener map
        typedef std::pair<EventListenerMap::iterator, bool> EventListenerMapIRes;

        // queue of pending- or processing-events
        typedef std::list<EventPtr> EventQueue;

        enum eConstants
        {
            kNumQueues = 2
        };

        EventTypeSet     _typeList;           // list of registered event types

        EventListenerMap _registry;           // mapping of event types 
                                              // to listeners

        EventQueue       _queues[kNumQueues]; // event processing queue,
                                              // double buffered to
                                              // prevent infinite cycles

        int              _activeQueue;        // valid denoting which 
                                              // queue is actively
                                              // processing, en-queing
                                              // events goes to the
                                              // opposing queue
    };

    // These methods are used for easy-access methods to carry out
    // basic operations without needing to pass around a pointer-to
    // (or some other construct) for sharing a global event manager.

    bool safeAddListener(EventListenerPtr const & inHandler,
                         EventType const & inType);

    bool safeDelListener(EventListenerPtr const & inHandler,
                         EventType const & inType);

    bool safeTriggerEvent(Event const & inEvent);

    bool safeQueueEvent(EventPtr const & inEvent);

    bool safeAbortEvent(EventType const & inType,
                        bool allOfType);

    bool safeTickEventManager(unsigned long maxMillis);

    bool safeValidateEventType(EventType const & inType);
}

#endif // GALAXY_CORE_EVENTMANAGER
