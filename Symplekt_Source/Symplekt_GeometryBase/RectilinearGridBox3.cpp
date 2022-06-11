/*! \file RectilinearGridBox3.cpp
*   \brief Implementation of a 3D Box aligned with a global rectilinear grid with given cell size.
*
\verbatim
-------------------------------------------------------------------------------
created  : 21.10.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "RectilinearGridBox3.h"

#include "Box3.h"
#include "Vector3Utils.h"

#include<cmath>

namespace Symplektis::GeometryBase
{
	RectilinearGridBox3& RectilinearGridBox3::Set(const Vector3& min, const Vector3& max)
	{
		const double nXMinus = std::floor(min.X() / m_CellSize);
		const double nXPlus = std::ceil(max.X() / m_CellSize);

		const double nYMinus = std::floor(min.Y() / m_CellSize);
		const double nYPlus = std::ceil(max.Y() / m_CellSize);

		const double nZMinus = std::floor(min.Z() / m_CellSize);
		const double nZPlus = std::ceil(max.Z() / m_CellSize);

		m_Min = Vector3(nXMinus, nYMinus, nZMinus) * m_CellSize;
		m_Max = Vector3(nXPlus, nYPlus, nZPlus) * m_CellSize;

		return *this;
	}

	RectilinearGridBox3& RectilinearGridBox3::Set(const Box3& box3)
	{
		const auto& min = box3.Min();
		const auto& max = box3.Max();

		return Set(min, max);
	}

	Vector3 RectilinearGridBox3::GetCenter() const
	{
		return Vector3(0.5 * (m_Max + m_Min));
	}

	Vector3 RectilinearGridBox3::GetSize() const
	{
		return Vector3(m_Max - m_Min);
	}

} // Symplektis::GeometryBase