/**
 * Ascii code based MAP
 * => Can replace to vector with index as a key.
 * Size can be determined using, 'z' - '0' + 1 or 'z' - 'a' + 1 => Just put the last character - first character + 1 as a size!
 */

class Solution
{
public:
    struct Count
    {
        int cnt = 0;
        char c;
    };
    string frequencySort(string s)
    {
        vector<Count> v('z' - '0' + 1); // for last elem
        for (int i = 0; i < v.size(); i++)
        {
            v[i].c = i + '0';
        }

        for (char &c : s)
        {
            v[c - '0'].cnt++;
        }

        sort(v.begin(), v.end(), [](const Count &a, const Count &b)
             { return a.cnt > b.cnt; });

        int idx = 0;
        for (int i = 0; i < v.size(); i++)
        {
            while (v[i].cnt-- > 0)
            {
                s[idx++] = v[i].c;
            }
        }
        return s;
    }
};