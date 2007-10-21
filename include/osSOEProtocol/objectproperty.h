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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTPROPERTY
#define OPENSWG_SOEPROTOCOL_OBJECTPROPERTY

#include <osSOEProtocol/export.h>
#include <gsCore/callback.h>
#include <gsCore/log.h>
#include <gsCore/types.h>
#include <boost/shared_ptr.hpp>

#include <string>

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT ObjectProperty
	{
	public:
		virtual ~ObjectProperty() {}
		virtual void setType(const uint type) { m_type = type; }
		virtual const uint &getType() const { return m_type; }

		virtual void copyFrom(const ObjectProperty& otherProperty) = 0;
		const std::string &getName() const { return m_name; }
		const std::string &getLabel() const { return m_label; }
		const std::string &getDescription() const { return m_description; }

		bool isReadOnly() { return m_readOnly; }

		void setReadOnly(bool readOnly) { m_readOnly = readOnly; }
		
		void setGroup(const std::string& name) { m_group = name; }
		const std::string& getGroup() const { return m_group; }

	protected:
		ObjectProperty(const std::string& name,
					   const std::string& label,
					   const std::string& description,
					   const std::string& group,
					   bool readOnly = false)
		: m_name(name)
		, m_label(label)
		, m_description(description)
		, m_readOnly(readOnly)
		{
			group.empty() ? setGroup("Base") : setGroup(group);
		}

		std::string m_group;

	//	virtual ~ObjectProperty() {}

	private:
		uint m_type;
		std::string m_name;
		std::string m_label;
		std::string m_description;
		bool m_readOnly;
	};

	template <class SetType, class GetType>
	class OS_SOEPROTOCOL_EXPORT GenericObjectProperty : public ObjectProperty
	{
	public:
		GenericObjectProperty(const std::string &name,
							  const std::string &label,
							  CBFunctor1<SetType> &set,
							  CBFunctor0wRet<GetType> &get,
							  const std::string desc,
							  const std::string group,
							  bool readOnly = false) 
		: m_setPropertyFunctor(set)
		, m_getPropertyFunctor(get)
		, ObjectProperty(name, label, desc, group, readOnly)
		{}

		virtual void copyFrom(const ObjectProperty& otherProperty)
		{
			if (getType() != otherProperty.getType())
			{
				gsCore::Log::getMainLog().error("Object property types incompatible. Aborting copy.");
			}

			const GenericObjectProperty<SetType, GetType>& prop =
				static_cast<const GenericObjectProperty<SetType, GetType>& >(otherProperty);

			setValue(prop.getValue());
		}

		void setValue(SetType value)
		{
			!isReadOnly() ? m_setPropertyFunctor(value) : gsCore::Log::getMainLog().error("Attempted to set the value of a read-only property.");
		}

		GetType getValue() const { return m_getPropertyFunctor(); }

	protected:
		virtual ~GenericObjectProperty() {}

	private:
		CBFunctor1<SetType> m_setPropertyFunctor;
		CBFunctor0wRet<GetType> m_getPropertyFunctor;
	};
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTPROPERTY