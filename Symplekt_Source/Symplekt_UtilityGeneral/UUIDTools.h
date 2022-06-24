/*! \file  UUIDTools.h
 *  \brief Tools for manipulating with UUID/GUID (Universally unique identifier/ Globally unique identifier) types
 *
 *   \author M. Cavarga (MCInversion)
 *   \date   22.11.2021
 *
 */

#pragma once

#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#include <rpc.h>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

 // disable: "'localtime': This function or variable may be unsafe. Consider using localtime_s instead."
#pragma warning (disable: 4996)

namespace Symplektis::Util
{
    //-----------------------------------------------------------------------------
    /*! \brief Generates a new UUID.
     *  \return newly generated UUID.
     *
     *   \ingroup UTILITY_GENERAL
     *   \author M. Cavarga (MCInversion)
     *   \date   22.11.2021
     */
     //-----------------------------------------------------------------------------
	inline UUID CreateUUID() noexcept
	{
		UUID result = GUID_NULL;
		
		if (CoCreateGuid(&result) != RPC_S_OK)
			return GUID_NULL;

		return result;		
	}

    //-----------------------------------------------------------------------------
    /*! \brief Get std::string output from a given UUID/GUID, e.g.: "123e4567-e89b-12d3-a456-426652340000"
     *  \param[in] uuid          UUID to be converted to string.
     *  \return std::string form of a given UUID/GUID
     *
     *   \ingroup UTILITY_GENERAL
     *   \author M. Cavarga (MCInversion)
     *   \date   22.11.2021
     */
     //-----------------------------------------------------------------------------
    inline std::string GetUUIDString(const UUID& uuid)
	{
		std::string result;
        RPC_CSTR szUuid = nullptr;
        if (::UuidToStringA(&uuid, &szUuid) == RPC_S_OK)
        {
            const char* cStrUUID = reinterpret_cast<const char*>(szUuid);
            result = std::string{ cStrUUID };
            ::RpcStringFreeA(&szUuid);
        }
        return result;
	}

    //-----------------------------------------------------------------------------
    /*! \brief Creates a timestamp string in "d-m-Y H-M-S" format.
     *  \return generated timestamp string
     *
     *   \ingroup UTILITY_GENERAL
     *   \author M. Cavarga (MCInversion)
     *   \date   27.11.2021
     */
     //-----------------------------------------------------------------------------
	inline std::string GetTimestampString()
	{
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::stringstream stream;
        stream << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        return stream.str();
	}
}