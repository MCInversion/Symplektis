/*! \file Box2.h
*   \brief Declaration of 3D box class
*
\verbatim
-------------------------------------------------------------------------------
created  : 6.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Vector3.h"

#include <vector>

namespace Symplektis::GeometryBase
{
	//=============================================================================
	/// \class Box3
	/// \brief A class acting as an axis-aligned 3D box (min-max)
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date 2.6.2021
	//=============================================================================
	class Box3
	{
	public:
		/// @{
		/// \name Default special members
		Box3() = default;
		~Box3() = default;
		Box3(Box3&&) = default;
		Box3(Box3&) = default;
		Box3& operator= (Box3&&) = default;

		
		/// @{
		/// \name Constructors

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] min            minimum point
		*   \param[in] max            maximum point
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 2.6.2021
		*
		*   Initialize Box3 from given MIN and MAX points.
		*/
		//-----------------------------------------------------------------------------
		Box3(const Vector3& min, const Vector3& max)
			: m_Min(min)
			, m_Max(max)
		{
		}

		//-----------------------------------------------------------------------------
		/*! \brief Set constructor
		*   \param[in] vectors   Points to be expanded by (std::vector<Vector3>)
		*
		*   \author M. Cavarga (MCInversion)
		*   \date 3.6.2021
		*
		*   Initialize Box3 from a vector of points.
		*/
		//-----------------------------------------------------------------------------
		explicit Box3(const std::vector<Vector3>& vectors)
		{
			Set(vectors);
		}

		//-----------------------------------------------------------------------------
		/*! \brief Standard assignment operator.
		*   \param[in] box     Box3 to be copied.
		*   \return Reference to this Box3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   6.5.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& operator=(const Box3& box)
		{
			if (this == &box)
				return *this;

			Set(box);
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*! \brief IsEmpty
		*   \return true if this Box3 does not contain any space
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsEmpty() const;

		//-----------------------------------------------------------------------------
		/*! \brief Intersects another box
		*   \param[in] box    another Box3 to be intersected
		*   \return true if this Box3 intersects box
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IntersectsBox(const Box3& box) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 3D axis aligned boxes without tolerance.
		*   \param[in] box    Compared Box3.
		*   \return True when box min-maxes are equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  2.6.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator==(const Box3& box) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of 3D axis aligned boxes with tolerance.
		*   \param[in] box    Compared Box3.
		*   \return True when boxes are equal up to Symplektis::Util::GetCoordinateTolerance(), otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool EqualsWithTolerance(const Box3& box) const;

		//-----------------------------------------------------------------------------
		/*! \brief Comparison of boxes without tolerance.
		*   \param[in] box    Compared Box3.
		*   \return True when box min maxes are not equal, otherwise false.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  2.6.2021
		*
		*   Be careful, this method works without tolerance!
		*/
		//-----------------------------------------------------------------------------
		bool operator!=(const Box3& box) const;

		//-----------------------------------------------------------------------------
		/*! \brief Get the min vector reference.
		*   \return reference to Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
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
		*   \date   2.6.2021
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
		*   \date   2.6.2021
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
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& Max() const
		{
			return m_Max;
		}

		//-----------------------------------------------------------------------------
		/*! \brief Get the min or max vector reference depending on index.
		*	\param[in] id     index (0 -> min, other integers -> max)
		*   \return reference to Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] const Vector3& GetMinOrMaxById(const int& id) const;

		//-----------------------------------------------------------------------------
		/*! \brief Set the min or max vector reference depending on index.
		*	\param[in] id     index (0 -> min, other integers -> max)
		*	\param[in] vec    vector value to be assigned to min or max
		*   \return reference to Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Vector3& SetMinOrMaxById(const int& id, const Vector3& vec);

		//-----------------------------------------------------------------------------
		/*! \brief Get the center point of this box.
		*   \return center Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Vector3 GetCenter() const;

		//-----------------------------------------------------------------------------
		/*! \brief Get the size vector (max - min) of this box.
		*   \return size Vector3.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] Vector3 GetSize() const;

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from min and max vectors (Vector3)
		*   \param[in] min   minimum Vector3
		*   \param[in] max   maximum Vector3
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& Set(const Vector3& min, const Vector3& max)
		{
			m_Min = min; m_Max = max;
			return *this;
		}

		//-----------------------------------------------------------------------------
		/*!\brief Initialize from Box3.
		*   \param[in] box   Box3
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   2.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& Set(const Box3& box)
		{
			return Set(
				box.m_Min,
				box.m_Max
			);
		}

		//-----------------------------------------------------------------------------
		/*!\brief Clear & initialize from a Vector of points
		*   \param[in] vectors   Points to be expanded by (std::vector<Vector3>)
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		* 
		*   this method resets m_Min and m_Max!
		*/
		//-----------------------------------------------------------------------------
		Box3& Set(const std::vector<Vector3>& vectors)
		{
			Clear();
			return ExpandByPoints(vectors);
		}

		//-----------------------------------------------------------------------------
		/*!\brief Expand Box3's min and max vectors by given point.
		*   \param[in] vec   Point to be expanded by (Vector3)
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& ExpandByPoint(const Vector3& vec);

		//-----------------------------------------------------------------------------
		/*!\brief Expand Box3's min and max vectors by given vector of points.
		*   \param[in] vectors   Points to be expanded by (std::vector<Vector3>)
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& ExpandByPoints(const std::vector<Vector3>& vectors);

		//-----------------------------------------------------------------------------
		/*!\brief Clears this Box3's min and max vectors resetting them to empty state
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& Clear();

		//-----------------------------------------------------------------------------
		/*!\brief Expand Box3's min and max vectors by a given offset value
		*   \param[in] offset      value to be added to this box's bounds
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& ExpandByOffset(const double& offset);

		//-----------------------------------------------------------------------------
		/*!\brief Expand Box3's min and max vectors by a given offset vector
		*   \param[in] offsets   offset Vector3
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& ExpandByOffsets(const Vector3& offsets);

		//-----------------------------------------------------------------------------
		/*!\brief Expand Box3's min and max vectors by a given factor
		*   \param[in] factor     factor value this box's to be expanded by
		*   \return reference to this Box3
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   3.6.2021
		*/
		//-----------------------------------------------------------------------------
		Box3& ExpandByFactor(const double& factor);

		//-----------------------------------------------------------------------------
		/*! \brief Tests if 3D vector is inside this 3D bounding box
		*   \param[in] vec   vector
		*   \return true if vector is inside this box
		*
		*   \author M. Cavarga (MCInversion)
		*   \date  3.6.2021
		*/
		//-----------------------------------------------------------------------------
		[[nodiscard]] bool IsPointInside(const Vector3& vec) const;

	private:

		Vector3 m_Min{ DBL_MAX, DBL_MAX, DBL_MAX };
		Vector3 m_Max{ -DBL_MAX, -DBL_MAX, -DBL_MAX };
	};

} // Symplektis::GeometryBase