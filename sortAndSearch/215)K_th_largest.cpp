/**
 * Using a pq!
 */

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> pq;

        for (auto &num : nums)
        {
            if (pq.size() < k)
            {
                pq.push(num);
            }
            else
            {
                if (pq.top() < num)
                {
                    pq.pop();
                    pq.push(num);
                }
            }
        }
        return pq.top();
    }
};

/**
 * Quick select, partition!
 */

class Solution
{
public:
    // partition L~R based on pivot.
    int partition(vector<int> &nums, int L, int R)
    {
        int pivot = nums[L]; // set L as pivot
        int pivotIndex = L;
        // want to place bigger or equal elems Left and small elems Right
        while (L <= R)
        { // go one over so that it can change the spot with the number that is >= pivot.
            while (L < R && nums[L] >= pivot)
            { // searching for elem smaller than pivot
                L++;
            }
            // go one over so that it can change the spot with the number that is >= pivot.
            while (L <= R && nums[R] < pivot)
            { // searching for elem bigger or equal than pivot
                R--;
            }
            if (L >= R)
                break;
            swap(nums[L], nums[R]);
        }
        swap(nums[R], nums[pivotIndex]);
        return R; // L is the new pivot Index
    }
    int quickSelect(vector<int> &nums, int L, int R, int k)
    {
        if (L >= R)
        {
            return nums[k - 1];
        }
        int randIndex = L + rand() % (R - L + 1);
        swap(nums[L], nums[randIndex]);
        int pivotIndex = partition(nums, L, R);
        if (pivotIndex == k - 1)
            return nums[pivotIndex];
        else if (pivotIndex < k - 1)
        { // [ _ _ _ P _ _ K _ _ _]
            return quickSelect(nums, pivotIndex + 1, R, k);
        }
        else
        {
            return quickSelect(nums, L, pivotIndex - 1, k);
        }
    }
    int findKthLargest(vector<int> &nums, int k)
    {
        return quickSelect(nums, 0, nums.size() - 1, k);
    }
};