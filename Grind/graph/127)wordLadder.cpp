/**
 * @brief Can we come up with the idea of using a graph?
 *
 * In unweighted graph minimum distance => BFS!
 * Using dfs takes lots of time because it has to find
 * all path from A to B
 *
 * Finding Shortest Path
 * One end BFS vs Two end BFS
 * https://stackoverflow.com/questions/10995699/how-do-you-use-a-bidirectional-bfs-to-find-the-shortest-path
 * https://efficientcodeblog.wordpress.com/2017/12/13/bidirectional-search-two-end-bfs/
 * We can utilize bi-directional serach here
 */

class Solution
{
public:
    bool isDifferByOne(string &a, string &b)
    {
        if (a.size() != b.size())
            return false;
        bool diff = false;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i])
            {
                if (diff)
                    return false;
                diff = true;
            }
        }
        return true;
    }
    void dfs(vector<vector<int>> &graph, vector<string> &wordList, string &endWord, vector<bool> &visited, int curLength, int curIndex, int &minPath)
    {

        if (endWord == wordList[curIndex])
        {
            minPath = min(minPath, curLength);
            return;
        }
        if (curLength >= wordList.size())
            return;

        for (int i = 0; i < graph[curIndex].size(); i++)
        {
            int nextIndex = graph[curIndex][i];
            if (!visited[nextIndex])
            {
                visited[nextIndex] = true;
                dfs(graph, wordList, endWord, visited, curLength + 1, nextIndex, minPath);
                visited[nextIndex] = false;
            }
        }
    }

    int bfs(vector<vector<int>> &graph, vector<string> &wordList, string &beginWord, string &endWord, queue<int> &q, vector<bool> &visited)
    {
        int distance = 1;
        while (!q.empty())
        {
            int qSize = q.size();
            distance++;
            for (int i = 0; i < qSize; i++)
            {
                int curIndex = q.front();
                q.pop();

                for (int next : graph[curIndex])
                {
                    if (!visited[next])
                    {
                        // cout << wordList[next] << endl;
                        visited[next] = true;
                        if (wordList[next] == endWord)
                        {
                            return distance + 1;
                        }
                        q.push(next);
                    }
                }
            }
        }
        return -1;
    }
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        bool isEndWordExist = false;
        for (string &w : wordList)
        {
            if (w == endWord)
                isEndWordExist = true;
        }
        if (!isEndWordExist)
            return 0;

        vector<vector<int>> graph(wordList.size());
        for (int i = 0; i < wordList.size(); i++)
        {
            for (int j = i + 1; j < wordList.size(); j++)
            {
                if (isDifferByOne(wordList[i], wordList[j]))
                {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        vector<bool> visited(wordList.size(), false);
        queue<int> q;
        for (int i = 0; i < wordList.size(); i++)
        {
            if (isDifferByOne(beginWord, wordList[i]))
            {
                if (wordList[i] == endWord)
                    return 2;
                visited[i] = true;
                q.push(i);
            }
        }

        int ans = bfs(graph, wordList, beginWord, endWord, q, visited);

        return ans == -1 ? 0 : ans;
    }
};

/**
 * @brief Bidrectional search
 * We just need two queues(forward, backward)
 * Then if there is an overlap in visited nodes of both direction,
 * MEET!
 * Others, keep moving
 *
 * https://xq-blog.dev/blog/bidirectional-search/
 */

int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    int endWordIndex = -1, beginWordIndex = -1;

    for (int i = 0; i < wordList.size(); i++)
    {
        if (wordList[i] == endWord)
            endWordIndex = i;
        if (wordList[i] == beginWord)
            beginWordIndex = i;
    }

    if (endWordIndex == -1)
        return 0;

    vector<vector<int>> graph(wordList.size());
    for (int i = 0; i < wordList.size(); i++)
    {
        for (int j = i + 1; j < wordList.size(); j++)
        {
            if (isDifferByOne(wordList[i], wordList[j]))
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    if (beginWordIndex == -1)
    {
        vector<int> beginNeighbor;
        for (int i = 0; i < wordList.size(); i++)
        {
            if (isDifferByOne(beginWord, wordList[i]))
            {
                beginNeighbor.push_back(i);
                graph[i].push_back(wordList.size());
            }
        }
        graph.push_back(beginNeighbor);
        beginWordIndex = graph.size() - 1;
    }
    // make graph done
    queue<int> forward, backward;
    unordered_set<int> fVisited, bVisited;
    int ladder = 2;
    forward.push(beginWordIndex);
    fVisited.insert(beginWordIndex);
    backward.push(endWordIndex);
    bVisited.insert(endWordIndex);

    while (!forward.empty() && !backward.empty())
    {
        if (fVisited.size() + bVisited.size() > wordList.size() + 1)
        {
            break;
        }
        int fqSize = forward.size();

        for (int c = 0; c < fqSize; c++)
        {
            int fFront = forward.front();
            forward.pop();

            for (int i = 0; i < graph[fFront].size(); i++)
            {
                int next = graph[fFront][i];
                if (bVisited.find(next) != bVisited.end())
                {
                    return ladder;
                }
                if (fVisited.find(next) == fVisited.end())
                {
                    fVisited.insert(next);
                    forward.push(next);
                }
            }
        }
        ladder++;

        int bqSize = backward.size();

        for (int c = 0; c < bqSize; c++)
        {
            int bFront = backward.front();
            backward.pop();

            for (int i = 0; i < graph[bFront].size(); i++)
            {
                int next = graph[bFront][i];
                if (fVisited.find(next) != fVisited.end())
                {
                    return ladder;
                }
                if (bVisited.find(next) == bVisited.end())
                {
                    bVisited.insert(next);
                    backward.push(next);
                }
            }
        }
        ladder++;
    }
    return 0;
}