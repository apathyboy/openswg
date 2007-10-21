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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTPROPERTYTYPES
#define OPENSWG_SOEPROTOCOL_OBJECTPROPERTYTYPES

#include <osSOEProtocol/export.h>
#include <gsCore/callback.h>
#include <osSOEProtocol/objectproperty.h>

namespace osSOEProtocol
{
	enum OS_SOEPROTOCOL_EXPORT PropertyType
	{
		PROP_FLOAT = 0,
		PROP_UINT,
		PROP_UINT8,
		PROP_UINT16,
		PROP_UINT32,
		PROP_UINT64,
		PROP_STRING,
		PROP_UNICODE,
		PROP_BOOLEAN
	};

	class OS_SOEPROTOCOL_EXPORT FloatObjectProperty : public GenericObjectProperty<float,float>
	{
	public:
		FloatObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<float> set, CBFunctor0wRet<float> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<float,float>(name, label, set, get, description, group)
		{
			setType(PROP_FLOAT);
		}

	protected:
		virtual ~FloatObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT UintObjectProperty : public GenericObjectProperty<uint,uint>
	{
	public:
		UintObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<uint> set, CBFunctor0wRet<uint> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint,uint>(name, label, set, get, description, group)
		{
			setType(PROP_UINT);
		}

	protected:
		virtual ~UintObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT Uint8ObjectProperty : public GenericObjectProperty<uint8,uint8>
	{
	public:
		Uint8ObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<uint8> set, CBFunctor0wRet<uint8> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint8,uint8>(name, label, set, get, description, group)
		{
			setType(PROP_UINT8);
		}

	protected:
		virtual ~Uint8ObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT Uint16ObjectProperty : public GenericObjectProperty<uint16,uint16>
	{
	public:
		Uint16ObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<uint16> set, CBFunctor0wRet<uint16> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint16,uint16>(name, label, set, get, description, group)
		{
			setType(PROP_UINT16);
		}

	protected:
		virtual ~Uint16ObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT Uint32ObjectProperty : public GenericObjectProperty<uint32,uint32>
	{
	public:
		Uint32ObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<uint32> set, CBFunctor0wRet<uint32> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint32,uint32>(name, label, set, get, description, group)
		{
			setType(PROP_UINT32);
		}

	protected:
		virtual ~Uint32ObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT Uint64ObjectProperty : public GenericObjectProperty<uint64,uint64>
	{
	public:
		Uint64ObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<uint64> set, CBFunctor0wRet<uint64> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint64,uint64>(name, label, set, get, description, group)
		{
			setType(PROP_UINT);
		}

	protected:
		virtual ~Uint64ObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT StringObjectProperty : public GenericObjectProperty<std::string,std::string>
	{
	public:
		StringObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<std::string> set, CBFunctor0wRet<std::string> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<std::string,std::string>(name, label, set, get, description, group)
		{
			setType(PROP_STRING);
		}

	protected:
		virtual ~StringObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT UnicodeObjectProperty : public GenericObjectProperty<std::wstring,std::wstring>
	{
	public:
		UnicodeObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<std::wstring> set, CBFunctor0wRet<std::wstring> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<std::wstring,std::wstring>(name, label, set, get, description, group)
		{
			setType(PROP_UNICODE);
		}

	protected:
		virtual ~UnicodeObjectProperty() {}
	};

	class OS_SOEPROTOCOL_EXPORT BooleanObjectProperty : public GenericObjectProperty<bool,bool>
	{
	public:
		BooleanObjectProperty(const std::string& name, const std::string& label,
			CBFunctor1<bool> set, CBFunctor0wRet<bool> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<bool,bool>(name, label, set, get, description, group)
		{
			setType(PROP_BOOLEAN);
		}

	protected:
		virtual ~BooleanObjectProperty() {}
	};
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTPROPERTYTYPES

