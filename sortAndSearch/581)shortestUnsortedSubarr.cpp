/**
 * @brief Subarray! -> Contiguous -> sliding window or two pointers?
 * The key over here is not just finding the place where the order is messed up but,
 * Gotta know where does it start, where does it end.
 * Where does it start? -> where the minimum value in the unsorted subarray should go?.
 * When we find nums[i] > nums[i+1], we should find where is the place of nums[i+1] in a sorted array.
 * Where does it end? -> where the maximum value in the unsorted subarray should go?.
 * When we find nums[i] > nums[i+1], the validation after this should consider nums[i] in mind. because
 * nums[i] > nums[i + 1] and nums[i+1] < nums[i+2] does not captures nums[i] in mind.
 *
 * Thus, we keep track of minValue and maxValue
 * minValue gives us a starting point, maxValue gives us an end point!
 *
 * Important thing of O(nlogn) -> O(n)
 * We do not need to know where each small values go. Only need to know where does
 * "MINIMUM" value goes. Thus we can just do linear search for Min.
 */

class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        int start = -1, end = -1;
        int minSoFar = -1;
        int maxSoFar = -1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] <= nums[i + 1])
            {
                if (end == -1)
                    continue;
                if (maxSoFar > nums[i]) // passed local validation(nums[i] <= nums[i + 1]), but
                    end = i;            // order is still messed up cuz maxSoFar is bigger
                if (maxSoFar > nums[i + 1])
                    end = i + 1; // same as above
            }
            else
            {
                if (end == -1)
                {
                    minSoFar = nums[i + 1];
                    maxSoFar = nums[i];
                }
                minSoFar = min(minSoFar, nums[i + 1]); // update new min
                maxSoFar = max(maxSoFar, nums[i]);     // update max to capture the global max
                end = i + 1;
            }
        }
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] > minSoFar)
            {
                start = i;
                break;
            }
        }

        return start == -1 ? 0 : end - start + 1;
    }
};