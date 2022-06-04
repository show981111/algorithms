class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        int dest = graph.size() - 1;
        vector<vector<int>> res;
        vector<bool> visited(dest + 1, false);
        stack<int> st;
        st.push(0);
        visited[0] = true;
        vector<int> path;
        path.reserve(dest + 1);

        while (!st.empty())
        {
            int cur = st.top();
            path.push_back(cur);
            if (cur == dest)
            {
                res.push_back(path);
            }
            st.pop();
            bool stepBack = true;
            for (int i = 0; i < graph[cur].size(); i++)
            {
                if (!visited[graph[cur][i]])
                {
                    stepBack = false;
                    visited[graph[cur][i]] = true;
                    st.push(graph[cur][i]);
                }
            }
            if (stepBack)
                path.pop_back();
            visited[cur] = false;
        }

        return res;
    }
};