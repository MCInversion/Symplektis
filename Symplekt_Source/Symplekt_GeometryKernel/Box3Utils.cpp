#include "Box3Utils.h"
/* \file Box3Utils.cpp
*  \brief Implmentation of the external 3D box utilities
* 
\verbatim
-------------------------------------------------------------------------------
created  : 3.6.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

namespace Symplektis::GeometryKernel
{
	Vector3& SetVectorToBoxSize(Vector3& vector, const Box3& box)
	{
		if (box.IsEmpty())
		{
			return vector;
		}

		return vector.Set(
			(box.Max().X() - box.Min().X()),
			(box.Max().Y() - box.Min().Y()),
			(box.Max().Z() - box.Min().Z())
		);
	}

	Vector3& SetVectorToBoxHalfSize(Vector3& vector, const Box3& box)
	{
		if (box.IsEmpty())
		{
			return vector;
		}

		return vector.Set(
			0.5 * (box.Max().X() - box.Min().X()),
			0.5 * (box.Max().Y() - box.Min().Y()),
			0.5 * (box.Max().Z() - box.Min().Z())
		);
	}

	Vector3& SetVectorToBoxCenter(Vector3& vector, const Box3& box)
	{
		if (box.IsEmpty())
		{
			return vector;
		}

		return vector.Set(
			0.5 * (box.Max().X() + box.Min().X()),
			0.5 * (box.Max().Y() + box.Min().Y()),
			0.5 * (box.Max().Z() + box.Min().Z())
		);
	}

	bool IsPointInsideBox(const Vector3& vector, const Box3& box)
	{
		if (vector.X() < box.Min().X())
			return false;

		if (vector.X() > box.Max().X())
			return false;

		if (vector.Y() < box.Min().Y())
			return false;

		if (vector.Y() > box.Max().Y())
			return false;

		if (vector.Z() < box.Min().Z())
			return false;

		return (vector.Z() <= box.Max().Z());
	}

} // Symplektis::GeometryKernel