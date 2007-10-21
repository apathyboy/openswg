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

#ifndef GALAXY_CORE_LOG
#define GALAXY_CORE_LOG

#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsCore/export.h>

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Layout.hh>

namespace gsCore
{	
    class GS_CORE_EXPORT LogLayout : public log4cpp::Layout
    {
    public:
        LogLayout();
        virtual ~LogLayout();
        
        /**
         * Formats the LoggingEvent in BasicLayout style:<br>
         * "timeStamp priority category ndc: message"
         **/
        virtual std::string format(const log4cpp::LoggingEvent& event);
    };

    class GS_CORE_EXPORT LogOutputLayout : public log4cpp::Layout
    {
    public:
        LogOutputLayout();
        virtual ~LogOutputLayout();
        
        /**
         * Formats the LoggingEvent in BasicLayout style:<br>
         * "timeStamp priority category ndc: message"
         **/
        virtual std::string format(const log4cpp::LoggingEvent& event);
    };

    class GS_CORE_EXPORT Log
    {
    public:
        Log();
        virtual ~Log();
        static log4cpp::Category& getMainLog() { return log4cpp::Category::getInstance("mainLog"); }
        static log4cpp::Category& getPacketLog() { return log4cpp::Category::getInstance("packetLog"); }
        static log4cpp::Category& getEventLog() { return log4cpp::Category::getInstance("eventLog"); }
        void static initMainLog(std::string logFile = "");
        void static initPacketLog(std::string logFile = "");
        void static initEventLog(std::string logFile = "");
    };
};

#define sMainLog log4cpp::Category::getInstance("mainLog")
#define sPacketLog log4cpp::Category::getInstance("packetLog")

#endif // GALAXY_UTILS_LOG_H

