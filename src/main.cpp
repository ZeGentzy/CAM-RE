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

#include "Job.hpp"
#include "WorkerPool.hpp"

#include <cstdint>
#include <cstdio>
#include <cassert>

const size_t threadCount = std::thread::hardware_concurrency() * 2 + 1;
//const size_t threadCount = 1;

namespace OL
{
class Main
{
	public:
	Main() {}
	void Start();
	void Done
	(
		void* userData,
		CAM::WorkerPool* wp,
		size_t thread,
		CAM::Job* thisJob
	);
	void DoneMain
	(
		void* userData,
		CAM::WorkerPool* wp,
		size_t thread,
		CAM::Job* thisJob
	);

	private:
};
}

void OL::Main::Start()
{
	CAM::WorkerPool wp;

	for (size_t i = 0; i < threadCount - 1; ++i)
	{
		wp.AddWorker(std::make_unique<CAM::Worker>(&wp, true));
	}

	auto myWorkerUni = std::make_unique<CAM::Worker>(&wp, false);
	auto myWorker = myWorkerUni.get();
	wp.AddWorker(std::move(myWorkerUni));

	wp.StartWorkers();

	using namespace std::placeholders;
	auto dJob = wp.GetJob
	(
		std::bind(&Main::Done, this, _1, _2, _3, _4),
		nullptr,
		1,
		false
	);
	auto dmJob = wp.GetJob
	(
		std::bind(&Main::DoneMain, this, _1, _2, _3, _4),
		nullptr,
		1,
		true
	);

	wp.SubmitJob(std::move(dJob));
	wp.SubmitJob(std::move(dmJob));

	myWorker->WorkerRoutine();
}

void OL::Main::Done
(
	void* /*userData*/,
	CAM::WorkerPool* /*wp*/,
	size_t thread,
	CAM::Job* /*thisJob*/
)
{
	printf("Thread %zu says, \"thanks for playing.\"\n", thread);
}

void OL::Main::DoneMain
(
	void* /*userData*/,
	CAM::WorkerPool* /*wp*/,
	size_t thread,
	CAM::Job* /*thisJob*/
)
{
	assert(thread == threadCount - 1);
	printf("Main thread %zu says, \"thanks for playing.\"\n", thread);
}

int main()
{
	OL::Main m;
	m.Start();

	return 0;
}
