/*! \file  SymplektisCommandDispatcher.h
 *  \brief Object for handling basic commands for Symplektis_GeometryAnalyzer.
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   15.10.2021
 *
 */

#pragma once

namespace Symplektis::IOService
{

    class SymplektisCommandDispatcher
    {
	public:
		/// @{
		/// \name Default special members

		// ------------------------------------------------------------------------------
		/// \brief Default and deleted special member functions of SymplektisCommandDispatcher singleton
		/// 
		SymplektisCommandDispatcher() = default;
		~SymplektisCommandDispatcher() = default;
		SymplektisCommandDispatcher(const SymplektisCommandDispatcher&) = delete;
		SymplektisCommandDispatcher(const SymplektisCommandDispatcher&&) = delete;
		SymplektisCommandDispatcher& operator=(const SymplektisCommandDispatcher&) = delete;
		SymplektisCommandDispatcher& operator=(const SymplektisCommandDispatcher&&) = delete;
		/// 
		// ------------------------------------------------------------------------------

		/// @{
		/// \name Static Members

		//-----------------------------------------------------------------------------
		/*! \brief Singleton instance getter
		 *  \return SymplektisCommandDispatcher instance.
		*
		*   \author M. Cavarga (MCInversion)
		*   \date   15.10.2021
		*/
		//-----------------------------------------------------------------------------
		static SymplektisCommandDispatcher& GetInstance()
		{
			static SymplektisCommandDispatcher instance{};
			return instance;
		}
    };

} // Symplektis::IOService