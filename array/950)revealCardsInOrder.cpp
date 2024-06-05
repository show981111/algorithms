class Solution
{
public:
    /*
    Return an ordering of the deck that would reveal the cards in increasing order.
    We pop one, and send the top to the bottom.

    Can we do the reverse? since we know the end result (increasing order),
    we go back from this deterministic result.
    2 3 5 7 11 13 17

    2 _ 3 _ 5 _ 7
    _ _ _ _ _ _ _ _
    1 5 2 7 3 6 4 8
    _ _ _ _ _ _ _
    1.6 2.5 3.7 4

    1. let's first decide, the ordering of revealing.
        In which order, each card in the index will be revealed?
    2. Then, we can just assign numbers based on that reveal ordering!
    Be simple and don't try to over-optimize! If it's anyways O(N), go to easy to understand code.
    */
    vector<int> deckRevealedIncreasing(vector<int> &deck)
    {
        sort(deck.begin(), deck.end());
        int N = deck.size();
        vector<int> ordering(N, -1);
        int revealOrder = 0;
        int idx = 0;
        bool skipped = true;
        for (int i = 0; i < N; i = (i + 1) % N)
        {
            if (revealOrder == N)
                break;
            if (skipped && ordering[i] == -1)
            {
                ordering[i] = deck[revealOrder++];
                skipped = false;
            }
            else if (!skipped && ordering[i] == -1)
            {
                skipped = true;
            }
        }

        return ordering;
    }
};