/**
 * base_server_test.cpp: Unit tests for the BaseServer class.
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

#include "galaxy/base_server_test.h"

#include <galaxy/network/socket_listener.h>
#include <galaxy/server/base_server.h>

#include "mocks/zthread_executor_mock.h"
#include "mocks/socket_listener_mock.h"
#include "mocks/protocol_handler_mock.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BaseServerTest);

bool gRunning;

using namespace Galaxy;

void BaseServerTest::setUp()
{}

void BaseServerTest::tearDown()
{}

void BaseServerTest::testCanStartSocketListeners()
{
    BaseServer server;

    SocketListener *listener1 = OSWG_NEW SocketListener;
    SocketListener *listener2 = OSWG_NEW SocketListener;

    server.addSocketListener(listener1);
    server.addSocketListener(listener2);

    ZThreadExecutorMock* executor = OSWG_NEW ZThreadExecutorMock;
    (*executor).executeCounter.setExpected(2);
    
    server.startSocketListeners(executor);

    (*executor).verify();

    SAFE_DELETE(executor);
}

void BaseServerTest::testSocketListenersStopOnShutdown()
{
    BaseServer server;

    SocketListenerMock *listener1 = OSWG_NEW SocketListenerMock;
    (*listener1).toggleRunningCounter.setExpected(1);

    SocketListenerMock *listener2 = OSWG_NEW SocketListenerMock;
    (*listener2).toggleRunningCounter.setExpected(1);

    server.addSocketListener(listener1);
    server.addSocketListener(listener2);

    server.shutdown();

    (*listener1).verify();
    (*listener2).verify(); 
}

