/**
 * Brute force.
 * compute all pairs. -> NMlog(NM)
 *
 * Two arrays are sorted.
 * -> We know next possible candidates.
 * A B ..
 * X Y ..
 * Since A < B, X < Y, A + X < A + Y or X + B < B + Y
 * Thus, from index [i,j] next candidates are [i+1,j] & [i, j+1]
 * => Priority Queue to give me the smallest sum all the time!!!
 *
 * Key point is, can we use map or set? PQ is better in this case because there can be a lot of duplicates.
 * Duplicates in sum(key). EX) [2,2] == [1,3] have the same sum but different pair. We want to allow duplicate keys.
 * So set and map would not be good since they don't allow dup keys!
 *
 * Problem - duplicates
 *
 * Starting from (0,0), we will insert (1,0) & (0,1).
 *
 * If we pop (1,0), we insert (2,0) (1,1)
 * If we pop (0,1), we insert (0,2) (1,1)
 * (1,1) is inserted twice!
 *
 * How to filter duplicates?
 * One way to do is, we separate pairs into two cases.
 * (X, Y) X >= Y or X < Y.
 * As we increase indices, we compare this and avoid dups!
 */

class Solution
{
public:
    typedef pair<int, int> Pair;
    vector<vector<int>> kSmallestPairs(const vector<int> &nums1, const vector<int> &nums2, int k)
    {
        auto comp = [&nums1, &nums2](const Pair &a, const Pair &b)
        {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        vector<vector<int>> ans;
        // can allow dup elements!
        priority_queue<Pair, vector<Pair>, decltype(comp)> pq(comp);
        pq.push({0, 0});

        while (ans.size() < k)
        {
            Pair p = pq.top();
            pq.pop();
            ans.push_back({nums1[p.first], nums2[p.second]});

            if (p.first + 1 < nums1.size() && (p.first + 1 >= p.second)) // to avoid dups. If we increase .first, then should bigger than second
            {
                // cout << p.first + 1 <<  p.second << endl;
                pq.push({p.first + 1, p.second});
            }
            if (p.second + 1 < nums2.size() && (p.second + 1 > p.first)) // if we increase second, should bigger than first
            {
                // cout << p.first <<  p.second + 1<< endl;
                pq.push({p.first, p.second + 1});
            }
        }

        return ans;
    }
};