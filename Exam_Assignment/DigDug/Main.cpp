#include "MiniginPCH.h"
#include <ctime>
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )
	srand(unsigned(std::time(NULL)));
	dae::Minigin engine;
	engine.Run();
    return 0;
}

