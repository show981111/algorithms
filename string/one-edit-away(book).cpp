/**
 * Cracking Coding Interview P.212
 * One Away: There are three types of edits that can be performed on strings:
 * insert a character, remove a character, or replace a character. Given two strings,
 *  write a function to check if they are one edit (or zero edits) away.
 *  EXAMPLE
 *  pale, ple -> true
 *  pales, pale -> true
 *  pale, bale -> true
 *  pale, bae -> false
 *
 * (A) First Approach: Using LCS. -> getting LCS O(M*N)
 * If to - LCS length <= 1 && from - LCS length <= 1 -> One edit away!
 * to - LCS == 0, from -LCS == 0, to == from
 * to - LCS == 0, from - LCS == 1, delete one char from "from"
 * to - LCS == 1, from - LCS == 1, replace one char from "from" to "to"
 * to - LCS == 1, from - LCS == 0, Insert one char to "from"
 *
 * Seems too complicated? We only need to know if it is one edit away..
 * feels like we can do this by purely comparing two strings!
 */

bool canInsert(string &from, string &to); // helper

bool isOneEditAway(string &a, string &b) // a -> b
{
    if (a.size() == b.size())
    { // can we replace?
        bool replaced = false;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i]) // if differs, replace!
            {
                if (replaced)
                    return false;
                replaced = true;
            }
        }
    }
    else if (a.size() - 1 == b.size())
    { // can we insert?
        return canInsert(a, b);
    }
    else if (a.size() + 1 == b.size())
    { // can we delete? == can we insert one to "b" and make a?
        return canInsert(b, a);
    }
}

bool canInsert(string &from, string &to)
{ // a -> b
    int index1 = 0, index2 = 0;
    while (index1 < from.size())
    {
        if (from[index1] != to[index2])
        { // differ? insert to[index2] to before from[index1], which equals to only proceed index2
            if (index1 != index2)
                return false;
            index2++; // since we inseted to[index2] to before from[index1], we should compare index1 and updated index2
        }
        index1++;
        index2++;
    }
}

// we can merge canInsert and replace... since replace is just using a one pointer,
// we can just use two pointers to compare from and to...