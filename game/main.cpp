#include "commons.hpp"
#include "Scene.hpp"

int main() {
	Log::setFlags(Log::Timestamp);
	Game* g = new Game(Window::DisplayMode::createWindowedMode(1000,1000), ContextSettings());
	Scene* s = new Scene();
	s->addTo(g);
	g->run();
	delete g;
	return 0;
}

