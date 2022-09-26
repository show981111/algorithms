/**
 * @brief
 *
 * In the sorted array how to find a pair with lower <= a_i - a_j <= upper, in O(N)?
 * Key point is starting from the Biggest Row, and go smaller!
 * This way we can set the lower bound.
 *      if the lower bound is X_th col in bigger row, then for smaller row, lower bound is X+a_th col
 * L < x < R
 * Lower Bound => Biggest Number from the number with <= L
 * Upper Bound => Smallest Number from the number with >= R
 *
 * 헷갈리면 2D 사각형 그려서 대소비교!(정렬된 사각형...)
 */

class Solution
{
public:
    void merge(vector<long> &accum, int L, int M, int R, int &count, int lower, int upper)
    {
        vector<long> temp(R - L + 1);
        int index = 0;
        int i = L, j = M + 1;
        int low = M + 1, high = M + 1;
        // counting! KEY ALGORITHM!
        while (i <= M)
        {
            while (low <= R && accum[low] - accum[i] < lower)
                low++;
            while (high <= R && accum[high] - accum[i] <= upper)
                high++;
            count += (high - low);
            i++;
        }
        i = L;
        // sort
        while (i <= M || j <= R)
        {
            if (i >= M + 1)
                temp[index++] = accum[j++];
            else if (j >= R + 1)
                temp[index++] = accum[i++];
            else
            {
                if (accum[i] > accum[j])
                    temp[index++] = accum[j++];
                else
                    temp[index++] = accum[i++];
            }
        }
        copy(temp.begin(), temp.end(), accum.begin() + L);
    }
    void mergeSort(vector<long> &accum, int L, int R, int &count, int lower, int upper)
    {
        if (L >= R)
        {
            if (accum[L] >= lower && accum[L] <= upper)
                count++;
            return;
        }
        int M = L + (R - L) / 2;
        mergeSort(accum, L, M, count, lower, upper);
        mergeSort(accum, M + 1, R, count, lower, upper);
        merge(accum, L, M, R, count, lower, upper);
    }
    int countRangeSum(vector<int> &nums, int lower, int upper)
    {
        vector<long> accum(nums.size());
        int count = 0;
        accum[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            accum[i] += (accum[i - 1] + nums[i]);
        }
        // now, sum[i:j] = accum[j] - accum[i];
        mergeSort(accum, 0, accum.size() - 1, count, lower, upper);
        return count;
    }
};