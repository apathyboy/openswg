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

#include <gsCore/processmanager.h>

using namespace gsCore;

// ProcessManager::attach - gets a process to run
//
void ProcessManager::attach(ProcessPtr process )
{
	m_processList.push_back(process);
	process->setAttached(true);
}

// CProcessManager::Detach 
//  - Detach a process from the process list, but don't delete it
//
void ProcessManager::detach(ProcessPtr process)
{
	m_processList.remove(process);
	process->setAttached(false);
}

// ProcessManager::isProcessActive 
//  - Are there any active processes of this type?
//
bool ProcessManager::isProcessActive( int type )
{
	for(ProcessList::iterator i=m_processList.begin(); i!=m_processList.end(); ++i)
	{
		// Check for living processes.  If they are dead, make sure no children 
		// are attached as they will be brought to life on next cycle.
		if ( ( *i )->getType() == type && 
			 ( ( *i )->isDead() == false || ( *i )->getNext() ) )
			return true;
	}
	return false;
}

// ProcessManager::hasProcesses 
//  - Are there any processes at all?
//
bool ProcessManager::hasProcesses()
{
	return !m_processList.empty();
}

// ProcessManager::deleteProcessList 
//  - run through the list of processes and detach them
//
void ProcessManager::deleteProcessList()
{
	for(ProcessList::iterator i = m_processList.begin(); i != m_processList.end(); )
	{
		detach(* (i++) );
	}
}

// ProcessManager::tick
//  - run through the list of processes and update them
//
void ProcessManager::tick(uint64_t deltaMilliseconds)
{
	ProcessPtr next;
    ProcessList::iterator i = m_processList.begin();

    for (; i != m_processList.end(); i++)
	{
		ProcessPtr p = ProcessPtr(*i);

		if ( p->isDead() )
		{
			// Check for a child process and add if exists
			next = p->getNext();
			if ( next )
			{
				p->setNext(ProcessPtr((Process *)NULL));
				attach( next );
			}
			detach( p );
		}
		else if ( p->isActive() && !p->isPaused() )
		{
			p->update(deltaMilliseconds);
		}
	}
}

