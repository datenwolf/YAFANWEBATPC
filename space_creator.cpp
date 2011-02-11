#include "space_creator.h"
#include <cstring>
#include <math.h>
#include <stdlib.h>
float rand_FloatRange(float a, float b)
{
return ((b-a)*((float)rand()/RAND_MAX))+a;
}
float mkrandomness(float in) {
  return in+rand_FloatRange(-in/SPACE_CREATOR_RANDOMNESS_FACTOR,in/SPACE_CREATOR_RANDOMNESS_FACTOR);
}
std::vector<space_object> space_create_tree(std::vector<space_object> in,
											unsigned int id,
											bool init_system=false){
	if(init_system){
		space_object tmp;
		tmp.id=id;
		tmp.parent=id;
		tmp.objtype=star;
    float r=mkrandomness(STAR_SYSTEM_BASE_DISTANCE/100000.0f);
    float theta=random_angle();
    float phi=random_angle();
		tmp.x=r*sin(theta)*cos(phi);
		tmp.y=r*sin(theta)*sin(phi);
		tmp.z=r*cos(theta);
		tmp.rotx=random_angle();
		tmp.roty=random_angle();
		tmp.rotz=random_angle();
		strcpy(tmp.model,"models/planet.3ds");
		strcpy(tmp.texname,"models/planet_uv_perlin.bmp");
		in.push_back(tmp);
		return in;
	}
  return in;
}
