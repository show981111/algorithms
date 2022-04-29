class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        vector<int> res;
        int left = 0;
        int right = numbers.size() - 1;
        while (left <= right)
        {
            int sumOfPair = numbers[left] + numbers[right];
            if (sumOfPair == target)
            {
                return vector<int>{left + 1, right + 1};
            }
            else if (sumOfPair > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return vector<int>();
    }
};