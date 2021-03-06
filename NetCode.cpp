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
#include "NetCode.h"
#include "ServerInfo.h"
#include "globals.h"
#include <iostream>

using std::endl;

const int NetCode::version = 8;

NetCode::NetCode() : lastnettick(SDL_GetTicks()),
                     currnettick(0),
                     error(false),
                     sendbps(0),
                     sentbytes(0)
{
   sendpacketnum.next(); // 0 has special meaning
   if (!(packet = SDLNet_AllocPacket(5000))) // 5000 is somewhat arbitrary
   {
      logout << "SDLNet_AllocPacket: " << SDLNet_GetError() << endl;
      error = true;
   }
   
   // Keep a universal list of packets that need acking so we don't have to handle it specially in every subclass
   acktypes.insert("h");
   acktypes.insert("s");
   acktypes.insert("D");
   acktypes.insert("m");
   acktypes.insert("O");
   acktypes.insert("r");
   acktypes.insert("T");
   acktypes.insert("I");
   acktypes.insert("K");
   acktypes.insert("P");
   acktypes.insert("f");
   acktypes.insert("t");
   acktypes.insert("L");
   acktypes.insert("d");
   acktypes.insert("R");
   acktypes.insert("Y");
}

NetCode::~NetCode()
{
   SDLNet_FreePacket(packet);
   SDLNet_UDP_Close(socket);
}


void NetCode::Update()
{
   if (!error)
   {
      Receive();
      Send();
      SendLoop();
   }
}


void NetCode::SendLoop()
{
   list<Packet>::iterator i = sendqueue.begin();
   Uint32 currtick = SDL_GetTicks();
   while (i != sendqueue.end())
   {
      if (i->sendtick <= currtick)
      {
         sentbytes += i->Send(packet, socket);
         if (!i->ack || i->attempts > 5000) // Non-ack packets get sent once and then are on their own
         {
            i = sendqueue.erase(i);
            continue;
         }
      }
      ++i;
   }

   if (sentbytestimer.elapsed() > 1000)
   {
      sendbps = (size_t)((float)sentbytes / (float)sentbytestimer.elapsed() * 1000.f);
      sentbytes = 0;
      sentbytestimer.start();
   }
}


void NetCode::SendPacket(Packet& p)
{
   sendqueue.push_back(p);
}


void NetCode::Receive()
{
   while (SDLNet_UDP_Recv(socket, packet))
   {
      getdata = (char*)packet->data;
      stringstream get(getdata);

      get >> packettype;
      get >> packetnum;

      HandlePacket(get);
      
      DoAck();
   }

   ReceiveExtended();
}


void NetCode::HandleAck(const unsigned long acknum)
{
   for (list<Packet>::iterator i = sendqueue.begin(); i != sendqueue.end(); ++i)
   {
      if (i->ack == acknum)
      {
         sendqueue.erase(i);
         break;
      }
   }
}


void NetCode::Ack(const unsigned long acknum)
{
   Packet response(&address);
   response << "A\n";
   response << 0 << eol;
   response << acknum << eol;
   SendPacket(response);
}


// If you need to use a different Ack function, you will need to override this
void NetCode::DoAck()
{
   if (acktypes.find(packettype) != acktypes.end())
      Ack(packetnum);
}





