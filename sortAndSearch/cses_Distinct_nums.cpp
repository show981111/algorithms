#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    unordered_set<int> st;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        st.insert(x);
    }
    cout << st.size();
}