#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "math.h"

class Circle : public Entity //hole sẽ kế thừa các hàm của Entity
{
public:
    Circle(Vector2f p_pos, SDL_Texture* p_tex);
private:
};

