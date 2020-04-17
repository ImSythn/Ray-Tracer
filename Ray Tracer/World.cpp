#include "World.h"

World::World() {
	// Set your display resolution (hight, width, fov, background colour) 
	settings.Width = 1920;
	settings.Height = 1080;
	settings.Fov = 55;
	settings.Bais = 0.0001;
	settings.MaxRecursion = 1;
	settings.RadiosityRayCount = 32;
	framebuffer = new Vec3f[settings.Width * settings.Height];
}

World::~World() {}


void World::BuildScene() {
	objects.push_back(std::unique_ptr<Object>(new Sphere(Vec3f(2, 1, -10), 5)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(Vec3f(-2, -3, -10), 2)));
	lights.push_back(std::unique_ptr<Light>(new Light(Vec3f(-2, 5, -10), 10)));
}

void World::RenderScene() {
	Vec3f* pixel = framebuffer;

	// Frame aspact ratio & scale used for pixel remapping 
	float scale = tan(MathFunc::DegreeToRadian(settings.Fov * 0.5));
	float aspectRatio = (float)settings.Width / (float)settings.Height;

	// Origin of the primary rays (0, 0, 0)
	Vec3f origin;

	for (uint16_t y = 0; y < settings.Height; y++) {
		for (uint16_t x = 0; x < settings.Width; x++) {
			// Direction of the primary rays from raster to world space
			float xDirection = (2 * (x + 0.5) / (float)settings.Width - 1) * aspectRatio * scale;
			float yDirection = (1 - 2 * (y + 0.5) / (float)settings.Height) * scale;
			Vec3f direction = Vec3f::Normalize(Vec3f(xDirection, yDirection, -1));

			// Cast ray for each pixel of selected resolution
			// Store pixel colour after calculating ray behaviour 
			*(pixel++) = CastRay::Ray(origin, direction, objects, lights, settings, 0);
		}
	}
}

void World::DisplayScene() {
	SDL_Window* window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		settings.Width, settings.Height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC,
		settings.Width, settings.Height);
	uint32_t* buffer = new uint32_t[(settings.Width * settings.Height)];

	memset(buffer, 0, (settings.Width * settings.Height * sizeof(uint32_t)));
	for (uint32_t i = 0; i < settings.Height * settings.Width; ++i) {
		unsigned char r = (unsigned char)(255 * MathFunc::Clamp(0, 1, framebuffer[i].x));
		unsigned char g = (unsigned char)(255 * MathFunc::Clamp(0, 1, framebuffer[i].y));
		unsigned char b = (unsigned char)(255 * MathFunc::Clamp(0, 1, framebuffer[i].z));

		// Convert rgb char to hexa
		buffer[i] = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}

	SDL_UpdateTexture(texture, NULL, buffer, settings.Width * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Event event;

	// Garbage collection 
	delete[] framebuffer;
	delete[] buffer;

	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyTexture(texture);
			SDL_DestroyWindow(window);
			SDL_Quit();
			break;
		}
	}
}