#pragma once

#include <SDL.h>
#include <ECS.h>

#include "Update.h"
#include "Message.h"

class Grid : public ECS::Entity<Update, Message>
{
};
