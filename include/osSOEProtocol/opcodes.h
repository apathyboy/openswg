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

#ifndef OPENSWG_SOEPROTOCOL_OPCODES
#define OPENSWG_SOEPROTOCOL_OPCODES    

enum soe_opcodes {
    SOE_SESSION_REQUEST          = 0x0100,
    SOE_SESSION_RESPONSE         = 0x0200,
    SOE_MULTI_PKT                = 0x0300,
    SOE_NOT_USED                 = 0x0400,
    SOE_DISCONNECT               = 0x0500,
    SOE_PING                     = 0x0600,
    SOE_NET_STATUS_REQ           = 0x0700,
    SOE_NET_STATUS_RES           = 0x0800,
    SOE_CHL_DATA_A               = 0x0900,
    SOE_CHL_DATA_B               = 0x0A00,
    SOE_CHL_DATA_C               = 0x0B00,
    SOE_CHL_DATA_D               = 0x0C00,
    SOE_DATA_FRAG_A              = 0x0D00,
    SOE_DATA_FRAG_B              = 0x0E00,
    SOE_DATA_FRAG_C              = 0x0F00,
    SOE_DATA_FRAG_D              = 0x1000,
    SOE_OUT_ORDER_PKT_A          = 0x1100,
    SOE_OUT_ORDER_PKT_B          = 0x1200,
    SOE_OUT_ORDER_PKT_C          = 0x1300,
    SOE_OUT_ORDER_PKT_D          = 0x1400,
    SOE_ACK_A                    = 0x1500,
    SOE_ACK_B                    = 0x1600,
    SOE_ACK_C                    = 0x1700,
    SOE_ACK_D                    = 0x1800,
    SOE_MULTI_DATA_CHL           = 0x1900,
    SOE_FATAL_ERR                = 0x1D00,
    SOE_FATAL_ERR_REP            = 0x1E00,
};

enum login_opcodes {
    SMSG_LS_STRING               = 0x0E20D7E9,
    SMSG_LS_NUM                  = 0x58C07F21,
    SMSG_SERVER_NAMES            = 0xC11C63B9,
    SMSG_SERVER_ADDR             = 0x3436AEB6,
    SMSG_CHAR_LIST               = 0x65EA4574,
    SMSG_CHAR_DEL                = 0x989B0002,
    CMSG_CHAR_DEL                = 0xE87AD031,
    CMSG_ACCT_VERSION            = 0x41131F96,
    SMSG_STATION_SESSION         = 0xAAB296C6,
};

enum zone_opcode {
    SMSG_CS_STRING                = 0x0E20D7E9,
    SMSG_CS_NUM                   = 0x58C07F21,
    CMSG_NOTIFY_SESSION           = 0x31805EE0,
    CMSG_DATA_SES_VER             = 0xD5899226,
    SMSG_OK_PACKET                = 0xA16CF9AF,
    SMSG_CHAR_OPTS                = 0xE00730E5,
    CMSG_GEN_CHAR_NAME            = 0xD6D1B6D1,
    CMSG_CHECK_CHAR_NAME          = 0x9EB04B9F,
    SMSG_APPROVE_NAME             = 0xE85FB868,
    CMSG_CREATE_CHAR              = 0xB97F3074,
    SMSG_ASSIGN_CHAR_ID           = 0x1DB575CC,
    CMSG_LOGIN_CHAR               = 0xB5098D76,
    SMSG_SETTING_UNK1             = 0x7102B15F,
    SMSG_UNK_INT900               = 0x487652DA,
    SMSG_NEW_MAIL                 = 0xD72FE9BE,
    SMSG_LOAD_TERRN               = 0x3AE6DFAE,
    CMSG_OBJ_PRELOAD              = 0x2E365218, 
    SMSG_OBJ_PRELOAD              = 0x08A1C126,
    SMSG_OBJ_INIT                 = 0xFE89DDEA,
    SMSG_OBJ_UPDATE               = 0x68A75F0C,
    SMSG_OBJ_FINISH               = 0x2C436037,
    SMSG_OBJ_PREFINISH            = 0x0BDE6B41,
    SMSG_OBJ_LINK                 = 0x56CBDE9E,
    CMSG_LOAD_READY               = 0x43FD1C22,
    SMSG_LOAD_READY               = 0x43FD1C22,
    SMSG_POS_UPDATE               = 0x1B24F808,
    CMSG_POS_UPDATE               = 0x3F360154,
    SMSG_FACTION_STATE            = 0x08A1C126,
    AMSG_INT_PACKET               = 0x80CE5E46,
    AMSG_TEL_PACKET               = 0x84BB21F7,
    AMSG_CT_PACKET                = 0x3C565CED,
    AMSG_CTF_PACKET               = 0x88DBB381,
    SMSG_DELTA_UPDATE           = 0x12862153,//0x0BDE6B41,
    SMSG_SYSMSG_PACKET            = 0x6D2A6413,

	// revz
	SMSG_SEND_EFFECT			  = 0x8855434A,
	SMSG_CELL_POS_UPDATE		  = 0xC867AB5A,

};

#endif // OPENSWG_SOEPROTOCOL_OPCODES

