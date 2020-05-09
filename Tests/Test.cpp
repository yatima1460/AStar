
#include <Pathfinder.hpp>

#include "gtest/gtest.h"


TEST(Pathfinding, Square3x3)
{
    unsigned char pMap[] =
    {
    1, 1, 1,
    1, 0, 1,
    1, 1, 1,
    };

    int pOutBuffer[9];
    const int result = FindPath(2, 1, 0, 2, pMap, 3, 3, pOutBuffer, 9);

    EXPECT_NE(result, -1);
    EXPECT_EQ(pOutBuffer[0], 8);

}

TEST(Pathfinding, Sample1)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 
    0, 1, 0, 1, 
    0, 1, 1, 1
    };
    int pOutBuffer[12];

    const int result = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    EXPECT_EQ(result, 3);
    EXPECT_EQ(pOutBuffer[0], 1);
    EXPECT_EQ(pOutBuffer[1], 5);
    EXPECT_EQ(pOutBuffer[2], 9);
}

// #include <unordered_map>
// TEST(OpenComparer, Sample1)
// {
//     class OpenComparer{
//     std::unordered_map<int, int>& node_f_local;
// public:
//     OpenComparer(std::unordered_map<int, int>& node_f) : node_f_local(node_f) {}
//     bool operator()(int a, int b) const {
   
//         //const bool infinity = node_f_local.find(b) == node_f_local.end();
//         return node_f_local[a] < node_f_local[b];
    
//     };


//     std::set<int, OpenComparer> open(cmp);
// };



//     EXPECT_EQ(result, 3);
//     EXPECT_EQ(pOutBuffer[0], 1);
//     EXPECT_EQ(pOutBuffer[1], 5);
//     EXPECT_EQ(pOutBuffer[2], 9);
// }


TEST(Pathfinding, Sample2)
{
    unsigned char pMap[] = 
    {
    0, 0, 1, 
    0, 1, 1, 
    1, 0, 1
    };
    int pOutBuffer[7];
    const int result = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

    EXPECT_EQ(result, -1);
}


TEST(Pathfinding, SourceEqualTarget)
{
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[99];

    const int result = FindPath(1, 2, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    EXPECT_EQ(result, 0);
}






TEST(Pathfinding, Backtracking1)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1
    };

    int pOutBuffer[70];
    const int result = FindPath(6, 2, 0, 2, pMap, 7, 5, pOutBuffer, 70);

    EXPECT_NE(result, -1);
    
}







TEST(Pathfinding, Rectangle)
{
    unsigned char pMap[] = 
    {
    1, 1, 1,
    1, 0, 1,
    1, 0, 1,
    1, 1, 1
    };

    

    int pOutBuffer[4];
    const int result = FindPath(2, 2, 0, 2, pMap, 3, 5, pOutBuffer, 4);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(pOutBuffer[0], 11);

}



TEST(Pathfinding, Backtracking2)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1
    };

    int pOutBuffer[9];
    const int result = FindPath(6, 2, 0, 3, pMap, 7, 5, pOutBuffer, 9);

    EXPECT_NE(result, -1);
    EXPECT_EQ(pOutBuffer[0], 27);

}




TEST(Pathfinding, TwoXOneMapHorizontal)
{
    unsigned char pMap[] = 
    {
    1, 1
    };
    int pOutBuffer[5];
    const int result = FindPath(1, 0, 0, 0, pMap, 2, 1, pOutBuffer, 5);

    const int path[] = {0};
    EXPECT_EQ(result, 1);

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}

TEST(Pathfinding, TwoXOneMapVertical)
{
    unsigned char pMap[] = 
    {
    1, 
    1
    };
    int pOutBuffer[5];
    const int result = FindPath(0, 0, 0, 1, pMap, 1, 2, pOutBuffer, 5);

    const int path[] = {1};
    EXPECT_EQ(result, 1);

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}



// TEST(Pathfinding, Evil3)
// {
//     unsigned char pMap[] = 
//     {
//     1
//     };
//     int pOutBuffer[5];
//     const int result = FindPath(8, 0, 1, 7, pMap, 9, 8, pOutBuffer, 5);

    
//     EXPECT_EQ(result, 14);
      
// }


TEST(Pathfinding, Evil2)
{
    unsigned char pMap[] = 
    {
    1,0,1,0,1,0,1,0,1,
    1,1,1,1,1,1,1,1,1,
    1,0,1,0,1,0,1,0,1,
    1,1,1,1,1,1,1,1,1,
    1,0,1,0,1,0,1,0,1,
    1,1,1,1,1,1,1,1,1,
    1,0,1,0,1,0,1,0,1,
    1,1,1,1,1,1,1,1,1,
    };
    int pOutBuffer[5];
    const int result = FindPath(8, 0, 1, 7, pMap, 9, 8, pOutBuffer, 5);

    
    EXPECT_EQ(result, 14);
      
}

TEST(Pathfinding, Evil1)
{
    unsigned char pMap[] = 
    {
    1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,1,0,0,0,1,
    1,1,1,1,0,1,0,0,0,1,
    1,0,0,0,0,1,1,1,1,1,
    1,1,1,0,1,1,0,1,0,1,
    1,0,0,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1
    };
    int pOutBuffer[5];
    const int result = FindPath(0, 0, 3, 4, pMap, 10, 10, pOutBuffer, 5);

    
    EXPECT_EQ(result, 35);
      
}





//TODO:  pOutBuffer bounds segfault test 

TEST(Pathfinding, AShapedHorizontalMap)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1,
    1, 0, 1, 0, 0,
    1, 1, 1, 1, 1
    };
    int pOutBuffer[6];
    const int result = FindPath(4, 0, 4, 2, pMap, 5, 3, pOutBuffer, 6);
    EXPECT_EQ(result, 6);
    std::vector<int> mapgood(pOutBuffer, pOutBuffer+result);
    const int path[] = {3,2,7,12,13,14};
    

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}








TEST(Pathfinding, UShapedHorizontalMap)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1,
    1, 0, 0, 0, 0,
    1, 1, 1, 1, 1
    };
    int pOutBuffer[11];
    const int result = FindPath(4, 0, 4, 2, pMap, 5, 3, pOutBuffer, 11);

    const int path[] = {3,2,1,0,5,10,11,12,13,14};
    EXPECT_EQ(result, 10);

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}


TEST(Pathfinding, pOutBufferSmallerThanPath)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1,
    1, 0, 0, 0, 0,
    1, 1, 1, 1, 1
    };
    int pOutBuffer[3];
    pOutBuffer[2] = 0xDEADBEEF;
    const int result = FindPath(4, 0, 4, 2, pMap, 5, 3, pOutBuffer, 2);

    const int path[] = {3,2,1,0,5,10,11,12,13,14};
    EXPECT_EQ(result, 10);



    EXPECT_EQ(pOutBuffer[0], path[0]);
    EXPECT_EQ(pOutBuffer[1], path[1]);
    EXPECT_EQ(pOutBuffer[2], 0xDEADBEEF);
      
}




TEST(Pathfinding, EightShapedHorizontalMap)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1,
    1, 0, 1, 0, 1,
    1, 1, 1, 1, 1
    };
    int pOutBuffer[3];
    const int result = FindPath(4, 0, 4, 2, pMap, 5, 3, pOutBuffer, 3);

    const int path[] = {9,14};
    EXPECT_EQ(result, 2);

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}




TEST(Pathfinding, LinearMap)
{
    unsigned char pMap[] = 
    {
    1, 1, 1, 1, 1
    };
    int pOutBuffer[5];
    const int result = FindPath(0, 0, 4, 0, pMap, 5, 1, pOutBuffer, 5);

    const int path[] = {1,2,3,4};
    EXPECT_EQ(result, 4);

    for (int i = 0; i < result; i++)
    {
        EXPECT_EQ(pOutBuffer[i], path[i]);
    }
      
}

TEST(Pathfinding, SquareWalkable10x10Map)
{
    const auto cellsCount = 10*10;
    unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * cellsCount);
    
    //memset(pMap,1, cellsCount);
    for (int i = 0; i < cellsCount; i++)
    {
        pMap[i] = 1;
    }
    int pOutBuffer[50];
    
    assert(pMap[0] == 1);
    assert(pMap[99] == 1);
    const int result = FindPath(0, 0, 9, 9, pMap, 10, 10, pOutBuffer, 50);

   
    EXPECT_NE(result, -1);
    free(pMap);

      
}

TEST(Pathfinding, BigWalkableMap)
{
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 200;
 
    unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * MAP_WIDTH*MAP_HEIGHT);
    assert(pMap != nullptr);
    
    memset(pMap,1, MAP_WIDTH*MAP_HEIGHT);

    int pOutBuffer[5];
    
    assert(pMap[0] == 1);
    assert(pMap[(MAP_WIDTH-1)+(MAP_HEIGHT-1)*MAP_WIDTH] == 1);
    const int result = FindPath(0, 0, MAP_WIDTH-1, MAP_HEIGHT-1, pMap, MAP_WIDTH, MAP_HEIGHT, pOutBuffer, 5);

   
    EXPECT_NE(result, -1);
    free(pMap);

      
}


TEST(Pathfinding, BigWalkableMapWithEndBlocked)
{
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 200;
 
    unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * MAP_WIDTH*MAP_HEIGHT);
    assert(pMap != nullptr);
    
    memset(pMap,1, MAP_WIDTH*MAP_HEIGHT);

    int pOutBuffer[5];
    
    assert(pMap[0] == 1);
    assert(pMap[(MAP_WIDTH-1)+(MAP_HEIGHT-1)*MAP_WIDTH] == 1);
    pMap[(MAP_WIDTH-2)+(MAP_HEIGHT-1)*MAP_WIDTH] = 0;
    pMap[(MAP_WIDTH-1)+(MAP_HEIGHT-2)*MAP_WIDTH] = 0;
    const int result = FindPath(0, 0, MAP_WIDTH-1, MAP_HEIGHT-1, pMap, MAP_WIDTH, MAP_HEIGHT, pOutBuffer, 5);
   
    EXPECT_EQ(result, -1);
    free(pMap);

      
}



TEST(Pathfinding, BigWalkableMapWithStartBlocked)
{
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 200;
 
    unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * MAP_WIDTH*MAP_HEIGHT);
    assert(pMap != nullptr);
    
    memset(pMap,1, MAP_WIDTH*MAP_HEIGHT);

    int pOutBuffer[5];
    
    assert(pMap[0] == 1);
    assert(pMap[(MAP_WIDTH-1)+(MAP_HEIGHT-1)*MAP_WIDTH] == 1);
    pMap[(MAP_WIDTH-2)+(MAP_HEIGHT-1)*MAP_WIDTH] = 0;
    pMap[(MAP_WIDTH-1)+(MAP_HEIGHT-2)*MAP_WIDTH] = 0;
    const int result = FindPath(MAP_WIDTH-1, MAP_HEIGHT-1, 0, 0, pMap, MAP_WIDTH, MAP_HEIGHT, pOutBuffer, 5);
   
    EXPECT_EQ(result, -1);
    free(pMap);

      
}



TEST(Pathfinding, BigBlockedMap)
{
    const auto cellsCount = 100*200;
    unsigned char* pMap = (unsigned char* )malloc( sizeof(unsigned char) * cellsCount);
    memset(pMap, 0, cellsCount);
    pMap[0] = 1;
    pMap[cellsCount-1] = 1;
    int pOutBuffer[5];
    const int result = FindPath(0, 0, 100-1, 200-1, pMap, 5, 1, pOutBuffer, 5);

   
    EXPECT_EQ(result, -1);
    free(pMap);

      
}


#ifndef WIN32
TEST(StaticAnalyzer, CppCheck)
{
    const auto ret = system("cppcheck --enable=warning,performance,portability --error-exitcode=1 -v /home/$(whoami)/Desktop/AStar/Source");
    EXPECT_EQ(ret, 0);
}


TEST(StaticAnalyzer, Clang)
{
    const auto ret = system("clang-tidy /home/$(whoami)/Desktop/AStar/Source/Pathfinder.cpp -checks='*' -- -std=c++17");
    EXPECT_EQ(ret, 0);
}
#endif
  
//unsigned int size map

// TEST(Pathfinder, MapSideIsOne)
// {
//     // unsigned char pMap[] = {1};
//     // int pOutBuffer[12];

//     // const int result = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

//     // EXPECT_EQ(result, 3);
//     // EXPECT_EQ(pOutBuffer[0], 1);
//     // EXPECT_EQ(pOutBuffer[0], 5);
//     // EXPECT_EQ(pOutBuffer[0], 9);
// }


