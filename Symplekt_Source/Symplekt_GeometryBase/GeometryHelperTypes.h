/*! \file GeometryHelperTypes.h
*   \brief Iterators and other useful types for geometry representations
*
\verbatim
-------------------------------------------------------------------------------
created  : 26.8.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/
#pragma once

#include "Symplekt_UtilityGeneral/ContainerTypes.h"

#include <vector>

namespace Symplektis::GeometryBase
{
	/// forward declarations
	class Vertex;
	class Face;
	class Edge;
	class HalfEdge;
	class VertexNormal;

	// ======!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=======
	//       A discussion should take place whether iterators are really the reference types
	//       suitable for this job. There is, for example, an instance where an IsIsolated()
	//       test is called for a Vertex. This vertex should (likely under old C++ standards) 
	//       return m_HalfEdge == dummyEmptyHalfEdgeVector.end(), but this causes multiple 
	//       problems. Namely, dummyEmptyHalfEdgeVector needs to be compatible across sources
	//       (Vertex and geometry implementations) otherwise no such comparison is possible.
	//       Current solution is that geometry builders implement their own IsIsolated using
	//       the HalfEdges container itself for this comparison while passing HalfEdges 
	//       vector's end iterator to truly isolated vertices while they're constructed.
	// ======!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=======

	// ======!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=======
	//       EXPERIMENT RESULTS (Edit: Sept. 21st 2021):
	//       I tried changing std::vector<>::iterator's to std::shared_ptr<>'s. Google test framework,
	//       wasn't able to detect unit tests that instantiated geometries with shared_ptr reference
	//       types. The same results, but with additional heap corruption when omitting pointer deletion
	//       in mesh elements' destructors, can be seen when using raw pointers (e.g.: Vertex*, Face*,...).
	//       Not being able to verify iterator validity in mesh utils is what I consider a far better deal
	//       than spending another week on making these iterators safe. Critical entry/escape points
	//       should, however, be handled by try-catch blocks, so that potential crashes are caught.
	// ======!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=======

	//-----------------------------------------------------------------------------
	/*! \typedef VertexIterator
	 *  \brief std::vector<>::iterator for Vertex objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<Vertex>::iterator VertexIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef VertexConstIterator
		*  \brief std::vector<>::const_iterator for Vertex objects
		*
		*  \ingroup GEOMETRY_BASE
		*  \author M. Cavarga (MCInversion)
		*  \date 26.8.2021
		*/
		//-----------------------------------------------------------------------------
	typedef std::vector<Vertex>::const_iterator VertexConstIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef FaceIterator
	 *  \brief std::vector<>::iterator for Face objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<Face>::iterator FaceIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef FaceConstIterator
	*  \brief std::vector<>::const_iterator for Face objects
	*
	*  \ingroup GEOMETRY_BASE
	*  \author M. Cavarga (MCInversion)
	*  \date 26.8.2021
	*/
	//-----------------------------------------------------------------------------
	typedef std::vector<Face>::const_iterator FaceConstIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef EdgeIterator
	 *  \brief std::vector<>::iterator for Edge objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<Edge>::iterator EdgeIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef EdgeConstIterator
	 *  \brief std::vector<>::const_iterator for Edge objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<Edge>::const_iterator EdgeConstIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef HalfEdgeIterator
	 *  \brief std::vector<>::iterator for HalfEdge objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<HalfEdge>::iterator HalfEdgeIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef HalfEdgeConstIterator
	 *  \brief std::vector<>::const_iterator for HalfEdge objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 26.8.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<HalfEdge>::const_iterator HalfEdgeConstIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef VertexNormalIterator
	 *  \brief std::vector<>::iterator for VertexNormal objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 12.10.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<VertexNormal>::iterator VertexNormalIterator;

	//-----------------------------------------------------------------------------
	/*! \typedef VertexNormalConstIterator
	 *  \brief std::vector<>::const_iterator for VertexNormal objects
	 *
	 *  \ingroup GEOMETRY_BASE
	 *  \author M. Cavarga (MCInversion)
	 *  \date 12.10.2021
	 */
	 //-----------------------------------------------------------------------------
	typedef std::vector<VertexNormal>::const_iterator VertexNormalConstIterator;

	//
	// ====================== Geometry Containers ==================================
	//

	///=============================================================================
	/// \typedef VertexContainer
	/// \brief A linear iterable container for Vertex data identified by a UUID.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::UniqueIndexedContainer<Vertex> VertexContainer;

	///=============================================================================
	/// \typedef FaceContainer
	/// \brief A linear iterable container for Face data identified by a UUID.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::UniqueIndexedContainer<Face> FaceContainer;

	///=============================================================================
	/// \typedef EdgeContainer
	/// \brief A linear iterable container for Edge data identified by a UUID.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::UniqueIndexedContainer<Edge> EdgeContainer;

	///=============================================================================
	/// \typedef HalfEdgeContainer
	/// \brief A linear iterable container for HalfEdge data identified by a UUID.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::UniqueIndexedContainer<HalfEdge> HalfEdgeContainer;

	///=============================================================================
	/// \typedef VertexNormalContainer
	/// \brief A linear iterable container for VertexNormal data identified by a UUID.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::UniqueIndexedContainer<VertexNormal> VertexNormalContainer;

	//
	// ======================== Geometry Handles ===================================
	//

	///=============================================================================
	/// \typedef VertexHandle
	/// \brief A handle object for ContainerIndex also containing a reference to VertexContainer.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::ContainerIndexHandle<Vertex> VertexHandle;

	/// \brief A null VertexHandle pointing no a non-existent position in a VertexContainer.
	constexpr VertexHandle NULL_VERTEX{};

	///=============================================================================
	/// \typedef FaceHandle
	/// \brief A handle object for ContainerIndex also containing a reference to FaceContainer.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::ContainerIndexHandle<Face> FaceHandle;

	/// \brief A null FaceHandle pointing no a non-existent position in a FaceContainer.
	constexpr FaceHandle NULL_FACE{};
	
	///=============================================================================
	/// \typedef EdgeHandle
	/// \brief A handle object for ContainerIndex also containing a reference to EdgeContainer.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::ContainerIndexHandle<Edge> EdgeHandle;

	/// \brief A null EdgeHandle pointing no a non-existent position in a EdgeContainer.
	constexpr EdgeHandle NULL_EDGE{};

	///=============================================================================
	/// \typedef HalfEdgeHandle
	/// \brief A handle object for ContainerIndex also containing a reference to HalfEdgeContainer.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::ContainerIndexHandle<HalfEdge> HalfEdgeHandle;

	/// \brief A null HalfEdgeHandle pointing no a non-existent position in a HalfEdgeContainer.
	constexpr HalfEdgeHandle NULL_HALF_EDGE{};

	///=============================================================================
	/// \typedef VertexNormalHandle
	/// \brief A handle object for ContainerIndex also containing a reference to VertexNormalContainer.
	///
	/// \ingroup GEOMETRY_BASE
	///
	/// \author M. Cavarga (MCInversion)
	/// \date   24.6.2022
	/// 
	///=============================================================================
	typedef Util::ContainerIndexHandle<VertexNormal> VertexNormalHandle;

	/// \brief A null VertexNormalHandle pointing no a non-existent position in a VertexNormalContainer.
	constexpr VertexNormalHandle NULL_VERTEX_NORMAL{};

} // Symplektis::GeometryBase