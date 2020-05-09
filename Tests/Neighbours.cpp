// #include <Pathfinder.hpp>

// #include "gtest/gtest.h"





// TEST(GetNeighbours, AllWalkable)
// {
//     unsigned char pMap[] = 
//     {
//     0, 1, 0, 
//     1, 1, 1, 
//     0, 1, 0
//     };

//     const std::vector<int> nResults = {1,5,7,3};
  
//     EXPECT_EQ(GetNeighboursIndexes(pMap, 4, 3, 3), nResults);
    
// }




// TEST(GetNeighbours, Sample2)
// {
//     unsigned char pMap[] = 
//     {
//     0, 0, 1, 
//     0, 1, 1, 
//     1, 0, 1
//     };

//     const std::vector<std::vector<int>> nResults = {{},{2,4},{5},{4,6},{5},{2,8,4},{},{4,8,6},{5}};
//     for (size_t i = 0; i < 9; i++)
//         EXPECT_EQ(GetNeighboursIndexes(pMap, i, 3, 3), nResults[i]);
    
// }



// TEST(GetNeighbours, OneXOneMap)
// {
//     unsigned char pMap[] = 
//     {
//     0
//     };
//     const auto result = GetNeighboursIndexes(pMap, 0, 1, 1);
//     EXPECT_EQ(result.size(), 0);
// }




// TEST(GetNeighbours, LinearMap)
// {
//     unsigned char pMap[] = 
//     {
//     1, 1, 1, 1, 1
//     };

//     const std::vector<std::vector<int>> nResults = {
//         {1},{0,2},{1,3},{2,4},{3},
  
//     };
//     for (size_t i = 0; i < 4; i++)
//         EXPECT_EQ(GetNeighboursIndexes(pMap, i, 1, 5), nResults[i]);
    
      
// }



// TEST(GetNeighbours, LongBoi)
// {
//      const auto cellsCount = 10000;
//     unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * cellsCount);
//     memset(pMap,1,cellsCount);
//     int pOutBuffer[5];
//     const int result = FindPath(0, 0, cellsCount-1, 0, pMap, cellsCount, 1, pOutBuffer, 5);

//     EXPECT_EQ(result, cellsCount-1);
//     free(pMap);
// }


// TEST(GetNeighbours, NoneWalkable)
// {
//     unsigned char pMap[] = 
//     {
//     0, 0, 0, 
//     0, 1, 0, 
//     0, 0, 0
//     };

//     const std::vector<int> nResults;
  
//     EXPECT_EQ(GetNeighboursIndexes(pMap, 4, 3, 3), nResults);
    
// }


// TEST(GetNeighbours, AShapedHorizontalMap)
// {
//     unsigned char pMap[] = 
//     {
//     1, 1, 1, 1, 1,
//     1, 0, 1, 0, 0,
//     1, 1, 1, 1, 1
//     };

//     const std::vector<std::vector<int>> nResults = {
//         {1,5},{2,0},{3,7,1},{4,2},{3},
  
//     };
//     for (size_t i = 0; i < 4; i++)
//         EXPECT_EQ(GetNeighboursIndexes(pMap, i, 5, 3), nResults[i]);
    
      
// }