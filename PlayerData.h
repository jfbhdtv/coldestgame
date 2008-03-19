#ifndef __PLAYERDATA
#define __PLAYERDATA

#include "Vector3.h"
#include <list>
#include <set>
#include "SDL_net.h"
#include "DynamicObject.h"
#include "Mesh.h"
#include "Hit.h"
#include "types.h"

class PlayerData
{
   public:
      PlayerData(Meshlist&);
      void Disconnect();
      
      Vector3 pos;
      Vector3 clientpos; // So server can keep track of both
      float pitch, rotation, roll, facing;
      bool moveforward, moveleft, moveright, moveback;
      bool leftclick, rightclick;
      bool run;
      bool spawned;
      Meshlist::iterator torso, legs, larm, rarm;
      set<unsigned long> partids;
      //set<unsigned long> hitids;
      set<unsigned long> acked;
      //list<Hit> servhits;  // Used by server only
      vector<short> weapons;
      Uint32 lastupdate;  // How long since last player update?
      Uint32 lastmovetick;
      Uint32 lastfiretick;
      Uint32 lastcoolingtick;
      float size;
      float fallvelocity;
      short id;
      IPaddress addr;
      bool connected;
      unsigned long recpacketnum;
      short unit;
      short currweapon;
      short pingtick;
      short ping;
      short hp[numbodyparts];
      short kills, deaths;
      float temperature;
      string name;
      
   private:
      Meshlist* meshes;
};
#endif
