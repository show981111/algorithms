/**
 * @brief MAX PROB
 *
 * Why we can use Dijkstra even tho it is a max path problem?
 * Dijkstra will choose the max prob from current node.
 * Can it be increased later?? => NO
 * Since 0 <= prob <= 1, the path will decrease or stay the same,
 * So Greedy Approach works!!
 *
 */

class Solution
{
public:
    struct Edge
    {
        int to;
        double prob;
        Edge(int t, double p) : to(t), prob(p) {}
    };
    class Comp
    {
    public:
        bool operator()(const Edge &a, const Edge &b)
        {
            return a.prob < b.prob;
        }
    };
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end)
    {
        vector<double> prob(n, 0);
        vector<vector<Edge>> graph(n);
        for (int i = 0; i < edges.size(); i++)
        {
            graph[edges[i][0]].push_back(Edge(edges[i][1], succProb[i]));
            graph[edges[i][1]].push_back(Edge(edges[i][0], succProb[i]));
        }
        priority_queue<Edge, vector<Edge>, Comp> pq;
        pq.push(Edge(start, 1));
        prob[start] = 1;
        while (!pq.empty())
        {
            Edge t = pq.top();
            pq.pop();
            if (t.to == end)
                return prob[end];

            for (int i = 0; i < graph[t.to].size(); i++)
            {
                int next = graph[t.to][i].to;
                double newProb = prob[t.to] * graph[t.to][i].prob;
                if (newProb > prob[next])
                {
                    prob[next] = newProb;
                    pq.push(Edge(next, newProb));
                }
            }
        }
        return 0;
    }
};