# ALGORITHM

## Invariant = "IFF" condition

- What must be true for this problem?
- If we find the correct invariant, we can **Assume** that is true.
    Or we can just trying to fit to that invariant (using IFF condition, instead of iterating all of them, just check if it suffices that IFF condition)

EX) 160.
After Intersection, all nodes are the same! -> Length of the list is at least [Intersection ~ End] -> Intersection cannot occur from the preceding nodes of longer list.
-> we can just skip those nodes!

## Counting problems

- Utilize Hashmap!
- Divisible? -> MOD! -> only need to think about numbers under MOD!

## Tree == Undirected, Connected, Acyclic Graph

- Depth: from Root -> `cur node's depth = parentDepth + 1`

- Height: from bottom(leaf) -> `cur node's height = max(leftHeight, rightHeight) + 1`

- **_Longest Path in Tree = Diameter_**

### Tree + DP

- Bottom up fashion, Calculate something for children, use that information to get what we want for current node
- Typical pattern is, (Tree diameter, Graph > abridge_opt, Tree > cses_max_matching)

    ```Cpp
    void dfs(int cur, int parent) {
        Recording something for cur; // usually something we calculate while going down the tree

        // For leaf node, deal with base case.
        
        for (auto child : adj[cur]) {
           if (child == parent) continue;
           int res = dfs(child, cur); // Perform calculation for children
           // Do something with the result. Here, res. 
        } 

        // Merge the result. 
    }
    ```

- While walk down the tree, calculate something, and after returning from children,
get what we want from children and merge the result

### Tree Traversal

- Pre-order(unqiue for tree)
- Post-order(unqiue for tree)
- In-order(not unique)

### BST

- **_ALL NODES_** in left subtree <= cur->val < **_ALL NODES_** in right subtree!
    This inequality is true for **_ALL NODES_**
    Thus, cur node should be the max for left subtree, min for right subtree for **_ALL NODES_**
- Specifically, Left Subtree **_RIGHTMOST_** val < cur value < Right Subtree **_LEFTMOST_** val
- In order traversal gives us an ordered list!

### MIN/MAX Heap

## Graph Traversal

### DFS (Recursion)

**ONE INVARIANT IN DFS: Traverse all paths from starting point + its children**\
If we call dfs from (r,c) it traverse all paths from (r,c) and its children\
Thus, if we computed something from (r,c) than it should be optimal for (r,c) and its children.\
=>**No need to do dfs again for children of (r,c)**: Important for memoization

### BFS

WHERE SHOULD WE CHECK VISITED?
FOR BFS it does matter because nodes at same level could push the same node twice!

Thus, **_mark visited when you push to the queue_** to prevent inserting the
same node twice and do the logic twice!
ex) A, B is in same level, C is neighbor of both A,B. then C is inserted twice.

- PATTERN A) make it visited when we add nodes to the queue
    REMEMBER : for starting point, we cannot make it visited cause it is already in the queue
    Thus, **_we should make starting point visited before!!_**

    ```
        BFS(){
            visited[src] = true; // set starting node to TRUE
            while(!q.empty()){
                q.pop();
                for(neighbor : neighbors[src]){
                    if(!visited[neighbor] /* and other constraints*/){
                        visited[neighbor] = true; --> IMPORTANT!
                        q.push(neighbor);
                    }
                }
            }
        }
    ```

- PATTERN B) just push it, and check it when we pop it

    ```
    BFS(){
        while(!q.empty()){
            cur = q.front();
            q.pop()
            if(visited[cur] /_ or other constraints_/)
            continue;
            visited[cur] = true;

            for(neighbor : neighbors[src]){
                q.push(neighbor);
            }
        }
    }
    ```

In general, pattern B takes more time and memory because it allows redundant push to queue

- Distinguishing Each Level

    Since BFS pops all nodes from the same level, and push all nodes in the next level,
    we can adjust this to divide the step.

    ```
        BFS(){
            int level = 0;
            q.push(start);
            visited[start] = true;
            while(!q.empty()){
                levelSize = q.size();

                // all nodes being popped at this for-loop has the same level

                for(int i = 0; i < levelSize; i++){
                    cur = q.front();
                    q.pop()
                    // pushing nodes in the next level
                    for(neighbor: graph[cur]){
                        if(!visited[neighbor]){
                            visited[neighbor] = true;
                            q.push(neighbor)
                        }
                    }
                }
                // after popping all nodes, level changes
                level++;
            }
        }
    ```

### Bidirectional Search

- Finding the **_Distance_** between node A and B.
    If we use traditional BFS from A, it will be O(K^d) (Suppose each node has K neighbors and A~B is d)
    If we use bidirectional, then start from A and B at the same time -> early collision. -> O(K^(d/2))
    HUGE DIFFERENCE!

### Finding Cycle

- find a node whose neighbor (other than the previous node in the current path) has already been visited.

#### Directed Graph

- DFS: (3 coloring: unvisited/visited/in current stack) Visited array + current_path array. current_path[i] = node i is in current stack.
        If we visited a node that is already in the path(stack), that means we have a cycle.
        We still can use visited array to skip visited node because as soon as we step into any nodes in the cycle,
        We will get a cycle. If we confirmed that we visited that node, but no cycle was detected, we can just skip exploring that node.
        <https://cp-algorithms.com/graph/finding-cycle.html>
- Bellman Ford: If N_th iteration still reduces the distance -> There is an edge.
        Key point: Bellman ford tells us there is a node that is **"Reachable"** by negative cycle
        -> So we need a **parent array** and backTrack at most N times to get the actual element of cycle.
        From that point, we can just backTrack to get all elements of the cycle (Since it is a cycle, parent array will keep circling)
        EX) CSES > Finding_cycle

#### Undirected graph

- Check if #edges == #vertex - 1

## LinkedList

- Utilize Fast & Slow Pointer
- Problem of Removing HEAD or TAIL -> **TEMPORARY(DUMMY)** head or tail!
- Usually, knowing the **LENGTH** helps a lot!
- Most problems: finding mid, reverse order(stack or in-place), weaving!

## Stack & Queue

- Implementation: Using array (top pointer for stack, front/back pointer for queue) or linkedList

## Ordered Contaienr

- Priority Queue : YES dups, Insert/Delete -> O(logn) (For adjusting HEAP)

    **_When to use?_**
  - When there are two standards to consider when sorting (Optimizing based on two variables).
    Key intuition is, if we have two variables, we need to **FIX ONE**. Thus, we need to find a condition,
    such that if we fix this one, can we use the result in next iteration (fix next element)?
    EX) get min from X **such that** Y <= K. Or get min from range [0:i]
    We can sort base array and as we traverse, we add/remove elems to priority queue. Then, we can get the min/max within that range!

    ```Cpp
    // From array X and Y, want to compute max of : (Y[y1] + ... + Y[yk]) * min(X[y1], ..., X[yk])
    // Here, max answer depends on two components : (Y[y1] + ... + Y[yk]) & min(X[y1], ..., X[yk])
    // We can increase either size to make the result big.
    /*
    1. One array is the base array that works as a BASE. (Fix BASE(one component), and maximize rest)
        Key point of sorted condition array: items in [:i] should be available when i+1_th item is the base.
            => This allows pushing elems to PQ as we go without violating constraints.
    2. Perform Sliding Window on PQ to maintain the size of the window! => Key to O(NK) -> O(NlogN)
    */
    vector<int> X; vector<int> Y; vector<pair<int,int>> paired
    sort(paired, X_ASCENDING) // sort in X descending 
    priority_queue<int> pq; // PQ for Y elems 
    For paired[i].X in paired: // X descending order. Thus, if we have paired[i].X ~ paired[i+j].X, paired[i+1].X should be the base since we take min min(X[y1], ..., X[yk]).
        Set X[i] as a base. 
        pq.push(paired[i].Y); 
        // contains top K elements from 0 ~ i. At i+1_th iteration, these Y's are available since 
        // corresponding X value of these Y are all bigger than i+1_th X. (paired[0 ~ i].X < paired[i+1].X)
        Computer answer = runningSum * base
    
    ```

- Ordered Set/map : NO dups, Insert/Delete -> O(logn) (Internally using balanced Tree)

## Dynamic Programming (Memoization)

- Overlapping subproblems -> caching those results!
- Come up with Recursive formula! ex) T(n) = T(n-1) + T(n-2)
- Suppose we have the answer for T(n), what should we do to get T(n+1)? **_Induction_**
- Important Note: When summing up the previous cases.. think if it is overlapped(redundant)
    It is crucial to come up with non-overlapping, unique scenarios and sum them up!
    ex) when u count T(n) = T(n-1) + T(n-2), if T(n-1) includes T(n-2) cases, then redundant count happen!
- **_Optimization_**, like getting a minimum of maximum => It might be DP!!

### KnapSack Pattern (1/0 problem)

- How do I know if it is knapsack?

  - Use it or not use it -> Combination of given item to make target == **_SUBSET PROBLEM_** or **_COMBINATION_**
  - When we have a target amount, and we have an item to reach that target.
  - Sometimes we have constraints too(ex maximum weights)
  - Want to make a **_target value_** with the **_Subset_**

- Typical pattern is,

  - x-axis is the amount we want to make 0 ~ K
  - y-axis is the index of items we want to use, ex) we want to use 0 ~ i_th item
  - Then, #ways = when using current item + when only using ~i-1 items

- Do we have infinite amount per each item? or only one?

  - IF we have only one per each item, if we use current item, we should only use 0 ~ i-1_th item
    - So, T(N, i) = T(N - value[i], i-1) + T(N, i-1) = using current + only using 0 ~ i-1_th
  - IF we have infinite per each item, even though we used current item, we can still use current item(0 ~ i_th item).
    - So, T(N, i) = T(N - value[i], i) + T(N, i-1)

### Subset vs Subsequence

- Subset: 0/1, don't care about the index ordering. EX) [5,3,1,4,8], can choose {8,5,4} == {4,5,8}
- Subsequence: also 0/1, but should ensure the index ordering [3,4,8], [5,4,8], but cant mix them up
- Subsequence -> Subset?: when we can re-arrange the picked subset based on index ordering. EX) after we picked {8,5,4} we re-arrange them ti [5,4,8]

### LIS Pattern (Subsequence == Subset with ordering)

- Also subset problem, but with ordering
- Cannot convert to subset problem since after we pick the subset, we cannot re-arrange based on index.\
EX) [5,3,1,4,8] => {4,5,8} -> [5,4,8] (based on index) breaks the LIS restriction
- **Does T(i)'s optimal solution should be included in T(i+k)'s optimal solution?** \
    EX) check 1239 thought process
- Important restriction is the **ordering**
- Subesequence here, we cannot re-order items as we want after we pick, since we can only reorder them in an increasing order & increasing index order
- **BE CAREFUL OF TIE**. IF there are multiple subsequence that makes max T(i). Can I pick anything? or does it affect the answer?

- ## Typical pattern is, get the desired value when we **include i_th element**

  - So, we get T_i(N) = max(T_i(0:N-1)) where T_i(N) is the maximum lenght of subsequence that ends with i and **includes i**
- Now, from that array, we choose max!
- The reason behind this is, we cannot get all possible cases for subsequence(subset), so we calculate the case where we assume that we include i_th element. Then, we iterate all options to get N+1_th

### LCS Pattern

- we have two strings.. so probably 2D array?
- T(i,j) is the longest common subsequence of a[:i] and b[:j]

## DP & BackTracking

- DP and backtracking is all about **_"노가다를 어떻게 뛰냐?"_**
- Building a **_경우의수 Tree_** helps a lot. -> Each level could be an index we pass to back tracking ex) curIndex
- **_How_** to divide big problem with smaller problem?
  - Think about how to divide the cases.
        ex) Knapsack - With I_th item / Without I_th item
        LIS - sequence that ends with 0th, 1st, 2nd ... Nth item.
        Permutation - starting with a_1, a_2, ... , a_n
        coinChange - make 100 with 0,1,2,3,4 quarters...
  - this cases will be looped inside of **_For loop_** in Backtrack.
  - and jumping the level will be dealt with **_curIndex_**

## Divide & Conquer

- Non-overlapping subproblems!
- 1. Divide
  2. recursive call to each divided data
  3. Merge them

## Topological Sort

When should we use this? : When we want to find the **_ORDERING_**, usually when we have the restriction in how to deploy some items, and want to know the **_Sequence under that restriction_**!
ex) Graph > 210

- DFS
    Naturally topSort because we visit nodes sequentially. We need to push those nodes to stack after we visited all neighbors (push nodes after it reaches the end and come back). To detect cycle, we need to check if we visit the nodes on the path(trace) again => use Trace array or different mark for visited arr
- BFS
    Using an Indegree. Put nodes with 0 indegrees to the queue, delete them and update indegree, and repeat!

## Backtracking

- 대부분의 노가다 케이스는 DFS 로 가능하다...
    노가다 = 모든 경우의수 그래프 = DFS
    노가다를 뛰는데 **제약조건** 이 중요하다.
    제약조건 아래에 노가다 => Backtracking but with conditions inside to only create cases
    that satisfies certaion condition!

- backtrack/22.genParan 의 경우, 제약조건, ) 는 무조건 ( 다음에 온다! 개수가 매칭되야한다!
    EX) generate 3 paran
    '(' -> '()' -> '()('
    ....-> '((' => '(()' ...
    ............=> '((('
    Basically DFS!
    **Create children using FOR loop** (iterate through!)
    At the end, if we reach the leaf node condition, insert them to result!

- Branch & Bound
    경우의 수 트리에서, 어떻게 하면 Branch 를 줄일 수 있을까?
    Find **invariant!!** => if we violate that invariant, that branch is not promising!
    So, finding the condition that we can for sure eliminate that cases is important!
    ex) backTracking/51
    For N-queens, we know that for each row, there must be one queen => one queen per row.
    Thus, we dont have to iterate 2 for loop for row & col, we can just iterate one loop for col.

- Permutation(Order matters) vs Combination(Order doesnt matter)
    For permutation, we can choose anything from the first item.
    For combination, we cannot choose from the first item because it will cause duplicate count.
    ex) [1,3,2] == [2,3,1]. So we have to choose from prevIndex + 1, to avoid duplicate

## Sliding Window + Two Pointers (subarray, substring)

- Usually, start && end pointer. Proceed end once at a time, and shrink the window by
    pushing start as far as we can. Then, proceed end, repeat. (catapillar method)
- **_3 Things in mind_**
    1. Condition to keep the window size ex) subArray sum < X
    2. When should we shrink and when should we stop? (break while) ex) subArray sum >= X
    3. How to get what we want **from start,end indices.** ex) result += start, += end - start + 1, += start
        => Playing with Indices to get the COUNT
    4. If I use catapillar method, once I push right and shrink left, do I need to move left back
       when I start a new phase with current right?
- For counting, key is, how can we count something **without Dup and without iterating again**
  - Without Dup: How many of them when it ends at "end"? -> each case becomes unique that ends at "end" idx. ex) [1,2,3,4], arr that ends at 2 vs 3 vs 4 all unique, no redundant

  - Am I counting all? : Important thing is, after I move forward "start" for current "end", and I move "end" forward, is it okay to start "start" from the previous start? Would it impact counting of next End? => This is why we need a little heck to avoid re-iterating
  
  - Without Iterating - Need some heck.
        EX) end - start + 1 (length == #subarray that contains item at "end")
        ex)[... {1,2,3} ...] -> {3}, {3,2}, {3,2,1}
        or += start(after shrink) [1,2,3, ... N ...] -> {1 ~ N}, {2 ~ N}, {3 ~ N}
  - **_Exatcly K = At most K - At most K-1_**
  - Translating Problems to **_At Most K or Exactly K_** simplifies the problem!
- Pattern

```Cpp
while(end < N){
    // Increasing end by 1 at a time makes it easier to compute the count for each ending index!
    do something; end++; (usually increase count or something)
    // For this end,

    // SHRINK WINDOW - push start as far as we can
    while(condition met && start < end){
        do something; start++
    }

    get result for this "end"
    ex) get length == count subarray that contains "end" == end - start + 1
}
```

## BIT MANIPULATION

### XOR

- XOR rules
    X ^ X = 0; X ^ 0 = X
    Commutative / Associative
    A ^ B = B ^ A
    A ^ (B ^ C) = (A ^ B) ^ C

    Using this,
    if we have [1,4,3,2,0], missing number is 5.
    So, (1^4^3^2^0)^(0^1^2^3^4^5) = (0^0)^(1^1)^(2^2)^(3^3)^(4^4)^(5) = 0^0^0^0^0^5 = 5

## Monotonic Queue (Using Deque)

- Monotonic Queue
    -> (O(nlogn) -> O(n) just throw away bigger ones as we iterate!)
    Use it when we know that we can throw smaller values as we proceed!
    How to make it ?

## Greedy -> Another Optimization Problem

- Key of greedy. Prove if it is **optimal**!
**_Making a best choice for myself -> leads to the optimal decision for everyeone!_**

- Typical pattern.
    1) Greedy stays Ahead : at i_th choice, greedy is better than any other choices!
    2) Exchange : Suppose there is an optimal solution O which is different from Greedy solution, we can
                tweak O to get a better solution!

- Greedy cannot backTrack -> Each Choise should be optimal!
    Suppose there is an optimal solution O that is different from S (Greedy solution).
    Then, we can tweak O and create O' that is better than O' !
    Proof pattern is, Let O = {O_1, O_2 , ... , O_n} where O_i represents i_th choice.
    and if we replace O_i with S_i, then we can get better solution!

## ETC

A.Floyd's cycle detection algorithm (Two pointers)

- Fast pointers(move 2steps), Slow pointers(move 1step)
- If it meets at the end, there is no cycle
- If it doesn't meet at the end, then there is a cycle
- After they meet, send one pointer to the starting point.
- Proceed each pointer one step at a time. Then they will meet at the entrypoint of cycle!!
    (ref) <https://www.youtube.com/watch?v=PvrxZaH_eZ4&ab_channel=Insidecode>

### Bellman Ford: Shortest/Longest path for WEIGHTED DAG

Bellman ford is a DP algorithm where
`T(target, i) = The shortest path from the source to target using i number of edges`
Unless there is a **negative** weight cycle (positive cycle doesn't matter), we can find the shortest path. If there is a negative cycle, the shortest path can be -INF anyways.
Similarly, we can find the longest path unless there is a positive cycle.

For edge = (x,target)
T(target, i) = min(T(x,i-1) + weight) => Shortest distance to x using i-1 edges + current edge's weight which can take us to "target."
ex) Graph > Bellman Ford > CSES.

```Python
For cnt in Total number of edgs:
    For edge in Edges:
        T(edge.to, cnt) = min(T(edge.to, cnt), T(edge.from, cnt -1) + edge.weight)
                                                # Using current edge to update the distance
```

**NOTE: For unweighted, just use DFS/BFS will give us O(V+E) runtime.** \
DFS with memoization (memo T(v) = longest path from v) or BFS can be used for shortest path

### SPFA (BFS version of Bellmand Ford)

```Cpp
  While(!q.empty())
    node v = q.front(); q.pop();
    for(neighbor : graph[v]) // find v's neighbor
        NewDist = dp[v] + v->neighbor weight // going throguh v to get to neighbor
        if(NewDist < dp[neighbor])
            dp[neighbor] = NewDist;
            If neighbor not in q: // If neighbor is already in Queue, u can just update the distances when you pop that node.
                                // Since we are grabbing the distance information from dp so it doesn't matter
                q.push({neighbor});
```

## How to make O(N) searching to O(logN)?

1. Divid By Two : Binary Search or Divide & Conquer -> Can't use this case. Can't do random access.
2. Power Of Two : Make a quick access pointer(shortcut) at each power of two points
     ex) Binary Lifting(Record shortcut pointer to every 2^k), Segment Tree, Sparse Tables

## Monotonic Stack/Deque

    In the stream,
        (1) If we get bigger value, all previous smaller values are useless (Decresing stack)
        (2) If we get a smaller value, all previous bigger values are uesless (Increasing stack)
    EX) Citadel-tagged/42,85,221,239

## How to design a recursive function?

1. Need to pass the value from child -> parent? : use return value
2. Need to pass the value from parent -> child? : use parameter/ pass by reference

## Get the biggest difference among all pairs

ex) Maximum sum subarray with some restrictions (restricted length)
<https://leetcode.com/problems/maximum-sum-circular-subarray/solutions/4538281/prefix-monotonic-deque-approach-o-n/>

Use **monotonic stack/deque/queue!** and only stores values that is promising.
As we proceed, throw away that is not promising.
In above case, use increasing deque. Use front of the deque to get the smallest prefix.
When push, pop all elements that are bigger than current prefix because when we try to get
bigger subarray sum, we only need small prefix so we don't need big ones!

## Subsequence/subset questions

- Subsequence -> subset possible? : If we can rearrange the subset we chose based on the index, then we can do this. EX) [1,4,3,2,5] -> {5,4,3} (subset we chose) -> re-arrange {3,4,5} based on index. is it possible? For LIS, its not possible since it should be re-arranged to [3,4,5] but index of 4 < index of 3.
- Try DP: **LIS/LCS** pattern if sequence should be ordered
            or **knapsack(0/1)** if there is a restriction and it is not ordered(subset).
- Try sort/heap: if order doesn't matter, we can sort them
- Try BackTrack: no other options... try all possible subsets/subsequences

## Binary search

When we can for sure throw away the half without going through, we can use binary search.
Need to decide

- How do we know we can for sure throw away the half?
- Which half should we go searching?

However, Binary search is not just slicing an array. It can be a **GUESS** method. For example,
guess the number I am thinking between 1 and 20. Use bin search to guess the number!
