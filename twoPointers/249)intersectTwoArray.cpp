/**
 * When using sorting + two pointers.
 *
 * Decide how to proceed each pointer.
 * 3 cases
 *  arr[i] == arr[j]
 *  arr[i] > arr[j]
 *  arr[i] < arr[j]
 * => what should we do in each case?
 */
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        vector<int> ans;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();)
        {
            if (nums1[i] == nums2[j])
            {
                ans.push_back(nums1[i]);
                while (i < nums1.size() && nums1[i] == ans.back())
                {
                    i++;
                }
                while (j < nums2.size() && nums2[j] == ans.back())
                {
                    j++;
                }
            }
            else if (nums1[i] < nums2[j])
                i++;
            else
                j++;
        }
        return ans;
    }
};