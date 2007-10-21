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

#include "galaxy/binary_packet_test.h"
#include <galaxy/network/binary_packet.h>

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryPacketTest);

using namespace Galaxy;

void BinaryPacketTest::setUp()
{}

void BinaryPacketTest::tearDown()
{}

void BinaryPacketTest::testCanWriteBinaryData()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Write an uint32 value to the packet, this should
    // return a size of 4: (0x00000000) = (0x00) (0x00) (0x00) (0x00)
    p->append<uint32>(100);

    CPPUNIT_ASSERT_EQUAL((uint32)4, p->getLength());
}

void BinaryPacketTest::testCanWriteStdStrings()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Create a string container with some test data.
    std::string str("Test String Data");

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    p->append<std::string>(str);

    CPPUNIT_ASSERT_EQUAL((uint32)16, p->getLength());
}


void BinaryPacketTest::testCanWriteCharStrings()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Create a string container with some test data.
    char* str = OSWG_NEW char[16];
    str = "Test String Data";

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    p->append<char*>(str);

    CPPUNIT_ASSERT_EQUAL((uint32)16, p->getLength());
}

void BinaryPacketTest::testCanChainWriteCommands()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Write uint32, uint64, uint8, uint16 values to the packet, this should
    // return a size of 15: (uint32)(0x00000000) = (0x00) (0x00) (0x00) (0x00) = 4
    // (uint64)(0x00000000 0x00000000) = (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) = 8
    // (uint8)(0x00) = 1
    // (uint16)(0x0000) = (0x00) (0x00) = 2
    p->append<uint32>(100)
     ->append<uint64>(23)
     ->append<uint8>(1)
     ->append<uint16>(34);

    CPPUNIT_ASSERT_EQUAL((uint32)15, p->getLength());
}

void BinaryPacketTest::testCanClearBinaryData()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Write an uint32 value to the packet, this should
    // return a size of 4: (0x00000000) = (0x00) (0x00) (0x00) (0x00)
    p->append<uint32>(100);

    CPPUNIT_ASSERT_EQUAL((uint32)4, p->getLength());

    // Clear the packet and verify it is now empty.
    p->clear();

    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());
}

void BinaryPacketTest::testCanStreamBinaryDataToPacket()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Stream an uint32 value to the packet, this should
    // return a size of 4: (0x00000000) = (0x00) (0x00) (0x00) (0x00)
    *p << (uint32)100;

    CPPUNIT_ASSERT_EQUAL((uint32)4, p->getLength());
}

void BinaryPacketTest::testCanStreamStdStringsToPacket()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Create a string container with some test data.
    std::string str("Test String Data");

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    *p << str;

    CPPUNIT_ASSERT_EQUAL((uint32)16, p->getLength());
}

void BinaryPacketTest::testCanStreamCharStringsToPacket()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Create a string container with some test data.
    char* str = OSWG_NEW char[16];
    str = "Test String Data";

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    *p << str;

    CPPUNIT_ASSERT_EQUAL((uint32)16, p->getLength());
}

void BinaryPacketTest::testCanChainStreamCommands()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);
    
    // Verify that we have an empty packet with no 
    // data in it before writing.
    CPPUNIT_ASSERT_EQUAL((uint32)0, p->getLength());

    // Write uint32, uint64, uint8, uint16 values to the packet, this should
    // return a size of 15: (uint32)(0x00000000) = (0x00) (0x00) (0x00) (0x00) = 4
    // (uint64)(0x00000000 0x00000000) = (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) (0x00) = 8
    // (uint8)(0x00) = 1
    // (uint16)(0x0000) = (0x00) (0x00) = 2
    *p << (uint32)100 << (uint64)23 << (uint8)1 << (uint16)34;

    CPPUNIT_ASSERT_EQUAL((uint32)15, p->getLength());
}

void BinaryPacketTest::testCanReadBinaryData()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);

    // Write an uint32 value to the packet, this should
    // return a size of 4: (0x00000000) = (0x00) (0x00) (0x00) (0x00)
    p->append<uint32>(100);

    CPPUNIT_ASSERT_EQUAL((uint32)4, p->getLength());

    // Read the data back in from the packet and ensure it equals 100.
    uint32 value = p->read<uint32>();

    CPPUNIT_ASSERT_EQUAL((uint32)100, value);
}

void BinaryPacketTest::testCanReadStdStringData()
{    
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);

    // Create string containers with some test data.
    std::string str1("Test1 String Data");
    std::string str2("Test2 String Data");

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    p->append<uint16>((uint16)17);
    p->append<std::string>(str1);
    p->append<uint16>((uint16)17);
    p->append<std::string>(str2);

    CPPUNIT_ASSERT_EQUAL((uint32)38, p->getLength());

    p->setReadPosition(0);

    // Read the data back in from the packet and ensure it equals "Test1 String Data"
    std::string returnStr1 = p->read<std::string>();
    CPPUNIT_ASSERT_EQUAL(0, str1.compare(returnStr1));

    // Read the data back in from the packet and ensure it equals "Test2 String Data"
    std::string returnStr2 = p->read<std::string>();
    CPPUNIT_ASSERT_EQUAL(0, str2.compare(returnStr2));
}

void BinaryPacketTest::testCanStreamBinaryDataFromPacket()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);

    // Stream an uint32 value to the packet, this should
    // return a size of 4: (0x00000000) = (0x00) (0x00) (0x00) (0x00)
    *p << (uint32)100;

    // Read the data back in from the packet and ensure it equals 100.
    uint32 value;
    *p >> value;

    CPPUNIT_ASSERT_EQUAL((uint32)100, value);
}

void BinaryPacketTest::testCanStreamStdStringsFromPacket()
{
    BinaryPacketPtr p(OSWG_NEW BinaryPacket);

    // Create string containers with some test data.
    std::string str1("Test1 String Data");
    std::string str2("Test2 String Data");

    // Write the string to the packet, this should set
    // the size of the packet to 16.
    *p << (uint16)17;
    *p << str1;
    *p << (uint16)17;
    *p << str2;

    CPPUNIT_ASSERT_EQUAL((uint32)38, p->getLength());

    // Read the data back in from the packet and ensure it equals "Test1 String Data"
    std::string returnStr1;
    *p >> returnStr1;
    CPPUNIT_ASSERT_EQUAL(0, str1.compare(returnStr1));

    // Read the data back in from the packet and ensure it equals "Test2 String Data"
    std::string returnStr2;
    *p >> returnStr2;
    CPPUNIT_ASSERT_EQUAL(0, str2.compare(returnStr2));
}

