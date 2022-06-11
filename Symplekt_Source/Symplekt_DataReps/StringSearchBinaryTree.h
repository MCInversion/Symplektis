/*! \file  StringSearchBinaryTree.h
 *  \brief A test class for binary tree architecture with switchable implementation.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   27.11.2021
 *
 */

#pragma once

#include "BinaryTree.h"
#include "IBinaryTreeQueryDataNode.h"

#include <vector>
#include <string>

namespace Symplektis::DataReps
{

    //=============================================================================
    /// \struct StringSearchNodeData
    /// \brief Overridden data wrapper struct for string search tree.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   27.11.2021
    //=============================================================================
    struct StringSearchNodeData : NodeDataWrapper
    {
        // --------------------------------------
        // --------------------------------------
        std::string DataString{};
        // --------------------------------------

        //------------------------------------------------------------------------
        /// \brief Evaluates whether the node with this data wrapper is preferred over other node.
        //------------------------------------------------------------------------
        [[nodiscard]] bool IsPreferredOver(const StringSearchNodeData& other) const
        {
            return DataString < other.DataString;
        }
    };

    //=============================================================================
    /// \class StringSearchNode
    /// \brief A query data node type storing StringSearchNodeData wrapper.
    ///
    /// \ingroup DataRepsITY_GENERAL
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   27.11.2021
    //=============================================================================
    class StringSearchNode final
		: public IBinaryTreeQueryDataNode
    {
    public:
        /// @{
        /// \name Constructor

        //-----------------------------------------------------------------------------
        /*! \brief Construct this data node with a given pointer to a data wrapper.
         *  \param[in] nodeData            data node's data wrapper containing actual data
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        explicit StringSearchNode(std::shared_ptr<StringSearchNodeData> nodeData)
            : m_Data(std::move(nodeData)) { }

        /// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief Node data getter.
         *  \return this data node's data.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<StringSearchNodeData> GetData() const
        {
            return m_Data;
        }

        /// @{
        /// \name Functionality
    	
        //-----------------------------------------------------------------------------
        /// \copydoc Sypmplektis::DataReps::IBinaryTreeQueryDataNode::IntersectsData
        //-----------------------------------------------------------------------------
        [[nodiscard]] bool IntersectsData(const std::shared_ptr<NodeDataWrapper>& queryData) const override;
    	
        /// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeQueryDataNode::GetDataWrapper
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::shared_ptr<NodeDataWrapper> GetDataWrapper() const override
        {
            return m_Data;
        }

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeQueryDataNode::DebugPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string DebugPrint() const override;

        //-----------------------------------------------------------------------------
        /// \copydoc Symplektis::DataReps::IBinaryTreeQueryDataNode::PlantUMLPrint
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string PlantUMLPrint() const override;

    private:

        std::shared_ptr<StringSearchNodeData> m_Data; //>! Data wrapper for evaluation
    };

    //=============================================================================
    /// \class StringSearchBinaryTree
    /// \brief A concrete BinaryTree object used for searching for strings in alphabetical order.
    ///
    /// \ingroup DataRepsITY_GENERAL
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   27.11.2021
    //=============================================================================
    class StringSearchBinaryTree final
		: public BinaryTree
    {
    public:

        /// @{
        /// \name Constructors

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Initialize this BinaryTree from implementation type.
        *   \param[in] data               string data (search space).
        *   \param[in] implType           implementation type enumerator.
        *   \param[in] name               tree name.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   27.11.2021
        */
        //-----------------------------------------------------------------------------
        StringSearchBinaryTree(const std::vector<std::string>& data, const BinaryTreeImplementationType& implType, std::string name)
            : BinaryTree(name, implType)
        {
            m_DataForConstruction = data;
        }

        //-----------------------------------------------------------------------------
        /*! \brief Constructor. Initialize this BinaryTree from implementation type.
        *   \param[in] data               string data (search space).
        *   \param[in] implType           implementation type enumerator.
        *   \param[in] name               tree name.
        *   \param[in] isSelfBalancing    self-balancing flag for this string search tree.
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   27.11.2021
        */
        //-----------------------------------------------------------------------------
    	StringSearchBinaryTree(const std::vector<std::string>& data, const BinaryTreeImplementationType& implType, std::string name, const bool& isSelfBalancing)
    		: BinaryTree(name, implType, isSelfBalancing)
        {
            m_DataForConstruction = data;
        }
    	

        /// @{
        /// \name Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Finds a matching string stored in some node of this binary tree.
         *  \param[in] comparedStr           string searched for in this tree.
         *  \return matched string
        *
        *   \author M. Cavarga (MCInversion)
        *   \date   27.11.2021
        */
        //-----------------------------------------------------------------------------
        [[nodiscard]] std::string FindMatch(std::string& comparedStr) const
        {
            if (comparedStr.empty())
                return comparedStr;

            std::string result;

            return result;
        }

    private:

        /// @{
        /// \name Internal Initializers

        //-----------------------------------------------------------------------------
		/// \copydoc Symplektis::DataReps::BinaryTree::InternalBuildFromData
		//-----------------------------------------------------------------------------
        [[nodiscard]] BinaryTreeErrorCode InternalBuildFromData() override;

        //
        // =============== Data ========================================================
        //

    	//>! String data for tree construction.
        std::vector<std::string> m_DataForConstruction{};
    };
	
} // Symplektis::DataReps