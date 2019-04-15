#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		enum TypeOfScene
		{
			TestScene
		};
		void CreateScene(const std::string& name, TypeOfScene type);

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
	};

}
