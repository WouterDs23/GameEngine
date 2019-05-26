#include "MiniginPCH.h"
#include "MapGenerator.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include <fstream>
#include "ConnectionComponent.h"
#include "HelperFunctions.h"
#include "RockComponent.h"

dae::MapGenerator::MapGenerator()
{
}


dae::MapGenerator::~MapGenerator()
{
}

std::vector<std::shared_ptr<dae::GameObject>> dae::MapGenerator::CreateMap(std::string location, int nrOfTilesWidth, int nrOfTilesHeight)
{
	if (m_Tiles.size() != 0)
	{
		if (m_Location == location)
		{
			return  m_Tiles;
		}
		else
		{
			m_Tiles.clear();
			m_Rocks.clear();
		}
		
	}
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
	createConnections();
	m_Tiles.insert(m_Tiles.end(), m_Rocks.begin(), m_Rocks.end());
	m_Location = location;
	return  m_Tiles;
}

void dae::MapGenerator::addTile(Type type, float x, float y, float xSize, float ySize)
{
	std::shared_ptr<dae::GameObject> obj = std::make_shared<GameObject>();
	obj->SetPosition(x, y);
	obj->SetSize(xSize, ySize);
	obj->AddComponent(std::make_shared<CollisionComponent>());
	obj->AddComponent(std::make_shared<NodeComponent>());
	obj->AddComponent(std::make_shared<ConnectionComponent>());
	switch (type)
	{
	case Dirt:
		obj->SetTexture("dirt.png");
		obj->GetComponent<CollisionComponent>().lock()->SetIsObstacle();
		break;
	case Path:		
		obj->SetTexture("dirtway.png");
		break;
	case Rock:
		obj->SetTexture("dirtway.png");
		std::shared_ptr<dae::GameObject> rock = std::make_shared<GameObject>();
		rock->SetPosition(x, y);
		rock->SetSize(xSize, ySize);
		rock->SetTexture("Rock.png");
		rock->AddComponent(std::make_shared<Environment::RockComponent>());
		m_Rocks.push_back(rock);
		break;
	}
	m_Tiles.push_back(obj);
}

void dae::MapGenerator::createConnections()
{
	for (auto object : m_Tiles)
	{
		if (!object->GetComponent<NodeComponent>().lock())
		{
			continue;
		}
		glm::vec3 coordinatesLeft{ object->GetTransform().GetMiddlePosition() };
		coordinatesLeft.x -= object->GetTransform().GetSize().x;
		glm::vec3 coordinatesRight{ object->GetTransform().GetMiddlePosition() };
		coordinatesRight.x += object->GetTransform().GetSize().x;
		glm::vec3 coordinatesUp{ object->GetTransform().GetMiddlePosition() };
		coordinatesUp.y += object->GetTransform().GetSize().y;
		glm::vec3 coordinatesDown{ object->GetTransform().GetMiddlePosition() };
		coordinatesDown.y -= object->GetTransform().GetSize().y;

		std::weak_ptr<GameObject> pCurrentLeftNode{};
		std::weak_ptr<GameObject> pCurrentRightNode{};
		std::weak_ptr<GameObject> pCurrentUpNode{};
		std::weak_ptr<GameObject> pCurrentDownNode{};
		for (auto obj : m_Tiles)
		{
			if (obj == object)
			{
				continue;
			}
			if (!obj->GetComponent<NodeComponent>().lock())
			{
				continue;
			}
			const auto tempDistanceLeft = DistanceBetween2Objects(obj->GetTransform().GetMiddlePosition(), coordinatesLeft);
			const auto tempDistanceRight = DistanceBetween2Objects(obj->GetTransform().GetMiddlePosition(), coordinatesRight);
			const auto tempDistanceUp = DistanceBetween2Objects(obj->GetTransform().GetMiddlePosition(), coordinatesUp);
			const auto tempDistanceDown = DistanceBetween2Objects(obj->GetTransform().GetMiddlePosition(), coordinatesDown);
			if (tempDistanceLeft.x <= 1.f && tempDistanceLeft.y <= 1.f)
			{
				pCurrentLeftNode = obj;
			}
			if (tempDistanceRight.x <= 1.f && tempDistanceRight.y <= 1.f)
			{
				pCurrentRightNode = obj;
			}
			if (tempDistanceUp.x <= 1.f && tempDistanceUp.y <= 1.f)
			{
				pCurrentUpNode = obj;
			}
			if (tempDistanceDown.x <= 1.f && tempDistanceDown.y <= 1.f)
			{
				pCurrentDownNode = obj;
			}
		}
		if (pCurrentLeftNode.lock())
		{
			object->GetComponent<NodeComponent>().lock()->AddConnection(pCurrentLeftNode);
		}
		if (pCurrentRightNode.lock())
		{
			object->GetComponent<NodeComponent>().lock()->AddConnection(pCurrentRightNode);
		}
		if (pCurrentUpNode.lock())
		{
			object->GetComponent<NodeComponent>().lock()->AddConnection(pCurrentUpNode);
		}
		if (pCurrentDownNode.lock())
		{
			object->GetComponent<NodeComponent>().lock()->AddConnection(pCurrentDownNode);
		}
	}
}


