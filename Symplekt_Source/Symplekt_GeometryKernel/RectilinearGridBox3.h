/*! \file RectilinearGridBox3.h
*   \brief 3D Box aligned with a global rectilinear grid with given cell size.
*
\verbatim
-------------------------------------------------------------------------------
created  : 21.10.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#pragma once

#include "Vector3.h"

#include "Symplekt_UtilityGeneral/Assert.h"

#include <cmath>

namespace Symplektis::GeometryKernel
{
	// forward declarations
	class Box3;

	//=============================================================================
	/// \class RectilinearGridBox3
	/// \brief A class acting as an axis-aligned 3D box (min-max) also aligned with a global rectilinear grid with a given cell size.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 21.10.2021
	//=============================================================================
	class RectilinearGridBox3
	{
	public:
		/// @{
		/// \name Default special members
		RectilinearGridBox3() = default;
		~RectilinearGridBox3() = default;
		RectilinearGridBox3(RectilinearGridBox3&&) = default;
		RectilinearGridBox3(RectilinearGridBox3&) = default;
		RectilinearGridBox3& operator= (RectilinearGridBox3&) = default;
		RectilinearGridBox3& operator= (RectilinearGridBox3&&) = default;

		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] cellSize        cell size of rectilinear (voxel) grid.
		*   \param[in] min             minimum point (will adjust to global grid).
		*   \param[in] max             maximum point (will adjust to global grid).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 23.10.2021
		*/
		//-----------------------------------------------------------------------------
		RectilinearGridBox3(const double& cellSize, const Vector3& min, const Vector3& max)
			: m_CellSize(std::fabs(cellSize))
		{
			if (m_CellSize <= DBL_EPSILON)
			{
				MSG_CHECK(false, "RectilinearGridBox3: Cannot construct a RectilinearGridBox3 with a non-positive cell size!!!\n");
			}

			Set(min, max);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] box3        a generic Box3 to be used for min and max points
		*   \param[in] cellSize    cell size of rectilinear (voxel) grid.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 23.10.2021
		*/
		//-----------------------------------------------------------------------------
		RectilinearGridBox3(const double& cellSize, const Box3& box3)
			: m_CellSize(std::fabs(cellSize))
		{
			if (m_CellSize <= DBL_EPSILON)
			{
				MSG_CHECK(false, "RectilinearGridBox3: Cannot construct a RectilinearGridBox3 with a non-positive cell size!!!\n");
			}

			Set(box3);
		}

		/// @{
		/// \name Setters

		//-----------------------------------------------------------------------------
		/*! \brief Set from min and max vectors.
		*   \param[in] min             minimum point (will adjust to global grid).
		*   \param[in] max             maximum point (will adjust to global grid).
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 23.10.2021
		*/
		//-----------------------------------------------------------------------------
		RectilinearGridBox3& Set(const Vector3& min, const Vector3& max);

		//-----------------------------------------------------------------------------
		/*! \brief Set from a Box3 object.
		*   \param[in] box3        a generic Box3 to be used for min and max points
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 23.10.2021
		*/
		//-----------------------------------------------------------------------------
		RectilinearGridBox3& Set(const Box3& box3);

		/// @{
		/// \name Getters

		//-----------------------------------------------------------------------------
		/*! \brief Get the min vector reference.
		*   \return reference to Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		Vector3& Min()
		{
			return m_Min;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the min vector const reference.
		*   \return Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& Min() const
		{
			return m_Min;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the max vector reference.
		*   \return reference to Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		Vector3& Max()
		{
			return m_Max;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the max vector const reference.
		*   \return Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& Max() const
		{
			return m_Max;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the center point of this box.
		*   \return center Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Vector3 GetCenter() const;

		//-----------------------------------------------------------------------------
		/*! \brief Get the size vector (max - min) of this box.
		*   \return size Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   23.10.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Vector3 GetSize() const;
	
	private:

		double m_CellSize{0.0};                                //>! (cube) voxel cell size

		Vector3 m_Min{ DBL_MAX, DBL_MAX, DBL_MAX };      //>! min vector of bounding box
		Vector3 m_Max{ -DBL_MAX, -DBL_MAX, -DBL_MAX };   //>! max vector of bounding box
	};

	
} // Symplektis::GeometryKernel