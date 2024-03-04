class Solution
{
public:
/*
Grouping the person who knows secret -> Union-Find?

Then, we should know edges between person who knows the secret = meetings

Problem:
Anyone who knows the scret at time T can spread secret after the meeting >= T.
Thus, connections before < T doesn't affect spreading secret
=> Can't use the same "Parent" array since it carries the connections from previous time.
Also, secret propagates instantly -> All meetings at the same time will know

For meetings at Time "T" => Build connection and group. If anyone in the group knows the secret, all members know

*/
#define MAX_TIME 1e5 + 5

    int get(vector<int> &par, int x)
    {
        if (x == par[x])
            return x;
        else
            return par[x] = get(par, par[x]);
    }

    void merge(vector<int> &temp, vector<vector<int>> &meetings,
               const pair<int, int> &meetingInSameTime, vector<int> &knowSecret)
    {
        // reset
        for (int i = meetingInSameTime.first; i <= meetingInSameTime.second; i++)
        {
            temp[meetings[i][0]] = meetings[i][0];
            temp[meetings[i][1]] = meetings[i][1];
        }

        // build a group
        for (int i = meetingInSameTime.first; i <= meetingInSameTime.second;
             i++)
        {
            int ap = get(temp, meetings[i][0]);
            int bp = get(temp, meetings[i][1]);

            if (knowSecret[ap] || knowSecret[bp])
            {
                knowSecret[ap] = true;
                knowSecret[bp] = true; // mark root to know the secret if one knows
            }

            // should mark knowsecret before we merge since we want to propagate one group's secret to other
            if (ap <= bp)
                temp[bp] = ap; // merge with smaller root
            else
                temp[ap] = bp;
        }

        // members will know if the root knows -> In case merging secret comes later
        for (int i = meetingInSameTime.first; i <= meetingInSameTime.second; i++)
        {
            int ap = get(temp, meetings[i][0]);
            int bp = get(temp, meetings[i][1]);
            if (knowSecret[ap] || knowSecret[bp])
            {
                knowSecret[meetings[i][0]] = true;
                knowSecret[meetings[i][1]] = true;
            }
        }
    }

    vector<int> findAllPeople(int n, vector<vector<int>> &meetings,
                              int firstPerson)
    {
        vector<int> par(n);
        vector<int> ans;
        vector<int> knowSecret(n);

        knowSecret[0] = true;
        knowSecret[firstPerson] = true;
        sort(meetings.begin(), meetings.end(),
             [](vector<int> &a, vector<int> &b)
             {
                 return a[2] < b[2]; // meeting ascending order.
             });

        int t = meetings[0][2];
        pair<int, int> meetingInSameTime = {0, 0};

        for (int i = 0; i < meetings.size(); i++)
        {
            // problem: meeting that occurs after one person knows the secret
            // can be merged. otherwise can't merge
            if (t == meetings[i][2])
            {
                meetingInSameTime.second = i;
            }
            else
            {
                // t != meetingp[2] -> MERGE prev meetings
                merge(par, meetings, meetingInSameTime, knowSecret);

                // next
                meetingInSameTime = {i, i};
                t = meetings[i][2];
            }
        }
        merge(par, meetings, meetingInSameTime, knowSecret);
        for (int i = 0; i < n; i++)
        {
            if (knowSecret[i])
                ans.push_back(i);
        }
        return ans;
    }
};
