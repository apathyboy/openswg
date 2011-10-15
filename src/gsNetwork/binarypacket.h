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

#include <cassert>
#include <cstdint>

#include <memory>
#include <string>
#include <vector>

namespace gsNetwork
{
    class BinaryPacket
    {
    public:
        const static size_t DEFAULT_SIZE = 0x400;

        BinaryPacket();
        BinaryPacket(const unsigned char *data, size_t length);
        virtual ~BinaryPacket();

        virtual char * getData() const;
        virtual char * getData(uint32_t offset) const;
        virtual uint32_t getLength() const;

        virtual void clear();

        void setTimestamp(uint64_t timestamp);
        uint64_t getTimestamp();

        void setWritePosition(size_t position);
        size_t getWritePosition();

        void setReadPosition(size_t position);
        size_t getReadPosition();

        std::string getLogString();

        BinaryPacket &operator<<(uint8_t data)
        {
            append<uint8_t>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint16_t data)
        {
            append<uint16_t>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint32_t data)
        {
            append<uint32_t>(data);
            return *this;
        }

        BinaryPacket &operator<<(uint64_t data)
        {
            append<uint64_t>(data);
            return *this;
        }

        BinaryPacket &operator<<(float data)
        {
            append<float>(data);
            return *this;
        }

        BinaryPacket &operator<<(const std::string &data)
        {
            append((uint8_t *)data.c_str(), data.length());
            return *this;
        }

        BinaryPacket &operator<<(const char *data)
        {
            append((uint8_t *)data, strlen(data));
            return *this;
        }

        BinaryPacket &operator>>(uint8_t &data) {
            data = read<uint8_t>();
            return *this;
        }

        BinaryPacket &operator>>(uint16_t &data) {
            data = read<uint16_t>();
            return *this;
        }

        BinaryPacket &operator>>(uint32_t &data) {
            data = read<uint32_t>();
            return *this;
        }

        BinaryPacket &operator>>(uint64_t &data) {
            data = read<uint64_t>();
            return *this;
        }

        BinaryPacket &operator>>(float &data) {
            data = read<float>();
            return *this;
        }

        BinaryPacket &operator>>(std::string &data) {
            data.clear();

            if (read<uint8_t>() == 0)
            {
                read<uint8_t>();
                return *this;
            }

            setReadPosition(getReadPosition()-1);

            uint16_t length = read<uint16_t>();

            if (length == 0)
            {
                setReadPosition(getReadPosition()-2);
                return *this;
            }

            for (uint32_t i = 0; i < length; ++i)
            {
                char c = read<char>();
                data += c;
            }

            return *this;
        }
		
		template <typename T>
        BinaryPacket* append(T data)
        {
            append((uint8_t *)&data, sizeof(data));
            return this;
        }

        void append(const uint8_t *data, size_t length)
        {
            if (m_packetData.size() < m_writePosition + length)
                m_packetData.resize(m_writePosition + length);

            memcpy(&m_packetData[m_writePosition], data, length);

            m_writePosition += length;
        }

        void append(std::shared_ptr<BinaryPacket> packet)
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
        std::vector<uint8_t> m_packetData;
        size_t m_readPosition, m_writePosition;
        uint64_t m_timestamp;
    };
	

    template <>
    inline BinaryPacket* BinaryPacket::append<std::string>(std::string data)
    {
       append((uint8_t *)data.c_str(), data.size());
       return this;
    }

    template <>
    inline BinaryPacket* BinaryPacket::append<char*>(char* data)
    {
        append((uint8_t *)data, strlen(data));
        return this;
    }

    template<>
    inline std::string BinaryPacket::read<std::string>()
    {
        std::string buf;

        if (BinaryPacket::read<uint8_t>() == 0)
        {
            BinaryPacket::read<uint8_t>();
            return buf;
        }

        BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-1);

        uint16_t length = BinaryPacket::read<uint16_t>();

        if (length == 0)
        {
            BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-2);
            return buf;
        }

        for (uint32_t i = 0; i < (uint32_t)(length); ++i)
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

        uint32_t length = BinaryPacket::read<uint32_t>();

        if (length == 0)
        {
            BinaryPacket::setReadPosition(BinaryPacket::getReadPosition()-4);
            return buf;
        }

        for (uint32_t i = 0; i < (uint32_t)(length); ++i)
        {
            wchar_t c = BinaryPacket::read<wchar_t>();
            buf += c;
        }

        return buf;
    }
};

#endif // GALAXY_NETWORK_BINARYPACKET

