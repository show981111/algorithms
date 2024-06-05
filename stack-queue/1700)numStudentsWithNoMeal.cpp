class Solution
{
public:
    /*
    Simple Queue and Stack.
    However, can we do it without iterating all the time?
    */
    int countStudents(vector<int> &students, vector<int> &sandwiches)
    {
        queue<int> q;
        for (int i = 0; i < students.size(); i++)
            q.push(students[i]);
        int top = 0;

        while (!q.empty())
        {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++)
            {
                // cout << q.size() << " sz \n";
                if (q.front() == sandwiches[top])
                {
                    top++;
                    // cout << "POP " << q.front() << endl;
                    q.pop();
                    break;
                }
                else
                {
                    q.push(q.front());
                    q.pop();
                }
            }
            if (q.size() == 0)
                break;
            if (qSize == q.size() || top == sandwiches.size())
            {
                // cannot pop anyone.
                return qSize;
            }
        }
        return 0;
    }
};