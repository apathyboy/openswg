/**
 * binary_packet_test.h: Unit tests for the BinaryPacket class.
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

#ifndef GALAXY_TESTS_NETWORK_BINARY_PACKET_TEST_H
#define GALAXY_TESTS_NETWORK_BINARY_PACKET_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class BinaryPacketTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BinaryPacketTest);
    CPPUNIT_TEST(testCanWriteBinaryData);
    CPPUNIT_TEST(testCanWriteStdStrings);
    CPPUNIT_TEST(testCanWriteCharStrings);
    CPPUNIT_TEST(testCanChainWriteCommands);
    CPPUNIT_TEST(testCanClearBinaryData);
    CPPUNIT_TEST(testCanStreamBinaryDataToPacket);
    CPPUNIT_TEST(testCanStreamStdStringsToPacket);
    CPPUNIT_TEST(testCanStreamCharStringsToPacket);
    CPPUNIT_TEST(testCanChainStreamCommands);
    CPPUNIT_TEST(testCanReadBinaryData);
    CPPUNIT_TEST(testCanReadStdStringData);
    CPPUNIT_TEST(testCanStreamBinaryDataFromPacket);
    CPPUNIT_TEST(testCanStreamStdStringsFromPacket);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCanWriteBinaryData();
    void testCanWriteStdStrings();
    void testCanWriteCharStrings();
    void testCanChainWriteCommands();

    void testCanClearBinaryData();

    void testCanStreamBinaryDataToPacket();
    void testCanStreamStdStringsToPacket();
    void testCanStreamCharStringsToPacket();
    void testCanChainStreamCommands();

    void testCanReadBinaryData();
    void testCanReadStdStringData();
 
    void testCanStreamBinaryDataFromPacket();
    void testCanStreamStdStringsFromPacket();
};

#endif // GALAXY_TESTS_NETWORK_BINARY_PACKET_TEST_H

