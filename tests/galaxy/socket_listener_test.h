/**
 * socket_listener_test.h: Unit tests for the SocketListener class.
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

#ifndef GALAXY_TESTS_NETWORK_SOCKET_LISTENER_TEST_H
#define GALAXY_TESTS_NETWORK_SOCKET_LISTENER_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class SocketListenerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SocketListenerTest);
    CPPUNIT_TEST(testCanCheckAndSetRunningState);
    CPPUNIT_TEST(testCallingToggleReturnsNewState);
    CPPUNIT_TEST(testCanListenForUdpMessages);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCanCheckAndSetRunningState();
    void testCallingToggleReturnsNewState();
    void testCanListenForUdpMessages();
};

#endif // GALAXY_TESTS_NETWORK_SOCKET_LISTENER_TEST_H

