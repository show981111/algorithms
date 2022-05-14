/**
 * @brief Using XOR
 * A XOR A = 0, 0 XOR A = A, using this we can get a single number
 * We can also use MAP, SORT etc
 */

class Solution
{
public:
    // XOR is ^ , bitwise not is ~, A xor B is not !a & !b a= 0, b = 0, then,,, contradiction
    int singleNumber(vector<int> &nums)
    {
        int res = 0;
        for (auto iter = nums.begin(); iter != nums.end(); ++iter)
        {
            res = res ^ (*iter);
        }
        return res;
    }
};