/**
 * @brief IDEA
 * doing a binary search on two array.
 * and trying to find kth element.
 *
 * if the total index is larger than k,
 * we should decrease the bigger one to get to K
 *
 * if the total index(ai + bi) is smaller than k,
 * we should increase smaller one to get to K
 *
 * if total index is equal to K?
 * we do not know yet which one to choose...
 * we might choose a bigger one? but we should first decide
 * this partition is correct or not by checking the next idex of both of them
 * I this necessary to check next index?
 * We can just increase smaller one to go as far as it can.
 * then, we can just do b[k-aL] because we know that
 * a[:aL] are smaller than b[bi], (bi = (bR + bL)/2)
 *
 */

class Solution
{
public:
    // get Kth smallest from [a,b]
    double getKth(vector<int> &a, vector<int> &b, int k, int aL, int aR, int bL, int bR)
    {
        if (aL > aR)          // should not be an equal
            return b[k - aL]; // a[:aL] is smaller than curren mid of b
        if (bL > bR)
            return a[k - bL];
        int ai = (aL + aR) / 2;
        int bi = (bL + bR) / 2;

        if (ai + bi < k)
        { // enlarge smaller one
            if (a[ai] > b[bi])
                return getKth(a, b, k, aL, aR, bi + 1, bR);
            else
                return getKth(a, b, k, ai + 1, aR, bL, bR);
        }
        else
        { // ai + bi + 1 >= k, shrink larger one
            if (a[ai] > b[bi])
                return getKth(a, b, k, aL, ai - 1, bL, bR);
            else
                return getKth(a, b, k, aL, aR, bL, bi - 1);
        }
    }
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int N = nums1.size();
        int M = nums2.size();
        double mid = getKth(nums1, nums2, (N + M) / 2, 0, N - 1, 0, M - 1);
        if ((N + M) % 2 == 0)
        {
            double mid1 = getKth(nums1, nums2, (N + M) / 2 - 1, 0, N - 1, 0, M - 1);
            return (mid + mid1) / 2;
        }
        return mid;
    }
};