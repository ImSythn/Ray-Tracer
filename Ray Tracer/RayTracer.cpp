#include "World.h"

int main() {
	World world = World();
	world.BuildScene();
	world.RenderScene();
	world.DisplayScene();
	return 0;
}