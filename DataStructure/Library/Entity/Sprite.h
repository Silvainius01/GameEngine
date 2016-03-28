#pragma once
#include "Stat.h"

class Sprite
{
private:
	Transform *p;
	Vec2 size;
	unsigned textureHandle;
	char *location;
public:
	union
	{
		float height, width;
		Vec2 dimensions = Vec2{ 1, 1 };
	};

	Sprite(Transform &parent, char *filePath, Vec2 mapSize) 
	{
		p = &parent;
		location = filePath;
		size = mapSize;
	}
	Sprite(Transform &parent, char *filePath, Vec2 mapSize, Vec2 dim)
	{
		p = &parent;
		location = filePath;
		size = mapSize;
		dimensions = dim;
	}

	void draw(Vec2 textmapLocation)
	{
		float matrix[16];
		for (int a = 0, c = 0; a < 3; a++)
		{
			for (int b = 0; b < 3; b++)
			{
				matrix[c] = p->getTransMatrix().data[a][b];
				c++;
			}
			c++;
		}
		matrix[3] = 0, matrix[7] = 0, matrix[11] = 0;
		matrix[12] = 0, matrix[13] = 0, matrix[14] = 0; matrix[15] = 1;

		drawTextureMatrix(textureHandle, (int)(textmapLocation.y * textmapLocation.x) + (int)(width - 1), clr_WHITE, matrix);
	}

};