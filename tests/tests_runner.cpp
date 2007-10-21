/**
 * tests_runner.cpp: Runs all registered cppunit tests.
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

#include <galaxy/common.h>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main()
{
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Add the test to the list of tests to run
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter(
        OSWG_NEW CppUnit::CompilerOutputter(&runner.result(), std::cerr)
    );

    // Run the tests.
    bool wasSuccessful = runner.run();

    return wasSuccessful ? 0 : 1;
}

