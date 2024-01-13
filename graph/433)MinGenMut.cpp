class Solution
{
public:
    /*
    Unweighted graph MIN/Shortest? -> BFS!
    Shortest path will arrive earliest to the destination in BFS traversal
    */
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        queue<string> q;
        q.push(startGene);
        unordered_set<string> st;
        unordered_set<string> visited;
        visited.insert(startGene);
        for (const auto b : bank)
            st.insert(b);
        int dist = 0;

        if (st.count(endGene) == 0)
            return -1;
        if (startGene == endGene)
            return 0;

        const char choice[] = {'A', 'C', 'G', 'T'};
        while (!q.empty())
        {
            int qSize = q.size();

            dist++;
            for (int iter = 0; iter < qSize; iter++)
            {
                string &f = q.front(); // To prevent copying. Queue/Stack etc.. we can modify elems.
                // For map,set, pq etc, we cannot modify a "key" cuz it will impact ordering

                for (int i = 0; i < 8; i++)
                {
                    char temp = f[i];
                    for (int j = 0; j < 4; j++)
                    {
                        f[i] = choice[j];
                        if (f == endGene)
                            return dist;
                        if (st.count(f) > 0 && visited.count(f) == 0)
                        {
                            q.push(f);
                            // cout << f << " ";
                            visited.insert(f);
                        }
                    }
                    f[i] = temp;
                }
                q.pop();
            }
        }
        return -1;
    }
};