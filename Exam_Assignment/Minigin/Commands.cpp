#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"

dae::Commands::Commands()
{

}

dae::Commands::~Commands()
{

}

bool dae::Commands::execute(std::weak_ptr<dae::GameObject> actor)
{
	return false;
}


