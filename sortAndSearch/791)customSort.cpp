/**
 * Custom ordered counting sort!
 *
 * All we need is an ordered bucket so that we can fill in letters in order.
 */

class Solution
{
public:
    string customSortString(string order, string s)
    {
        vector<int> freq(28, 0);
        for (char &c : s)
        {
            freq[c - 'a']++;
        }

        int idx = 0;
        for (char &c : order)
        {
            int i = c - 'a';
            while (freq[i] > 0)
            {
                s[idx++] = c;
                freq[i]--;
            }
        }
        for (int i = 0; i < 28; i++)
        {
            char c = i + 'a';
            while (freq[i] > 0)
            {
                s[idx++] = c;
                freq[i]--;
            }
        }

        return s;
    }
};

/**
 * Alternative, custom comparator
 */
class Solution
{
public:
    string customSortString(string order, string s)
    {
        vector<int> orderLoc(28, -1);
        for (int i = 0; i < order.size(); i++)
        {
            orderLoc[order[i] - 'a'] = i;
        }
        sort(s.begin(), s.end(), [&orderLoc](char &a, char &b)
             {
            if(orderLoc[a - 'a'] != -1 && orderLoc[b - 'a'] != -1){
                if(orderLoc[a - 'a'] < orderLoc[b - 'a']) return true;
                return false;
            }else if(orderLoc[a - 'a'] != -1){
                return true;
            }else{
                return false;
            } });

        return s;
    }
};