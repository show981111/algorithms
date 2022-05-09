/**
 * @brief BackTracking
 * Find the recursive relation of the problem
 * T(n) = something + T(n-1)
 * We can make T(n) if we add or do something to T(n-1) -> recursive!
 * Set BaseCase and decide how to forward the recursive
 * In this problem 0~n-1 is fixed, rest of them are changing!
 * So fixed part is moving forward until the end of path!
 * Divde Fixed part and Not fixed(unkown) part!!
 */

class Solution
{
public:
    vector<string> res;
    void genPerms(int n, int lastLetterIndex, string &path)
    {
        // cout << "n is " << n << endl;
        if (n > lastLetterIndex)
        {
            res.push_back(path);
            return;
        }
        if (isalpha(path[n]))
        {
            if (islower(path[n]))
            {
                path[n] = toupper(path[n]);
                // cout << n+1 << "is called \n";
                genPerms(n + 1, lastLetterIndex, path);
                path[n] = tolower(path[n]);
            }
            else
            {
                path[n] = tolower(path[n]);
                // cout << n+1 << "is called \n";
                genPerms(n + 1, lastLetterIndex, path);
                path[n] = toupper(path[n]);
            }
        }
        genPerms(n + 1, lastLetterIndex, path);
    }
    vector<string> letterCasePermutation(string s)
    {
        int lastLetterIndex;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (isalpha(s[i]))
            {
                lastLetterIndex = i;
                break;
            }
        }
        genPerms(0, lastLetterIndex, s);
        return res;
    }
};