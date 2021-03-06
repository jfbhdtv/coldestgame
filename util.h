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


#ifndef __UTIL_H
#define __UTIL_H

#include <string>
#include <sstream>
#include <iomanip>
#include <csignal>
#include <SDL/SDL.h>
#include "Vector3.h"
#include "GraphicMatrix.h"
#include "tsint.h"
#include "logout.h"

using std::string;
using std::stringstream;
using std::ostringstream;

#ifdef _WIN32
typedef long pid_t;
#endif

string PadNum(int, int);
string AddressToDD(Uint32);
bool floatzero(float, float error = .00001);
float Random(float min, float max);
Vector3 RotateBetweenVectors(Vector3, const Vector3&);
pid_t gettid();
int bitcount();
void setsighandler();
vector<string> split(const string&, const string&);
string ToString(const float, const int);

extern bool running;

template <typename T>
string ToString(const T &input)
{
   stringstream temp;
   temp << input;
   return temp.str();
}


template <typename T>
int ToInt(const T &input, std::ios_base& (*f)(std::ios_base&) = std::dec)
{
   stringstream temp;
   temp << input;
   int retval;
   temp >> f >> retval;
   return retval;
}


template <typename T>
T lerp(T x, T y, float a)
{
   return (x * a + y * (1.f - a));
}

template <typename T>
T smoothstep(T x, T y, T a)
{
   if (a < x) return 0;
   if (a > y) return 1;
   return ((a - x) / (y - x));
}

template <typename T>
T clamp(T min, T max, T val)
{
   if (val < min) return min;
   if (val > max) return max;
   return val;
}


// Compares two subscriptable containers to see if their contents are the same
template <typename T>
bool equal(T first, T second)
{
   size_t fsize = first.size();
   if (fsize != second.size()) return false;
   
   for (size_t i = 0; i < fsize; ++i)
   {
      if (first[i] != second[i])
         return false;
   }
   return true;
}

#endif
