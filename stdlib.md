# C++ Stdlib

### reverse(s.begin(), s.end())

    => reverse from s.begin() to s.end();

### Iterator

    Iterator is just like a pointer. If the element that iterator refers to get erased,
    that Iterator is an invalid iterator. Need to re-initialize. 

### nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>())

    1,3) Linear in std::distance(first, last) on average.
    => getting Kth largest element(1-indexed)

### next_permutation(iterator, iterator) -> boolean (in-place)

    https://en.cppreference.com/w/cpp/algorithm/next_permutation
    True if next permutation is possible
    false if permutation reaches end and it went back to first permutation

### Unordered_map

- erase(key or iterator)

### list

- .erase(iterator), .remove(key): note that it erases all nodes with key

### Priority_queue / Heap

    Default max heap. It pop's from the back of the vector. So sorting in reverse order!
    - Min heap: priority_queue<int, vector<int>, greater<int>> pq;
    - Max heap: priority_queue<int, vector<int>, less<int>> pq;

### Custom comparator

    When define comparator with external data, be careful because 
    equality is defined as `!comp(a,b) && !comp(b,a)`, which means `!(a < b) && !(b < a)` => `a == b`

### map & set => Bidirectional Iterator (not random access iterator)

- **_Use map.lower_bound or set.lower_bound => O(logN)!!_**\
    Typical std::lower_bound will cause O(N) cuz it is Bidirectional Iterator!

### lower_bound(begin, end, val , [](const T& elem, const T& val){return elem < val;})

- **comp(elem, val) = false 인 첫번째 아이템** \
    -> *Previous elems are all comp(elem, val) = True = elem < val = Smaller than Val!*
- By default, ***(elem >= val 인 첫 아이템)***
- Thus returned elem will _**val <= elem!**_, which means returned elem can be bigger!

  - SHOULD BE AN INCREASING ORDER(use Rbegin for reverse order)

    ``` Cpp
    low = lower_bound (v.begin(), v.end(), 20,
        [](const int& elem, const int& val){
            return elem <= val; -> elem > val 인 첫번째 아이템
    });
    // This makes lower_bound like an upper_bound
    ```

    ``` Cpp
    v = [1, 2, 3, 4, 5, 6]
    lower_bound(v.begin(), v.end(), 4) -> returns 3rd index.
    // This tells us 0~2nd indices are all comp(elem,val) = elem < val = true!
    ```

upper_bound(begin, end, val , [](const T& val, const T& elem){return val < elem;})

- _**comp(val, elem) = true 인 첫번째 아이템**_  (elem > val 인 첫 아이템)\
    -> *Previous elems are all Comp(val, elem) = false = val >= elem = Smaller or equal to Val!*

    ``` Cpp
        auto it = upper_bound(mp[key].begin(), mp[key].end(), timestamp,
                                [](const int &val, const pair<int, string > &a){
                                    return val < a.first;
                                });
    ```

    Getting the last element such that a < b => use Upper bound, and decrement the index!!
- Upper_bound gets the first element such that val < elem
- lower_bound gets the first element such that val <= elem

### Split string

``` Cpp
    std::stringstream test("this_is_a_test_string");
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, '_'))
    {
    seglist.push_back(segment);
    }
```

    + >> operation only reads that bytes skipping whitespace.
    For example, 

``` Cpp
    istringstream in(" 3 + 4 / 5 * 4");
    int n;
    char op;
    while(in >> n){ // read first 3, then 4, 5 ,... 
        in >> op;  // read next operation ex 3 skipping white space
    }
```

    cin reads until it fills its size or until skipping whitespaces
