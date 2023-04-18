#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "ECS.hpp"
#include "Component.hpp"
#include "../TextureManager.hpp"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}


	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	}
	std::string getTag() { // Add a getTag function to return the collider's tag
        return tag;
    }

private:

};