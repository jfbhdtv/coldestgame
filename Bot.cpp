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
// Copyright 2008, 2011 Ben Nemec
// @End License@


#include "Bot.h"

// Static initialization
vector<PlayerData> Bot::players = vector<PlayerData>();
MutexPtr Bot::playermutex = MutexPtr();
vector<PathNodePtr> Bot::pathnodes = vector<PathNodePtr>();

// Should leave thread to be initialized last so that all other data has been initialized first
Bot::Bot() : botrunning(true),
             netcode(new BotNetCode()),
             targetplayer(0)
{
   timer.start();
   movetimer.start();
   thread = SDL_CreateThread(Start, this);
}


Bot::~Bot()
{
   logout << "Bot id " << netcode->id << " shutting down." << endl;
   botrunning = false;
   SDL_WaitThread(thread, NULL);
}


// static
int Bot::Start(void* obj)
{
   setsighandler();
   
   logout << "Bot id " << gettid() << " started." << endl;
   
   ((Bot*)obj)->Loop();
   return 0;
}


void Bot::Loop()
{
   netcode->id = gettid();
   while (botrunning)
   {
      while (updatetimer.elapsed() < 1000 / console.GetInt("tickrate"))
      {
         SDL_Delay(1);
      }
      updatetimer.start();
      Update();
      netcode->Update();
   }
}


void Bot::Update()
{
   localplayers = GetPlayers();
   
   // Movement
   if (netcode->bot.moveleft)
      netcode->bot.facing -= .1f * movetimer.elapsed();
   if (netcode->bot.moveright)
      netcode->bot.facing += .1f * movetimer.elapsed();
   movetimer.start();
   if (console.GetBool("botsmove") && netcode->bot.spawned)
   {
      if (!currpathnode)
         FindCurrPathNode();
      
      if (!targetplayer || !localplayers[targetplayer].spawned)
         targetplayer = SelectTarget();
      
      if (targetplayer)
      {
         UpdateHeading();
         
         AimAtTarget(targetplayer);
         
         // Weapons fire
         if (firetimer.elapsed() > netcode->bot.CurrentWeapon().ReloadTime() &&
            netcode->bot.temperature < 100.f - netcode->bot.CurrentWeapon().Heat()
         )
         {
            netcode->SendFire();
            firetimer.start();
         }
      }
   }
   else if (!netcode->bot.spawned)
   {
      currpathnode = PathNodePtr();
   }
}


int Bot::SelectTarget()
{
   // Build list of players on the other team
   intvec otherteam;
   for (int i = 1; i < localplayers.size(); ++i)
   {
      if (i != netcode->PlayerNum())
      {
         if (localplayers[i].team != localplayers[netcode->PlayerNum()].team && localplayers[i].spawned)
         {
            otherteam.push_back(i);
         }
      }
   }
   
   if (!otherteam.size())
      return 0;

   size_t index = Random(0, otherteam.size() - 1e-5f);
   return otherteam[index];
}


void Bot::AimAtTarget(int target)
{
   Vector3 aimvec = localplayers[target].pos - localplayers[netcode->PlayerNum()].pos;
   
   Vector3 facingvec(0.f, 0.f, -1.f);
   GraphicMatrix m;
   m.rotatey(netcode->bot.facing);
   facingvec.transform(m);
   
   Vector3 rots = RotateBetweenVectors(facingvec, aimvec);
   
   netcode->bot.rotation = rots.y + Random(-3.f, 3.f);
   netcode->bot.pitch = rots.x + Random(-1.f, 1.f);
}


// This will probably be a touch slow, but it won't need to be done much so that should be okay
void Bot::FindCurrPathNode()
{
   float currdist = 1e38f;
   for (size_t i = 0; i < pathnodes.size(); ++i)
   {
      float checkdist = pathnodes[i]->position.distance2(netcode->bot.pos);
      if (checkdist < currdist)
      {
         currdist = checkdist;
         currpathnode = pathnodes[i];
      }
   }
}


void Bot::UpdateHeading()
{
   Vector3 direct = localplayers[targetplayer].pos - localplayers[netcode->PlayerNum()].pos;
   direct.normalize();
   direct *= 100.f;
   Vector3 current = direct;
   
   while (!currpathnode->Validate(current, netcode->bot.size))
   {
      
   }
}

// This must be called before creating bots
//static
void Bot::Initialize()
{
   if (!playermutex)
      playermutex = MutexPtr(new Mutex);
}

//static
void Bot::SetPlayers(vector<PlayerData>& in)
{
   playermutex->lock();
   players = in;
   playermutex->unlock();
}

//static
vector<PlayerData> Bot::GetPlayers()
{
   playermutex->lock();
   vector<PlayerData> retval = players;
   playermutex->unlock();
   return retval;
}

