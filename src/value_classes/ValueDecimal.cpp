//-----------------------------------------------------------------------------
//
//	ValueDecimal.cpp
//
//	Base class for all OpenZWave Value Classes
//
//	Copyright (c) 2010 Mal Lansell <openzwave@lansell.org>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#include "tinyxml.h"
#include "ValueDecimal.h"
#include "Msg.h"
#include "Log.h"

using namespace OpenZWave;


//-----------------------------------------------------------------------------
// <ValueDecimal::ValueDecimal>
// Constructor
//-----------------------------------------------------------------------------
ValueDecimal::ValueDecimal
(
	uint8 const _nodeId,
	uint8 const _commandClassId,
	uint8 const _instance,
	uint8 const _index,
	string const& _label,
	bool const _bReadOnly,
	string const& _value
):
	Value( _nodeId, _commandClassId, _instance, _index, _label, _bReadOnly ),
	m_value( _value )
{
}

//-----------------------------------------------------------------------------
// <ValueDecimal::ValueDecimal>
// Constructor (from XML)
//-----------------------------------------------------------------------------
ValueDecimal::ValueDecimal
(
	TiXmlElement* _pValueElement
):
	Value( _pValueElement )
{
	char const* str = _pValueElement->Attribute( "value" );
	if( str )
	{
		m_value = str;
	}
}

//-----------------------------------------------------------------------------
// <ValueDecimal::WriteXML>
// Write ourselves to an XML document
//-----------------------------------------------------------------------------
void ValueDecimal::WriteXML
(
	TiXmlElement* _pValueElement
)
{
	Value::WriteXML( _pValueElement );
	_pValueElement->SetAttribute( "value", m_value.c_str() );
}

//-----------------------------------------------------------------------------
// <ValueDecimal::Set>
// Set a new value in the device
//-----------------------------------------------------------------------------
bool ValueDecimal::Set
(
	string const& _value
)
{
	if( _value == m_value )
	{
		// Value already set
		return true;
	}

	m_pending = _value;
	return Value::Set();
}

//-----------------------------------------------------------------------------
// <ValueDecimal::OnValueChanged>
// A value in a device has changed
//-----------------------------------------------------------------------------
void ValueDecimal::OnValueChanged
(
	string const& _value
)
{
	if( _value == m_value )
	{
		// Value already set
		return;
	}

	m_value = _value;
	Value::OnValueChanged();
}



