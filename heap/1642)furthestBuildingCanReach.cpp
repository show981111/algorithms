class Solution
{
public:
    /*
    Should use ladder for bigger gap
    -> Greedy?

    Can't sort all the gaps since it should be contiguous.

    *** First try Heap for the case when we need an ordered container, then optimize it with monotonic stack

    [4,2,7,6,9,11,12]
    ShouldClimb [5,3,2, 15 ]
    [5,3,15]
    Dec deque,
    if we see bigger gap, try pop them with ladder from FRONT. => No, we might have to save the ladder for
    future. => We need to compare the gap in the future and current gap. => Heap is needed
    If we see smaller gap, push to deque. Then later pop from front using ladder

    How about incDeque?
    If we see bigger gap, just push back
    if we see smaller gap, -> Not sure we use ladder or brick still...

    T(i,b,l) = can reach building I with "b" bricks and "l" ladders?
    T(i,b,l) = T(i-1,b - cur_gap, l) || T(i-1,b,l-1);
    O(N*B*L)

    At each step of facing taller building, we need an ordered sequence
    of gaps so far.
    => HEAP instead of ordered stack

    */
    int furthestBuilding(vector<int> &heights, int bricks, int ladders)
    {
        long brickConsumed = 0;
        priority_queue<int, vector<int>, less<int>> bricksQ; // Should keep the bottom X gaps (should pop big ones)
        long laddersConsumed = 0;
        for (int i = 0; i < heights.size() - 1; i++)
        {
            int gap = heights[i + 1] - heights[i];
            if (gap <= 0)
                continue;
            if (gap > bricks)
            { // Must use ladder
                laddersConsumed++;
                if (laddersConsumed > ladders)
                    return i; // cannot accomodate current gap
                continue;
            }

            // try bricks first. Should push this first since we don't know that
            // this gap should use ladder or brick. If we push gap later and
            // force this gap to go to bricks, then the smaller gap than this gap can consume ladder!
            bricksQ.push(gap);
            brickConsumed += gap;

            while (!bricksQ.empty() && brickConsumed > bricks)
            {
                int biggestGapInBricks = bricksQ.top();
                brickConsumed -= biggestGapInBricks;
                bricksQ.pop();
                laddersConsumed++; // Ladder is necessary. Biggest gap we have now and smaller ones already used maximum amount of bricks
                if (laddersConsumed > ladders)
                    return i; // cannot accomodate current gap
            }
        }
        return heights.size() - 1;
    }
};