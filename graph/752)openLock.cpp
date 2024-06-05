class Solution
{
public:
    /*
    Minimum distance from src to target.
    Use BFS!
    Don't forget VISITED!
    Mark visited when we PUSH to the queue.
    Each element should go to Queue only once.
    */

    int openLock(vector<string> &deadends, string target)
    {
        string init = "0000";
        if (init == target)
            return 0;
        unordered_set<string> dds;
        unordered_set<string> visited;
        for (string &d : deadends)
        {
            dds.insert(d);
        }
        queue<string> q;
        if (dds.count(init) == 0)
        {
            q.push(init);
            visited.insert(init);
        }
        int moves = 0;

        while (!q.empty())
        {
            int qSize = q.size();
            moves++;
            for (int t = 0; t < qSize; t++)
            {
                string f = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    for (int d = -1; d <= 1; d += 2)
                    {
                        char temp = f[i];
                        int num = f[i] - '0';
                        num += d;
                        if (num < 0)
                            f[i] = '9';
                        else if (num >= 10)
                            f[i] = '0';
                        else
                            f[i] = num + '0';
                        if (dds.count(f) == 0 && visited.count(f) == 0)
                        {
                            if (f == target)
                            {
                                return moves;
                            }
                            // cout << "Next " << f << endl;
                            visited.insert(f);
                            q.push(f);
                        }
                        f[i] = temp;
                    }
                }
            }
        }
        return -1;
    }
};
