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

#ifndef CAM_MAIN_HPP
#define CAM_MAIN_HPP

#include "Jobs/Job.hpp"
#include "Jobs/WorkerPool.hpp"

#include <cstdint>
#include <cstdio>

#include "Renderer/Renderer.hpp"

#include "Config.hpp"

namespace CAM
{
class Main
{
	public:

	Main() {}
	void Start();

	void Init
	(
		CAM::Jobs::WorkerPool* wp,
		size_t thread,
		CAM::Jobs::Job* thisJob
	);

	void FrameStart
	(
		CAM::Jobs::WorkerPool* wp,
		size_t thread,
		CAM::Jobs::Job* thisJob
	);

	void Done
	(
		CAM::Jobs::WorkerPool* wp,
		size_t thread,
		CAM::Jobs::Job* thisJob
	);
	void DoneMain
	(
		CAM::Jobs::WorkerPool* wp,
		size_t thread,
		CAM::Jobs::Job* thisJob
	);

	private:
	Jobs::WorkerPool wp;
	std::unique_ptr<Renderer::Renderer> renderer;
};
}

#endif
