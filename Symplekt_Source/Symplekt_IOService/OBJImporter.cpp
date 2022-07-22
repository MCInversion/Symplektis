/*! \file  OBJImporter.cpp
 *  \brief Implementation of an object for importing 3D geometry data from Wavefront OBJ (*.obj) files
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   6.10.2021
 *
 */

#include "OBJImporter.h"

#include "Symplekt_UtilityGeneral/Assert.h"

#include <string>
#include <fstream>
#include <map>

namespace Symplektis::IOService
{
	using namespace GeometryKernel;

	//-----------------------------------------------------------------------------
	/*! \brief Read a line token composed of three floating point coordinates
	 *  \param[in] sStream         read token's string stream.
	 *  \param[in] vectorBuffer    buffer where Vector3 instances are pushed
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   10.10.2021
	*/
	//-----------------------------------------------------------------------------
	static void ReadVector3Line(std::stringstream& sStream, std::vector<Vector3>& vectorBuffer)
	{
		double x, y, z;
		sStream >> x >> y >> z;

		vectorBuffer.emplace_back(Vector3(x, y, z));
	}

	//-----------------------------------------------------------------------------
	/*! \brief Parse 1-based index triples p/[t]/[n], where [.] are optional tokens, p are polygon vertex indices, t are texture coordinate indices, and n are normal indices.
	 *  \param[in] token         particular "p/[t]/[n]" token.
	 *  \return {iPoly, iTexture, iNormal} triple
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   10.10.2021
	*/
	//-----------------------------------------------------------------------------
	static std::tuple<int, int, int> ParsePolygonIndex(const std::string& token)
	{
		std::stringstream sStreamIn{ token };
		std::string indexString;
		
		int indices[3] = { -1, -1, -1 };
		unsigned int i = 0;

		while (std::getline(sStreamIn, indexString))
		{
			std::stringstream sStream{ indexString };
			sStream >> indices[i++];
		}

		return std::tuple{ indices[0] - 1, indices[1] - 1, indices[2] - 1 };
	}

	//-----------------------------------------------------------------------------
	/*! \brief Read a line token composed of three floating point coordinates
	 *  \param[in] sStream            read token's string stream.
	 *  \param[in] polyIndexBuffer    buffer where polygon index tuples are pushed.
	 *  \param[in] textureIndexBuffer buffer where polygon texture coord index tuples are pushed
	 *  \param[in] normalIndexBuffer  buffer where polygon vertex normal index tuples are pushed
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   10.10.2021
	*/
	//-----------------------------------------------------------------------------
	static void ReadVertexIndices(std::stringstream& sStream, 
		std::vector<std::vector<unsigned int>>& polyIndexBuffer, 
		std::vector<std::vector<unsigned int>>& textureIndexBuffer,
		std::vector<std::vector<unsigned int>>& normalIndexBuffer)
	{
		std::vector<unsigned int> polyIndices;
		std::vector<unsigned int> textureIndices;
		std::vector<unsigned int> normalIndices;
		std::string currentToken;

		while (sStream >> currentToken)
		{
			const auto [iPoly, iTexture, iNormal] = ParsePolygonIndex(currentToken);
			polyIndices.push_back(iPoly);
			if (iTexture > -1) textureIndices.push_back(iTexture);
			if (iNormal > -1) normalIndices.push_back(iNormal);
		}

		polyIndexBuffer.emplace_back(polyIndices);
		if (!textureIndices.empty()) polyIndexBuffer.emplace_back(textureIndices);
		if (!normalIndices.empty()) polyIndexBuffer.emplace_back(normalIndices);
	}

	//-----------------------------------------------------------------------------
	/*! \brief Parse mesh file name from the imported file path.
	 *  \param[in] importedFilePath     path to the imported file.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   9.6.2022
	*/
	//-----------------------------------------------------------------------------
	static std::wstring GetGeometryNameFromFilePath(const std::filesystem::path& importedFilePath)
	{
		const auto stem = importedFilePath.stem();
		return stem.wstring();
	}
	
	ImportStatus OBJImporter::Import(const std::filesystem::path& importedFilePath)
	{
		if (importedFilePath.empty() || !exists(importedFilePath))
			return ImportStatus::FileNotFound;

		if (!importedFilePath.has_extension() || importedFilePath.extension() != ".obj")
			return ImportStatus::InvalidExtension;

		std::ifstream fileInStream(importedFilePath.c_str(), std::ios::in);
		if (!fileInStream.is_open())
			return ImportStatus::FileNotOpened;

		ClearIOData();
		m_Data.Name = GetGeometryNameFromFilePath(importedFilePath);

		std::vector<std::vector<unsigned int>> textureIndices{};
		std::vector<std::vector<unsigned int>> normalIndices{};

		std::vector<Vector3> nonIndexedVertexNormals{};

		std::string line;
		unsigned int lineNumber = 0;
		while (std::getline(fileInStream, line))
		{
			std::stringstream sStream{ line };
			std::string token;
			sStream >> token;

			if (token == "v")
			{
				ReadVector3Line(sStream, m_Data.Vertices);
				lineNumber++;
				continue;
			}
			if (token == "vt")
			{
				// TODO: use texture coords
				lineNumber++;
				continue;
			}
			if (token == "vn")
			{
				ReadVector3Line(sStream, nonIndexedVertexNormals);
				lineNumber++;
				continue;
			}
			if (token == "f")
			{
				ReadVertexIndices(sStream, m_Data.VertexIndices, textureIndices, normalIndices);
				lineNumber++;
				continue;
			}
			if (token == "o") // object name. Not handling tree structures yet
			{
				lineNumber++; continue;
			} 
			if (token[0] == '#') // comment
			{
				lineNumber++;
				continue;
			}
			if (token == "g") // group name
			{
				lineNumber++;
				continue;
			}
			if (token == "s") // smoothing group 
			{
				lineNumber++;
				continue;
			}
			if (token == "mtllib") // material library
			{
				lineNumber++;
				continue;
			}
			if (token == "usemtl") // material
			{
				lineNumber++;
				continue;
			}
			if (token.empty()) // empty string 
			{
				lineNumber++;
				continue;
			}

			const std::string errMessage = "OBJImporter::Import: invalid token in *.obj file, found on line " + std::to_string(lineNumber) + ": " + line + "\n";
			MSG_CHECK(false, errMessage);
			fileInStream.close();
			return ImportStatus::InternalError;
		}

		PostProcessVertexNormalsFromIndices(normalIndices, nonIndexedVertexNormals);

		// TODO: Do something with textureIndices

		fileInStream.close();
		return ImportStatus::Complete;
	}

	//-----------------------------------------------------------------------------
	/*! \brief Creates a map of vertices without normals with false values.
	 *  \param[in] verticesCount         returned map size
	 *  \return (vertex index, false) map.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   13.10.2021
	*/
	//-----------------------------------------------------------------------------
	static std::map<unsigned int, bool> GetVerticesWithoutNormals(const size_t& verticesCount)
	{
		std::map<unsigned int, bool> vertexHasNormal;
		for (unsigned int i = 0; i < verticesCount; i++) vertexHasNormal[i] = false;
		return vertexHasNormal;
	}

	//-----------------------------------------------------------------------------
	/*! \brief Find vertices without normal.
	 *  \param[in] vertexHasNormal         map of vertexIndex -> hasNormal.
	 *  \return true if there is at least one vertex without a normal.
	*
	*   \author M. Cavarga (MCInversion)
	*   \date   13.10.2021
	*/
	//-----------------------------------------------------------------------------
	static bool VerticesWithoutNormalsExist(const std::map<unsigned int, bool>& vertexHasNormal)
	{
		bool vertexWithoutNormal = false;
		for (const auto& [vertId, hasNormal] : vertexHasNormal)
		{
			if (!hasNormal) vertexWithoutNormal = true;
		}

		if (vertexWithoutNormal)
		{
			const std::string errMessage = "OBJImporter::PostProcessVertexNormalsFromIndices: There is a vertex without a normal! Skipping normal postprocessing.\n";
			MSG_CHECK(false, errMessage);
		}

		return vertexWithoutNormal;
	}

	void OBJImporter::PostProcessVertexNormalsFromIndices(
		const std::vector<std::vector<unsigned int>>&  collectedNormalIndices,
		const std::vector<Vector3>&                    nonIndexedVertexNormals)
	{
		if (nonIndexedVertexNormals.empty())
			return; // do nothing. There are no normals indexed or non-indexed.

		if (collectedNormalIndices.empty())
		{
			if (nonIndexedVertexNormals.size() == m_Data.Vertices.size())
			{
				// assuming that there is already a one-to-one correspondence between vertices and vertex normals.
				m_Data.VertexNormals = nonIndexedVertexNormals;
				return;
			}
			
			size_t totalVertexIndexCount = 0;
			for (const auto & indexTuple : m_Data.VertexIndices) totalVertexIndexCount += indexTuple.size();

			if (nonIndexedVertexNormals.size() != totalVertexIndexCount)
			{
				// if there is a different number of vertex normals than that of total vertex indices, and there are no normal indices,
				// there is no way to assign a vertex normal to each vertex (other than compute it from adjacent triangulated faces).
				// Vertex normals are therefore discarded.
				const std::string errMessage = "OBJImporter::PostProcessVertexNormalsFromIndices: Non-indexed vertex normals buffer is of different size than vertex indices buffer. Discarding vertex normals!\n";
				MSG_CHECK(false, errMessage);
				return;
			}

			//
			// ------------------ V A R I A N T        I. ----------------------------------------------------------------------
			// ===== computing vertex normals according to vertex index tuples =================================================
			//

			const size_t verticesCount = m_Data.Vertices.size();

			// pre-define the same number of normals as vertices
			std::vector<Vector3> resultNormals(verticesCount);
			std::map<unsigned int, bool> vertexHasNormal = GetVerticesWithoutNormals(verticesCount);

			for (unsigned int normalIndex = 0; auto& indexTuple : m_Data.VertexIndices)
			{
				for (auto & index : indexTuple)
				{
					if (vertexHasNormal[index])
						continue;

					if (index >= verticesCount)
					{
						const std::string errMessage = "OBJImporter::PostProcessVertexNormalsFromIndices: Index " + std::to_string(index) + " is out of vertex buffer range! Skipping normal postprocessing.\n";
						MSG_CHECK(false, errMessage);
						return;
					}

					resultNormals[index] = nonIndexedVertexNormals[normalIndex];
					vertexHasNormal[index] = true;

					normalIndex++;
				}
			}

			if (VerticesWithoutNormalsExist(vertexHasNormal)) return;

			m_Data.VertexNormals = resultNormals;
			return;
		}

		//
		// ------------------ V A R I A N T       II. ----------------------------------------------------------------------
		// ===== computing vertex normals according to normal index tuples =================================================
		//        >>>>>>  TODO: Test on actual data. No data of this kind was tested yet <<<<<< 

		const size_t verticesCount = m_Data.Vertices.size();
		
		// pre-define the same number of normals as vertices
		std::vector<Vector3> resultNormals(verticesCount); 
		std::map<unsigned int, bool> vertexHasNormal = GetVerticesWithoutNormals(verticesCount);

		const size_t normalsCount = nonIndexedVertexNormals.size();
		for (unsigned int faceIndex = 0; auto& indexTuple : collectedNormalIndices)
		{
			for (unsigned int tupleIndex = 0; auto& index : indexTuple)
			{
				if (index >= normalsCount)
				{
					const std::string errMessage = "OBJImporter::PostProcessVertexNormalsFromIndices: Index " + std::to_string(index) + " is out of normal buffer range! Skipping normal postprocessing.\n";
					MSG_CHECK(false, errMessage);
					return;
				}

				if (vertexHasNormal[index])
					continue;

				if (index >= verticesCount)
				{
					const std::string errMessage = "OBJImporter::PostProcessVertexNormalsFromIndices: Index " + std::to_string(index) + " is out of vertex buffer range! Skipping normal postprocessing.\n";
					MSG_CHECK(false, errMessage);
					return;
				}

				const unsigned int vertexIndex = m_Data.VertexIndices[faceIndex][tupleIndex];
				resultNormals[vertexIndex] = nonIndexedVertexNormals[index];
				vertexHasNormal[vertexIndex] = true;

				tupleIndex++;
			}

			faceIndex++;
		}

		if (VerticesWithoutNormalsExist(vertexHasNormal)) return;

		m_Data.VertexNormals = resultNormals;
	}

	
} // Symplektis::IOService