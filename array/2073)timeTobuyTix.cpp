/**
 * Optimal one-pass
 */

class Solution
{
public:
    /*
    3 4 5 <6> 4 3 2 Row sum
    2 3 4 5 6 7 8 | + 7
    1 2 3 4 5 6 7 | + 7
    0 1 2 3 4 5 6 | + 7
    0 0 1 2 3 4 5 | + 6
    0 0 0 1 2 3 4 | + 5
    0 0 0 0 1 2 3 | + 1
    3 + 4 +5 + 6 + 5+ 5 + 5 = colsum
    For target X, at least X iteration is needed.
    So, (X-1)*arr.size() but arr.size() is changing...

    Lets sum it up as a column not the row from the above board!

    Always visualizing is helpful!
    */
    int timeRequiredToBuy(vector<int> &tickets, int k)
    {
        int t = 0;
        int it = tickets[k];
        for (int i = 0; i < tickets.size(); i++)
        {
            if (i <= k)
            {
                if (tickets[i] < it)
                {
                    t += tickets[i];
                }
                else
                {
                    t += it;
                }
            }
            else
            {
                if (tickets[i] < it)
                {
                    t += tickets[i];
                }
                else
                {
                    t += it - 1;
                }
            }
        }
        return t;
    }
};

/**
 * B-force
 */
class Solution
{
public:
    /*
    3 4 5 <6> 4 3 2
    2 3 4 5 6 7 8 + 7
    1 2 3 4 5 6 7 + 7
    0 1 2 3 4 5 6 + 6
    0 0 1 2 3 4 5 + 5
    0 0 0 1 2 3 4 + 4
    0 0 0 0 1 2 3 + 1

    For target X, at least X iteration is needed.
    So, (X-1)*arr.size() but arr.size() is changing...
    */
    int timeRequiredToBuy(vector<int> &tickets, int k)
    {
        int t = 0;
        int it = tickets[k];
        for (int i = 0; i < it; i++)
        {
            for (int j = 0; j < tickets.size(); j++)
            {
                if (tickets[j] > 0)
                {
                    t++;
                    tickets[j]--;
                }
                if (tickets[k] == 0)
                    break;
            }
        }
        return t;
    }
};