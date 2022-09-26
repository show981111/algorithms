class Solution
{
public:
    int partition(vector<int> &a, int left, int right)
    {
        int pivot = left; // set left as a pivot!
        int l = left + 1, r = right;
        while (true)
        {
            while (l <= r && a[l] < a[pivot])
                l++;
            while (r >= l && a[r] >= a[pivot])
                r--;
            if (l >= r)
                break;
            swap(a[l], a[r]);
        }
        swap(a[r], a[pivot]);
        return r; // the place of pivot is r because we swapped!
    }
    void quickSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;
        int randIndex = left + rand() % (right - left + 1);
        swap(nums[randIndex], nums[left]); // pick random element as a pivot and put it to left!
        int pivot = partition(nums, left, right);
        quickSort(nums, left, pivot);
        quickSort(nums, pivot + 1, right);
    }
    vector<int> sortArray(vector<int> &nums)
    {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

/**
 * @brief BubbleSort
 *
 */
void bubble(vector<int> &nums, int left, int right)
{
    for (int i = right; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (nums[j - 1] > nums[j])
                swap(nums[j - 1], nums[j]);
        }
    }
}

/**
 * @brief Select
 *
 */
void Select(vector<int> &nums, int left, int right)
{
    for (int i = 0; i < right + 1; i++)
    {
        int minIndex = i;
        for (int j = i; j < right + 1; j++)
        {
            if (nums[j] < nums[minIndex])
                minIndex = j;
        }
        swap(nums[minIndex], nums[i]);
    }
}

/**
 * @brief Insertion
 *
 */

void Insert(vector<int> &nums, int left, int right)
{
    for (int i = 0; i < right + 1; i++)
    {
        int j = i;
        while (j >= 1 && nums[j - 1] > nums[j])
        {
            swap(nums[j - 1], nums[j]);
            j--;
        }
    }
}