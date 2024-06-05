/**
 * Since we know the range, 0 ~ 2^N -1, we just sort and
 * return first number that doesn't appear => NAIVE
 */
class Solution
{
public:
    string findDifferentBinaryString(vector<string> &nums)
    {
        sort(nums.begin(), nums.end());
        int leng = nums[0].size();
        int n = 0;
        for (string &s : nums)
        {
            bitset<16> b(s);
            if (b.to_ulong() != n)
                return bitset<16>(n).to_string().substr(16 - leng);
            else
                n++;
        }
        return bitset<16>(n).to_string().substr(16 - leng);
    }
};

/**
 * CANTOR's method
 */
class Solution
{
public:
    string findDifferentBinaryString(vector<string> &nums)
    {
        // Cantor's diagonal method
        // If i_th digit is different from i_th string, then it is different from all other strings!
        string ans = "";
        for (int i = 0; i < nums.size(); i++)
        {
            ans += nums[i][i] == '0' ? '1' : '0';
        }
        return ans;
    }
};