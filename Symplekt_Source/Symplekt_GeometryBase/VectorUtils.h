/*! \file VectorUtils.h
*   \brief Enums and utilities for safer manipulation with Cartesian coordinate objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 5.5.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once
#define C26812_PREFER_ENUM_CLASS_WARNING 26812

// >>>>>>>>>>>>>>>>>>> READ BEFORE USING THESE ENUMS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/* ========== Note: =====================================================================================
* 
* - Conventional enums implicitly convert to int, causing errors when we don't want them to act as integers.
* 
* - They export their enumerators to the surrounding scope causing potential name clashes.
* 
* - The underlying type of an enum cannot be specified causing confusion, compatibility problems and making 
*   forward declaration impossible.
* 
*		Bjarne Stroustrup, C++11 FAQ
* =======================================================================================================
* In our case:
*	- Forward declaration is not needed since these enums are only included once for every class in Symplekt_GeometryBase
*	- Names are designed within Symplektis::GeometryBase namespace so that they do not class
* 
*	- and finally, with Vector3 vec3;
* 
*	 Neither of:
*		vec3.SetCoordById(-7.35, X_COORD_2D);
*		vec3.SetCoordById(-7.35, static_cast<int>(X_COORD_2D));
*		vec3.SetCoordById(-7.35, 0);
*		vec3.GetCoordById(X_COORD_2D)
*		vec3.GetCoordById(0)
* 
*	 compile, so I'm disabling the C26812_PREFER_ENUM_CLASS_WARNING for classes that pass the enums in this header
*    as method parameters:
*		Vector2, Vector3, Matrix2, Matrix3.
* 
*	 BEWARE, However, that (X_COORD_3D == X_COORD_2D) compiles and returns true!
*			 Also:
*				vec3.GetCoordById(static_cast<eCood3D_ID>(0)); // compiles
*				vec3.GetCoordById(static_cast<eCoord3D_ID>(X_COORD_2D)); // compiles
* 
*			M. Cavarga (MCInversion), 10.6.2021
* 
*/

namespace Symplektis::GeometryBase
{
	/// dim values to avoid magic numbers
	constexpr size_t GEOMETRY_DIMENSION2 = 2;
	constexpr size_t GEOMETRY_DIMENSION3 = 3;
	constexpr size_t GEOMETRY_DIMENSION4 = 4;

	constexpr size_t GEOMETRY_DIMENSION_2x2 = 4;
	constexpr size_t GEOMETRY_DIMENSION_3x3 = 9;
	constexpr size_t GEOMETRY_DIMENSION_4x4 = 16;

	//-----------------------------------------------------------------------------
	/*! \enum eCoord2D_ID
	 *  \brief Coordinate identification of 2D vectors
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 3.6.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum eCoord2D_ID
	{
		  X_COORD_2D = 0 //!< 2D   X coordinate id
		, Y_COORD_2D = 1 //!< 2D   Y coordinate id
	};

	//-----------------------------------------------------------------------------
	/*! \enum eCoord3D_ID
	 *  \brief Coordinate identification of 3D vectors
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 3.6.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum eCoord3D_ID
	{
		  X_COORD_3D = 0 //!< 3D   X coordinate id
		, Y_COORD_3D = 1 //!< 3D   Y coordinate id
		, Z_COORD_3D = 2 //!< 3D   Z coordinate id
	};

	//-----------------------------------------------------------------------------
	/*! \enum eCoord4D_ID
	 *  \brief Coordinate identification of 4D vectors
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 3.6.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum eCoord4D_ID
	{
		  X_COORD_4D = 0 //!< 4D   X coordinate id
		, Y_COORD_4D = 1 //!< 4D   Y coordinate id
		, Z_COORD_4D = 2 //!< 4D   Z coordinate id
		, W_COORD_4D = 3 //!< 4D   W coordinate id
	};

	//-----------------------------------------------------------------------------
	/*! \enum e2x2_MatrixCoordIdentification
	 *  \brief Coordinate identification for 2x2 matrices
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 9.5.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum e2x2_MatrixCoordID
	{
		  MAT2_11 = 0, MAT2_12 = 1,
		  MAT2_21 = 2, MAT2_22 = 3
	};

	//-----------------------------------------------------------------------------
	/*! \enum e3x3_MatrixCoordIdentification
	 *  \brief Coordinate identification for 3x3 matrices
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 9.5.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum e3x3_MatrixCoordID
	{
		MAT3_11 = 0, MAT3_12 = 1, MAT3_13 = 2,
		MAT3_21 = 3, MAT3_22 = 4, MAT3_23 = 5,
		MAT3_31 = 6, MAT3_32 = 7, MAT3_33 = 8
	};

	//-----------------------------------------------------------------------------
	/*! \enum e4x4_MatrixCoordIdentification
	 *  \brief Coordinate identification for 4x4 matrices
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 9.5.2021
	 *
	 *  Used for better identification of coordinate index in array of values.
	 */
	 //-----------------------------------------------------------------------------
	enum e4x4_MatrixCoordID
	{
		MAT4_11 = 0,  MAT4_12 = 1,  MAT4_13 = 2,  MAT4_14 = 3,
		MAT4_21 = 4,  MAT4_22 = 5,  MAT4_23 = 6,  MAT4_24 = 7,
		MAT4_31 = 8,  MAT4_32 = 9,  MAT4_33 = 10, MAT4_34 = 11,
		MAT4_41 = 12, MAT4_42 = 13, MAT4_43 = 14, MAT4_44 = 15
	};

} // Symplektis::GeometryBase