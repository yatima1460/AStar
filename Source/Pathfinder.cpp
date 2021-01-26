#ifdef GOOGLE_TEST
#include "Pathfinder.hpp"
#endif

#include <cmath>
#include <queue>
#include <unordered_map>

/*
============================================================
     ___         _    
    /   \     /\| |/\ 
   /  ^  \    \ ` ' / 
  /  /_\  \  |_     _|
 /  _____  \  / , . \ 
/__/     \__\ \/|_|\/ 
                      
Pathfinding implementation using A*

Supports checking a partial path first to avoid
the algorithm wasting time when the world is walkable but
the end is narrowly enclosed

Note: in general I tried to avoid as many IFs as possible
to not have failing CPU branch prediction in the hot path.

============================================================
*/

// ============ CONFIGS ============

/*
How much the dot product between the (start,end) and (current,end)
matters in the heuristics, multiplied by this value,
WARNING: don't make it too big otherwise you risk to overshoot
WARNING: using the dot product can increase performance but paths
could look "strange" in a game, not really human-like in some cases
better to use for things where no graphics is involved
*/
#define DOT_PRODUCT_WEIGHT 0.0005f

/*
How much of the world area to scan from the end before starting
To avoid situations where just the end is enclosed but the world is walkable
*/
#define CHECK_END_IF_NARROWLY_ENCLOSED_BEFORE_STARTING true
#define WORLD_MAP_END_ENCLOSED_WEIGHT 0.0005f

// =================================

/*
Can pollute the namespace, but at least for this test's code you get better readability
But be careful to use this in the real world
*/
using namespace std;

// Sometimes this saved like 20ms
// Hey it's a whole game frame time, even more!
#ifdef __GNUC__
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif

// Bundle most used data together to have fewer cache misses
struct NodeData
{
    int nDistance = numeric_limits<int>::max();
    float nScore = 0.0f;
    int nParentIndex = -1;
};

// Same as FindPath, but with a cutoff of nodes count discovered
int PartialFindPath(const int nStartIndex, const int nStartX, const int nStartY, const int nTargetIndex, const int nTargetX, const int nTargetY,
                    const unsigned char *pMap, const int nMapWidth, const int nMapHeight,
                    int *pOutBuffer, const int nOutBufferSize, const int nCutoff)
{

    unordered_map<int, NodeData> nodeMetadata;

    /*
    I actually wanted to use a Set with a custom comparator instead of a priority queue + 
    an unordered_map to check if an element is inside in O(1)...
    but for Sets C++ also uses the comparator for equivalence using reflexivity
    instead of the element operator== 
    two set keys are considered equal if !comp(a,b) && !comp(b,a))
    I think the problem is that C++ has strict weak ordering containers
    I read that C++2020 will fix this, so this can be improved even further
    */
    const auto openNodesComparator = [&nodeMetadata] (const int &nIndexLHS, const int &nIndexRHS) 
    {
        const auto &nodeDataLHS = nodeMetadata[nIndexLHS];
        const auto &nodeDataRHS = nodeMetadata[nIndexRHS];
        return nodeDataLHS.nScore == nodeDataRHS.nScore ? nodeDataLHS.nDistance > nodeDataRHS.nDistance : nodeDataLHS.nScore > nodeDataRHS.nScore;
    };

    // Maybe a Fibonacci heap is better for this by having O(1) insert and O(logN) amortised extract? 🤔
    vector<int> openNodesContainer; // so clang-tidy doesn't complain
    priority_queue<int, vector<int>, decltype(openNodesComparator)> openNodesPriorityQueue(openNodesComparator, openNodesContainer);

    // Setup root node
    openNodesPriorityQueue.push(nStartIndex);
    nodeMetadata[nStartIndex].nDistance = 0;
    int nCurrentIndex = nStartIndex;

    // Useful for later for heuristics
    const auto nDeltaXStartTarget = nStartX - nTargetX;
    const auto nDeltaYStartTarget = nStartY - nTargetY;

    static const int NEIGHBOURS_X_OFFSET[4] = {+0, +1, +0, -1};
    static const int NEIGHBOURS_Y_OFFSET[4] = {-1, +0, +1, +0};

    // Stop if open nodes is empty, if we reached the destination or if we reached the cutoff
    while (unlikely(!openNodesPriorityQueue.empty() && nCurrentIndex != nTargetIndex && (int)nodeMetadata.size() < nCutoff))
    {
        // O(1) to get the node with the lower f because open is sorted
        nCurrentIndex = openNodesPriorityQueue.top();
        openNodesPriorityQueue.pop();

        // Calculate new Dijkstra's cost, it's a 2D grid so always +1
        const auto gCurrent = nodeMetadata[nCurrentIndex].nDistance + 1;

        // Get X and Y of current node from the index
        const int xCurrent = nCurrentIndex % nMapWidth;
        const int yCurrent = nCurrentIndex / nMapWidth;

        // Dot product between (start,end) and (current,end), used later for heuristics
        const auto nDeltaXCurrentTarget = xCurrent - nTargetX;
        const auto nDeltaYCurrentTarget = yCurrent - nTargetY;
        const auto dot = abs(nDeltaXCurrentTarget * nDeltaYStartTarget - nDeltaXStartTarget * nDeltaYCurrentTarget);

        for (int i = 0; i < 4; ++i)
        {
            const int new_x = xCurrent + NEIGHBOURS_X_OFFSET[i];
            const int new_y = yCurrent + NEIGHBOURS_Y_OFFSET[i];
            const int neighbourIndex = new_x + new_y * nMapWidth;

            // if neighbour inside the map && walkable && better cost
            if (likely(new_x >= 0 && new_y >= 0 && new_x < nMapWidth && new_y < nMapHeight) 
                && static_cast<bool>(pMap[neighbourIndex])
                && unlikely(gCurrent < nodeMetadata[neighbourIndex].nDistance))
            {
                // save where we came from to reconstruct path later
                nodeMetadata[neighbourIndex].nParentIndex = nCurrentIndex;

                // save new better cost
                nodeMetadata[neighbourIndex].nDistance = gCurrent;

                // f = dijkstra + Manhattan + dot product between (start,end) and (current,end)
                const auto Manhattan = fabs(static_cast<float>(new_x - nTargetX)) + fabs(static_cast<float>(new_y - nTargetY));
                nodeMetadata[neighbourIndex].nScore = gCurrent + Manhattan + dot * DOT_PRODUCT_WEIGHT;

                // better cost so add it to open
                openNodesPriorityQueue.push(neighbourIndex);
            }
        }
    }

    // If we broke the while because we found the target
    if (nCurrentIndex == nTargetIndex)
    {
        // Reconstruct path
        int i = 0;
        while (likely(nodeMetadata[nCurrentIndex].nParentIndex != -1))
        {
            nCurrentIndex = nodeMetadata[nCurrentIndex].nParentIndex;
            if (likely(i < nOutBufferSize))
                pOutBuffer[i] = nCurrentIndex;
            i++;
        }
        return i == 0 ? -1 : i;
    }

    // If no path found
    return static_cast<int>(nodeMetadata.size()) < nCutoff ? -1 : -2;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char *pMap, const int nMapWidth, const int nMapHeight,
             int *pOutBuffer, const int nOutBufferSize)

{
    // Consider simple case if target is the same as position
    if (unlikely(nStartX == nTargetX && nStartY == nTargetY))
        return 0;

    // Useful for later, so we don't calculate them every time
    const auto nStartIndex = nStartX + nStartY * nMapWidth;
    const auto nTargetIndex = nTargetX + nTargetY * nMapWidth;

#if CHECK_END_IF_NARROWLY_ENCLOSED_BEFORE_STARTING
    // Checks a bit of the world map around start before the normal search
    const int nCutoff = static_cast<int>(nMapWidth * nMapHeight * WORLD_MAP_END_ENCLOSED_WEIGHT);
    const auto nPartialResult = PartialFindPath(nStartIndex, nStartX, nStartY, nTargetIndex, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, nCutoff);
    if (unlikely(nPartialResult == -1))
        return -1;
#endif

    // Reverse nTargetIndex and nStartIndex so the path doesn't need to be reversed later on
    return PartialFindPath(nTargetIndex, nTargetX, nTargetY, nStartIndex, nStartX, nStartY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, nMapWidth * nMapHeight + 1);
}