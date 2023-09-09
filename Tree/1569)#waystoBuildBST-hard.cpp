/**
 * @brief How to build the same BST?
 *
 * As long as we set the root, it doesn't matter which one we insert.
 * Sequence should be, ROOT -> LEFT -> RIGHT or ROOT -> RIGHT -> LEFT (parent -> children)
 * ex) [2, 1, 3], [2, 3, 1]
 *      2
 *   1     3
 *
 * Thought Flow
 * 1) under this sequence restriction, we will build the same tree (parent -> children)
 *      Building a tree(graph).. ordering under the restriction -> TOP SORT? -> but,, we only need
 *      # ways, not the exact ordering.. Also, how do we know the parent - child relationship?
 *
 * FINDING PARENT AND CHILD RELATIONSHIP
 *      First one becomes root, after smaller one becomes left child, bigger one becomes right child
 *      -> Recursively, decide Root, left subtree, right subtree, and go to those subtree!
 *
 *
 * 2) If we know root, and have left and right subtree elems
 *      Weave left and right elems
 * ex) [3,4,5,1,2]
 * 3 is root, [1,2] left, [4,5] right
 * WEAVE -> [1,2,4,5], [1,4,2,5], [1,4,5,2], [1,4,2,5], [4,5,1,2], [4,1,5,2]
 * => 4!/(2!*2!) = 4C2
 * ok, as long as we have root/left elems/ right elems, we can get #ways!
 *
 * Divide & Conquer
 * 1) divide -> left subtree, right subtree based on root(first elem of array)ee
 * 2) Run recursive -> Run recursive on left and right subtree
 * 3) Merge -> we have # ways to build left tree and right tree... how can we know #ways to build whole tree?
 *     Possible permutations(suppose left and right is fixed) * #ways to build left tree * #ways to buld right tree
 */

class Solution
{
public:
    vector<vector<long long>> pascal;

    int numOfWays(vector<int> &nums)
    {
        long long mod = 1e9 + 7;
        pascal.resize(nums.size() + 1);
        pascal[0].resize(1, 1); // pscal[0][0] = 1;

        // pascal triangle for combination
        for (int i = 1; i < pascal.size(); i++)
        {
            pascal[i] = vector<long long>(i + 1, 1);
            for (int j = 1; j <= i / 2; j++)
            { // nC0 = 1, nCn = 1
                pascal[i][j] = (pascal[i - 1][j - 1] + pascal[i - 1][j]) % mod;
                pascal[i][i - j] = pascal[i][j];
                // cout << i << "-" << j <<" = " <<pascal[i][j] << endl;
            }
        }

        return weaving(nums, mod) - 1;
    }

    long long weaving(vector<int> &nums, long long mod)
    {
        if (nums.size() <= 2) // one for root, no way to permut
            return 1;
        vector<int> left;
        vector<int> right;
        int root = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long l = weaving(left, mod) % mod;
        long long r = weaving(right, mod) % mod;
        // [LEFT], [RIGHT] -> [ROOT, {L, R weaved}]

        return ((pascal[nums.size() - 1][left.size()] * l) % mod * r) % mod;
    }
};