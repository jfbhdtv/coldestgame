// @Begin License@
// This file is part of Coldest.
//
// Coldest is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Coldest is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Coldest.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2008-2012 Ben Nemec
// @End License@
#ifndef MESHDATA_H
#define MESHDATA_H

#include "ResourceManager.h"
#include "Triangle.h"
#include "Vertex.h"
#include "MeshNode.h"
#include <boost/shared_ptr.hpp>

class Mesh;  // Forward declaration because of the circular reference

// A class to hold all of the mesh data that cannot be default copy-constructed so we don't have to write a huge
// copy constructor for the main Mesh class.
class MeshData
{
   public:
      MeshData(ResourceManager&);
      MeshData(const MeshData&);
      MeshData& operator=(const MeshData&);
      void EnsureMaterials();
      
      void AddTriangle(const Triangle& t) {tris.push_back(t);}
      void AddTriangle(const TrianglePtr& t) {triptrs.push_back(t);}
      Triangle& Tri(const size_t i) {return tris.size() ? tris[i] : *triptrs[i];}
      size_t NumTris() const {return tris.size() ? tris.size() : triptrs.size();}
      void SortTris();
      void ClearTris() {tris.resize(0); triptrs.resize(0);}
      
      VertexPtrvec vertices;
      vector<MeshNodePtr> frameroot;
      ResourceManager& resman;
      
      MaterialPtr impmat;
      shared_ptr<Mesh> impostor;

   private:
      void DeepCopy(const MeshData&);
      
      Trianglevec tris;
      TrianglePtrvec triptrs;
};

#endif // MESHDATA_H
