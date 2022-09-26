/**
 * @brief Counting pairs in the Array => we can use mergeSort a lot!
 * If we can divide the array's problem into subarray's problem... => divide and conquer
 * Process is T(N) = T(L, M) + T(M+1, R) + C (C is merging the subproblems)
 * Time complexity depends on C!
 *
 * Key function to implement is a "Merge"
 * How can we Linearly count something?
 * => user Sorting and Two pointers...
 */

class Solution
{
public:
    struct Entity
    {
        int val;
        int index;
        Entity(int v, int i) : val(v), index(i) {}
        Entity() {}
    };
    /**
     * Shortened version of Merge.
     * merge the process of sorting and counting
     */
    void merge(vector<Entity> &arr, int L, int M, int R, vector<int> &count)
    {
        int i = L, j = M + 1;
        vector<Entity> temp(R - L + 1);
        int index = 0;
        // count
        while (i <= M)
        {
            while (j <= R && arr[i].val > arr[j].val)
            {
                temp[index++] = arr[j];
                j++;
            }
            count[arr[i].index] += (j - M - 1);
            temp[index++] = arr[i++];
        }
        while (j <= R)
        {
            temp[index++] = arr[j++];
        }
        copy(temp.begin(), temp.end(), arr.begin() + L);
    }
    /*
     * old version
     */
    void merge(vector<Entity> &arr, int L, int M, int R, vector<int> &count)
    {
        int i = L, j = M + 1;
        vector<Entity> temp(R - L + 1);
        int index = 0;
        // count
        while (i <= M)
        {
            while (j <= R && arr[i].val > arr[j].val)
            {
                j++;
            }
            count[arr[i].index] += (j - M - 1);
            i++;
        }
        // sort
        i = L;
        j = M + 1;
        while (i <= M || j <= R)
        {
            if (i > M)
            {
                temp[index++] = arr[j++];
            }
            else if (j > R)
            {
                temp[index++] = arr[i++];
            }
            else
            {
                if (arr[i].val < arr[j].val)
                    temp[index++] = arr[i++];
                else
                    temp[index++] = arr[j++];
            }
        }
        copy(temp.begin(), temp.end(), arr.begin() + L);
    }
    void mergeSort(vector<Entity> &arr, vector<int> &count, int L, int R)
    {
        if (L >= R)
            return;
        int mid = L + (R - L) / 2;
        mergeSort(arr, count, L, mid);
        mergeSort(arr, count, mid + 1, R);
        merge(arr, L, mid, R, count);
    }

    vector<int> countSmaller(vector<int> &nums)
    {
        vector<Entity> arr(nums.size());
        vector<int> count(nums.size());
        for (int i = 0; i < nums.size(); i++)
            arr[i] = Entity(nums[i], i);
        mergeSort(arr, count, 0, nums.size() - 1);
        return count;
    }
};