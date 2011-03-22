#ifndef NETCODE_H
#define NETCODE_H

#include "Packet.h"
#include "IDGen.h"
#include "Timer.h"
#include <SDL_net.h>
#include <list>

using std::list;

class NetCode
{
   public:
      NetCode();
      virtual ~NetCode();
      virtual void Update();
      void SendPacket(Packet&);
      static int Version(){return version;}

   protected:
      // No copying
      NetCode(const NetCode&);
      NetCode& operator=(const NetCode&);
      virtual void HandlePacket(stringstream&){}
      void HandleAck(const unsigned long);
      void Ack(const unsigned long);
      virtual void Send(){}
      
      void SendLoop();
      
      virtual void Receive();
      virtual void ReceiveExtended(){}

      UDPsocket socket;
      UDPpacket* packet;
      IPaddress address;

      Uint32 lastnettick;
      Uint32 currnettick;
      IDGen sendpacketnum;
      bool error;

      stringstream get;
      string getdata;
      string packettype;
      unsigned long packetnum;

      const static int version;

      size_t sendbps;
      Timer sentbytestimer;

   private:
      list<Packet> sendqueue;
};

#endif // NETCODE_H