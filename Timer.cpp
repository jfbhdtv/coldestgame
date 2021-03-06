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


#include "Timer.h"

Timer::Timer() : starttick(SDL_GetTicks())
{
}


void Timer::start()
{
   starttick = SDL_GetTicks();
}


Uint32 Timer::stop()
{
   logout << "Time: " << (SDL_GetTicks() - starttick) << endl;
   return (SDL_GetTicks() - starttick);
}


Uint32 Timer::elapsed()
{
   return (SDL_GetTicks() - starttick);
}
