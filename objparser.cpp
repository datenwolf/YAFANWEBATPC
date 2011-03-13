#include "objparser.h"
#include "objverttag.h"

ObjParser::ObjParser(QFile& objfile) :
    objfile(objfile)
{
    ObjVertTag* v=new ObjVertTag;
    parser[v->tag()]=v;
}
