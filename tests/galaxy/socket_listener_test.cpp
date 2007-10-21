/**
 * socket_listener_test.cpp: Unit tests for the SocketListener class.
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

#include "galaxy/socket_listener_test.h"

#include <galaxy/common.h>
#include <galaxy/network/socket_listener.h>

CPPUNIT_TEST_SUITE_REGISTRATION(SocketListenerTest);

using namespace Galaxy;

void SocketListenerTest::setUp()
{}

void SocketListenerTest::tearDown()
{}

void SocketListenerTest::testCanCheckAndSetRunningState()
{
    SocketListener listener;

    CPPUNIT_ASSERT_EQUAL(false, listener.isRunning());

    listener.toggleRunning();

    CPPUNIT_ASSERT_EQUAL(true, listener.isRunning());

    listener.toggleRunning();

    CPPUNIT_ASSERT_EQUAL(false, listener.isRunning());
}


void SocketListenerTest::testCallingToggleReturnsNewState()
{
    SocketListener listener;

    CPPUNIT_ASSERT_EQUAL(true, listener.toggleRunning());
    CPPUNIT_ASSERT_EQUAL(false, listener.toggleRunning());
}

void SocketListenerTest::testCanListenForUdpMessages()
{
}

