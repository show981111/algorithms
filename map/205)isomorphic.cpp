/**
 * Bidirectional Map
 * A->B, B->A
 */

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        unordered_map<char, char> fw;
        unordered_map<char, char> bw;

        int N = s.size();
        for (int i = 0; i < N; i++)
        {
            if (fw.count(s[i]) > 0)
            {
                if (fw[s[i]] != t[i])
                    return false;
            }
            else
            {
                fw[s[i]] = t[i];
                if (bw.count(t[i]) > 0 && bw[t[i]] != s[i])
                    return false;
                bw[t[i]] = s[i];
            }
        }

        return true;
    }
};