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

#ifndef GALAXY_CORE_PROCESSMANAGER
#define GALAXY_CORE_PROCESSMANAGER

#include <gsCore/process.h>

#include <boost/shared_ptr.hpp>

#include <list>

namespace gsCore
{
    class ProcessManager
    {
    public:
        void tick(uint64_t updateTimestamp);

        void deleteProcessList();
        bool isProcessActive(int type);
        void attach(ProcessPtr process);
        bool hasProcesses();

    protected:
        typedef std::list< boost::shared_ptr<Process> > ProcessList;
        ProcessList m_processList;

    private:
        void detach(ProcessPtr process);
    };
}

#endif // GALAXY_CORE_PROCESSMANAGER

