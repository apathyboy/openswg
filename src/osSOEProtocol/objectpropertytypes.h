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

#include <functional>

#include <osSOEProtocol/objectproperty.h>

namespace osSOEProtocol
{
	enum PropertyType
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

	class FloatObjectProperty : public GenericObjectProperty<float,float>
	{
	public:
		FloatObjectProperty(const std::string& name, const std::string& label,
			std::function<void (float)> set, std::function<float()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<float,float>(name, label, set, get, description, group)
		{
			setType(PROP_FLOAT);
		}

	protected:
		virtual ~FloatObjectProperty() {}
	};

	class UintObjectProperty : public GenericObjectProperty<uint32_t,uint32_t>
	{
	public:
		UintObjectProperty(const std::string& name, const std::string& label,
			std::function<void (uint32_t)> set, std::function<uint32_t()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint32_t,uint32_t>(name, label, set, get, description, group)
		{
			setType(PROP_UINT);
		}

	protected:
		virtual ~UintObjectProperty() {}
	};

	class Uint8ObjectProperty : public GenericObjectProperty<uint8_t,uint8_t>
	{
	public:
		Uint8ObjectProperty(const std::string& name, const std::string& label,
			std::function<void (uint8_t)> set, std::function<uint8_t()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint8_t,uint8_t>(name, label, set, get, description, group)
		{
			setType(PROP_UINT8);
		}

	protected:
		virtual ~Uint8ObjectProperty() {}
	};

	class Uint16ObjectProperty : public GenericObjectProperty<uint16_t,uint16_t>
	{
	public:
		Uint16ObjectProperty(const std::string& name, const std::string& label,
			std::function<void (uint16_t)> set, std::function<uint16_t()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint16_t,uint16_t>(name, label, set, get, description, group)
		{
			setType(PROP_UINT16);
		}

	protected:
		virtual ~Uint16ObjectProperty() {}
	};

	class Uint32ObjectProperty : public GenericObjectProperty<uint32_t,uint32_t>
	{
	public:
		Uint32ObjectProperty(const std::string& name, const std::string& label,
			std::function<void (uint32_t)> set, std::function<uint32_t()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint32_t,uint32_t>(name, label, set, get, description, group)
		{
			setType(PROP_UINT32);
		}

	protected:
		virtual ~Uint32ObjectProperty() {}
	};

	class Uint64ObjectProperty : public GenericObjectProperty<uint64_t,uint64_t>
	{
	public:
		Uint64ObjectProperty(const std::string& name, const std::string& label,
			std::function<void (uint64_t)> set, std::function<uint64_t()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<uint64_t,uint64_t>(name, label, set, get, description, group)
		{
			setType(PROP_UINT);
		}

	protected:
		virtual ~Uint64ObjectProperty() {}
	};

	class StringObjectProperty : public GenericObjectProperty<std::string,std::string>
	{
	public:
		StringObjectProperty(const std::string& name, const std::string& label,
			std::function<void (std::string)> set, std::function<std::string()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<std::string,std::string>(name, label, set, get, description, group)
		{
			setType(PROP_STRING);
		}

	protected:
		virtual ~StringObjectProperty() {}
	};

	class UnicodeObjectProperty : public GenericObjectProperty<std::wstring,std::wstring>
	{
	public:
		UnicodeObjectProperty(const std::string& name, const std::string& label,
			std::function<void (std::wstring)> set, std::function<std::wstring()> get,
			const std::string &description = "", const std::string &group = "")
		: GenericObjectProperty<std::wstring,std::wstring>(name, label, set, get, description, group)
		{
			setType(PROP_UNICODE);
		}

	protected:
		virtual ~UnicodeObjectProperty() {}
	};

	class BooleanObjectProperty : public GenericObjectProperty<bool,bool>
	{
	public:
		BooleanObjectProperty(const std::string& name, const std::string& label,
			std::function<void (bool)> set, std::function<bool()> get,
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

