#ifndef __PARTICLE
#define __PARTICLE

#include <list>
#include <stack>
#include "CollisionDetection.h"
#include "Vector3.h"
#include "Timer.h"
#include "DynamicObject.h"
#include "SDL.h"
#include "SDL_thread.h"

using namespace std;

class Particle
{
   public:
      Particle(Mesh&);
      Particle(Vector3, Vector3, float, float, float, float, bool, Uint32, Mesh&);
      bool Update(Mesh&);
      CollisionDetection *cd;
      bool unsent;
      unsigned short senttimes;
      short playernum;
      unsigned long id;
      unsigned long playerid;
      
      Vector3 dir;
      Vector3 pos;
      float velocity;
      float accel;
      float weight;
      float radius;
      bool explode;
      Uint32 lasttick;
      stack<Mesh*> hitobjs;
      int damage;
      float dmgrad;
      Mesh mesh;
      
   private:
      static unsigned long nextid;
};

#endif
