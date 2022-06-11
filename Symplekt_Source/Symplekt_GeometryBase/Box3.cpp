/*! \file Box3.cpp
*   \brief Implmentation of the 3D box class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#include "Box3.h"

#include "Vector3Utils.h"

namespace Symplektis::GeometryBase
{
	bool Box3::IsEmpty() const
	{
		if (m_Min.X() >= m_Max.X())
			return true;

		if (m_Min.Y() >= m_Max.Y())
			return true;

		return (m_Min.Y() > m_Max.Y());
	}

	bool Box3::IntersectsBox(const Box3& box) const
	{
		if (box.m_Max.X() < m_Min.X() || box.m_Min.X() > m_Max.X())
			return false;

		if (box.m_Max.Y() < m_Min.Y() || box.m_Min.Y() > m_Max.Y())
			return false;

		return (box.m_Max.Z() >= m_Min.Z() && box.m_Min.Z() <= m_Max.Z());
	}

	bool Box3::operator==(const Box3& box) const
	{
		if (m_Min != box.m_Min)
			return false;

		return (m_Max == box.m_Max);
	}

	bool Box3::EqualsWithTolerance(const Box3& box) const
	{
		if (!m_Min.EqualsWithTolerance(box.m_Min))
			return false;

		return (m_Max.EqualsWithTolerance(box.m_Max));
	}

	bool Box3::operator!=(const Box3& box) const
	{
		if (m_Min != box.m_Min)
			return true;

		return (m_Max != box.m_Max);
	}

	const Vector3& Box3::GetMinOrMaxById(const int& id) const
	{
		if (id == 0)
			return m_Min;

		return m_Max;
	}

	Vector3& Box3::SetMinOrMaxById(const int& id, const Vector3& vec)
	{
		if (id == 0)
		{
			m_Min.Set(vec);
			return m_Min;
		}

		m_Max.Set(vec);
		return m_Max;
	}

	Vector3 Box3::GetCenter() const
	{
		return Vector3(0.5 * (m_Max + m_Min));
	}

	Vector3 Box3::GetSize() const
	{
		return Vector3(m_Max - m_Min);
	}

	Box3& Box3::ExpandByPoint(const Vector3& vec)
	{
		m_Min.Min(vec);
		m_Max.Max(vec);

		return *this;
	}

	Box3& Box3::ExpandByPoints(const std::vector<Vector3>& vectors)
	{
		for (auto& vec : vectors)
			ExpandByPoint(vec);

		return *this;
	}

	Box3& Box3::Clear()
	{
		m_Min.Set(DBL_MAX, DBL_MAX, DBL_MAX);
		m_Max.Set(-DBL_MAX, -DBL_MAX, -DBL_MAX);
		return *this;
	}

	Box3& Box3::ExpandByOffset(const double& offset)
	{
		m_Min -= offset;
		m_Max += offset;
		return *this;
	}

	Box3& Box3::ExpandByOffsets(const Vector3& offsets)
	{
		m_Min -= offsets;
		m_Max += offsets;
		return *this;
	}

	Box3& Box3::ExpandByFactor(const double& factor)
	{
		const Vector3 halfSize = 0.5 * GetSize();
		const Vector3 offsetVector = (factor - 1.0) * halfSize;
		ExpandByOffsets(offsetVector);

		return *this;
	}

	bool Box3::IsPointInside(const Vector3& vec) const
	{
		if (vec.X() < m_Min.X())
			return false;

		if (vec.X() > m_Max.X())
			return false;

		if (vec.Y() < m_Min.Y())
			return false;

		if (vec.Y() > m_Max.Y())
			return false;

		if (vec.Z() < m_Min.Z())
			return false;

		return (vec.Z() <= m_Max.Z());
	}



} // Symplektis::GeometryBase