#ifndef __PROCEDURALTREE_H
#define __PROCEDURALTREE_H

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include "WorldObjects.h"
#include "GraphicMatrix.h"

using namespace std;

class ProceduralTree
{
   public:
      ProceduralTree();
      long GenTree(list<WorldObjects>::iterator);
      void ReadParams(ifstream&);
      
      int numlevels;
      int firstleaflevel;
      int numslices;
      int numbranches[10];
      int totalprims;
      int numsegs;
      int numleaves;
      int randseed;
      int trunknumslices;
      int trunknumsegs;
      int branchevery;
      int sidebranches;
      int sidebranchdirection;
      float maxangle;
      float minangle;
      float maxbranchangle;
      float initrad;
      float radreductionperc;
      float initheight;
      float heightreductionperc;
      float leafsize;
      float trunkrad;
      float trunktaper;
      float maxsidebranchangle;
      float minheightvar;
      float maxheightvar;
      float sidetaper;
      bool continuebranch;
      bool multitrunk;
      bool split;
      bool branchwithleaves;
      list<WorldObjects>::iterator object;
      
   private:
      void GenBranch(GraphicMatrix, int, int, vector<Vector3>, bool, int);
      float Random(float, float);
      
      
};

#endif
