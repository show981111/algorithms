#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
using namespace std;

bool swapEval(string &x, string &y, string &z, char op)
{
    string tempx = x, tempy = y, tempz = z;
    for (int i = 0; i < min(tempx.size(), tempy.size()); i++)
    {
        swap(tempx[i], tempy[i]);
        if (op == '+')
        {
            if (stoi(tempx) + stoi(tempy) == stoi(tempz))
            {
                x = tempx, y = tempy, z = tempz;
                return true;
            }
        }
        else if (op == '*')
        {
            if (stoi(tempx) * stoi(tempy) == stoi(tempz))
            {
                x = tempx, y = tempy, z = tempz;
                return true;
            }
        }
    }
    return false;
}

bool work(string &x, string &y, string &z, char op)
{
    if (swapEval(x, y, z, op))
    {
        return true;
    }
    if (swapEval(x, y, z, op))
    {
        return true;
    }
    tempx = x, tempy = y, tempz = z;
    for (int i = 0; i < min(tempy.size(), tempz.size()); i++)
    {
        swap(tempy[i], tempz[i]);
        if (op == '+')
        {
            if (stoi(tempx) + stoi(tempy) == stoi(tempz))
            {
                x = tempx, y = tempy, z = tempz;
                return true;
            }
        }
        else if (op == '*')
        {
            if (stoi(tempx) * stoi(tempy) == stoi(tempz))
            {
                x = tempx, y = tempy, z = tempz;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string x, y, z;
    char op;
    string word;
    int idx = 0;
    while (cin >> word)
    {
        if (idx == 0)
            x = word;
        else if (idx == 1)
            op = word[0];
        else if (idx == 2)
            y = word;
        else if (idx == 4)
            z = word;
        idx++;
    }
    // cout << x << " " << y << " " << z << endl;
    work(x, y, z, op);
    cout << x << " " << op << " " << y << " = " << z << "\n";
}