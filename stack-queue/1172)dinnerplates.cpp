/**
 * @brief STACK + SET
 *
 * Ordered Container: Priority_queue OR ordered set OR ordered MAP
 *  I DO NOT WANT DUPS! -> USER ordered Set or Map => use iterator to access sequentially!
 *  DONT MIND DUPS or Should contain dups -> PQ
 *
 * BOTH container's INSERT, REMOVE takes O(logn)
 *
 * Problem:
 *  Due to Pop At Stack, left most Available index keeps changing!
 *  -> need an ordered container for leftMostIndex
 *
 * THought Flow:
 *   Need an increasing sequence for LEFT MOST INDEX...
 *   if i use pq, then it can contain duplicates...
 *   I don't want dups --> no dups, ordered container => SET or MAP
 *
 */

class DinnerPlates
{
public:
    vector<long long> st;
    vector<int> tops; // top index of currently being used indices
    set<int> availables;
    int c;
    DinnerPlates(int capacity)
    {
        c = capacity;
    }

    void push(int val)
    {
        if (!availables.empty())
        {
            int leftMost = *availables.begin();
            int index = leftMost * c + tops[leftMost];
            // cout << "INDEX " << index << " = " << val << endl;
            if (index >= st.size())
            {
                st.push_back(val);
            }
            else
                st[index] = val;
            tops[leftMost]++;
            // cout << "Tops[" << leftMost <<"] = " <<  tops[leftMost] << endl;
            if (tops[leftMost] >= c)
            {
                availables.erase(leftMost);
            }
        }
        else
        {
            int newIndex = tops.size();
            // cout << "::INDEX " << newIndex << " = " << val << endl;
            availables.insert(newIndex);
            tops.push_back(1);
            st.push_back(val);

            if (tops[newIndex] >= c)
            {
                availables.erase(newIndex);
            }
        }
    }

    int pop()
    {
        for (int i = tops.size() - 1; i >= 0; i--)
        {
            if (tops[i] > 0)
            {
                return popAtStack(i);
            }
            else
            {
                tops.pop_back();
                availables.erase(i);
                // if this index is empty, we can just remove and reuse it later
                // do not need to keep it!
            }
        }
        return -1;
    }

    int popAtStack(int index)
    {
        // cout << "TOPS.size() " << tops.size() << endl;
        if (index >= tops.size() || index < 0 || tops[index] <= 0)
        {
            return -1;
        }
        int val = st[index * c + tops[index] - 1];
        tops[index]--;
        availables.insert(index);
        return val;
    }
};
