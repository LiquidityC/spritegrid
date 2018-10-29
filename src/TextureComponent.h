#pragma once

#include <string>
#include "Component.h"
#include "Texture.h"

class TextureComponent : public Component
{
	private:
		std::string imagePath;
		Texture texture;

	private:

	public:
		void loadImage(SDL_Renderer *renderer);
		void update(const Update&);
		void receive(const Message&);
};
