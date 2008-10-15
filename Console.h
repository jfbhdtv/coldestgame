#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <map>
#include <iostream>
#include <string>
#include <deque>
#include <set>
#include "gui/TextArea.h"
#include "renderdefs.h"
#include "netdefs.h"
#include "Packet.h"

using std::map;
using std::string;
using std::endl;
using std::deque;
using std::set;
using std::inserter;

class Console
{
   public:
      Console();
      int GetInt(const string&);
      float GetFloat(const string&);
      string GetString(const string&);
      bool GetBool(const string&);
      void Parse(const string&, bool echo = true);
      void InitWidget(TextArea&);
      void WriteToConsole(const string&);
      void SaveToFile(const string&, const bool forcesave = false);
      
      
   private:
      int NumTokens(const string&);
      string Token(const string&, int);
      string SimplifyWhitespace(const string&);
      void Action(const string&);
      void Lock() {SDL_mutexP(mutex);}
      void Unlock() {SDL_mutexV(mutex);}
      
      map<string, string> values;
      set<string> saveval;
      deque<string> consolebuffer;
      TextArea* consoleout;
      SDL_mutex* mutex;
};

void SetupSDL();
void SetupOpenGL();
void Quit();

#endif
