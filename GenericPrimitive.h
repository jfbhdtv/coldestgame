#ifndef __GENERIC_PRIMITIVE_H
#define __GENERIC_PRIMITIVE_H

#include "Material.h"
#include "Vector3.h"
#include <string>
#include <list>
#include <vector>

using namespace std;

class GenericPrimitive
{
   public:
      GenericPrimitive();
      void Init();
      Vector3 v[4];
      Vector3 tangent;
      float rad, rad1;
      string type;
      bool collide;
      bool dynamic;
      int vboindex;
      vector< vector< vector<float> > > texcoords; // texcoords[texunit][vertex][st]
      int texnum;
      GLuint texnums[6];
      string shader;
      float color[4][4];
      float dist;
      Material* material;
};
#endif
