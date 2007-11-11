#ifndef __TEXTURE_MANAGER_H
#define __TEXTURE_MANAGER_H

#include "TextureHandler.h"
#include <SDL_opengl.h>
#include <map>
#include <set>

using std::map;
using std::set;
using std::make_pair;

class TextureManager
{
   public:
      TextureManager(TextureHandler* th = NULL);
      ~TextureManager();
      void LoadTexture(string);
      void BindTexture(string);
      TextureHandler* texhand;
      
   private:
      map<string, GLuint> texnames;
      set<string> loaded;
};

#endif
