#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> applications(n);
    vector<int> sizeOfApt(m);
    for (int i = 0; i < n; i++)
    {
        cin >> applications[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> sizeOfApt[i];
    }
    sort(applications.begin(), applications.end());
    sort(sizeOfApt.begin(), sizeOfApt.end());
    int allocNum = 0;

    int aptIdx = 0, appIdx = 0;
    for (; appIdx < n; ++appIdx)
    {
        // cout << "[appIdx] Apt Candidate For " << applications[appIdx];
        auto aptCandidate = lower_bound(sizeOfApt.begin() + aptIdx, sizeOfApt.end(), applications[appIdx] - k);
        if (aptCandidate == sizeOfApt.end())
            break;
        // cout << " is " << *aptCandidate << endl;
        if (*aptCandidate > applications[appIdx] + k)
        {
            continue;
        }
        if (*aptCandidate <= applications[appIdx] + k)
        {
            // cout << applications[appIdx] << " TO " << *aptCandidate << endl;
            allocNum++;
            aptIdx = aptCandidate - sizeOfApt.begin() + 1; // starting from next apt
        }
    }
    cout << allocNum << "\n";
}