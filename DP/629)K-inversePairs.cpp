/**
 * Super Math Heavy
 * https://leetcode.com/problems/k-inverse-pairs-array/solutions/4632022/4-term-recurrence-mahonian-numbers-dp-o-nk-6-ms-beats-87-36/?envType=daily-question&envId=2024-01-27
 *
 * Counting Everything => Extreme 노가다 => Use DP or Backtrak.
 * Try DP first. (better TC/SC)
 */

class Solution
{
public:
    const int MOD = 1e9 + 7;
    int kInversePairs(int n, int k)
    {
        if (k > (n * (n - 1)) / 2)
            return 0;
        if (k == 0 || k == (n * (n - 1)) / 2)
            return 1;
        /*
        Backtrack or DP?
        Try DP.
        T(n,k) = #arrays of 1-n array with k inverse pair
        T(N,0) + T(N,1) + .. + T(N, NC2) = N!
        T(2,0) = [1,2]. T(3,0) = [1,2,3]         T(4,0) = [1,2,3,4] = 1
        T(2,1) = [2,1]  T(3,1) = [1,3,2] [2,1,3] T(4,1) = [1,3,2,4], [2,1,3,4], [1,2,4,3] = 3
                        T(3,2) = [3,1,2] [2,3,1] T(4,2) = [3,1,2,4] [2,3,1,4] [1,3,4,2], [2,1,4,3], [1,4,2,3] = 5
                        T(3,3) = [3,2,1]         T(4,3) = [3,2,1,4] // [3,1,4,2] = 6
                                                 T(4,4) = 5 = [4,2,1,3] =>
                                                 T(4,5) = 3
                                                 T(4,6) = 1

                                                 T(5,5) =
        T(n,k) = T(n-1,k) // just add n at the end of T(n-1,k). Since .. N-1 <=N
                + T(n, k-1) //swap N with previous previous elem
                − T(n−1,k−n) // ??????
        T(n,k) == T(n,nC2 - k) // since we can just flip! total nC2 pairs. From nC2 pairs, k pairs are out of order. and nC2 -k are in order. If we flip the array, nC2-k are out of order, k are in order!
        3 -> 6 -> 10 -> 15
        T(5,5) = T(5,4) + T(4,5)- T(4,0)
            = 20            3
        0 1 2 3 4 5 6 7 8 9 10
        */
        if (n == 1)
            return 1;
        vector<int> prevMemo(1, 1); // For each i, record the T(i,p)
        vector<int> curMemo(1, 1);

        for (int i = 2; i <= n; i++)
        {
            long long totalPairs = (i * (i - 1)) / 2;
            long long until = min((long long)k, totalPairs / 2);
            long long p = 1;
            for (; p <= until; p++)
            {
                int cur = (prevMemo[p] + curMemo[p - 1]) % MOD;
                // cout << p - n << " " << prevMemo.size() << " " << p <<" " << i << endl;
                if (p - i >= 0 && p - i < prevMemo.size())
                {
                    // cout << prevMemo[p-i] << " ";
                    cur = (cur - prevMemo[p - i] + MOD) % MOD;
                }
                if (p < curMemo.size())
                    curMemo[p] = cur;
                else
                    curMemo.push_back(cur);
                if (i == n && p == k)
                    return cur;
            }
            for (; p <= min((long long)k, totalPairs); p++)
            {
                // cout << totalPairs-p << " ";
                if (p < curMemo.size())
                    curMemo[p] = curMemo[totalPairs - p];
                else
                    curMemo.push_back(curMemo[totalPairs - p]);
                if (i == n && p == k)
                    return curMemo[totalPairs - p];
            }
            // cout << i << " " << curMemo.size() << endl;
            prevMemo = curMemo;
        }
        return 0;
    }
};