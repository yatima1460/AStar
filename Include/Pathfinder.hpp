#pragma once

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);


#ifdef GOOGLE_TEST
#include <vector>
std::vector<int> GetNeighboursIndexes(const unsigned char *pMap,const int currentIndex,const int nMapWidth,const int nMapHeight);
#endif