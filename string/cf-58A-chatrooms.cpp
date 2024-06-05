#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Can we delete couple letters from X to make it "hello"?
 * Finding a sub sequence!
 * Dont think complicated. Just iterate the string, and mark a character as appeard if so.
 * Since it has to be ordered and we are looking for a subsequence (not substring which should be contiguous) we are good
 *
 */
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string input;
    cin >> input;

    const string hello = "hello";
    int ind = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == hello[ind])
        {
            ind++;
            if (ind == hello.size())
            {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}
