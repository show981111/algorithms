class Solution
{
public:
    /*
    Find i,j,k such that
    XOR of [i,j) == XOR of [j,k]
    B-force: O(N^3)
    Cannot sort or change the array since indexing matters.
    Can I get the XOR of all subarrays? -> O(N^2), still searching this space will be O(N^2^2)

    HINT: A ^ A == 0. [A, B]. IF A ^ B == 0, A == B.
    Now the problem is equal to finding the subarray of length >= 2 where XOR == 0
    A ^ B ^ B = A
    arr[i:k] == 0
    arr[i:k-j] ^ arr[k-j:k] == 0
    Using this, we can know that arr[i:i+1] == arr[i+1:k], arr[i:i+2] == arr[i+2:k] ...
    Thus, if arr[i:k] == 0, there are k - i number of pairs that have the same XOR
    */
    int countTriplets(vector<int> &arr)
    {
        int c = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            int pref = arr[i];
            for (int j = i + 1; j < arr.size(); j++)
            {
                pref ^= arr[j];
                if (pref == 0)
                {
                    c += j - i;
                }
            }
        }
        return c;
    }
};
