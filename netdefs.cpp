#include "netdefs.h"

bool running, connected, doconnect, pingresponse, spawnrequest, spawnschanged;
unsigned long recpacketnum, ackpack;
IDGen sendpacketnum;
set<unsigned long> partids;
vector<ServerInfo> servers;
set<ServerInfo> knownservers;
SDL_Thread* netout;
SDL_Thread* netin;
string chatstring;
vector<string> newchatlines;
vector<unsigned short> newchatplayers;
short changeteam;

