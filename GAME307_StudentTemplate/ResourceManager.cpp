#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::~ResourceManager() {
	/// delete all images
	for (auto it = textures.rbegin(); it != textures.rend(); ++it) {
		SDL_DestroyTexture(*it);
	}
	textures.clear();
	for (auto it = images.rbegin(); it != images.rend(); ++it) {
		SDL_FreeSurface(*it);
	}
	images.clear();
}

ResourceManager::ResourceManager() {
	std::cout << "Resource Manager singeleton instance created" << std::endl;
}

ResourceManager* ResourceManager::getInstance() {
	if (instance == nullptr) {
		instance = new ResourceManager();
	}
	return instance;
	return nullptr;
}

unsigned int ResourceManager::AddImage(GameManager* game_, std::string fileName) {
	SDL_Surface* image = IMG_Load(fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game_->getRenderer(), image);
	images.push_back(image);
	textures.push_back(texture);

	return textures.size() - 1;
}

void ResourceManager::RenderImage(GameManager* game_, int imageId, Vec3 pos_, Vec3 scale_, float orientation_) {
	SDL_Renderer* renderer = game_->getRenderer();
	Matrix4 projectionMatrix = game_->getProjectionMatrix();

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;
	Vec3 screenCoords;
	float    w, h;

	// convert the position from game coords to screen coords

	screenCoords = projectionMatrix * pos_;

	// Scale the image, in case the .png file is too big or small
	w = images.at(imageId)->w * scale_.x;
	h = images.at(imageId)->h * scale_.y;

	// The square's x and y values represent the top left corner of 
	// where SDL will draw the .png image.
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtraction!!!!)
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	// Convert character orientation from radians to degrees.
	//float orientationDegrees = orientation * 180.0f / M_PI;

	float orientationDegrees = orientation_ * 180.0f / M_PI;

	if (game_->isDebug()) {
		// draw rectangle
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &square);
	}
	SDL_RenderCopyEx(renderer, textures.at(imageId), nullptr, &square,
		orientation_, nullptr, SDL_FLIP_NONE);
}

