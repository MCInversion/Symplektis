/*! \file  MeshGeometryDataForTesting.h
 *  \brief Test data for ReferencedMeshGeometry
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   9.9.2021
 *
 */

#pragma once

#include "../../Symplekt_GeometryBase/Vector3.h"

#include <vector>

namespace Symplektis::UnitTests
{
    const double phi = (1.0 + sqrt(5.0)) / 2.0;

    using namespace GeometryBase;

    inline std::vector icosahedronDataVertices{
		/* v0 */ Vector3{-1.0, phi, 0.0},  /* v1 */ Vector3{1.0, phi, 0.0},
		/* v2 */ Vector3{-1.0, -phi, 0.0}, /* v3 */ Vector3{1.0, -phi, 0.0},
        /* v4 */ Vector3{0.0, -1.0, phi},  /* v5 */ Vector3{0.0, 1.0, phi},
        /* v6 */ Vector3{0.0, -1.0, -phi}, /* v7 */ Vector3{0.0, 1.0, -phi},
        /* v8 */ Vector3{phi, 0.0, -1.0},  /* v9 */ Vector3{phi, 0.0, 1.0},
        /* v10 */Vector3{-phi, 0.0, -1.0},/* v11 */ Vector3{-phi, 0.0, 1.0}
    };

    inline std::vector<std::vector<unsigned int>> icosahedronDataVertexIndices{
		{0, 11, 5},    {0, 5, 1},    {0, 1, 7},    {0, 7, 10},    {0, 10, 11},
    	{1, 5, 9},     {5, 11, 4},   {11, 10, 2},  {10, 7, 6},    {7, 1, 8},
    	{3, 9, 4},     {3, 4, 2},    {3, 2, 6},    {3, 6, 8},     {3, 8, 9},
    	{4, 9, 5},     {2, 4, 11},   {6, 2, 10},   {8, 6, 7},     {9, 8, 1}
    };

    // missing triangles 11 and 12
    inline std::vector<std::vector<unsigned int>> icosahedronMissingTwoTrianglesDataVertexIndices{
	    {0, 11, 5},    {0, 5, 1},     {0, 1, 7},    {0, 7, 10},    {0, 10, 11},
	    {1, 5, 9},    {5, 11, 4},   {11, 10, 2},    {10, 7, 6},      {7, 1, 8},
	    {3, 9, 4},    /* {3, 4, 2},       {3, 2, 6}, */  {3, 6, 8},      {3, 8, 9},
	    {4, 9, 5},    {2, 4, 11},    {6, 2, 10},     {8, 6, 7},      {9, 8, 1}
    };

    inline std::vector<std::vector<unsigned int>> icosahedronFirstQuadDataVertexIndices{
        {0, 11, 5, 1},                  {0, 1, 7},    {0, 7, 10},    {0, 10, 11},
        {1, 5, 9},    {5, 11, 4},   {11, 10, 2},    {10, 7, 6},      {7, 1, 8},
        {3, 9, 4},     {3, 4, 2},     {3, 2, 6},     {3, 6, 8},      {3, 8, 9},
        {4, 9, 5},    {2, 4, 11},    {6, 2, 10},     {8, 6, 7},      {9, 8, 1}
    };

    const double ico_edge_length = (icosahedronDataVertices[11] - icosahedronDataVertices[0]).GetLength();
    const double ico_triangle_area = 5.0 * sqrt(3.0) * ico_edge_length * ico_edge_length / 20.0;
	

} // Symplektis::UnitTests