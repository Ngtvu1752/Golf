#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "math.h"

class Hole : public Entity //hole sẽ kế thừa các hàm của Entity
{
public:
    Hole(Vector2f p_pos, SDL_Texture* p_tex);
private:
};
