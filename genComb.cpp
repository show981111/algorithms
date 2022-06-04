#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

void print(vector<int> &p)
{
    cout << "----------------\n";
    for (int item : p)
        cout << item << " ";
    cout << endl;
}
vector<vector<int>> res;
void genComb(vector<int> &path, size_t from, int n, int k)
{
    if (path.size() == (size_t)k)
    {
        res.push_back(path);
        return;
    }

    int to = from + n - (k - (int)path.size());
    for (int i = from; i <= min(n, to); i++)
    {
        path.push_back(i);
        cout << "BEFORE \n";
        print(path);
        genComb(path, i + 1, n, k);
        path.pop_back();
        cout << "AFTER \n";
        print(path);
    }
} // genPerms()
vector<vector<int>> k_combinations(int n, int k)
{ // nCk
    vector<int> path;
    genComb(path, 1, n, k);
    return res;
}

int main()
{
    k_combinations(5, 4);
    cout << "*************\n";
    for (size_t i = 0; i < res.size(); i++)
    {
        for (size_t j = 0; j < res[i].size(); j++)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}