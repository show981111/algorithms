/**
 * @brief DP Mindset
 *
 * Always think, including this elem, and not, what's the relationship?
 *
 * T(n) =
 *      1) s[n] and s[n-1 ~ n] is both decodable => T(n) = T(n-1) + T(n-2) : s[n] can be separated and s[n-1~n] can be separated
 *      2) only s[n] is decodable => T(n) = T(n-1) : s[n] should be separated from 0~ n-1
 *      3) only s[n-1 ~ n] is decodable => T(n) = T(n-2) : s[n-1 ~ n] should be seperated from 0~ n-2
 *      4) both are not decodable => that string is not decodable at all
 */

class Solution
{
public:
    int numDecodings(string s)
    {
        vector<int> memo(s.length(), 0);
        if (s[0] - '0' > 0 && s[0] - '0' < 27)
        {
            memo[0] = 1;
            if (s.length() == 1)
                return 1;

            bool curDecodable = s[1] - '0' > 0 && s[1] - '0' < 27;
            bool adjDecodable = stoi(s.substr(0, 2)) > 0 && stoi(s.substr(0, 2)) < 27;

            if (curDecodable && adjDecodable)
                memo[1] = 2;
            else if (curDecodable || adjDecodable)
                memo[1] = 1;
            else
                return 0;
        }
        else
            return 0;
        // set up base cases, n = 0, n = 1;
        int N = s.length();
        for (int i = 2; i < N; i++)
        {
            bool curDecodable = s[i] - '0' > 0 && s[i] - '0' < 27;
            bool adjDecodable = s[i - 1] - '0' != 0 && stoi(s.substr(i - 1, 2)) > 0 && stoi(s.substr(i - 1, 2)) < 27;
            if (curDecodable && adjDecodable)
                memo[i] = memo[i - 1] + memo[i - 2];
            else if (curDecodable)
                memo[i] = memo[i - 1];
            else if (adjDecodable)
                memo[i] = memo[i - 2];
            else
                return 0;
        }

        // for(int i = 0; i < N ;i++)
        //     cout << memo[i] << " ";
        // cout << endl;

        return memo[N - 1];
    }
};

/**
 * @brief Bottom-up O(1) Space
 *
 */

class Solution
{
public:
    int numDecodings(string s)
    {
        int fir = 0, sec = 0, third = 0;
        if (s[0] - '0' > 0 && s[0] - '0' < 27)
        {
            fir = 1;
            if (s.length() == 1)
                return 1;

            bool curDecodable = s[1] - '0' > 0 && s[1] - '0' < 27;
            bool adjDecodable = stoi(s.substr(0, 2)) > 0 && stoi(s.substr(0, 2)) < 27;

            if (curDecodable && adjDecodable)
                sec = 2;
            else if (curDecodable || adjDecodable)
                sec = 1;
            else
                return 0;
        }
        else
            return 0;
        third = sec;
        int N = s.length();
        for (int i = 2; i < N; i++)
        {
            bool curDecodable = s[i] - '0' > 0 && s[i] - '0' < 27;
            bool adjDecodable = s[i - 1] - '0' != 0 && stoi(s.substr(i - 1, 2)) > 0 && stoi(s.substr(i - 1, 2)) < 27;
            if (curDecodable && adjDecodable)
                third = fir + sec;
            else if (curDecodable)
                third = sec;
            else if (adjDecodable)
                third = fir;
            else
                return 0;

            fir = sec;
            sec = third;
        }

        // for(int i = 0; i < N ;i++)
        //     cout << memo[i] << " ";
        // cout << endl;

        return third;
    }
};