#pragma once

#include <ECS.h>
#include "Update.h"
#include "Message.h"

class Component : public ECS::Component<Update, Message>
{
};
