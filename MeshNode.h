#ifndef __MESHNODE_H
#define __MESHNODE_H

#include "Triangle.h"
#include "Vector3.h"
#include "types.h"
#include "Material.h"
#include "GraphicMatrix.h"
#include "ResourceManager.h"
#include <boost/shared_ptr.hpp>

/**
	@author Ben Nemec <cybertron@nemebean.com>
*/

using boost::shared_ptr;

class Mesh;

class MeshNode
{
   public:
      MeshNode();
      void Transform(const shared_ptr<MeshNode>&, const float, VertexPtrvec&, const GraphicMatrix&, const GraphicMatrix&, const Vector3&);
      void TransformLoop(const shared_ptr<MeshNode>&, const float, VertexPtrvec&, const GraphicMatrix&, const GraphicMatrix&, const Vector3&);
      void TransformNoInt(VertexPtrvec&, const GraphicMatrix&, const GraphicMatrix&, const Vector3&);
      void TransformNoIntLoop(VertexPtrvec&, const GraphicMatrix&, const GraphicMatrix&, const Vector3&);
      shared_ptr<MeshNode> Clone();
      void GetContainers(map<string, shared_ptr<MeshNode> >& cont, shared_ptr<MeshNode>&);
      void Scale(const float&);
      void ScaleZ(const float&);
      void SetGL(const bool);
      
      int id, parentid;
      bool facing;
      bool gl;
      Vector3 rot1, rot2;
      Vector3 trans;
      vector<shared_ptr<MeshNode> > children;
      Vertexvec vertices;
      GraphicMatrix m;
      string name;
      MeshNode* parent;
};

typedef shared_ptr<MeshNode> MeshNodePtr;

#endif
