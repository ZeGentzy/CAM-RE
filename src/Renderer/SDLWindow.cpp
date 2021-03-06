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

#include "SDLWindow.hpp"
#include "Renderer.hpp"
#include "../Config.hpp"
#include "../Utils/Assert.hpp"

CAM::Renderer::SDLWindow::SDLWindow
(
	Jobs::WorkerPool* wp,
	Jobs::Job* /*thisJob*/,
	Renderer* parent
) : wp(wp), parent(parent)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::string error = SDL_GetError();
		throw std::runtime_error("Unable to init SDL Video: " + error);
    }

	window = SDL_CreateWindow
	(
		"CAM-RE",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		Config::StartingWindowWidth,
		Config::StartingWindowHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN
	);

	if (window == nullptr)
	{
		std::string error = SDL_GetError();
		throw std::runtime_error("Unable to create SDL window: " + error);
	}

	unsigned extCount;
	SDL_Vulkan_GetInstanceExtensions(window, &extCount, nullptr);
	reqExts.resize(extCount);
	SDL_Vulkan_GetInstanceExtensions(window, &extCount, reqExts.data());
}

void CAM::Renderer::SDLWindow::HandleEvents
(
	CAM::Jobs::WorkerPool* /*wp*/,
	size_t /*thread*/,
	CAM::Jobs::Job* /*thisJob*/
)
{
	static auto a = 0;
	const auto s = 300;

	static std::chrono::time_point<std::chrono::high_resolution_clock> last;
	++a;
	if (a == s)
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> diff = now - last;
		printf("Ev avg %fms (aka %ffps)\n", diff.count() / s, 1000. / (diff.count() / s));
		last = now;
		a = 0;
	}
	else if (a == 1)
	{
		last = std::chrono::high_resolution_clock::now();
	}

	SDL_Event event;
	while(SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
		{
			shouldContinue.store(false, std::memory_order_release);
		}
	}
}

CAM::Renderer::SDLWindow::~SDLWindow()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
