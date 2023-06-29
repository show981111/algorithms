/**
 * @brief 대부분의 노가다 케이스는 DFS 로 가능하다...
 * 노가다 = 모든 경우의수 그래프 = DFS
 * 노가다를 뛰는데 **제약조건** 이 중요하다.
 * 제약조건 아래에 노가다 => Backtracking but with conditions inside to only create cases
 * that satisfies certaion condition!
 *
 * 이 경우, 제약조건, ) 는 무조건 ( 다음에 온다! 개수가 매칭되야한다!
 *
 * EX) generate 3 paran
 * '(' -> '()' -> '()('
 *     -> '((' => '(()' ...
 *             => '((('
 * Basically DFS!
 * Create children using FOR loop(iterate through!)
 */

class Solution
{
public:
    void genParan(int n, int left, int right, string &path, vector<string> &ans)
    {
        if (path.length() == 2 * n) // condition 1. total length should be 2*n matching paranthesis
        {
            ans.push_back(path);
            return;
        }

        if (left < n) // condition 2. we can place upto n open paranthesis!
        {
            left++;
            path.push_back('(');
            genParan(n, left, right, path, ans);
            left--;
            path.pop_back();
        }
        if (right < left) // condition 3. we can place close paranthesis only when we alr placed open pars.
        {
            right++;
            path.push_back(')');
            genParan(n, left, right, path, ans);
            right--;
            path.pop_back();
        }
    }

    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        string path = "";
        genParan(n, 0, 0, path, ans);
        return ans;
    }
};