/**
 * @brief number of 1's in X is ...
 * right shit X by one, then if X is odd, add 1(LSB)
 *                              X is even, add 0
 *
 * EX) 7 = (111), 3 = (11)
 *
 * Just counting 1's in X is,
 * while(X > 0)
 *     count += (X %2) or count += (X & 1);
 *     X /= 2;
 *
 */

class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> ans(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            if (i % 2 == 0)
            { // even
                ans[i] = ans[i >> 1];
            }
            else
            { // odd
                ans[i] = ans[i >> 1] + 1;
            }
        }
        return ans;
    }
};