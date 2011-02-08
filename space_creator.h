#ifndef SPACE_CREATOR_H
#define SPACE_CREATOR_H
#include "space_scene.h"
#include <vector>
                                        // 5%
#define SPACE_CREATOR_RANDOMNESS_FACTOR 0.05f

std::vector<space_object> space_create_tree(std::vector<space_object>,int,bool);
#endif
