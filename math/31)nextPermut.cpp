/**
 * @brief Math... Algo
 *
 * https://leetcode.com/problems/next-permutation/solutions/13867/c-from-wikipedia/
 * The next permutation of an array of integers is the next lexicographically greater permutation
 *
 * Lexicographically? -> probably ordering... If the array is descending order sorted => Reached end
 * Think incrementally(recursively)
 * Since permutation changes elem from the right(Left elem is fixed until the rest of the elem becomes
 * descending sorted), we start from the right.
 *
 * [2, 1, 4, 3]
 * i == 3 ~ end reverse sorted? Yes decrease i
 * i == 2 ~ end reverse sorted? Yes i--
 * i == 1 ~ end reverse sorted? No!! -> So, who is next pivot? (arr[i+1:] is reverse sorted)
 *                                      We need to select element that comes right next to arr[i]
 *                                      from arr[i+1:](next elem when is asc sorted)
 *        Then, swap arr[i] with that element! because that element is next pivot.
 *        Since arr[i] was right before the element we swapped, arr[i+1:] is still sorted in DSC order.
 *        Thus, now we can just reverse the arr[i+1:] then it becomes asc sorted order!
 *
 * SOME CPP NOTE
 */
class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        // last permut is descending order sort
        // [A, B, C, D] last elem reverse sort == current pos?
        // go to next index. i ~ end reverse sort == current pos?
        // if so, decrese i
        // else next_permut of (i ~ end)

        // 2, 1, 3, 4 -> 2, 1, 4, 3 -> 2, 3, 1, 4
        int N = nums.size();
        bool allSorted = false;
        int i = N - 1;
        while (!allSorted && i != 0) // O(N)
        {
            if (nums[i - 1] >= nums[i]) // check if it is sorted
            {
                i--;
            }
            else
            {
                // + O(logN) because we only do this once and break!
                // nums[i-1] < nums[i] ex) 2,(1,4),3
                auto nextPivot = upper_bound(nums.rbegin(), nums.rbegin() + N - 1 - i, nums[i - 1]);
                iter_swap(nextPivot, nums.begin() + i - 1);
                break;
            }
        }
        if (N > 1) // O(N)
            reverse(nums.begin() + i, nums.end());
    }
};