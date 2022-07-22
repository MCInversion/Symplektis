/*! \file Face.cpp
*   \brief 3D face implementation for structured mesh geometry objects
*
\verbatim
-------------------------------------------------------------------------------
created  : 29.7.2021 : M.Cavarga (MCInversion) :
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
\endverbatim
*/

#include "Face.h"

#include "Symplekt_UtilityGeneral/Assert.h"
#include "Symplekt_UtilityGeneral/ToleranceSettings.h"

#include "FaceUtils.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3Utils.h"
#include "Vertex.h"
#include "VertexNormal.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Poly2Tri_CDT.h"

#include <ctime>
#include <algorithm>

namespace Symplektis::GeometryKernel
{
	bool Face::operator==(const Face& face) const
	{
		return (m_HalfEdge == face.m_HalfEdge);
	}

    Face& Face::Set(const std::vector<VertexHandle>& vertices)
    {
        if (vertices.size() < 3) // degenerate (single-line or single-point) Face
        {
            MSG_CHECK(false, "Face::Set: Attempting to instantiate a Face with < 3 vertices!\n");
            return *this;
        }
		
        if (vertices.size() == 3) // triangle (trivial)
        {
            m_Triangulation = { {vertices[0], vertices[1], vertices[2]} };
            return *this;
        }
		
        if (vertices.size() == 4) // quad
        {
            const Vector3 e1 = vertices[1].GetElement().Position() - vertices[0].GetElement().Position();
            const Vector3 e2 = vertices[2].GetElement().Position() - vertices[0].GetElement().Position();
            const Vector3 e3 = vertices[3].GetElement().Position() - vertices[0].GetElement().Position();
            const Vector3 c21 = CrossProduct(e2, e1);
            const Vector3 c23 = CrossProduct(e2, e3);
            if (DotProduct(c21, c23) > Util::GetProductTolerance())
            {
                m_Triangulation = {
                    {vertices[0], vertices[1], vertices[3]},
                    {vertices[1], vertices[2], vertices[3]}
                };
                return *this;
            }

            m_Triangulation = {
                {vertices[0], vertices[1], vertices[2]},
                {vertices[0], vertices[2], vertices[3]}
            };

            return *this;
        }

        // ============= initializing a "penta-or-more-gon" ((n > 4)-gon): =============
        // ============= Note: using Poly2Tri util library for triangulation ===========

        const auto projections = ComputeProjectionsAlongNormal(vertices);
        Poly2Tri::CDT* constrainedDelaunay = nullptr;

        // poly2tri doesn't work well with duplicate or collinear points. it is possible that it will fail on certain inputs
        // if it fails, we retry with increasingly higher jitter. it usually works on first retry
        // if it doesn't work with 42 retries, there is no hope
        std::vector<Poly2Tri::Point> points{};

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (unsigned int triesUtilized = 0; triesUtilized < TRIANG_MAX_TRIES; triesUtilized++)
        {
            points.clear();
            points.reserve(projections.size());
            for (unsigned int i = 0; i < projections.size(); i++)
            {
                auto pt = Poly2Tri::Point(
                    projections[i].X() + (triesUtilized * (std::rand() / RAND_MAX * 0.001 - 0.0005)),
                    projections[i].Y() + (triesUtilized * (std::rand() / RAND_MAX * 0.001 - 0.0005))
                );
                pt._vIdx = i;
                points.emplace_back(pt);
            }

            try
            {
                std::vector<Poly2Tri::Point*> contour{};
                contour.reserve(points.size());
                for (auto& pt : points)
                    contour.emplace_back(&pt);

                constrainedDelaunay = new Poly2Tri::CDT(contour);
                if (constrainedDelaunay == nullptr)
                {
                    throw(std::runtime_error("Face::Set: Failed triangulation! constrainedDelaunay == nullptr\n"));
                }
				constrainedDelaunay->Triangulate();
                break; // assuming it all goes well
            }
            catch (const std::runtime_error& err)
            {
                std::string msg = std::string(err.what()) +
                    "\nFace::Set: Triangulation was not able to finish with " +
                    std::to_string(TRIANG_MAX_TRIES) + " tries!\n";
                MSG_CHECK(false, msg);
                continue;
            }
        }
		
		if (constrainedDelaunay == nullptr)
		{
			throw(std::runtime_error("Face::Set: Failed triangulation! constrainedDelaunay == nullptr\n"));
		}

        auto triangles = constrainedDelaunay->GetTriangles();
        m_Triangulation.clear();
        m_Triangulation.reserve(triangles.size());

		std::ranges::transform(triangles, std::back_inserter(m_Triangulation), 
            [&vertices](const auto& tri) -> auto {
            return std::tuple{
                vertices[tri->GetPoint(0)->_vIdx],
                vertices[tri->GetPoint(1)->_vIdx],
                vertices[tri->GetPoint(2)->_vIdx]
            };
        });

        delete constrainedDelaunay;
        return *this;
    }

    bool Face::IsBoundary() const
    {
        if (!m_HalfEdge.IsValid())
        {
            throw Symplektis::InvalidHandleException("Face::IsBoundary: m_HalfEdge handle is invalid!\n");
        }

        return m_HalfEdge.GetElement().IsBoundary();
    }

} // Symplektis::GeometryKernel