/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/*
All nodes who got 0 coin should get a coin from children or parent.
How do we get the min distance?
    3
 0    1
0 1

Optimal: 2
1 +3 = 4.
Is grabbing the nearest coin is optimal? NO! There is a case where if there is a tie,
grabbing one from random one can result in the other node to travel further.

Change the perspective to DISTRIBUTE. In order to choose shortest path, can we do BFS?
Still the problem of tie-braking exists.
Should we do back tracking?

Pivot the idea of sending a coin from a node to the other node.
Think, how many coins we should MOVE from a SUBTREE to other SUBTREE.
Like the opposite of inheritance.
If we fill 1's from the bottom by borrowing coins, and passing surplus to parents,
then that would be the shortest distance.
*/
class Solution
{
public:
    // what should we return? coins that node needs(-)/offloading(+) to parent
    // add distance everytime the returned value is non-zero. -> coin that should be moved.
    //      All coins should go through parents to be passed to further nodes other than children!
    // Each node needs, left's req + right's req + 1 amount of coins.
    // add the number of coins that are moved from parents to child. or vice versa
    // So the absolute value of returned value is the coins that should be moved.
    int solve(TreeNode *cur, int &totalDist)
    {
        if (cur == nullptr)
            return 0;

        int lReq = solve(cur->left, totalDist);
        int rReq = solve(cur->right, totalDist);
        totalDist += abs(lReq) + abs(rReq);
        return cur->val + lReq + rReq - 1;
    }
    int distributeCoins(TreeNode *root)
    {
        int d = 0;
        solve(root, d);
        return d;
    }
};
