/**
 * session_manager_test.cpp: Unit tests for the SessionManager class.
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

#include "galaxy/session_manager_test.h"
#include <galaxy/server/session_manager.h>
#include <galaxy/server/session.h>

CPPUNIT_TEST_SUITE_REGISTRATION(SessionManagerTest);

using namespace Galaxy;

void SessionManagerTest::setUp()
{}

void SessionManagerTest::tearDown()
{}

void SessionManagerTest::testCanAddAndFindSessions()
{
    std::string address("127.0.0.1:12345");
    SessionPtr session(OSWG_NEW Session());

    SessionManager* manager = OSWG_NEW SessionManager();

    CPPUNIT_ASSERT_EQUAL(false, manager->hasAddress(address));

    manager->addSession(address, session);

    CPPUNIT_ASSERT_EQUAL(true, manager->hasAddress(address));
    CPPUNIT_ASSERT_EQUAL(session, manager->findByAddress(address));
}

