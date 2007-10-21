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

#ifndef GALAXY_CORE_PROCESS
#define GALAXY_CORE_PROCESS

#include <gsCore/export.h>
#include <gsCore/types.h>

#include <boost/shared_ptr.hpp>

namespace gsCore
{
    // This process type enumeration is obviously subject to changes
    // based on the game design, for example, we are assuming the game will
    // have separate behaviors for voice, music, and sound effects
    // when in actuality, this engine will play all sound processes the same way
    enum PROCESS_TYPE
    {
      PROC_NONE = 0,
      PROC_MANAGESESSIONS,
		PROC_GALAXY, // i.e., cluster
		PROC_OBJECTS,
		PROC_TRAVEL
    };
    
    // Flags
    static const int PROCESS_FLAG_ATTACHED = 0x00000001;

    
    class Process;
    typedef boost::shared_ptr<Process> ProcessPtr;

    class GS_CORE_EXPORT Process
    {
        friend class GS_CORE_EXPORT ProcessManager;

    protected:
        int m_type;
        bool m_kill;
        bool m_isActive;
        bool m_isPaused;
        bool m_isInitialUpdate;
        ProcessPtr m_nextProcess;

    private:
        uint m_processFlags;

    public:
        Process(int type, uint order = 0);
        virtual ~Process();

    public:
        virtual bool isDead() const { return m_kill; }
        virtual void kill();
        
        virtual int getType() const { return m_type; }
        virtual void setType(const int type) { m_type = type; }

        virtual bool isActive() const { return m_isActive; }
        virtual void setActive(const bool active) { m_isActive = active; }
        virtual bool isAttached() const;
        virtual void setAttached(const bool attached);

        virtual bool isPaused() const { return m_isPaused; }
        virtual void togglePaused() { m_isPaused = !m_isPaused; }

        bool isInitialized() const { return ! m_isInitialUpdate; }

        ProcessPtr const getNext() const { return m_nextProcess; }
        virtual void setNext(ProcessPtr next);

        virtual void update(const uint64 updateTimestamp);
        virtual void initialize() {};

    private:
        Process(); // Disable default construction
        Process(const Process& p); // Disable copy construction
    };

    inline void Process::update(const uint64 deltaMilliseconds)
    {
        if (m_isInitialUpdate)
        {
            initialize();
            m_isInitialUpdate = false;
        }
    }
}

#endif // GALAXY_CORE_PROCESS

