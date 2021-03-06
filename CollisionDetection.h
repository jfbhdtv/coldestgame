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


#ifndef __COLLISION_DETECTION
#define __COLLISION_DETECTION

#include <vector>
#include <list>
#include "ObjectKDTree.h"
#include "Vector3.h"
#include "Quad.h"
#include "Timer.h"
#include "Map.h"
#include <SDL/SDL_thread.h>

//#define INLINE_COLDET

class CollisionDetection
{
   public:
      CollisionDetection();
      // Note that you cannot pass in null for the last non-defaulted parameter
      bool CheckSphereHit(const Vector3&, const Vector3&, const float&, vector<Mesh*>&, MapPtr, Vector3&, Mesh*&, Vector3vec* retval = NULL, 
                             vector<Mesh*>* = NULL, const bool debug = false);
      bool CheckSphereHit(const Vector3&, const Vector3&, const float&, vector<Mesh*>&, MapPtr, Vector3vec* retval = NULL, const bool debug = false);
      // Useful for external code too
      float DistanceBetweenPointAndLine(const Vector3&, const Vector3&, const Vector3&, const float);
      bool UnitTest();
      
      int intmethod;
      
   private:
      void CheckMain(const Vector3& oldpos,
                     const Vector3& newpos,
                     const float radius,
                     const Vector3& move,
                     const float movemaginv,
                     vector<Mesh*>& objs,
                     vector<Mesh*>* retobjs,
                     bool nomove,
                     Vector3vec& adjust,
                     intvec& adjusted,
                     vector<Triangle*>& neartris,
                     map<Triangle*, Mesh*>& trimap,
                     Triangle*& hittri,
                     Vector3& hitpos);
      void CheckEdges(const Vector3& oldpos,
                     const Vector3& newpos,
                     const float radius,
                     const Vector3& move,
                     const float movemaginv,
                     vector<Mesh*>* retobjs,
                     bool nomove,
                     Vector3vec& adjust,
                     intvec& adjusted,
                     vector<Triangle*>& neartris,
                     map<Triangle*, Mesh*>& trimap,
                     Triangle*& hittri,
                     Vector3& hitpos);
      void CheckCorners(const Vector3& oldpos,
                        const Vector3& newpos,
                        const float radius,
                        const Vector3& move,
                        const float movemaginv,
                        vector<Mesh*>* retobjs,
                        bool nomove,
                        Vector3vec& adjust,
                        intvec& adjusted,
                        vector<Triangle*>& neartris,
                        map<Triangle*, Mesh*>& trimap,
                        Triangle*& hittri,
                        Vector3& hitpos);
      void CheckWorldBounds(const Vector3& oldpos,
                           const Vector3& newpos,
                           const float radius,
                           MapPtr map,
                           Vector3vec& adjust,
                           intvec& adjusted,
                           Vector3& hitpos);
      
      bool PlaneSphereCollision(Vector3&, const Triangle&, Vector3, const Vector3&, const float&, Vector3&, const bool nomove, const bool debug = false);
      bool PlaneEdgeSphereCollision(Vector3&, const Triangle&, const Vector3&, const float&);
      bool VectorEdgeCheck(Vector3&, Vector3&, const Triangle&, const Vector3&, const Vector3&, const float&);
      bool InVector(Mesh*, vector<Meshlist::iterator>&);
      bool CrossesPlane(const Vector3&, const Vector3&, const Vector3&, const Vector3&, float&, Vector3&);
      bool CrossesPlane(const Vector3&, const Vector3&, const Vector3&, const float&, float&, Vector3&);
      bool CrossesPlane(const Vector3&, const Vector3&, const Vector3&, const float&, float&, Vector3&, float&, Vector3&);
      float DistanceBetweenLines(const Vector3& start, const Vector3& dir, const Vector3& start1, const Vector3& dir1, float&, float&);
      bool RaySphereCheck(const Vector3& raystart, const Vector3& rayend,
                     const Vector3& spherepos, const float radius, Vector3&, Vector3&, bool extcheck = true);
      bool RayCylinderCheck(const Vector3&, const Vector3&,
            const Vector3&, const Vector3&, const float,
            Vector3&, Vector3&, Vector3&);
};

// From http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
#ifdef INLINE_COLDET
inline
float CollisionDetection::DistanceBetweenPointAndLine(const Vector3& point, const Vector3& start, const Vector3& move, const float movemaginv)
{
   // This check is not required for any code that calls us and it helps performance significantly if we don't do it
   //if (movemag < 1e-5f) return 0.f;
   return(move.cross(start - point).magnitude() * movemaginv);
}
#endif
#endif
