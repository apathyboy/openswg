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

#include <gsCore/process.h>

using namespace gsCore;

// CProcess constructor
Process::Process(int type, uint order)
: m_type(type)
, m_kill(false)
, m_isActive(true)
, m_processFlags(0)
, m_isPaused(false)
, m_isInitialUpdate(true)
{}

// Process destructor - 
// @Note: always call kill(), never delete.
Process::~Process()
{}

// Process::kill() - marks the process for cleanup
void Process::kill()
{
    m_kill = true;
}

// Process::setNext - sets a process dependancy
//
// A->setNext(B)  means that B will wait until A is finished
void Process::setNext(gsCore::ProcessPtr next)
{
    m_nextProcess = next;
}

// Process attachement methods
//
// isAttached() - Is this process attached to the manager?
// setAttached() - Marks it as attached. Called only by the manager.
bool Process::isAttached() const
{
	return (m_processFlags & PROCESS_FLAG_ATTACHED) ? true : false;
}

void Process::setAttached(const bool attached)
{
	if(attached)
	{
		m_processFlags |= PROCESS_FLAG_ATTACHED;
	}
	else
	{
		m_processFlags &= ~PROCESS_FLAG_ATTACHED;
	}
}




