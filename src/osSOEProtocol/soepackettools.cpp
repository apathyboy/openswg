#include <osSOEProtocol/soepackettools.h>
#include <gsCore/macros.h>
#include <osSOEProtocol/soesession.h>
#include <gsCore/globals.h>
#include <malloc.h>
#include <zlib.h>

#define MAX_PACKET_SIZE 1000

using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

/** SWGEmu Code Below This Point
 *	Copyright (C) 2006 Team SWGEmu <http://www.swgemu.com>
 */

unsigned int osSOEProtocol::GenerateCrc(char* pData,unsigned short nLength,unsigned int nCrcSeed)
{
    unsigned int nCrc = g_nCrcTable[(~nCrcSeed) & 0xFF];
    nCrc ^= 0x00FFFFFF;
    unsigned int nIndex = (nCrcSeed >> 8) ^ nCrc;
    nCrc = (nCrc >> 8) & 0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];
    nIndex = (nCrcSeed >> 16) ^ nCrc;
    nCrc = (nCrc >> 8) & 0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];
    nIndex = (nCrcSeed >> 24) ^ nCrc;
    nCrc = (nCrc >> 8) &0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];

    for( short i = 0; i < nLength; i++ )
    {
        nIndex = (pData[i]) ^ nCrc;
        nCrc = (nCrc >> 8) & 0x00FFFFFF;
        nCrc ^= g_nCrcTable[nIndex & 0xFF];
    }
    return ~nCrc;
}


bool osSOEProtocol::CrcTest(char *pData, unsigned short nLength,unsigned int nCrcSeed, short nCrcLength)
{
    bool crctest = true;
    if(nCrcLength > 0)
    {
        unsigned int p_crc = GenerateCrc(pData,(nLength-nCrcLength),nCrcSeed);
        unsigned int  crc = 0;
        unsigned int mask = 0;
        unsigned int pullbyte = 0;
        pData = pData + (nLength-nCrcLength);
        for( short i = 0; i < nCrcLength; i++ )
        {
            pullbyte = (unsigned char)pData[i];
            crc |=(pullbyte << (((nCrcLength - 1) - i) * 8));
            mask <<= 8;
            mask |= 0xFF;
        }
        p_crc &= mask;
        if(p_crc != crc)
            crctest = false;
    }
    return crctest;
}

void osSOEProtocol::AppendCRC(char *pData, unsigned short nLength, unsigned int nCrcSeed, short nCrcLength)
{
    if (nCrcLength > 0)
    {
        unsigned int crc = GenerateCrc(pData,(nLength-nCrcLength),nCrcSeed);
        pData += (nLength-nCrcLength);
        for( short i = 0; i < nCrcLength; i++ )
        {
            pData[(nCrcLength - 1) - i] = (char)((crc >> (8 * i)) & 0xFF);
        }
    }

}

void osSOEProtocol::Encrypt(char *pData, unsigned short nLength, unsigned int nCrcSeed, bool header)
{
	unsigned int *Data;
    if (header) {
        nLength-=4;
        Data = (unsigned int*)(pData+2);
    }
    else {
        nLength-=2;
        Data = (unsigned int*)(pData);
    }
    short block_count = (nLength / 4);
    short byte_count = (nLength % 4);
    for(short count = 0;count<block_count;count++)
    {
        *Data ^= nCrcSeed;
        nCrcSeed = *Data;
        Data++;
    }
    pData = (char*)Data;
    for(short count = 0;count<byte_count;count++)
    {
        *pData ^= (char)nCrcSeed;
        pData++;
    }
}

void osSOEProtocol::Decrypt(char *pData,unsigned short nLength,unsigned int nCrcSeed, bool header)
{
	unsigned short lengthMod = 4;
	unsigned int *Data;
	if (header)
		Data = (unsigned int*)(pData+2);
	else
	{
		Data = (unsigned int*)(pData+1);
		lengthMod=1;
	}
	nLength-=lengthMod;

    short block_count = (nLength / 4);
    short byte_count = (nLength % 4);
    unsigned int itemp;
    for(short count = 0;count<block_count;count++)
    {
        itemp = *Data;
        *Data ^= nCrcSeed;
        nCrcSeed = itemp;
        Data++;
    }
    pData = (char*)Data;
    for(short count = 0;count<byte_count;count++)
    {
        *pData ^= nCrcSeed;
        pData++;
    }
}

char *osSOEProtocol::Decompress(char *pData, unsigned short &nLength)
{

    unsigned short offset;
    if(pData[0] == 0x00)
     offset = 2;
    else
     offset = 1;
    z_stream packet;
    char output[CompBuf];
    unsigned short newLength=0;
    packet.zalloc = Z_NULL;
    packet.zfree = Z_NULL;
    packet.opaque = Z_NULL;
    packet.avail_in = 0;
    packet.next_in = Z_NULL;
    inflateInit(&packet);
    packet.next_in = (Bytef*)(pData+offset);
    packet.avail_in = (nLength - offset -3);
    packet.next_out = (Bytef*)output;
    packet.avail_out = CompBuf;
    inflate(&packet,Z_FINISH);
    newLength = (uint16_t)packet.total_out;
    inflateEnd(&packet);
    char *Decomp_pData  = GS_NEW char [newLength + offset + 3];
    char *begDecomp_pData = Decomp_pData;
    *Decomp_pData = pData[0];
    Decomp_pData++;
    if(offset == 2)
	{
	 *Decomp_pData = pData[1];
     Decomp_pData++;
	}
    for(short x=0;x<newLength;x++)
    {
        *Decomp_pData = output[x];
        Decomp_pData++;
    }
	*Decomp_pData = 0x01;
    Decomp_pData++;
	pData += (nLength-2);
    *(unsigned short*)Decomp_pData = *(unsigned short*)pData;
    Decomp_pData = begDecomp_pData;
    nLength = newLength + offset + 3;
    return Decomp_pData;

}

bool osSOEProtocol::Compress(char **pData, unsigned short *nLength, bool crc)
{
	if (ZLIB_COMPRESSION_RATIO != Z_NO_COMPRESSION) {
        char *tempData = *pData;
        z_stream packet;

        char *output = GS_NEW char[*nLength+10];
        packet.zalloc = Z_NULL;
        packet.zfree = Z_NULL;
        packet.opaque = Z_NULL;
        packet.avail_in = 0;
        packet.next_in = Z_NULL;
        deflateInit(&packet,ZLIB_COMPRESSION_RATIO);
        packet.next_in = (Bytef* )((*pData)+2);
        packet.avail_in = (*nLength-3); //opcode + comp
        packet.next_out = (Bytef* )output;
        packet.avail_out = CompBuf;
        deflate(&packet,Z_FINISH);
        unsigned long newLength = packet.total_out;
        deflateEnd(&packet);
        if (newLength+3 >= *nLength) {
            delete [] output;
            return 0; //We didn't compress it.
        }
        else {
            char *comp_pData  = GS_NEW char [newLength+3];
            comp_pData[0] = (*pData)[0];
            comp_pData[1] = (*pData)[1];
            for(unsigned long x=0;x<newLength;x++)
            {
                comp_pData[2+x] = output[x];
            }
            comp_pData[2+newLength] = (uint8_t)1;
            delete [] output;
            delete [] tempData;
            newLength+=3;
            *nLength = (unsigned short)newLength;
            (*pData) = comp_pData;

            return 1; //We compressed it.
        }
    }
    return 0; //We didn't compress it.
}

long osSOEProtocol::SWGCRC(const char* buffer)
{
   int length = strlen(buffer);
   unsigned long CRC = 0xFFFFFFFF;
   for(short counter = 0; counter < length; counter++)
      CRC = swg_crctable[buffer[counter] ^ (CRC >> 24)] ^ (CRC << 8);
   return ~CRC;
}

void osSOEProtocol::PrepareSOEPacket(BinaryPacketPtr packet, SessionPtr session, bool encrypt, bool compress, bool crc)
{
	boost::shared_ptr<SOESession> soeSession = boost::shared_dynamic_cast<SOESession>(session);

    // Trigger an event for this? not sure how this should be handled 
    // for outgoing messages just yet.
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    char* tmp = new char[length];
    memcpy(tmp, data, length);

    data = tmp;

    if (! crc)
    {
        if (encrypt)
            Encrypt(data, (uint16_t)length, soeSession->getCrcSeed());
    }   
    else
    {
        length -= 2;

        if (! compress)
        {
            if (length > CompressSize)
                compress = true;
        }

        if (compress)
        {
            Compress(&data, (uint16_t*)&length, 1);
        }

        if (encrypt)
        {
            char* tmp = new char[length+2];
            memcpy(tmp, data, length);

            tmp[length]   = 0;
            tmp[length+1] = 0;

            data = tmp;

            length += 2;

            Encrypt(data, (uint16_t)length, soeSession->getCrcSeed());
        }

        AppendCRC(data, (uint16_t)length, soeSession->getCrcSeed());
    }

    // Clear the current data in the packet and add the processed
    // data back in.
    packet->clear();
    packet->append((uint8_t *)data, length);
}
