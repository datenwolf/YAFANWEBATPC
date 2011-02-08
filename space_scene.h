#ifndef SPACE_SCENE_H
#define SPACE_SCENE_H

#define ONE_AU_IN_KM 149597870.7f
#define ONE_AU_IN_LM 8.317f
#define ONE_AU_IN_LS 499.0f
#define ONE_LY_IN_AU 36241.0f
// 1ps/au=648000/pi
#define ONE_PS_IN_AU 206264.806247f

#define STAR_SYSTEM_BASE_DISTANCE 4.153E13f


enum objtype_enum{
    star,
    planet,
    moon,
    smallstationary,
    ship,
    other //try to avoid using "other"
};

typedef struct {
    unsigned int id;
    unsigned int parent; //parent==id for stars/suns, then all relative to last defined star/sun
    objtype_enum objtype;
    float x; //1.0f == 1.0f opengl unit == 1.0f kilometer
             // max value of float: E37
             // ~ø Sol: E6
             // ~[Sol->Pluto]: 5E9
             // ~[Sol->Alpha Centauri(Rigel Kentaurus A)]: 4.153E13
             // ~ø Milky Way (the galaxy, not the chocolate bar): 9.5E17
    float y;
    float z;
    int rotx; // rotating around +X, rightHandRule
    int roty; // rotating around +Y, rightHandRule
    int rotz; // rotating around +Z, rightHandRule
    char model[256];       //model.3ds
    char texname[256];     //if=="D474" use texdata, else use texname.bmp
    char texdata[262144];  //512*512px
} space_object;

const float sol_planet_distances_in_km[] = {
//  -MMMKKK000
      57910000.0f, //Mercury
     108210000.0f, //Venus
     149600000.0f, //Earth
     227940000.0f, //Mars
     778340000.0f, //Jupiter
    1427010000.0f, //Saturn
    2869670000.0f, //Uranus
    4496540000.0f, //Neptune
    5946600000.0f  //Pluto (YES F***IN PLUTO _IS_ A PLANET!!!)
};

const float sol_planet_diameters_in_km[] = {
          4840.0f, //Mercury
         12228.0f, //Venus
         12756.0f, //Earth
          6770.0f, //Mars
        143650.0f, //Jupiter
        120670.0f, //Saturn
         47100.0f, //Uranus
         50000.0f, //Neptune
          6000.0f  //Pluto (YES F***IN PLUTO _IS_ A PLANET!!!)
};

#endif
