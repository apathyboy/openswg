/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2007 OpenSWG Team <http://www.openswg.com>
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

#ifndef GALAXY_NETWORK_BINARYPACKET
#define GALAXY_NETWORK_BINARYPACKET

#include <gsCore/types.h>
#include <gsNetwork/export.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace gsNetwork
{
    class BinaryPacket;
    typedef GS_NETWORK_EXPORT boost::shared_ptr<BinaryPacket> BinaryPacketPtr;

    class GS_NETWORK_EXPORT BinaryPacket
    {
    public:
        const static size_t DEFAULT_SIZE = 0x400;

        BinaryPacket();
        BinaryPacket(const char *data, size_t length);
        virtual ~BinaryPacket();

        virtual char * getData() const;
        virtual char * getData(uint offset) const;
        virtual uint32 getLength() const;

        virtual void clear();

        void setTimestamp(uint64 timestamp);
        uint64 getTimestamp();

        void setWritePosition(size_t position);
        size_t getWritePosition();

        void setReadPosition(size_t position);
        size_t getReadPosition();

        std::string getLogString();

        BinaryPacket &operator<<(uint8 data)
        {
            append<uint8>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint16 data)
        {
            append<uint16>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint32 data)
        {
            append<uint32>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint64 data)
        {
            append<uint64>(data);
            return *this;
        }

        BinaryPacket &operator<<(float data)
        {
            append<float>(data);
            return *this;
        }

        BinaryPacket &operator<<(const std::string &data)
        {
            append((uint8 *)data.c_str(), data.length());
            return *this;
        }

        BinaryPacket &operator<<(const char *data)
        {
            append((uint8 *)data, strlen(data));
            return *this;
        }

        BinaryPacket &operator>>(uint8 &data) {
            data = read<uint8>();
            return *this;
        }

        BinaryPacket &operator>>(uint16 &data) {
            data = read<uint8>();
            return *this;
        }

        BinaryPacket &operator>>(uint32 &data) {
            data = read<uint8>();
            return *this;
        }

        BinaryPacket &operator>>(uint64 &data) {
            data = read<uint8>();
            return *this;
        }

        BinaryPacket &operator>>(float &data) {
            data = read<uint8>();
            return *this;
        }

        BinaryPacket &operator>>(std::string &data) {
            data.clear();

            if (read<uint8>() == 0)
            {
                read<uint8>();
                return *this;
            }

            setReadPosition(getReadPosition()-1);

            uint16 length = read<uint16>();

            if (length == 0)
            {
                setReadPosition(getReadPosition()-2);
                return *this;
            }

            for (uint i = 0; i < (uint)(length); ++i)
            {
                char c = read<char>();
                data += c;
            }

            return *this;
        }
		
		template <typename T>
        BinaryPacket* append(T data)
        {
            append((uint8 *)&data, sizeof(data));
            return this;
        }

        void append(const uint8 *data, size_t length)
        {
            if (m_packetData.size() < m_writePosition + length)
                m_packetData.resize(m_writePosition + length);

            memcpy(&m_packetData[m_writePosition], data, length);

            m_writePosition += length;
        }

        void append(BinaryPacketPtr packet)
        {
            if (m_packetData.size() < m_writePosition + packet->getLength())
                m_packetData.resize(m_writePosition + packet->getLength());
            
            memcpy(&m_packetData[m_writePosition], packet->getData(), packet->getLength());

            m_writePosition += packet->getLength();
        }

        template <typename T>
        T read() {
            T r = read<T>(m_readPosition);
            m_readPosition += sizeof(T);
            return r;
        }

        template <typename T>
        T read(size_t position) const {
            assert(position + sizeof(T) <= getLength());
            return *((T*)&m_packetData[position]);
        }

    protected:
        std::vector<uint8> m_packetData;
        size_t m_readPosition, m_writePosition;
        uint64 m_timestamp;
    };
	

    template <>
    inline BinaryPacket* BinaryPacket::append<std::string>(std::string data)
    {
       append((uint8 *)data.c_str(), data.size());
       return this;
    }

    template <>
    inline BinaryPacket* BinaryPacket::append<char*>(char* data)
    {
        append((uint8 *)data, strlen(data));
        return this;
    }

    template<>
    inline std::string BinaryPacket::read<std::string>()
    {
        std::string buf;

        if (BinaryPacket::read<uint8>() == 0)
        {
            BinaryPacket::read<uint8>();
            return buf;
        }

        BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-1);

        uint16 length = BinaryPacket::read<uint16>();

        if (length == 0)
        {
            BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-2);
            return buf;
        }

        for (uint i = 0; i < (uint)(length); ++i)
        {
            char c = BinaryPacket::read<char>();
            buf += c;
        }

        return buf;
    }

    template<>
    inline std::wstring BinaryPacket::read<std::wstring>()
    {
        std::wstring buf;

        uint32 length = BinaryPacket::read<uint32>();

        if (length == 0)
        {
            BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-4);
            return buf;
        }

        for (uint i = 0; i < (uint)(length); ++i)
        {
            wchar_t c = BinaryPacket::read<wchar_t>();
            buf += c;
        }

        return buf;
    }
};

#endif // GALAXY_NETWORK_BINARYPACKET

