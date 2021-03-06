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


#include "Quad.h"

Quad::Quad() : first(new Triangle()), second(new Triangle())
{
   second->v[0] = first->v[1];
   second->v[2] = first->v[2];
   floatvec tc(2, 0.f);
   vector<floatvec> tcv(4, tc);
   tcv[1][1] = 1.f;
   tcv[2][0] = 1.f;
   tcv[2][1] = 1.f;
   tcv[3][0] = 1.f;
   for (int i = 0; i < 8; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         GetVertNums(j);
         if (vert >= 0)
            first->v[vert]->texcoords[i] = tcv[j];
         if (vert1 >= 0)
            second->v[vert1]->texcoords[i] = tcv[j];
      }
   }
}


Quad::Quad(const Quad& q) : first(new Triangle(*q.first)), second(new Triangle(*q.second))
{
   for (size_t i = 0; i < 3; ++i)
   {
      first->v[i] = VertexPtr(new Vertex((*first->v[i])));
      second->v[i] = VertexPtr(new Vertex((*second->v[i])));
   }
   second->v[0] = first->v[1];
   second->v[2] = first->v[2];
}


Quad& Quad::operator=(const Quad& q)
{
   first = TrianglePtr(new Triangle(*q.first));
   second = TrianglePtr(new Triangle(*q.second));
   for (size_t i = 0; i < 3; ++i)
   {
      first->v[i] = VertexPtr(new Vertex((*first->v[i])));
      second->v[i] = VertexPtr(new Vertex((*second->v[i])));
   }
   second->v[0] = first->v[1];
   second->v[2] = first->v[2];
   return *this;
}


void Quad::SetVertexPtr(const int num, const VertexPtr& v)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      first->v[vert] = v;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1] = v;
}


VertexPtr Quad::GetVertexPtr(const int num)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      return first->v[vert];
   if (vert1 >= 0 && vert1 < 3) 
      return second->v[vert1];
   return VertexPtr(); // Uh oh
}


void Quad::SetVertex(const int num, const Vector3& v)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      first->v[vert]->pos = v;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1]->pos = v;
}


void Quad::SetNormal(const int num, const Vector3& v)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      first->v[vert]->norm = v;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1]->norm = v;
}


void Quad::SetColor(const int num, const GLubytevec& val)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      first->v[vert]->color = val;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1]->color = val;
}


void Quad::SetTexCoords(const int num, const int texunit, const floatvec& val)
{
   GetVertNums(num);
   
   if (vert >= 0 && vert < 3)
      first->v[vert]->texcoords[texunit] = val;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1]->texcoords[texunit] = val;
}


void Quad::SetTerrainWeight(const int vertex, const int tex, const float val)
{
   GetVertNums(vertex);
   
   if (vert >= 0 && vert < 3)
      first->v[vert]->terrainwt[tex] = val;
   if (vert1 >= 0 && vert1 < 3)
      second->v[vert1]->terrainwt[tex] = val;
}


void Quad::SetCollide(bool val)
{
   first->collide = val;
   second->collide = val;
}


void Quad::SetMaterial(Material* m)
{
   m->Use();
   first->material = m;
   second->material = m;
}


void Quad::Translate(const Vector3& v)
{
   for (int i = 0; i < 4; ++i)
   {
      GetVertNums(i);
      
      Vector3 current;
      if (vert >= 0 && vert < 3)
         current = first->v[vert]->pos;
      if (vert1 >= 0 && vert1 < 3)
         current = second->v[vert1]->pos;
      SetVertex(i, current + v);
   }
}


void Quad::Scale(const float scale)
{
   GetVertNums(0);
   Vector3 offset = first->v[vert]->pos;
   Translate(-offset);
   
   for (int i = 1; i < 4; ++i)
   {
      GetVertNums(i);
      
      Vector3 current;
      if (vert >= 0 && vert < 3)
         current = first->v[vert]->pos;
      if (vert1 >= 0 && vert1 < 3)
         current = second->v[vert1]->pos;
      SetVertex(i, current * scale);
   }
   
   Translate(offset);
}



