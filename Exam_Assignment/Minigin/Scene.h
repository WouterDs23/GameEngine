#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend void SceneManager::CreateScene(const std::string& name, SceneManager::TypeOfScene type);
	public:
		explicit Scene(const std::string& name);

		void Add(const std::shared_ptr<SceneObject>& object);

		virtual void Initialize();
		virtual void Update();
		virtual void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		

		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int idCounter; 
	};

}
