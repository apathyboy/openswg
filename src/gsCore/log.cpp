/**
 * log.cpp: A collection of custom logging classes for use with log4cpp.
 *
 * Copyright (C) 2006, 2007 OpenSWG Team <http://www.openswg.com>
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
#include <gsCore/log.h>
#include <gsCore/timing.h>

using namespace gsCore;

LogLayout::LogLayout() 
{}
    
LogLayout::~LogLayout() 
{}

std::string LogLayout::format(const log4cpp::LoggingEvent& event) {
    std::ostringstream message;

    time_t seconds = event.timeStamp.getSeconds();
    tm* time = localtime(&seconds);

    char* timeStr = GS_NEW char[80];

    strftime(timeStr, 80, "%c", time);
	
    const std::string& priorityName = log4cpp::Priority::getPriorityName(event.priority);
    message << "[" << timeStr << "]" << " " << priorityName << " " 
            << event.ndc << ": " 
            << event.message << std::endl;

    return message.str();
}

LogOutputLayout::LogOutputLayout() 
{}
    
LogOutputLayout::~LogOutputLayout() 
{}

std::string LogOutputLayout::format(const log4cpp::LoggingEvent& event) {
    std::ostringstream message;

    message << event.message << std::endl;

    return message.str();
}

Log::Log()
{}

Log::~Log()
{	
    // clean up and flush all appenders
	log4cpp::Category::shutdown();
}

void Log::initMainLog(std::string logFile)
{        
    if (logFile != "")
    {
        // 1 instantiate an appender object that 
        // will append to a log file
        log4cpp::Appender* fileAppender   = GS_NEW log4cpp::FileAppender("FileAppender", logFile);
        log4cpp::Appender* outputAppender = GS_NEW log4cpp::OstreamAppender("OstreamAppender", &std::cout);
        
        // 2. Instantiate a layout object
	    // Two layouts come already available in log4cpp
	    // unless you create your own.
	    // BasicLayout includes a time stamp
        log4cpp::Layout* fileLayout = GS_NEW LogLayout();
        log4cpp::Layout* outputLayout = GS_NEW LogOutputLayout();

	    // 3. attach the layout object to the 
	    // appender object
	    fileAppender->setLayout(fileLayout);
	    outputAppender->setLayout(outputLayout);

	    // 5. Step 2
        // this appender becomes the only one
        log4cpp::Category::getInstance("mainLog").setAppender(fileAppender);
        log4cpp::Category::getInstance("mainLog").setAppender(outputAppender);
    } 
}

void Log::initPacketLog(std::string logFile)
{        
    if (logFile != "")
    {
        // 1 instantiate an appender object that 
        // will append to a log file
        log4cpp::Appender* fileAppender = GS_NEW log4cpp::FileAppender("FileAppender", logFile);
        
        // 2. Instantiate a layout object
	    // Two layouts come already available in log4cpp
	    // unless you create your own.
	    // BasicLayout includes a time stamp
        log4cpp::Layout* fileLayout = GS_NEW LogLayout();

	    // 3. attach the layout object to the 
	    // appender object
	    fileAppender->setLayout(fileLayout);

	    // 5. Step 2
        // this appender becomes the only one
        log4cpp::Category::getInstance("packetLog").setAppender(fileAppender);
    } 
}

void Log::initEventLog(std::string logFile)
{        
    if (logFile != "")
    {
        // 1 instantiate an appender object that 
        // will append to a log file
        log4cpp::Appender* fileAppender = GS_NEW log4cpp::FileAppender("FileAppender", logFile);
        
        // 2. Instantiate a layout object
	    // Two layouts come already available in log4cpp
	    // unless you create your own.
	    // BasicLayout includes a time stamp
        log4cpp::Layout* fileLayout = GS_NEW LogLayout();

	    // 3. attach the layout object to the 
	    // appender object
	    fileAppender->setLayout(fileLayout);

	    // 5. Step 2
        // this appender becomes the only one
        log4cpp::Category::getInstance("eventLog").setAppender(fileAppender);
    } 
}

