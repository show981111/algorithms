class Solution
{
public:
    /*
    Greedy:
    We should always remove numbers with smallest count
    -> Use minimum # of elems we can use While Maximizing the benefit (remove all occurence of that elem)

    Use bucket sort to make O(N) sorting for bounded values!
    */
    int findLeastNumOfUniqueInts(vector<int> &arr, int k)
    {
        vector<int> bucket(arr.size() + 1, 0); // freq -> # elem that has this freq
        unordered_map<int, int> cnt;           // elem -> freq
        for (int i : arr)
        {
            cnt[i]++;
        }
        for (auto &[val, freq] : cnt)
        {
            bucket[freq]++;
        }
        int remove = 0;
        // from small frequency, remove as many as we can
        for (int freq = 1; freq < bucket.size(); ++freq)
        {
            int canRemove = min(k / freq, bucket[freq]);
            remove += canRemove;
            k -= canRemove * freq;
            if (k <= 0)
                break;
        }
        return cnt.size() - remove;
    }
};