/**
 * Failed version
 * Bactracking takes Worst case O(E^V). Backtracking basically traverse all decision paths, which is O(V^V) (for each node, max V amount of neighbors)
 */

class Solution
{
public:
    struct Ticket
    {
        string dest;
        int index;
    };
    unordered_set<string> failed;
    void solve(unordered_map<string, vector<Ticket>> &graph, const int tixSize, string &used, int curLength, vector<string> &curPath, bool &found)
    {
        if (curLength == tixSize + 1)
        {
            found = true;
            return;
        }
        string enc = used + curPath.back();
        if (failed.count(enc) > 0)
        {
            // cout << "a";
            return;
        }

        for (Ticket &t : graph[curPath.back()])
        {
            if (used[t.index] == '1')
                continue;
            used[t.index] = '1';
            curPath.push_back(t.dest);
            // cout << curLength << " " << t.dest << endl;
            solve(graph, tixSize, used, curLength + 1, curPath, found);
            if (found)
                break;
            curPath.pop_back();
            used[t.index] = '0';
        }
        failed.insert(enc);
    }
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        unordered_map<string, vector<Ticket>> graph;
        for (int i = 0; i < tickets.size(); i++)
        {
            graph[tickets[i][0]].push_back(Ticket{tickets[i][1], i});
        }
        for (auto &item : graph)
        {
            sort(item.second.begin(), item.second.end(), [](const Ticket &a, const Ticket &b)
                 { return a.dest < b.dest; });
        }
        // for(auto iter: graph){
        //     cout << iter.first << "\n";
        //     for(int i = 0; i < iter.second.size(); i++){
        //         cout << iter.second[i].dest << " ";
        //     }
        //     cout << endl;
        // }
        bool found = false;
        vector<string> path;
        path.push_back("JFK");
        string used(tickets.size(), '0');
        solve(graph, tickets.size(), used, 1, path, found);
        return path;
    }
};

/**
 * Euler Path
 *
 * 한붓그리기
 *
 * First, we know there is an Euler path by assumption of the problem.
 * All we need to do is, just traverse and delete that edge.
 *
 * There must be one exit point since there is an euler path.
 * If we hit the end that we cannot go further, that point is the Exit! Thus push it to the path
 * and recurse. As we delete visited edges, the exit point will change for that subgraph!
 */

class Solution
{
public:
    void solve(unordered_map<string, vector<string>> &graph, string cur, vector<string> &path)
    {
        while (graph[cur].size() > 0)
        {
            string next = graph[cur].back();
            graph[cur].pop_back();
            solve(graph, next, path);
        }

        path.push_back(cur);
    }
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        unordered_map<string, vector<string>> graph;
        for (int i = 0; i < tickets.size(); i++)
        {
            graph[tickets[i][0]].push_back(tickets[i][1]);
        }
        for (auto &item : graph)
        {
            sort(item.second.rbegin(), item.second.rend());
        }

        vector<string> path;
        solve(graph, "JFK", path);
        reverse(path.begin(), path.end());
        return path;
    }
};