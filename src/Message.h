#pragma once

#include <string>

enum MessageType
{
	NEW_IMAGE,
	DEFAULT
};

class Message
{
	private:
		MessageType type;

	public:
		std::string imagePath;

	public:
		Message(MessageType t) : type(t) { };

		MessageType getType() const;
};
