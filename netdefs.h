#ifndef __NETDEFS_H
#define __NETDEFS_H

#include <string>
#include <list>
#include <vector>
#include <set>
#include "ServerInfo.h"
#include "CollisionDetection.h"
#include "PlayerData.h"
#include "Particle.h"
#include "SDL.h"
#include "IDGen.h"

const char eol = '\n';

extern bool running, connected, doconnect, pingresponse, spawnrequest, spawnschanged, sendkill;
extern unsigned long recpacketnum, ackpack;
extern IDGen sendpacketnum;
extern set<unsigned long> partids;
extern SDL_Thread* netout;
extern SDL_Thread* netin;
extern vector<ServerInfo> servers;
extern set<ServerInfo> knownservers;
extern string chatstring;
extern vector<string> newchatlines;
extern vector<unsigned short> newchatplayers;
extern short changeteam;
extern bool useitem;
extern vector<Meshlist::iterator> deletemeshes;
extern deque<string> consolecommands;

void HandleAck(unsigned long);

#endif
