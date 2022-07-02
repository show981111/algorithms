/**
 * https://leetcode.com/problems/shuffle-an-array/discuss/1283088/C%2B%2B-Solution-with-Intuition-and-Explanation
 * @brief Shuffle with perfect randomness (Fisher Yates Algorithm)
 * https://www.youtube.com/watch?v=4zx5bM2OcvA&ab_channel=Insidecode
 *
 *
 */

class Solution
{
public:
    vector<int> origin;
    Solution(vector<int> &nums)
    {
        origin = nums;
    }

    vector<int> reset()
    {
        return origin;
    }

    vector<int> shuffle()
    {
        vector<int> shuffeled = origin;
        for (int i = 0; i < origin.size(); i++)
        {
            int offset = rand() % (origin.size() - i);
            // reducing the offset's range to [0, size-i-1] so that
            // Won't go over the length when we do i + offset
            // it means we are reducing the size of bags
            // [Shffeled |(index i) unshuffeled]
            swap(shuffeled[i], shuffeled[i + offset]);
        }

        return shuffeled;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */