#pragma once

#include <ECS.h>
#include "Update.h"
#include "Message.h"

class Entity : public ECS::Entity<Update, Message>
{
};
