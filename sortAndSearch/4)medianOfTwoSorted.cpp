/**
 * https://www.youtube.com/watch?v=q6IEA26hvXc&ab_channel=NeetCode
 */

class Solution
{
public:
    const int MIN_VAL = -2e6;
    const int MAX_VAL = 2e6;
    double findMedian(vector<int> &nums1, vector<int> &nums2, int medianSize, int aL, int aR, bool isOdd)
    {
        int aMidIndex = (aL + aR) / 2;
        if (aL + aR < 0 && (aL + aR) % 2 != 0)
        {
            aMidIndex--; // C++ negative integer rounding is default to ceil! truncation towards zero.
        }
        int bMidIndex = medianSize - aMidIndex - 2; // thanks to this, left side of aMid and bMid is always median index number of elements

        int aLeft = aMidIndex >= 0 && aMidIndex < nums1.size() ? nums1[aMidIndex] : MIN_VAL;
        int aRight = aMidIndex + 1 >= 0 && aMidIndex + 1 < nums1.size() ? nums1[aMidIndex + 1] : MAX_VAL;
        int bLeft = bMidIndex >= 0 && bMidIndex < nums2.size() ? nums2[bMidIndex] : MIN_VAL;
        int bRight = bMidIndex + 1 >= 0 && bMidIndex + 1 < nums2.size() ? nums2[bMidIndex + 1] : MAX_VAL;

        // cout << "..." <<aLeft << " " << aRight  << endl;
        // cout << "..." <<bLeft << " " << bRight  << endl;

        if (aLeft <= bRight && bLeft <= aRight)
        {
            if (isOdd)
                return max(aLeft, bLeft);
            else
                return ((double)max(aLeft, bLeft) + (double)min(aRight, bRight)) / 2;
        }
        else if (aLeft > bRight)
        {
            aR = aMidIndex - 1; // median exists in somewhere in the B after bRight, shrink A!
        }
        else
        {                       // bLeft > aRight
            aL = aMidIndex + 1; // extend A!
        }
        return findMedian(nums1, nums2, medianSize, aL, aR, isOdd);
    }
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int totalSize = nums1.size() + nums2.size();
        int medianSize = totalSize % 2 == 0 ? totalSize / 2 : totalSize / 2 + 1;
        // cout << (int)(-3 / 2 + 0.5) << endl;
        if (nums1.size() > nums2.size())
            swap(nums1, nums2);

        return findMedian(nums1, nums2, medianSize, 0, nums1.size() - 1, totalSize % 2 != 0);
    }
};