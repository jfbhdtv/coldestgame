#include "Item.h"

Item::Item(const int newid) : id(newid), usesleft(1), coolmultiplier(1.f), ammomultiplier(1.f), weight(0.f), name("None")
{
   switch (newid)
   {
      case Item::NoItem:
         break;
      case Item::SpawnPoint:
         LoadFromFile("items/spawn");
         break;
      case Item::HeatSink:
         LoadFromFile("items/heatsink");
         break;
      case Item::AmmoCarrier:
         LoadFromFile("items/ammocarrier");
         break;
      case Item::Radar:
         LoadFromFile("items/radar");
         break;
      default:
         cout << "Warning: attempted to create non-existent item." << endl;
         break;
   };
}


void Item::LoadFromFile(const string& file)
{
   IniReader read(file);
   
   read.Read(usesleft, "Uses");
   read.Read(coolmultiplier, "CoolMult");
   read.Read(ammomultiplier, "AmmoMult");
   read.Read(weight, "Weight");
   read.ReadLine(name, "Name");
}


