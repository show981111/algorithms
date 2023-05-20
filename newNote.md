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

-   Depth: from Root -> cur node's depth = parentDepth + 1

-   Height: from bottom(leaf) -> cur node's height = max(leftHeight, rightHeight) + 1

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

## LinkedList

-   Utilize Fast & Slow Pointer
-   Problem of Removing HEAD or TAIL -> **TEMPORARY(DUMMY)** head or tail!
-   Usually, knowing the **LENGTH** helps a lot!

## Stack & Queue

-   Implementation: Using array (top pointer for stack, front/back pointer for queue) or linkedList

## Ordered Contaienr

-   Priority Queue : YES dups, Insert/Delete -> O(logn) (For adjusting HEAP)
-   Ordered Set/map : NO dups, Insert/Delete -> O(logn) (Internally using balanced Tree)

## ETC

A.Floyd's cycle detection algorithm (Two pointers)

-   Fast pointers(move 2steps), Slow pointers(move 1step)
-   If it meets at the end, there is no cycle
-   If it doesn't meet at the end, then there is a cycle
-   After they meet, send one pointer to the starting point.
-   Proceed each pointer one step at a time. Then they will meet at the entrypoint of cycle!!
    (ref) https://www.youtube.com/watch?v=PvrxZaH_eZ4&ab_channel=Insidecode

````

```

```

```

```
````
