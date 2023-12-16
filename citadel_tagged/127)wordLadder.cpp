/**
 * BFS and string as a Node!
 *
 * Shortest + undirected graph => BFS
 *
 * Can use Bidirectional BFS
 * using ForwardQueue/ForwardVisited
 * BackwardQueue / BackwardVisited
 *
 * => If BackwardVisited.count(forward's next) > 0 or ForwardVisited.count(Backward's next) > 0 : Found the meeting point!
 *
 * Bidirectional TC: O(b^(d/2)) when b is a branching factor and d is a distance to target
 * Normal BFS would be O(b^d)
 */

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_map<string, vector<string>> graph;
        unordered_set<string> words;
        for (string &word : wordList)
        {
            words.insert(word);
        }
        if (words.count(endWord) == 0)
            return 0;
        words.insert(beginWord);
        wordList.push_back(beginWord);
        for (string &word : wordList)
        {
            vector<string> &neighbor = graph[word];
            for (int i = 0; i < word.size(); ++i)
            {
                char originalChar = word[i];
                for (char replaced = 'a'; replaced <= 'z'; ++replaced)
                {
                    word[i] = replaced;
                    if (words.count(word) > 0 && replaced != originalChar)
                    {
                        neighbor.push_back(word);
                    }
                }
                word[i] = originalChar;
            }
        }

        words.clear();
        queue<string> q;
        q.push({beginWord});
        words.insert(beginWord);
        int dist = 1;

        while (!q.empty())
        {
            int qSize = q.size();

            for (int i = 0; i < qSize; i++)
            {
                string cur = move(q.front());
                q.pop();

                for (string &neighbor : graph[cur])
                {
                    if (neighbor == endWord)
                    {
                        return dist + 1;
                    }
                    if (words.count(neighbor) == 0)
                    {
                        words.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            ++dist;
        }
        return 0;
    }
};

/**
 * Any node can be represented as an INT!
 */
class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_map<string, int> words;
        for (int i = 0; i < wordList.size(); ++i)
        {
            words[wordList[i]] = i;
        }
        if (words.count(endWord) == 0)
            return 0;

        words[beginWord] = wordList.size();
        wordList.push_back(beginWord);

        vector<vector<int>> graph(wordList.size());
        vector<bool> visited(wordList.size());

        for (int from = 0; from < wordList.size(); ++from)
        {
            vector<int> &neighbor = graph[from];
            string &word = wordList[from];
            for (int i = 0; i < word.size(); ++i)
            {
                char originalChar = word[i];
                for (char replaced = 'a'; replaced <= 'z'; ++replaced)
                {
                    word[i] = replaced;
                    if (words.count(word) > 0 && replaced != originalChar)
                    {
                        neighbor.push_back(words[word]);
                    }
                }
                word[i] = originalChar;
            }
        }

        queue<int> q;
        q.push(words[beginWord]);
        visited[words[beginWord]] = true;
        int dist = 1;

        while (!q.empty())
        {
            int qSize = q.size();

            for (int i = 0; i < qSize; i++)
            {
                int cur = q.front();
                q.pop();

                for (int &neighbor : graph[cur])
                {
                    if (wordList[neighbor] == endWord)
                    {
                        return dist + 1;
                    }
                    if (visited[neighbor] == false)
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            ++dist;
        }
        return 0;
    }
};