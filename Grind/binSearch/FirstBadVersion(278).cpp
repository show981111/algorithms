/**
 * @brief Binary Search
 * 1. When to break (base case)
 * 2. How to shrink the range by 1/2
 */

class Solution
{
public:
    int firstBadVersionHelper(int start, int end)
    {
        cout << start << " " << end << endl;
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2;
        bool isMidBad = isBadVersion(mid);
        bool isPrevBad = isBadVersion(mid - 1);
        if (!isPrevBad && isMidBad)
        {
            return mid;
        }
        else if (isMidBad)
        { // mid and prev are both bad
            end = mid - 1;
        }
        else
        { // mid and prev are both not bad. There is no way prev is bad and mid is good
          // cause after first bad, all are bad
            start = mid + 1;
        }
        return firstBadVersionHelper(start, end);
    }
    int firstBadVersion(int n)
    {
        return firstBadVersionHelper(1, n);
    }
};