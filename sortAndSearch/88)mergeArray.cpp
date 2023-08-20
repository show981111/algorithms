/**
 * @brief Two pointer!
 *  Importance of sorting is, invariant: a[i] <= a[i+1]
 *  This invariant allows us to skip various items or allow us to only
 *  compare item at the beginning or end.
 *  EX) if a[3] < b[3], {a[1] < a[2] < a[3]} < b[3]
 */

// Time O(m+n), Space O(m)
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        // non-decreasing -> a >= b >= c d e f
        vector<int> nums1Copy(nums1.begin(), nums1.begin() + m);
        int p1 = 0, p2 = 0, mergedIndex = 0;

        while (p1 < m || p2 < n)
        {
            if (p2 >= n)
            { // copied all p2 members
                nums1[mergedIndex++] = nums1Copy[p1++];
            }
            else if (p1 >= m)
            { // copied all p1 members
                nums1[mergedIndex++] = nums2[p2++];
            }
            else
            {
                if (nums1Copy[p1] <= nums2[p2])
                {
                    nums1[mergedIndex++] = nums1Copy[p1++];
                }
                else
                {
                    nums1[mergedIndex++] = nums2[p2++];
                }
            }
        }
    }
};

// O(1) space
/**
 * @brief Think from reverse! Think about what we need to do to do what I want!
 *
 */
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        // non-decreasing -> a >= b >= c d e f
        // how can we make this O(1) space?
        // Since 0 paddings are from the end... can we fill
        // data from the end? -> non-ascending order
        // if we start from the end, then we can just fill it in
        // non-ascending order from the end!
        int p1 = m - 1, p2 = n - 1, mergedIndex = m + n - 1;

        while (p1 >= 0 || p2 >= 0)
        {
            if (p1 < 0 || (p2 >= 0 && nums1[p1] < nums2[p2]))
            { // need to fill p2
                nums1[mergedIndex--] = nums2[p2--];
            }
            else
            { // p1 >= 0 && nums1[p1] >= nums2[p2] -> need to fill p1
                nums1[mergedIndex--] = nums1[p1--];
            }
        }
    }
};