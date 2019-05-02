#pragma once
namespace dae
{
	class GameObject;
	class MapGenerator final : public Singleton<MapGenerator>
	{
	public:
		MapGenerator();
		~MapGenerator();
		std::vector<std::shared_ptr<dae::GameObject>>CreateMap(std::string location, int nrOfTilesWidth, int nrOfTilesHeight);
	private:
		enum Type
		{
			Dirt,
			Path
		};
		void addTile(Type type, float x, float y, float xSize, float ySize);
		std::vector < std::shared_ptr<dae::GameObject>> m_Tiles;
	};
}

