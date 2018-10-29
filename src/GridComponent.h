#pragma once

#include <ECS.h>
#include "Update.h"
#include "Message.h"

class GridComponent : public ECS::Component<Update, Message>
{
	private:
		int spacing = 16;
		double scale = 1;

	private:
		void increaseSpacing();
		void decreaseSpacing();

	public:
		void update(const Update&) override;

		void receive(const Message&) override;
};
