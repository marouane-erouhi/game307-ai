#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "GameManager.h"

/*
	Simplifies making sprites and rendering them

	Base usage:
	// create an image
	int imageID = ResourceManager::getInstance()->AddImage(game, "Art/Desert.png");
	// render the image using it's ID, scale and orientation are optinal
	ResourceManager::getInstance()->RenderImage(game, imageID, position, [scale_vec3, orientation_float]);
*/

// contains all image assets used in game
class ResourceManager {
	std::vector<SDL_Surface*> images;
	std::vector<SDL_Texture*> textures;
	static ResourceManager* instance;

	// Delete copy constructor and assignment operator to prevent copying
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

public:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* getInstance();

	unsigned int AddImage(GameManager* game_, std::string fileName);
	void RenderImage(GameManager* game_, int imageId, Vec3 pos_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f), float orientation_ = 0.0f);
};

