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

/*
 * This is a mutex which maintains a count of how many lockers are left and
 * whether or not its currently locked.
 */

#ifndef CAM_UTILS_COUNTEDMUTEX_HPP
#define CAM_UTILS_COUNTEDMUTEX_HPP

#include <mutex>
#include <atomic>

namespace CAM
{
namespace Utils
{
class CountedMutex : public std::mutex
{
	public:
	inline void lock()
	{
		lockersLeft.fetch_add(1, std::memory_order_relaxed);
		mutex::lock();
		lockersLeft.fetch_sub(1, std::memory_order_relaxed);
		uniqueLocked.store(true, std::memory_order_relaxed);
	}

	bool try_lock()
	{
		lockersLeft.fetch_add(1, std::memory_order_relaxed);
		auto ret = mutex::try_lock();
		if (ret)
		{
			uniqueLocked.store(true, std::memory_order_relaxed);
		}
		lockersLeft.fetch_sub(1, std::memory_order_relaxed);
		return ret;
	}

	inline void unlock()
	{
		uniqueLocked.store(false, std::memory_order_relaxed);
		mutex::unlock();
	}

	[[nodiscard]] inline uint32_t LockersLeft() const { return lockersLeft.load(std::memory_order_relaxed); }
	[[nodiscard]] inline bool UniqueLocked() const { return uniqueLocked.load(std::memory_order_relaxed); }

	private:
	std::atomic<uint32_t> lockersLeft = 0;
	std::atomic<bool> uniqueLocked = false;

};
}
}
#endif
