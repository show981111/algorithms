class Solution
{
public:
    /*
    need capital[i] to gain profits[i].
    Need to choose a work that has a maximum profit, where capital[i] <= w (cur capital)
    Need a sorted container: Map, set, pq, sorted array
    Need to remove the element after we worked on that profit. (array not suitable)
    Duplicates in profits possibe. -> set might not ideal

    Need to take max from all profits with capital[i] <= w. Not just per capital. (map per captial doesn't work)

    How about per profit? Still need to traverse max K when captial changes
    Profit descending
    100 : 1 2 3 10 11 (cap ascending)
    50 : 1 2 5
    10 : 0 1

    Simple way: just sort by max profit. check capital, if we can work, pop, else pass
                (O(K*(N + logN) + NlogN)) TLE


    When define comparator with external data, be careful because equality is defined as
    !comp(a,b) && !comp(b,a), which means !(a < b) && !(b < a)

    Need to choose a work that has a maximum profit, where capital[i] <= w (cur capital)
    => Max Profit within that RANGE.
    You just keep adding data as we go over the range.
    Then, even thought threshold change, we still have previous data within that range!
    */
    struct Work
    {
        int capital;
        int profit;
    };
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        auto comp = [](const Work &a, const Work &b)
        {
            return a.capital < b.capital; // capital ascending
        };
        vector<Work> v;
        for (int i = 0; i < profits.size(); i++)
        {
            v.push_back({capital[i], profits[i]}); // O(NlogN)
        }
        sort(v.begin(), v.end(), comp);
        int ptr = 0;
        priority_queue<int> profitQueue; // maxHeap
        for (int i = 0; i < k; i++)
        { // O(K*logN)
            while (ptr < v.size() && v[ptr].capital <= w)
            {
                profitQueue.push(v[ptr++].profit);
            }
            if (profitQueue.empty())
                break; // no work can be done. Everything above cur capital
            w += profitQueue.top();
            profitQueue.pop();
        }
        return w;
    }
};