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
    // set rightmost as a pivot!
    int partition(vector<int> &nums, int L, int R)
    {
        // cout << L  << " " << R << endl;
        int pivot = nums[R];
        int pivotIndex = R--;
        while (L <= R)
        { // skip the same value!
            while (L <= R && nums[L] <= pivot)
            {
                L++;
            }
            // L > R or nums[L] > pivot
            while (L <= R && nums[R] >= pivot)
            {
                R--;
            }
            if (L >= R)
                break;
            swap(nums[L], nums[R]);
        }
        swap(nums[L], nums[pivotIndex]);
        // cout << "pivot " << pivot << " at " << L << "\n";
        return L;
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

class Solution
{
public:
    int partition(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return left;
        int pivotIndex = right;
        int pivot = nums[right--]; // last elem as a pivot
        while (true)
        {
            // forward until we find nums[left] >= pivot
            // if sorted, nums[left] == pivot and left == pivotIndex
            while (nums[left] < pivot)
            {
                left++;
            }
            // go back until we find nums[right] < pivot
            // if its sorted, right == left
            while (right > left && nums[right] >= pivot)
                right--;
            if (left >= right)
                break;
            swap(nums[left], nums[right]);
        }
        swap(nums[left], nums[pivotIndex]);
        return left;
    }
    void quick(vector<int> &nums, int left, int right)
    {
        if (left >= right)
        {
            return;
        }
        int randPivot = rand() % (right - left + 1) + left;
        swap(nums[randPivot], nums[right]);
        int pivotIndex = partition(nums, left, right);
        quick(nums, left, pivotIndex - 1);
        quick(nums, pivotIndex + 1, right);
    }
    vector<int> sortArray(vector<int> &nums)
    {
        quick(nums, 0, nums.size() - 1);
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