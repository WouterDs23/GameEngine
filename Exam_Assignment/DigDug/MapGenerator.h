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
		std::vector<std::shared_ptr<dae::GameObject>> GetMap(std::string location, int nrOfTilesWidth, int nrOfTilesHeight)
		{
			m_Tiles.clear();
			m_Rocks.clear();
			return CreateMap(location,nrOfTilesWidth,nrOfTilesHeight);
		}
	private:
		enum Type
		{
			Dirt,
			Path,
			Rock
		};
		void addTile(Type type, float x, float y, float xSize, float ySize);
		void createConnections();
		std::vector < std::shared_ptr<dae::GameObject>> m_Tiles;
		std::vector < std::shared_ptr<dae::GameObject>> m_Rocks;
		std::string m_Location{};
	};
}

