#pragma once

enum MessageType
{
	DEFAULT
};

class Message
{
	private:
		MessageType type;

	public:
		Message(MessageType t) : type(t) { };

		MessageType getType() const;
};
