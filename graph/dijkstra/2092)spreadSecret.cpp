/**
 * https://leetcode.com/problems/find-all-people-with-secret/solutions/4774640/dijkstra-approach-o-nlogn-with-intuition/
 *
 */

class Solution
{
public:
    /*
    0 + firstperson at time 0
    Shared meeting takes place with a person has secret
    Secret spread instaneously, person can attend multiple meetings at the same time

    First intuition: BFS. Since one person can spread the secret to all neighbors(person who has the meeting with), we can use BFS.
    However, we have the additional constraion = TIME. Meeting should happen after that person get to know the secret. -> Need to track the "earliest" time this person knows the secret -> Dijkstra
    */
    const int MAX_TIME = 1e5 + 5;
    struct Meet
    {
        int person;
        int time; // know at time
    };
    vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
    {
        vector<int> ans;
        vector<vector<Meet>> graph(n);
        vector<int> knowSecretSince(n, MAX_TIME);

        for (vector<int> &v : meetings)
        {
            graph[v[0]].push_back({v[1], v[2]});
            graph[v[1]].push_back({v[0], v[2]});
        }

        auto comp = [](const Meet &a, const Meet &b)
        {
            return a.time > b.time;
        };
        priority_queue<Meet, vector<Meet>, decltype(comp)> pq(comp);
        ans.push_back(0);
        ans.push_back(firstPerson);
        knowSecretSince[0] = 0;
        knowSecretSince[firstPerson] = 0;
        pq.push({0, 0});
        pq.push({firstPerson, 0});

        while (!pq.empty())
        {
            Meet p = pq.top();
            pq.pop();
            if (p.time > knowSecretSince[p.person])
                continue; // know the secret late

            for (Meet neighbor : graph[p.person])
            {
                if (neighbor.time >= knowSecretSince[p.person])
                { // Can spread the secret
                    if (knowSecretSince[neighbor.person] == MAX_TIME)
                        ans.push_back(neighbor.person); // first time getting the secret
                    else if (knowSecretSince[neighbor.person] <= neighbor.time)
                        continue; // knew if before

                    // this is the earliest time it gets to know the secret
                    knowSecretSince[neighbor.person] = neighbor.time;
                    pq.push(neighbor);
                }
            }
        }

        return ans;
    }
};