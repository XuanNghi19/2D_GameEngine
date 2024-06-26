#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 64;
	int width = 64;
	int scale = 1;


	int speed = 3;


	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = x;
	}
		
	TransformComponent(int w, int h, int sc)
	{
		width = w;
		height = h;
		scale = sc;
	}

	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}
	void  update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};