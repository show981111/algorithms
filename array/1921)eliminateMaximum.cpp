class Solution
{
public:
    /*
    We need to kill a monster that will come to us.
    So move monster first, until someone crosses 0.
    Check if we can kill all of them
    Otherwise, kill random monster.
    B-force = O(N*N)

    Binary search? -> We can guess how many monsters we can kill from 0 ~ # monsters.
                   -> For a given X, how do we know if we can kill X monsters or not in O(N) time?

    TTA (Time to arrive) = ceil(dist / speed)
    => For each monster, we have a deadline!!! We should kill at maximum TTA - 1 minute.
    Since at TTA, monster will arrive to 0.
    As long as we kill them within deadline, we are good.

    Now we don't even have to guess the number. We can just know by accumulating
    number of monsters we should kill before i time, and compare this to number
    of monsters we can kill at i time.
    */
    int eliminateMaximum(vector<int> &dist, vector<int> &speed)
    {
        vector<int> shouldKillAt(dist.size(), 0);
        // deadline -> number of monsters we should kill at or before
        for (int i = 0; i < dist.size(); i++)
        {
            int killAt = ceil((double)dist[i] / speed[i]) - 1; // deadline
            if (killAt < dist.size())
            {
                shouldKillAt[killAt]++;
            }
        }
        int shouldKill = 0;
        for (int i = 0; i < dist.size(); i++)
        {
            shouldKill += shouldKillAt[i];
            // accumulate how many monsters we should kill within deadline
            if (shouldKill > i + 1) // if that goes over the number of monsters we can kill
                return i + 1;       // Game over.
        }
        return dist.size();
    }
};

/**
 *
 * For binary search, be careful of borders.
 * EX) [start,mid] [mid + 1, end]
 * If we don't exclude mid, we get inf loop.
 * EX)
 * [0, 1] mid = 0
 * [0, 1] mid = 0
 * Thus, bin search recursive call should be
 * [start, mid-1], [mid+1,end]
 *
 */