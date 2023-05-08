#include "World.hpp"

World::World(vec3 x, vec3 y, vec3 z)
:
    x(x), y(y), z(z)
{

}
World::World():
    i{1,0,0},
    j(0,1,0),
    k(0,0,1)
{
    x=i;
    y=j;
    z=k;
}


World::~World()=default;

const vec3 World::ToGlobalSpace(const vec3 & pos) const
{
    return x * pos.x + y * pos.y + z * pos.z;   
}
