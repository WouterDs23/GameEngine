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
			MainMenu,
			FirstLevel,
			FirstLevel2p,
			FirstLevel2v2,
			SecondLevel,
			SecondLevel2p,
			SecondLevel2v2,
			EndScreen
		};
		void CreateScene(const std::string& name, TypeOfScene type);

		void SetActiveScene(const std::string& name, TypeOfScene type);

		void ResetScene();

		void DeleteActiveScene();

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene{};
		TypeOfScene m_LastUsedType{};
	};

}
