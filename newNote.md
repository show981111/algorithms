# ALGORITHM

## Invariant = "IFF" condition

-   What must be true for this problem?
-   If we find the correct invariant, we can **Assume** that is true.
    Or we can just trying to fit to that invariant (using IFF condition, instead of iterating all of them, just check if it suffices that IFF condition)

EX) 160.
After Intersection, all nodes are the same! -> Length of the list is at least [Intersection ~ End] -> Intersection cannot occur from the preceding nodes of longer list.
-> we can just skip those nodes!

## Counting problems

-   Utilize Hashmap!
-   Divisible? -> MOD! -> only need to think about numbers under MOD!

## Tree

-   Depth: from Root -> `cur node's depth = parentDepth + 1`

-   Height: from bottom(leaf) -> `cur node's height = max(leftHeight, rightHeight) + 1`

### Tree Traversal

-   Pre-order(unqiue for tree)
-   Post-order(unqiue for tree)
-   In-order(not unique)

### BST

-   **_ALL NODES_** in left subtree <= cur->val < **_ALL NODES_** in right subtree!
    This inequality is true for **_ALL NODES_**
    Thus, cur node should be the max for left subtree, min for right subtree for **_ALL NODES_**
-   Specifically, Left Subtree **_RIGHTMOST_** val < cur value < Right Subtree **_LEFTMOST_** val
-   In order traversal gives us an ordered list!

### MIN/MAX Heap

## Graph Traversal

### BFS

WHERE SHOULD WE CHECK VISITED?
FOR BFS it does matter because nodes at same level could push the same node twice!
ex) A, B is in same level, C is neighbor of both A,B. then C is inserted twice.

-   PATTERN A) make it visited when we add nodes to the queue
    REMEMBER : for starting point, we cannot make it visited cause it is already in the queue
    Thus, **_we should make starting point visited before!!_**

    ```
        BFS(){
            visited[src] = true; // set starting node to TRUE
            while(!q.empty()){
                q.pop();
                for(neighbor : neighbors[src]){
                    if(!visited[neighbor] /* and other constraints*/){
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    ```

-   PATTERN B) just push it, and check it when we pop it

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

-   Distinguishing Each Level

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

-   Finding the **_Distance_** between node A and B.
    If we use traditional BFS from A, it will be O(K^d) (Suppose each node has K neighbors and A~B is d)
    If we use bidirectional, then start from A and B at the same time -> early collision. -> O(K^(d/2))
    HUGE DIFFERENCE!

## LinkedList

-   Utilize Fast & Slow Pointer
-   Problem of Removing HEAD or TAIL -> **TEMPORARY(DUMMY)** head or tail!
-   Usually, knowing the **LENGTH** helps a lot!

## Stack & Queue

-   Implementation: Using array (top pointer for stack, front/back pointer for queue) or linkedList

## Ordered Contaienr

-   Priority Queue : YES dups, Insert/Delete -> O(logn) (For adjusting HEAP)
-   Ordered Set/map : NO dups, Insert/Delete -> O(logn) (Internally using balanced Tree)

## Topological Sort

When should we use this? : When we want to find the **_ORDERING_**, usually when we have the restriction in how to deploy some items, and want to know the **_Sequence under that restriction_**!
ex) Graph > 210

-   DFS
    Naturally topSort because we visit nodes sequentially. We need to push those nodes to stack after we visited all neighbors (push nodes after it reaches the end and come back). To detect cycle, we need to check if we visit the nodes on the path(trace) again => use Trace array or different mark for visited arr
-   BFS
    Using an Indegree. Put nodes with 0 indegrees to the queue, delete them and update indegree, and repeat!

## ETC

A.Floyd's cycle detection algorithm (Two pointers)

-   Fast pointers(move 2steps), Slow pointers(move 1step)
-   If it meets at the end, there is no cycle
-   If it doesn't meet at the end, then there is a cycle
-   After they meet, send one pointer to the starting point.
-   Proceed each pointer one step at a time. Then they will meet at the entrypoint of cycle!!
    (ref) https://www.youtube.com/watch?v=PvrxZaH_eZ4&ab_channel=Insidecode
