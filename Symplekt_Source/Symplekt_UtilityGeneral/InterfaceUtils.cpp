/*! \file  InterfaceUtils.cpp
 *  \brief Implementations of generic interface methods
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   17.11.2021
 *
 */

#include "InterfaceUtils.h"

namespace Symplektis::Util
{
	void SymplektUnknownObject::DeleteInterface(SymplektUnknownObject& obj)
	{
        if (obj.IsNull())
            return;

        obj.SetNull();
	}

	SymplektUnknownObject::SymplektUnknownObject(const SymplektUnknownObject& from)
	{		
		if (auto* fromObj = from.GetPointer(); fromObj != nullptr)
		{
			SetPointer(fromObj->Clone());
			return;
		}

		SetPointer(nullptr);
	}

	SymplektUnknownObject::SymplektUnknownObject(SymplektUnknownObject&& from) noexcept
	{
		SetPointer(from.GetPointer());
		from.SetPointer(nullptr);
	}
	
    SymplektUnknownObject::SymplektUnknownObject(const ISymplektBaseObject& from)
	{
		auto* pObject = from.Clone();
		SetPointer(pObject);
	}

	SymplektUnknownObject& SymplektUnknownObject::operator=(const SymplektUnknownObject& other)
	{
		if (this == &other)
			return *this;		
		
		if (auto* fromObj = other.GetPointer(); fromObj != nullptr)
			SetPointer(fromObj->Clone());
		else
			SetPointer(nullptr);
		
		return *this;
	}

	SymplektUnknownObject& SymplektUnknownObject::operator=(SymplektUnknownObject&& other) noexcept
	{
		DeletePointer();

		SetPointer(other.GetPointer());
		other.SetPointer(nullptr);
		return *this;
	}

	void SymplektUnknownObject::SetNull()
	{
		DeletePointer();
		m_pObject = nullptr;
	}
	
} // Symplektis::Util