/**
 * socket_listener_mock.h: Mock SocketListener object.
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

#ifndef GALAXY_MOCKS_SOCKET_LISTENER_MOCK_H
#define GALAXY_MOCKS_SOCKET_LISTENER_MOCK_H

#define HAVE_LIMITS

/*** Mockpp Includes ***/
#include <mockpp/mockpp.h>
#include <mockpp/MockObject.h>
#include <mockpp/ExpectationList.h>
#include <mockpp/ReturnObjectList.h>
#include <mockpp/ExpectationCounter.h>
#include <mockpp/constraint/ConstraintList.h>
#include <mockpp/chaining/ChainingMockObjectSupport.h>

/*** Project Includes ***/
#include <galaxy/common.h>
#include <galaxy/network/socket_listener.h>

/*** Mock Object Includes ***/

/** @basic Provides a black box testing object that can
 *  be used in place of NetworkListener to test client code.
 */
class SocketListenerMock : public Galaxy::SocketListener
    , public MOCKPP_NS::MockObject
{
public:
    SocketListenerMock()
        : MOCKPP_NS::MockObject(MOCKPP_PCHAR("SocketListenerMock"), 0)   
        , toggleRunningCounter(MOCKPP_PCHAR("SocketListenerMock/toggleRunningCounter"), this)
        , runCounter(MOCKPP_PCHAR("SocketListenerMock/runCounter"), this)
        , hasReceivedMessagesCounter(MOCKPP_PCHAR("SocketListenerMock/hasReceivedMessagesCounter"), this)        
        , hasReceivedMessagesBool(MOCKPP_PCHAR("SocketListenerMock/hasReceivedMessagesBool"), this)          
        , getNextReceivedMessageData(MOCKPP_PCHAR("SocketListenerMock/getNextReceivedMessageData"), this)    
        , hasSendMessagesCounter(MOCKPP_PCHAR("SocketListenerMock/hasSendMessagesCounter"), this)        
        , hasSendMessagesBool(MOCKPP_PCHAR("SocketListenerMock/hasSendMessagesBool"), this)          
        , getNextSendMessageData(MOCKPP_PCHAR("SocketListenerMock/getNextSendMessageData"), this)   
        , sendPacketBool(MOCKPP_PCHAR("SocketListenerMock/sendPacketBool"), this)
    {
    }

    virtual bool toggleRunning()
    {
        toggleRunningCounter.inc();
        return false;
    }

    virtual bool isRunning()
    {
        return true;
    }

    virtual void run()
    {
        runCounter.inc();
    }

    virtual bool hasReceivedMessages(uint64 boundryTimestamp = 0)
    {
        hasReceivedMessagesCounter.inc();
        return hasReceivedMessagesBool.nextReturnObject();
    }

    virtual Galaxy::BinaryPacketPtr getNextReceivedMessage()
    {
        return getNextReceivedMessageData.nextReturnObject();
    }

    virtual bool hasSendMessages(uint64 boundryTimestamp = 0)
    {
        hasSendMessagesCounter.inc();
        return hasSendMessagesBool.nextReturnObject();
    }

    virtual Galaxy::BinaryPacketPtr getNextSendMessage()
    {
        return getNextSendMessageData.nextReturnObject();
    }
    
    virtual void sendPacket(Galaxy::BinaryPacketPtr packet, bool immediately = false)
    {
    }

    MOCKPP_NS::ExpectationCounter runCounter;
    MOCKPP_NS::ExpectationCounter hasReceivedMessagesCounter;
    MOCKPP_NS::ReturnObjectList<bool> hasReceivedMessagesBool;
    MOCKPP_NS::ReturnObjectList<Galaxy::BinaryPacketPtr> getNextReceivedMessageData;
    MOCKPP_NS::ExpectationCounter hasSendMessagesCounter;
    MOCKPP_NS::ReturnObjectList<bool> hasSendMessagesBool;
    MOCKPP_NS::ReturnObjectList<Galaxy::BinaryPacketPtr> getNextSendMessageData;
    MOCKPP_NS::ExpectationCounter toggleRunningCounter;    
    MOCKPP_NS::ExpectationList<bool> sendPacketBool;
};

#endif // GALAXY_MOCKS_SOCKET_LISTENER_MOCK_H

