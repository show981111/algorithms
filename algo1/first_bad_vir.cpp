// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

// Binary Search
class Solution
{
public:
    int firstBadVersionHelper(int start, int end)
    {
        if (start > end)
            return -1;
        int mid = start + (end - start) / 2; // to prevent int overflow dont use (st + end)/2
        bool curRes = isBadVersion(mid);
        if (mid == 0 && curRes)
            return mid;
        bool prevRes = isBadVersion(mid - 1);
        if (curRes && !prevRes) // cur == true, prev == false
            return mid;
        if (prevRes == true) // prev == true
            return firstBadVersionHelper(start, mid - 1);
        return firstBadVersionHelper(mid + 1, end); // prev == false, cur == false
    }
    int firstBadVersion(int n)
    {
        return firstBadVersionHelper(0, n);
    }
};
