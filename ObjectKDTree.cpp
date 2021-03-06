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


#include "ObjectKDTree.h"

int ObjectKDTree::maxlevels = 7;

ObjectKDTree::ObjectKDTree(Meshlist *objs, Vector3vec v) : haschildren(false), vertices(v), retobjs(new MeshSet()), root(true), p(6, Quad())
{
   // Get pointers to objects
   for (Meshlist::iterator i = objs->begin(); i != objs->end(); ++i)
   {
      members.push_back(&(*i));
   }
   logout << "KD-Tree Objects: " << members.size() << endl;

   vertices[1].x = v[0].x;
   vertices[1].y = v[0].y;
   vertices[1].z = v[6].z;

   vertices[2].x = v[6].x;
   vertices[2].y = v[0].y;
   vertices[2].z = v[6].z;

   vertices[3].x = v[6].x;
   vertices[3].y = v[0].y;
   vertices[3].z = v[0].z;

   vertices[4].x = v[0].x;
   vertices[4].y = v[6].y;
   vertices[4].z = v[0].z;

   vertices[5].x = v[6].x;
   vertices[5].y = v[6].y;
   vertices[5].z = v[0].z;

   /*vertices[6].x = v[6].x;
   vertices[6].y = v[6].y;
   vertices[6].z = v[6].z;*/

   vertices[7].x = v[0].x;
   vertices[7].y = v[6].y;
   vertices[7].z = v[6].z;
}


ObjectKDTree::ObjectKDTree() : members(list<Mesh*>()), haschildren(false), retobjs(NULL), root(false)
{
}


ObjectKDTree& ObjectKDTree::operator=(const ObjectKDTree& o)
{
   if (this == &o) return *this;
   vertices = o.vertices;
   members = o.members;
   children = o.children;
   root = o.root;
   p = o.p;
   frustum = &p;
   haschildren = o.haschildren;
   if (haschildren && root)
   {
      children[0]->setfrustum(frustum);
      children[1]->setfrustum(frustum);
   }
   if (root)
   {
      retobjs = new MeshSet();
      setretobjs(retobjs);
   }
   return *this;
}


ObjectKDTree::ObjectKDTree(const ObjectKDTree& o)
{
   vertices = o.vertices;
   members = o.members;
   children = o.children;
   root = o.root;
   p = o.p;
   frustum = &p;
   haschildren = o.haschildren;
   if (haschildren && root)
   {
      children[0]->setfrustum(frustum);
      children[1]->setfrustum(frustum);
   }
   if (root)
   {
      retobjs = new MeshSet();
      setretobjs(retobjs);
   }
}


ObjectKDTree::~ObjectKDTree()
{
   if (root)
      delete retobjs;
}


void ObjectKDTree::refine(int level)
{
   int curraxis = level % 2;
   int iterations = 0;
   float currsplit = 0, minsplit, maxsplit;

   switch(curraxis)
   {
      case 0:
         minsplit = vertices[0].x;
         maxsplit = vertices[6].x;
         currsplit = (vertices[0].x + vertices[6].x) / 2;
         break;
      case 1:
         minsplit = vertices[0].z;
         maxsplit = vertices[6].z;
         currsplit = (vertices[0].z + vertices[6].z) / 2;
         break;
      case 2:
         minsplit = vertices[0].y;
         maxsplit = vertices[6].y;
         currsplit = (vertices[0].y + vertices[6].y) / 2;
         break;
   };

   Vector3vec v(8, Vector3());
   ObjectKDTreePtr newnode(new ObjectKDTree());
   children.push_back(newnode);
   newnode = ObjectKDTreePtr(new ObjectKDTree());
   children.push_back(newnode);
   haschildren = true;

   while (true)
   {
      // Set children vertices
      v[0] = vertices[0];
      v[6] = vertices[6];
      switch(curraxis)
      {
         case 0:
            v[0].x = currsplit;
            break;
         case 1:
            v[0].z = currsplit;
            break;
         case 2:
            v[0].y = currsplit;
            break;
      };
      children[0]->setvertices(v);

      v[0] = vertices[0];
      v[6] = vertices[6];
      switch(curraxis)
      {
         case 0:
            v[6].x = currsplit;
            break;
         case 1:
            v[6].z = currsplit;
            break;
         case 2:
            v[6].y = currsplit;
            break;
      }
      children[1]->setvertices(v);

      // Attempt to insert each object into the children, every object should be
      // successfully inserted into at least one of the children
      list<Mesh*>::iterator j;
      for (int i = 0; i < 2; ++i)
      {
         for (j = members.begin(); j != members.end(); ++j)
         {
            children[i]->insert(*j);
         }
      }

      // If we've successfully split approx. in half, or have tried enough
      int size0 = children[0]->size() + 1; // +1 to avoid div by zero
      int size1 = children[1]->size() + 1;
      if (((float)size0 / (float)size1 > .9 &&
           (float)size0 / (float)size1 < 1.1) || true)//iterations >= 5) // Try skipping best-fit, since it doesn't work well in some situations
      {
         if ((children[0]->size() >= 1 || children[1]->size() >= 1) &&
            (level + 1 < maxlevels))
         {
            children[0]->refine(level + 1);
            children[1]->refine(level + 1);
            // All members should be in a child now, so don't keep a copy
            members.clear();
         }
         else // Stop recursing
         {
            children.clear();
            haschildren = false;
         }

         if (root && haschildren)
         {
            setretobjs(retobjs);
            children[0]->setfrustum(frustum);
            children[1]->setfrustum(frustum);
         }
         return;
      }
      /* children[0] is actually the top half of the split, so
         average curr and max, curr and min for children[1].
      */
      else if (children[0]->size() > children[1]->size())
      {
         minsplit = currsplit;
         switch(curraxis)
         {
            case 0:
               currsplit = (currsplit + maxsplit) / 2;
               break;
            case 1:
               currsplit = (currsplit + maxsplit) / 2;
               break;
            case 2:
               currsplit = (currsplit + maxsplit) / 2;
               break;
         };
      }
      else
      {
         maxsplit = currsplit;
         switch(curraxis)
         {
            case 0:
               currsplit = (currsplit + minsplit) / 2;
               break;
            case 1:
               currsplit = (currsplit + minsplit) / 2;
               break;
            case 2:
               currsplit = (currsplit + minsplit) / 2;
               break;
         };
      }

      children[0]->members.clear();
      children[1]->members.clear();
      ++iterations;
   }
}


bool ObjectKDTree::insert(Mesh* obj)
{
   if (innode(obj->GetPosition(), obj->GetSize()))
   {
      members.push_back(obj);
      return true;
   }
   return false;
}


void ObjectKDTree::erase(Mesh* m)
{
   for (list<Mesh*>::iterator i = members.begin(); i != members.end(); ++i)
   {
      if (*i == m)
      {
         members.erase(i);
         break;
      }
   }
   if (haschildren)
   {
      children[0]->erase(m);
      children[1]->erase(m);
   }
}


bool ObjectKDTree::innode(Vector3 v, float size)
{
   return (v.x >= vertices[0].x - size &&
           v.y <= vertices[0].y + size &&
           v.z >= vertices[0].z - size &&
           v.x <= vertices[6].x + size &&
           v.y >= vertices[6].y - size &&
           v.z <= vertices[6].z + size);
}


vector<Mesh*> ObjectKDTree::getmeshes(const Vector3& pos, const float size)
{
   vector<Mesh*> ret;
   getmeshes(pos, size, ret);
   return ret;
}


vector<Mesh*> ObjectKDTree::getmeshes(const Vector3& oldpos, const Vector3& newpos, const float size)
{
   Vector3 midpoint = (oldpos + newpos) / 2.f;
   float newsize = size + oldpos.distance(newpos);
   return getmeshes(midpoint, newsize);
}


void ObjectKDTree::getmeshes(const Vector3& pos, const float size, vector<Mesh*>& ret)
{
   Timer t;

   if (root)
   {
      retobjs->clear();
   }

   if (innode(pos, size))
   {
      if (haschildren)
      {
         children[0]->getmeshes(pos, size, ret);
         children[1]->getmeshes(pos, size, ret);
      }
      else
      {
         for (list<Mesh*>::iterator i = members.begin(); i != members.end(); ++i)
         {
            if (retobjs->find(*i) == retobjs->end())
            {
               retobjs->insert(*i);
               if ((*i)->collide)
                  ret.push_back(*i);
            }
         }
      }
   }
}


/* Make sure to call setfrustum so this has the latest position info to
   work with
*/
list<Mesh*> ObjectKDTree::getmeshes()
{
   list<Mesh*> ret;
   getmeshes(ret);
   return ret;
}


void ObjectKDTree::getmeshes(list<Mesh*>& ret)
{
   list<Mesh*> temp;

   if (root)
   {
      retobjs->clear();
   }

   if (infrustum())
   {
      if (haschildren)
      {
         children[0]->getmeshes(ret);
         children[1]->getmeshes(ret);
      }
      else
      {
         for (list<Mesh*>::iterator i = members.begin(); i != members.end(); ++i)
         {
            if (retobjs->find(*i) == retobjs->end() && infrustum(*i))
            {
               retobjs->insert(*i);
               ret.push_back(*i);
            }
         }
      }
   }
}


bool ObjectKDTree::infrustum()
{
   /* Check if the tree node falls at all within the frustum
      Do this by checking each vertex of the node, and seeing
      if all of them fall outside of any single plane of the frustum
   */
   Vector3 v, s, t, u, norm;
   float d, startside;
   int hitcount;

   for (int i = 0; i < 6; ++i)
   {
      hitcount = 0;
      v = (*frustum)[i].GetVertex(0);
      s = (*frustum)[i].GetVertex(1);
      t = (*frustum)[i].GetVertex(2);
      u = (*frustum)[i].GetVertex(3);
      norm = (t - v).cross(s - v);
      norm.normalize();
      d = -norm.dot(s);

      for (int j = 0; j < 8; ++j)
      {
         startside = norm.dot(vertices[j]) + d;

         if (startside > -.0001)
         {
            ++hitcount;
            break;
         }
      }
      if (!hitcount)
      {
         return false;
      }
   }
   return true;
}


bool ObjectKDTree::infrustum(Mesh* obj)
{
   Vector3 v, s, t, u, norm;
   float d, startside;

   for (int i = 0; i < 6; ++i)
   {
      v = (*frustum)[i].GetVertex(0);
      s = (*frustum)[i].GetVertex(1);
      t = (*frustum)[i].GetVertex(2);
      u = (*frustum)[i].GetVertex(3);
      norm = (t - v).cross(s - v);
      norm.normalize();

      d = -norm.dot(s);

      startside = norm.dot(obj->GetPosition()) + d;
      startside = -startside;

      if (startside > obj->GetSize()) return false;

   }
   return true;
}


// This function should only ever be called on the root node.  Seg faults will result otherwise.
// Also note: This function must be called after copying KDTrees.  The frustum pointer is
// dangling after a copy

// Err, actually I think it's automatically called in the copy constructors now (as it should be)...
void ObjectKDTree::setfrustum(Vector3 pos, Vector3 rots, float nearz, float farz, float fov, float aspect)
{
   Vector3 currpoint;
   float nearx, neary, farx, fary;
   float radfov = fov * PI / 180.;
   nearz = -nearz;
   farz = -farz;
   neary = 2 * tan(radfov / 2) * nearz / 2;
   nearx = neary * aspect;
   fary = 2 * tan(radfov / 2) * farz / 2;
   farx = fary * aspect;

   currpoint.x = nearx;
   currpoint.y = neary;
   currpoint.z = nearz;
   p[0].SetVertex(0, currpoint);
   p[2].SetVertex(3, currpoint);
   p[3].SetVertex(2, currpoint);

   currpoint.x = nearx;
   currpoint.y = -neary;
   p[0].SetVertex(3, currpoint);
   p[3].SetVertex(3, currpoint);
   p[4].SetVertex(2, currpoint);

   currpoint.x = -nearx;
   currpoint.y = neary;
   p[0].SetVertex(1, currpoint);
   p[2].SetVertex(2, currpoint);
   p[5].SetVertex(3, currpoint);

   currpoint.x = -nearx;
   currpoint.y = -neary;
   p[0].SetVertex(2, currpoint);
   p[4].SetVertex(3, currpoint);
   p[5].SetVertex(2, currpoint);

   currpoint.x = -farx;
   currpoint.y = fary;
   currpoint.z = farz;
   p[1].SetVertex(0, currpoint);
   p[2].SetVertex(1, currpoint);
   p[5].SetVertex(0, currpoint);

   currpoint.x = -farx;
   currpoint.y = -fary;
   p[1].SetVertex(3, currpoint);
   p[4].SetVertex(0, currpoint);
   p[5].SetVertex(1, currpoint);

   currpoint.x = farx;
   currpoint.y = fary;
   p[1].SetVertex(1, currpoint);
   p[2].SetVertex(0, currpoint);
   p[3].SetVertex(1, currpoint);

   currpoint.x = farx;
   currpoint.y = -fary;
   p[1].SetVertex(2, currpoint);
   p[3].SetVertex(0, currpoint);
   p[4].SetVertex(1, currpoint);

   GraphicMatrix m;

   m.rotatex(-rots.x);
   m.rotatey(rots.y);
   //m.rotatez(rots.z);
   m.translate(pos);

   Vector3 currv;
   for (int i = 0; i < 6; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         currv = p[i].GetVertex(j);
         currv.transform(m.members);
         p[i].SetVertex(j, currv);
      }
   }
}


#ifndef DEDICATED
void ObjectKDTree::setfrustum(const Camera& cam, float nearz, float farz, float fov, float aspect, bool reflection)
{
   Vector3 actual = cam.GetActual();
   Vector3 look = cam.GetActualLook();
   // We always need the look direction, not the point
   look -= actual;

   Vector3 rots = RotateBetweenVectors(Vector3(0, 0, -1), look);
   if (reflection)
   {
      rots.x *= -1.f;
      actual.y *= -1.f;
   }
   setfrustum(actual, rots, nearz, farz, fov, aspect);
}
#endif


void ObjectKDTree::setfrustum(Quadvec* newp)
{
   frustum = newp;
   if (haschildren)
   {
      children[0]->setfrustum(frustum);
      children[1]->setfrustum(frustum);
   }
}


void ObjectKDTree::setvertices(Vector3vec v)
{
   vertices = v;

   vertices[1].x = v[0].x;
   vertices[1].y = v[0].y;
   vertices[1].z = v[6].z;

   vertices[2].x = v[6].x;
   vertices[2].y = v[0].y;
   vertices[2].z = v[6].z;

   vertices[3].x = v[6].x;
   vertices[3].y = v[0].y;
   vertices[3].z = v[0].z;

   vertices[4].x = v[0].x;
   vertices[4].y = v[6].y;
   vertices[4].z = v[0].z;

   vertices[5].x = v[6].x;
   vertices[5].y = v[6].y;
   vertices[5].z = v[0].z;

   /*vertices[6].x = v[6].x;
   vertices[6].y = v[6].y;
   vertices[6].z = v[6].z;*/

   vertices[7].x = v[0].x;
   vertices[7].y = v[6].y;
   vertices[7].z = v[6].z;
}


int ObjectKDTree::size()
{
   return members.size();
}


void ObjectKDTree::setretobjs(MeshSet* in)
{
   retobjs = in;
   if (haschildren)
   {
      children[0]->setretobjs(retobjs);
      children[1]->setretobjs(retobjs);
   }
}


// Grr, some of these quads are defined backwards, hence the disable face culling
void ObjectKDTree::visualize()
{
#ifndef DEDICATED
   float alpha = .05;
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_FOG);
   glDisable(GL_CULL_FACE);
   glEnable(GL_COLOR_MATERIAL);
   extern Material* skyboxmat; // Hack!  But then this whole function is a hack...
   skyboxmat->Use();
   glColor4f(0, 0, 1, alpha);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   glBegin(GL_QUADS);
   glVertex3f(vertices[0].x - 1, vertices[0].y - 1, vertices[0].z - 1);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[0].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[0].z);
   glVertex3f(vertices[6].x - 1, vertices[0].y - 1, vertices[0].z - 1);
   glEnd();

   glColor4f(1, 0, 1, alpha);
   glBegin(GL_QUADS);
   glVertex3f(vertices[0].x - 1, vertices[0].y - 1, vertices[0].z - 1);
   glVertex3f(vertices[0].x, vertices[0].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[0].y, vertices[6].z);
   glVertex3f(vertices[6].x - 1, vertices[0].y - 1, vertices[0].z - 1);
   glEnd();

   glColor4f(1, 1, 1, alpha);
   glBegin(GL_QUADS);
   glVertex3f(vertices[0].x, vertices[0].y, vertices[6].z);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[0].y, vertices[6].z);
   glEnd();

   glColor4f(1, 0, 0, alpha);
   glBegin(GL_QUADS);
   glVertex3f(vertices[0].x - 1, vertices[0].y - 1, vertices[0].z - 1);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[0].z);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[0].x - 1, vertices[0].y - 1, vertices[6].z - 1);
   glEnd();

   glColor4f(1, 1, 0, alpha);
   glBegin(GL_QUADS);
   glVertex3f(vertices[6].x, vertices[0].y, vertices[0].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[0].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[0].y, vertices[6].z);
   glEnd();

   glColor4f(0, 0, 0, alpha);
   glBegin(GL_QUADS);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[0].z);
   glVertex3f(vertices[0].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
   glVertex3f(vertices[6].x, vertices[6].y, vertices[0].z);
   glEnd();

   glColor4f(1, 1, 1, 1);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_FOG);
   glDisable(GL_COLOR_MATERIAL);

   if (!haschildren) return;
   for (int i = 0; i < 2; ++i)
      children[i]->visualize();
#endif
}
