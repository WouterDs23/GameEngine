#include "MiniginPCH.h"
#include "MapGenerator.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include <fstream>

dae::MapGenerator::MapGenerator()
{
}


dae::MapGenerator::~MapGenerator()
{
}

std::vector<std::shared_ptr<dae::GameObject>> dae::MapGenerator::CreateMap(std::string location, int nrOfTilesWidth, int nrOfTilesHeight)
{
	char tile{};
	std::ifstream mapFile;
	mapFile.open(location);
	if (!mapFile)
	{
		std::cerr << "Unable to open file " << location << std::endl;
		exit(1);   // call system to stop
	}
	const float tileSizeWidth = Renderer::GetInstance().GetWidth() / nrOfTilesWidth;
	const float tileSizeHeight = Renderer::GetInstance().GetHeight() / nrOfTilesHeight;

	float currentWidth{};
	float currentHeight{};
	for (int i = 0; i < nrOfTilesHeight; i++)
	{
		for (int k = 0; k < nrOfTilesWidth; k++)
		{
			mapFile.get(tile);
			if (tile == '\n')
			{
				mapFile.get(tile);
			}
			addTile(Type(atoi(&tile)), currentWidth, currentHeight, tileSizeWidth, tileSizeHeight);
			mapFile.ignore();
			currentWidth += tileSizeWidth;
		}
		currentHeight += tileSizeHeight;
		currentWidth = 0;
	}

	return  m_Tiles;
}

void dae::MapGenerator::addTile(Type type, float x, float y, float xSize, float ySize)
{
	std::shared_ptr<dae::GameObject> obj = std::make_shared<GameObject>();
	switch (type)
	{
	case Dirt:
		obj->SetPosition(x, y);
		obj->SetSize(xSize, ySize);
		obj->AddComponent(std::make_shared<CollisionComponent>());
		obj->SetTexture("dirt.png");
		obj->GetComponent<CollisionComponent>().lock()->SetIsObstacle();
		break;
	case Path:
		obj->SetPosition(x, y);
		obj->SetSize(xSize, ySize);
		obj->AddComponent(std::make_shared<CollisionComponent>());
		obj->SetTexture("dirtway.png");
		break;
	default:
		break;
	}
	m_Tiles.push_back(obj);
}


