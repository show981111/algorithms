class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        int limit = gcd(nums.size(), k); // if it goes over the gcd, then 이미 스왑한거 스왑, 즉 반복
        cout << gcd(nums.size(), k) << endl;
        for (int i = 0; i < limit; i++)
        {
            int start = i;
            int cur = (start + k) % nums.size();
            int prevValue = nums[start];
            int curValue = nums[cur];
            while (start != cur)
            {
                curValue = nums[cur];          // update current value
                nums[cur] = prevValue;         // update the value
                cur = (cur + k) % nums.size(); // update cur(index)
                prevValue = curValue;          // save curValue to prev
            }
            nums[cur] = prevValue;
        }
    }
};