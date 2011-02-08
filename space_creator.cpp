#include "space_creator.h"
#include <cstring>
std::vector<space_object> space_create_tree(std::vector<space_object> in,
											unsigned int id,
											bool init_system=false){
	if(init_system){
		space_object tmp;
		tmp.id=id;
		tmp.parent=id;
		tmp.objtype=star;
		tmp.x=0;
		tmp.y=0;
		tmp.z=0;
		tmp.rotx=0;
		tmp.roty=0;
		tmp.rotz=0;
		strcpy(tmp.model,"models/planet.3ds");
		strcpy(tmp.texname,"models/planet_uv_perlin.bmp");
		in.push_back(tmp);
		return in;
	}
}
