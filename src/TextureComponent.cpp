#include "TextureComponent.h"

void TextureComponent::loadImage(SDL_Renderer *renderer)
{
	texture.loadFromFile(imagePath, renderer);
	imagePath = "";
}

void TextureComponent::update(const Update& update)
{
	if (!imagePath.empty()) {
		loadImage(update.renderer);
	}
	texture.render(update.renderer, nullptr, &update.drawRect);
}

void TextureComponent::receive(const Message& message)
{
	if (message.getType() == NEW_IMAGE) {
		imagePath = message.imagePath;
	}
}
