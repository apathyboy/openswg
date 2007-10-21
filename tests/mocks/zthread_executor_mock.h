/**
 * zthread_executor_mock.h: Mock ZThreadExecutor object.
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

#ifndef GALAXY_MOCKS_ZTHREAD_EXECUTOR_MOCK_H
#define GALAXY_MOCKS_ZTHREAD_EXECUTOR_MOCK_H

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
#include <zthread/Executor.h>

/*** Mock Object Includes ***/

/** @basic Provides a black box testing object that can
 *  be used in place of ZThreadExecutor to test client code.
 */
class ZThreadExecutorMock : public ZThread::Executor
    , public MOCKPP_NS::MockObject
{
public:
    ZThreadExecutorMock()
        : MOCKPP_NS::MockObject(MOCKPP_PCHAR("ZThreadExecutorMock"), 0)     
        , executeCounter(MOCKPP_PCHAR("ZThreadExecutorMock/executeCounter"), this)
    {
    }

    virtual void execute(ZThread::Runnable* runnable);
    virtual void execute(const ZThread::Task & runnable)
    {
        executeCounter.inc();
    }

    virtual void cancel() {}
    virtual bool isCanceled() { return true; }
    virtual void interrupt() {}
    virtual bool wait(unsigned long timeout) { return true;}
    virtual void wait() {}
    
    MOCKPP_NS::ExpectationCounter executeCounter;
};

#endif // GALAXY_MOCKS_ZTHREAD_EXECUTOR_MOCK_H

