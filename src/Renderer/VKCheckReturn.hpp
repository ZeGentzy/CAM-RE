/*
 * Copyright (C) 2018 Hal Gentz
 *
 * This file is part of CAM-RE.
 *
 * CAM-RE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Bash is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * CAM-RE. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CAM_RENDERER_VKCHECKRETURN_HPP
#define CAM_RENDERER_VKCHECKRETURN_HPP

#define VKFNPRETTYRETURNCODE(x) case x: return #x;
#define VKFNPRETTYRETURNCODE_G(x) case x: return "SUCCESS: " #x;

#define VKFNCHECKRETURN(x) CAM::VKFN::CheckReturn(x, __FILE__, __LINE__)

namespace CAM
{
namespace VKFN
{
	[[nodiscard]] inline std::string PrettyReturnCode(VkResult res)
	{
		switch(res)
		{
			VKFNPRETTYRETURNCODE_G(VK_SUCCESS)		// The first eight arn't actually errors, someone fucked up
			VKFNPRETTYRETURNCODE_G(VK_NOT_READY)
			VKFNPRETTYRETURNCODE_G(VK_TIMEOUT)
			VKFNPRETTYRETURNCODE_G(VK_EVENT_SET)
			VKFNPRETTYRETURNCODE_G(VK_EVENT_RESET)
			VKFNPRETTYRETURNCODE_G(VK_INCOMPLETE)
			VKFNPRETTYRETURNCODE_G(VK_ERROR_OUT_OF_DATE_KHR)
			VKFNPRETTYRETURNCODE_G(VK_SUBOPTIMAL_KHR)

			VKFNPRETTYRETURNCODE(VK_ERROR_OUT_OF_HOST_MEMORY)
			VKFNPRETTYRETURNCODE(VK_ERROR_OUT_OF_DEVICE_MEMORY)
			VKFNPRETTYRETURNCODE(VK_ERROR_INITIALIZATION_FAILED)
			VKFNPRETTYRETURNCODE(VK_ERROR_DEVICE_LOST)
			VKFNPRETTYRETURNCODE(VK_ERROR_MEMORY_MAP_FAILED)
			VKFNPRETTYRETURNCODE(VK_ERROR_LAYER_NOT_PRESENT)
			VKFNPRETTYRETURNCODE(VK_ERROR_EXTENSION_NOT_PRESENT)
			VKFNPRETTYRETURNCODE(VK_ERROR_FEATURE_NOT_PRESENT)
			VKFNPRETTYRETURNCODE(VK_ERROR_INCOMPATIBLE_DRIVER)
			VKFNPRETTYRETURNCODE(VK_ERROR_TOO_MANY_OBJECTS)
			VKFNPRETTYRETURNCODE(VK_ERROR_FORMAT_NOT_SUPPORTED)
			VKFNPRETTYRETURNCODE(VK_ERROR_FRAGMENTED_POOL)
			VKFNPRETTYRETURNCODE(VK_ERROR_SURFACE_LOST_KHR)
			VKFNPRETTYRETURNCODE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
			VKFNPRETTYRETURNCODE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
			VKFNPRETTYRETURNCODE(VK_ERROR_VALIDATION_FAILED_EXT)
			VKFNPRETTYRETURNCODE(VK_ERROR_INVALID_SHADER_NV)
			VKFNPRETTYRETURNCODE(VK_ERROR_OUT_OF_POOL_MEMORY_KHR)
			VKFNPRETTYRETURNCODE(VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR)

			// Cause some fuckards can't be conformant
			#ifdef VK_ERROR_NOT_PERMITTED_EXT
				VKFNPRETTYRETURNCODE(VK_ERROR_NOT_PERMITTED_EXT)
			#endif

			default:
			return "UNKOWN: " + std::to_string(res);
		}
	}

	inline VkResult CheckReturn(VkResult res, std::string file, int line)
	{
		if
		(
			res == VK_SUCCESS
			|| res == VK_NOT_READY
			|| res == VK_TIMEOUT
			|| res == VK_EVENT_SET
			|| res == VK_EVENT_RESET
			|| res == VK_INCOMPLETE
			|| res == VK_ERROR_OUT_OF_DATE_KHR
			|| res == VK_SUBOPTIMAL_KHR
		)
		{
			return res;
		}

		throw std::runtime_error("Got error \"" + PrettyReturnCode(res) + "\" in " + file + ":" + std::to_string(line));
	}
}
}

#endif
