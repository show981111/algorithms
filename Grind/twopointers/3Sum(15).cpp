// can we use hashmap? -> will not remove duplicates automatically...
// Sort and skip?
// didnt consider duplicate between left & right
/**
 * Target sum => sort and use two pointers O(NlogN) OR use unordered map O(N)
 * Key point of using two pointers is, spliting the case and make it O(N) not O(N^2)
 *
 * @brief Key challenge of this problem : remove duplicates
 * two techniques removing dups
 * 1. sort + skip redundants
 * 2. Use set or map
 * Usually set and map are causing an extra space overhead.
 * If there is no TC adv, consider using sort + skip
 *
 * This case, using a map will be O(N^2) becuase of pivot loop * target sum loop
 * Using a sort will O(NlogN) + O(N^2) for pivot loop * two pointers = O(N^2)
 * Thus, using a map is not that beneficial in this case :(
 */
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> ans;
        size_t N = nums.size();
        sort(nums.begin(), nums.end());

        for (size_t pivotIndex = 0; pivotIndex < N - 2; pivotIndex++)
        {
            if (pivotIndex > 0 && nums[pivotIndex] == nums[pivotIndex - 1])
                continue;
            int pivot = nums[pivotIndex];
            size_t left = pivotIndex + 1;
            size_t right = N - 1;
            while (left < right)
            {
                int rightNum = nums[right];
                int leftNum = nums[left];
                int sum = pivot + leftNum + rightNum;
                if (sum > 0)
                {
                    // don't need this while because sum > 0, so won't affect the answer
                    while (left < right && nums[right] == rightNum)
                        right--;
                }
                else if (sum < 0)
                {
                    // don't need this while too
                    while (left < right && nums[left] == leftNum)
                        left++;
                }
                else
                {
                    vector<int> cand = {pivot, nums[left], nums[right]};
                    ans.push_back(cand);
                    // We need these while bc it affect the answer!
                    //  because sum == 0
                    while (left < right && nums[right] == rightNum)
                        right--;
                    while (left < right && nums[left] == leftNum)
                        left++;
                }
            }
        }

        return ans;
    }
};