#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Wouter De Smedt DigDug Engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		448,
		608,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{	
	SceneManager::GetInstance().CreateScene("MainMenu", SceneManager::MainMenu);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	

	LoadGame();
	{		
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		float lag{ 0 };
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			GameLifeSpan::deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += GameLifeSpan::deltaTime;
			doContinue = input.ProcessInput();
			int loops{};
			while (lag >= float(msPerFrame/1000.f))
			{
				if (loops >= maxLoops)
				{
					break;
				}
				loops++;
				sceneManager.Update();
				lag -= float(1.f/msPerFrame);
			}
			renderer.Render();
		}
	}

	Cleanup();
}
