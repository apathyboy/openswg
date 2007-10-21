/**
 * protocol_handler_mock.h: Mock ProtocolHandler object.
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

#ifndef GALAXY_TESTS_PROTOCOL_HANDLER_MOCK_H
#define GALAXY_TESTS_PROTOCOL_HANDLER_MOCK_H

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

/** @basic Provides a black box testing object that can
 *  be used in place of NetworkAddress to test client code.
 */
class ProtocolHandlerMock : public Galaxy::ProtocolHandler
    , public MOCKPP_NS::MockObject
{
public:
    ProtocolHandlerMock()
        : MOCKPP_NS::MockObject(MOCKPP_PCHAR("ProtocolHandlerMock"), 0)
        , handleData(MOCKPP_PCHAR("ProtocolHandlerMock/handleData"), this)
    {
    }

    virtual void handle(Galaxy::BinaryPacketPtr packet)
    {
        handleData.addActual(packet);
    }

    
    MOCKPP_NS::ExpectationList<Galaxy::BinaryPacketPtr> handleData;
};

#endif // GALAXY_TESTS_NETWORK_HANDLER_MOCK_H

