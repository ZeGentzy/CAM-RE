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

#ifdef VKFNGLOBALPROC
	VKFNGLOBALPROC(vkCreateInstance)
	VKFNGLOBALPROC(vkEnumerateInstanceExtensionProperties)
	VKFNGLOBALPROC(vkEnumerateInstanceLayerProperties)
#endif

#ifdef VKFNINSTANCEPROC
	VKFNINSTANCEPROC(vkCreateDevice)
	VKFNINSTANCEPROC(vkDestroyDevice)
	VKFNINSTANCEPROC(vkDestroyInstance)
	VKFNINSTANCEPROC(vkDestroySurfaceKHR)
	VKFNINSTANCEPROC(vkEnumerateDeviceExtensionProperties)
	VKFNINSTANCEPROC(vkEnumeratePhysicalDevices)
	VKFNINSTANCEPROC(vkGetDeviceProcAddr)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceFeatures)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceProperties)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceQueueFamilyProperties)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceSurfaceSupportKHR)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceSurfacePresentModesKHR)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
	VKFNINSTANCEPROC(vkGetPhysicalDeviceSurfaceFormatsKHR)
#endif

#ifdef VKFNINSTANCEPROC_VAL
	VKFNINSTANCEPROC_VAL(vkCreateDebugReportCallbackEXT)
	VKFNINSTANCEPROC_VAL(vkDestroyDebugReportCallbackEXT)
#endif

#ifdef VKFNDEVICEPROC
	VKFNDEVICEPROC(vkAcquireNextImageKHR)
	VKFNDEVICEPROC(vkCreateFence)
	VKFNDEVICEPROC(vkCreateImageView)
	VKFNDEVICEPROC(vkCreateSemaphore)
	VKFNDEVICEPROC(vkCreateSwapchainKHR)
	VKFNDEVICEPROC(vkDestroyFence)
	VKFNDEVICEPROC(vkDestroyImage)
	VKFNDEVICEPROC(vkDestroyImageView)
	VKFNDEVICEPROC(vkDestroySemaphore)
	VKFNDEVICEPROC(vkDestroySwapchainKHR)
	VKFNDEVICEPROC(vkDeviceWaitIdle)
	VKFNDEVICEPROC(vkGetDeviceQueue)
	VKFNDEVICEPROC(vkGetFenceStatus)
	VKFNDEVICEPROC(vkGetSwapchainImagesKHR)
	VKFNDEVICEPROC(vkQueuePresentKHR)
	VKFNDEVICEPROC(vkResetFences)
	VKFNDEVICEPROC(vkWaitForFences)
#endif
