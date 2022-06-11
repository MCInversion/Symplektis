/*! \file  IBinaryTreeQueryDataNode.h
 *  \brief A node data object interface used for querying/building a binary tree, regardless of implementation type.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   24.11.2021
 */

#pragma once

#include <memory>
#include <string>

namespace Symplektis::DataReps
{
    //=============================================================================
    /// \struct NodeDataWrapper
    /// \brief An extendable data wrapper base struct for binary tree node data.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   26.11.2021
    //=============================================================================
    struct NodeDataWrapper
    {
    	// --------------------------------------
        size_t DataSize;
    	// --------------------------------------
    };
	
    //=============================================================================
    /// \class IBinaryTreeQueryDataNode
    /// \brief A node data interface object for binary tree querying. Does not contain any data, only its extensions do.
    ///
    /// \ingroup DATA_REPS
    ///
    /// \author M. Cavarga (MCInversion)
    /// \date   24.11.2021
    //=============================================================================
	class IBinaryTreeQueryDataNode
	{
	public:
        /// @{
        /// \name Default Special Members

        /// \brief Default constructor.
        IBinaryTreeQueryDataNode() = default;

        /// \brief Default copy constructor.
        IBinaryTreeQueryDataNode(const IBinaryTreeQueryDataNode& other) = default;

        /// \brief Default move constructor.
        IBinaryTreeQueryDataNode(IBinaryTreeQueryDataNode&& other) = default;

        /// \brief Default copy-assignment operator.
        IBinaryTreeQueryDataNode& operator=(const IBinaryTreeQueryDataNode& other) = default;

        /// \brief Default move-assignment operator.
        IBinaryTreeQueryDataNode& operator=(IBinaryTreeQueryDataNode&& other) = default;
		
		/// \brief Default destructor.
		virtual ~IBinaryTreeQueryDataNode() = default;
		
        /// @{
        /// \name Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Evaluates whether given query data "intersects" (set-wise) this node data content.
         *  \param[in] queryData        query data for comparison.
         *  \return true if given queryData intersects this node data.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   24.11.2021
         */
        //-----------------------------------------------------------------------------
        [[nodiscard]] virtual bool IntersectsData(const std::shared_ptr<NodeDataWrapper>& queryData) const = 0;


        /// @{
        /// \name Getters

        //-----------------------------------------------------------------------------
        /*! \brief A data wrapper getter
         *  \return a pointer to node data wrapper
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   14.1.2022
         */
         //-----------------------------------------------------------------------------
		[[nodiscard]] virtual std::shared_ptr<NodeDataWrapper> GetDataWrapper() const = 0;

        /// @{
        /// \name Helper Functionality

        //-----------------------------------------------------------------------------
        /*! \brief Prints this data node's content
         *  \return a string of debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   27.11.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::string DebugPrint() const = 0;

        //-----------------------------------------------------------------------------
        /*! \brief Prints this data node's content as PlantUML class data.
         *  \return a string of PlantUML debug print lines.
         *
         *   \author M. Cavarga (MCInversion)
         *   \date   1.12.2021
         */
         //-----------------------------------------------------------------------------
        [[nodiscard]] virtual std::string PlantUMLPrint() const = 0;
	};
	
	
} // Symplektis::DataReps