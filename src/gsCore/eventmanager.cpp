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

#include <gsCore/eventmanager.h>

#include <cstring>
#include <zthread/FastMutex.h>

using namespace gsCore;

//--

static IEventManager * g_eventMgr = NULL;

IEventManager * IEventManager::get()
{
    return g_eventMgr;
}

IEventManager::IEventManager(
    char const * const name,
    bool setAsGlobal)
{
    if (setAsGlobal)
        g_eventMgr = this;
}

IEventManager::~IEventManager()
{
    if (g_eventMgr == this)
    {
        g_eventMgr = NULL;
    }
}

//--

void *
EventType::hash_name(char const * identStr)
{   
    // Relatively simple hash of arbitrary text string into a
    // 32-bit identifier. Output value is
    // input-valid-deterministic, but no guarantees are made
    // about the uniqueness of the output per-input.
    //
    // Input value is treated as lower-case to cut down on false
    // separations caused by human mistypes. Sure, it could be
    // construed as a programming error to mix up your cases, and
    // it cuts down on permutations, but in Real World Usage
    // making this text case-sensitive will likely just lead to
    // PAIN and SUFFERING.
    //
    // This code is loosely based upon the adler32 checksum by Mark
    // Adler and published as part of the zlib compression 
    // library sources.

    // largest prime smaller than 65536;
    unsigned long BASE = 65521L;

    // NMAX is the largest n such that 255n(n+1)/2 +
    // (n+1)(BASE-1) <= 2^32-1
    unsigned long NMAX = 5552;

#define DO1(buf,i)  {s1 += tolower(buf[i]); s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

    if (identStr == NULL)
		return NULL;

	if ( strcmp(identStr, kpWildcardEventType ) == 0 )
		return 0;
	
    unsigned long s1 = 0;
    unsigned long s2 = 0;

	for ( size_t len = strlen(identStr); len > 0 ; )
	{
        unsigned long k = (unsigned long)(len < NMAX ? len : NMAX);

		len -= k;

		while (k >= 16)
		{
            DO16(identStr);
			identStr += 16;
            k -= 16;
        }
		
        if (k != 0) do
		{
            s1 += *identStr++;
			s2 += s1;
        } while (--k);
		
        s1 %= BASE;
        s2 %= BASE;
    }

#pragma warning(push)
#pragma warning(disable : 4312)

    return reinterpret_cast<void *>( (s2 << 16) | s1 );

#pragma warning(pop)
#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
}

//--

EventManager::EventManager(char const * const name,
                           bool setAsGlobal)
    : IEventManager(name, setAsGlobal)
    , _activeQueue(0)
{
}

EventManager::~EventManager()
{
    _activeQueue = 0;
}

/** Register a listener for a specific event type, implicitly the
 *  event type will be added to the known event types if not
 *  already known.
 *
 *  The function will return false on failure for any reason. The
 *  only really anticipated failure reason is if the input event
 *  type is bad (e.g.: known-ident number with different
 *  signature text, or signature text is empty)
 */
bool EventManager::addListener(const EventListenerPtr &inListener, 
                               const EventType &inType)
{
    if (! validateType(inType))
        return false;

    // check / update type list
    EventTypeSet::iterator evIt = _typeList.find(inType);

    if (evIt == _typeList.end())
    {
        // was not in the list, add it ...
        EventTypeSetIRes ires = _typeList.insert(inType);

        // insert failed for some reason
        if (ires.second == false)
            return false;

        // somehow we inserted and left the list empty?!
        if (ires.first == _typeList.end())
            return false;

        evIt = ires.first; // store for later use
    }

    // find listener map entry, create one if no table already
    // exists for this entry ...
    EventListenerMap::iterator elmIt = _registry.find(inType.getIdent());

    if (elmIt == _registry.end())
    {
        EventListenerMapIRes elmIRes = _registry.insert(
            EventListenerMapEnt(inType.getIdent(), EventListenerTable())
        );

        // could not insert into map
        if (elmIRes.second == false)
            return false;

        // should not be possible, but somehow we have an empty
        // table after the insert.
        if (elmIRes.first == _registry.end())
            return false;

        // store it so we can update the mapped list next ...
        elmIt = elmIRes.first;
    }

	// update the mapped list of listeners, walk the existing
	// list (if any entries) to prevent duplicate addition of
	// listeners. This is a bit more costly at registration time
	// but will prevent the hard-to-notice duplicate event
	// propogation sequences that would happen if double-entries
	// were allowed.

	// note: use reference to make following code more simple
	EventListenerTable & evlTable = (*elmIt).second;
	
	for ( EventListenerTable::iterator it = evlTable.begin(),
			  itEnd = evlTable.end(); it != itEnd ; it++ )
	{
		bool bListenerMatch = ( *it == inListener );

		if ( bListenerMatch )
			return false;
	}

	// okay, event type validated, event listener validated,
	// event listener not already in map, add it

	evlTable.push_back( inListener );

	return true;
}


/** Remove a listener/type pairing from the internal tables.
 *
 *  Returns false if the pairing was not found.
 */
bool EventManager::delListener(EventListenerPtr const & inListener, EventType const & inType)
{
	if (! validateType(inType))
		return false;

	bool rc = false;

	// brute force method, iterate through all existing mapping
	// entries looking for the matching listener and remove it.

	for (EventListenerMap::iterator it = _registry.begin(),
			  itEnd = _registry.end(); it != itEnd; it++)
	{
		unsigned int const    kEventId = it->first;
		EventListenerTable & table     = it->second;

		for (EventListenerTable::iterator it2 = table.begin(),
				  it2End = table.end(); it2 != it2End; it2++)
		{
			if (*it2 == inListener)
			{
				// found match, remove from table,
				table.erase( it2 );

				// update return code
				rc = true;

				// and early-quit the inner loop as addListener()
				// code ensures that each listener can only
				// appear in one event's processing list once.
				break;
			}
		}
	}
	
	return rc;
}


/** Fire off event - synchronous - do it NOW kind of thing -
 *  analogous to Win32 SendMessage() API.
 *
 *  Returns true if the event was consumed, false if not. Note
 *  that it is acceptable for all event listeners to act on an
 *  event and not consume it, this return signature exists to
 *  allow complete propogation of that shred of information
 *  from the internals of this system to outside users.
 */
bool EventManager::trigger(Event const & inEvent) const
{
	if (! validateType(inEvent.getType()))
		return false;

	EventListenerMap::const_iterator itWC = _registry.find(0);

	if (itWC != _registry.end())
	{
		EventListenerTable const & table = itWC->second;

		bool processed = false;
	
		for (EventListenerTable::const_iterator it2 = table.begin(),
				  it2End = table.end(); it2 != it2End; it2++)
		{
			(*it2)->handleEvent(inEvent);
		}
	}
	
	EventListenerMap::const_iterator it = _registry.find(inEvent.getType().getIdent());

	if (it == _registry.end())
		return false;

	EventListenerTable const & table = it->second;

	bool processed = false;
	
	for (EventListenerTable::const_iterator it2 = table.begin(),
			  it2End = table.end(); it2 != it2End; it2++)
	{
		if ((*it2)->handleEvent(inEvent))
		{
			// only set to true, if processing eats the messages
			processed = true;
		}
	}
	
	return processed;
}


/** Fire off event - asynchronous - do it WHEN the event
 *  system tick() method is called, normally at a judicious
 *  time during game-loop processing.
 *
 *  Returns true if the message was added to the processing
 *  queue, false otherwise.
 */
bool EventManager::queueEvent (EventPtr const & inEvent)
{
	assert (_activeQueue >= 0);
	assert (_activeQueue < kNumQueues);

	if (! validateType(inEvent->getType()))
		return false;

	EventListenerMap::const_iterator it = _registry.find(inEvent->getType().getIdent());

	if (it == _registry.end())
	{		
		// if global listener is not active, then abort queue add
		EventListenerMap::const_iterator itWC = _registry.find( 0 );

		if (itWC == _registry.end())
		{
			// no listeners for this event, skipit
			return false;
		}
	}
	
	_queues[_activeQueue].push_back(inEvent);
	
	return true;
}

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
bool EventManager::abortEvent(EventType const & inType, bool allOfType)
{
	assert(_activeQueue >= 0);
	assert(_activeQueue < kNumQueues);

	if (! validateType(inType))
		return false;

	EventListenerMap::iterator it = _registry.find(inType.getIdent());

	if (it == _registry.end())
		return false; // no listeners for this event, skipit

	bool rc = false;
	
	for (EventQueue::iterator it = _queues[_activeQueue].begin(),
			  itEnd = _queues[_activeQueue].end(); it != itEnd; it++)
	{
		if ((*it)->getType() == inType)
		{
			_queues[_activeQueue].erase(it);
			rc = true;
			if (!allOfType)
				break;
		}
	}

	return rc;
}

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
bool EventManager::tick ( uint64 deltaMilliseconds )
{
    uint64 curMs = gsCore::getTimeInMs();
	uint64 maxMs =
		deltaMilliseconds == IEventManager::kINFINITE
		? IEventManager::kINFINITE
		: (curMs + deltaMilliseconds );

	EventListenerMap::const_iterator itWC = _registry.find(0);

	// swap active queues, make sure new queue is empty after the
	// swap ...
	
	ZThread::FastMutex mutex;
	mutex.acquire();
	int queueToProcess = _activeQueue;

	_activeQueue = (_activeQueue + 1) % kNumQueues;

	_queues[_activeQueue].clear();
	mutex.release();

	// now process as many events as we can ( possibly time
	// limited ) ... always do AT LEAST one event, if ANY are
	// available ...

	while (_queues[queueToProcess].size() > 0)
	{
		EventPtr event = _queues[queueToProcess].front();

		_queues[queueToProcess].pop_front();
		
		EventType const & eventType = event->getType();

		EventListenerMap::const_iterator itListeners = _registry.find(eventType.getIdent());

		if (itWC != _registry.end())
		{
			EventListenerTable const & table = itWC->second;

			bool processed = false;
	
			for (EventListenerTable::const_iterator it2 = table.begin(), 
                it2End = table.end(); it2 != it2End; it2++)
			{
				(*it2)->handleEvent(*event);
			}
		}

		// no listerners currently for this event type, skipit
		if (itListeners == _registry.end())
			continue;

		unsigned int const kEventId = itListeners->first;
		EventListenerTable const & table = itListeners->second;

		for (EventListenerTable::const_iterator
				  it = table.begin(), end = table.end();
			  it != end ; it++)
		{
			if ((*it)->handleEvent(*event))
			{
				break;
			}
		}

        curMs = gsCore::getTimeInMs();

		if (deltaMilliseconds != IEventManager::kINFINITE)
		{

			if (curMs >= maxMs)
			{
				// time ran about, abort processing loop
				break;
			}
		}
	}
	
	// if any events left to process, push them onto the active
	// queue.
	//
	// Note: to preserver sequencing, go bottom-up on the
	// raminder, inserting them at the head of the active
	// queue...

	bool queueFlushed = (_queues[queueToProcess].size() == 0);

	if (!queueFlushed)
	{
		while (_queues[queueToProcess].size() > 0)
		{
			EventPtr event = _queues[queueToProcess].back();

			_queues[queueToProcess].pop_back();

			_queues[_activeQueue].push_front(event);
		}
	}
	
	// all done, this pass
	
	return queueFlushed;
}

/**
 *  Validate an event type, this does NOT add it to the
 *  internal registry, only verifies that it is legal 
 *  (e.g.: eitehr the ident number is not yet assigned, or it is
 *  assigned to matching signature text, and the signature
 *  text is not empty).
 */
bool EventManager::validateType(EventType const & inType) const
{
	if (inType.getStr() == NULL)
		return false;

	if ((inType.getIdent() == 0) && (strcmp(inType.getStr(),kpWildcardEventType) != 0))
		return false;

	EventTypeSet::const_iterator evIt = _typeList.find(inType);

	if ( evIt != _typeList.end() )
	{
		// verify that the text signature is the same as already
		// known ...

		EventType const & known = *evIt;

		char const * const kKnownTag = known.getStr();
		char const * const kNewTag   = inType.getStr();

		int cv = _stricmp(kKnownTag, kNewTag);

		// tag mismatch for ident value, not accepted
		if (cv != 0)
			return false;
	}
	
	return true;
}

/** Get the list of listeners associated with a specific event type.
 */
EventListenerList EventManager::getListenerList (EventType const & eventType) const
{
	// invalid event type, so sad
	if (! validateType(eventType))
		return EventListenerList();

	EventListenerMap::const_iterator itListeners = _registry.find(eventType.getIdent());

	// no listerners currently for this event type, so sad
	if (itListeners == _registry.end())
		return EventListenerList();

	EventListenerTable const & table = itListeners->second;

	// there was, but is not now, any listerners currently for
	// this event type, so sad
	if (table.size() == 0)
		return EventListenerList();

	EventListenerList result;

	result.reserve(table.size());
	
	for (EventListenerTable::const_iterator it = table.begin(),
			  end = table.end(); it != end ; it++)
	{
		result.push_back(*it);
	}

	return result;
}

/** Get the list of known event types.
 */
EventTypeList EventManager::getTypeList(void) const
{
	// no entries, so sad
	if (_typeList.size() == 0)
		return EventTypeList();

	EventTypeList result;

	result.reserve(_typeList.size());

	for (EventTypeSet::const_iterator it = _typeList.begin(),
			  itEnd = _typeList.end(); it != itEnd; it++)
	{
		result.push_back(*it);
	}
	
	return result;
}

//--

// These functions make it less difficult to safely use a possibly
// not-ready system ...

bool gsCore::safeAddListener( EventListenerPtr const & inHandler, EventType const & inType )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->addListener( inHandler, inType );
}

bool gsCore::safeDelListener( EventListenerPtr const & inHandler, EventType const & inType )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->delListener( inHandler, inType );
}

bool gsCore::safeTriggerEvent( Event const & inEvent )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->trigger( inEvent );
}

bool gsCore::safeQueueEvent( EventPtr const & inEvent )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->queueEvent( inEvent );
}

bool gsCore::safeAbortEvent( EventType const & inType,
					 bool allOfType /*= false*/ )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->abortEvent( inType, allOfType );
}

bool gsCore::safeTickEventManager( unsigned long maxMillis /*= kINFINITE*/ )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->tick( maxMillis );
}

bool gsCore::safeValidateEventType( EventType const & inType )
{
	assert(IEventManager::get() && _T("No event manager!"));
	return IEventManager::get()->validateType( inType );
}

