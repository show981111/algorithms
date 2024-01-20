/**
 * Greedy + Heap approach for Subsequence.
 * In this problem, subsequence doesn't care about ordering.
 * == subset with size K
 * Thus, just sort them and get max using greedy approach.
 */
class Solution
{
public:
    struct Val
    {
        int index;
        int num1;
        int num2;
    };
    long long maxScore(vector<int> &nums1, vector<int> &nums2, int k)
    {
        /*
        Restraint + subsequence + 0/1 knapsack?

        T(i,k) = MaxScore from num[:i], with k elements
        T(i,k) = max(T(i-1,k), (T(i-1,k-1).scoreSum + nums1[i]) * min(T(i-1,k-1).min,nums2[i]);
                // not including ,  Including
           k: 0 1      2      3
    Index  0  0 2(1,2) 2      2
           1  0 3(3,1) 4(4,1) 4(4,1)
           2. 0 9(3,3) 6(6,1)
           3. 0
        NO!! THat recurrence does not guarantee optimal

        Since it is a subsequence, can we just sort?

        Sort based on nums2, fix the min nums2 and compute max sum.
        Reuse that sorting as we move forward nums2
        */
        auto comp = [](const Val &a, const Val &b)
        {
            return a.num2 > b.num2;
        };
        vector<Val> v;
        for (int i = 0; i < nums1.size(); i++)
        {
            v.push_back({i, nums1[i], nums2[i]});
        }
        sort(v.begin(), v.end(), comp);                         // O(NlogN)
        priority_queue<int, vector<int>, std::greater<int>> pq; // min heap

        long long ans = 0;
        long long curSum = 0;

        // Given min num2, compute max sum! => Keep the pq size == k that includes v[idx]
        for (int idx = 0; idx < v.size(); idx++)
        { // O(N) => O(N(logK))
            if (pq.size() == k)
            { // pq.size == k. need to remove smallest one
                curSum -= pq.top();
                pq.pop(); // O(logK)
            }
            pq.push(v[idx].num1); // add new element: O(logK)
            curSum += v[idx].num1;
            if (pq.size() < k)
                continue; // if we have less than k, should just keep pushing

            // pq.size() == k
            // k elements including v[idx] is in pq. Compute the answer!
            long long curMin = v[idx].num2;
            ans = max(curSum * curMin, ans);
        }
        return ans;
    }
};