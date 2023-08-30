/**
 * @brief K th Largest -> No need to maintain all numbers, Only need "K" numbers!
 * SO we can just maintain K large numbers, everytime we add the values.
 * We can throw away other values that falls out of K numbers!
 *
 */

class KthLargest
{
public:
    // default max heap using less<int> (pq pop from the back)
    priority_queue<int, vector<int>, greater<int>> pqOfSizeK; // min heap
    int k;
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;
        for (int num : nums)
        {
            pqOfSizeK.push(num);
        }
        while (pqOfSizeK.size() > k)
        {
            pqOfSizeK.pop(); // pop small ones!
        }
    }
    int add(int val)
    {
        pqOfSizeK.push(val);
        if (pqOfSizeK.size() > k)
        {
            pqOfSizeK.pop();
        }
        // assert(pqOfSizeK.size() == k) we maintain the size to be == k.
        // if it is not, something is wrong
        return pqOfSizeK.top();
    }
};
