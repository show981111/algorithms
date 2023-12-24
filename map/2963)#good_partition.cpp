/**
 * Pretty Much MATH(Combinatory)
 *
 * #good partition = 2^(#unique intervals - 1)
 * [] [] [] [], T(N) : #good partition until N_th index (index of unique interval)
 * -> T(N) = 2*T(N-1)
 * ex) 1, 2, 3, 4
 * T(2) = {(1),(2)}, {(1,2)} = 2
 * T(3) = {(1),(2),(3)}, {(1,2),(3)} => add (3) individually, {(1),(2,3)}, {(1,2,3)} => Add 3 to the last chunk
 *      = 4
 *
 * Now, how to divide the chunk? -> Since redundant elements can't go to separate group, need to merge them
 * How to merge the interval?
 * ex) [1,2,3,1,2,4,5] -> (1,2,3,1,2) is one interval
 *
 * (1) Sort and merge just like we did in merge interval
 * (2) Count based on last index
 */

// (1) method, O(nlogn)
class Solution
{
public:
    typedef pair<int, int> Interval;
    int numberOfGoodPartitions(vector<int> &nums)
    {
        int chunkNums = 0;
        unordered_map<int, Interval> chunks; // first occurence to the last occurence of "key"

        for (int i = 0; i < nums.size(); i++)
        {
            if (chunks.count(nums[i]) > 0)
            {
                chunks[nums[i]].second = i;
            }
            else
            {
                chunks[nums[i]] = make_pair(i, i);
            }
        }
        vector<Interval> v;

        for (auto &[key, interval] : chunks)
        {
            // cout << interval.first << "-" << interval.second << endl;
            v.emplace_back(interval);
        }
        sort(v.begin(), v.end(), [](Interval &a, Interval &b)
             {
            if(a.first < b.first) return true;
            else if(a.first == b.first) return a.second < b.second;
            return false; });
        // merging interval
        vector<Interval> mergedInterval;
        for (auto &i : v)
        {
            if (mergedInterval.empty() || mergedInterval.back().second < i.first)
            {
                mergedInterval.push_back(i);
            }
            else
            { // !mergedInterval.empty() && mergedInterval.back().second >= i.first
                mergedInterval.back().second = max(mergedInterval.back().second, i.second);
            }
        }

        chunkNums = mergedInterval.size();
        long res = 1;
        const int MOD = 1e9 + 7;
        for (int i = 0; i < chunkNums - 1; i++)
        {
            res *= 2;
            res %= MOD;
        }
        return res;
    }
};

/**
 * (2) Second method.
 * Use last occurence as a break point.
 * ex) 1, 2, 3, 1, 2, 3, 4, 5
 * bk  3  4  5  3  4  5  6  7
 * When the index goes over the break point, we can make a group!
 * (until last occurence, we cannot form any group!)
 */

class Solution
{
public:
    const int MOD = 1e9 + 7;
    long binaryExp(int target)
    {
        if (target == 0)
            return 1;

        int half = binaryExp(target / 2);
        if (target % 2 == 1)
        {
            return (2 * (long)(half % MOD) * (long)(half % MOD)) % MOD;
        }
        else
        {
            return ((long)(half % MOD) * (half % MOD)) % MOD;
        }
    }
    int numberOfGoodPartitions(vector<int> &nums)
    {
        int chunkNums = 0;
        unordered_map<int, int> chunks; // last index of key

        for (int i = 0; i < nums.size(); i++)
        {
            chunks[nums[i]] = i;
        }

        int nextChunkStarts = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nextChunkStarts < i)
                chunkNums++;
            nextChunkStarts = max(nextChunkStarts, chunks[nums[i]]);
        }

        return binaryExp(chunkNums - 1);
    }
};