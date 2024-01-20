class ExamRoom
{
public:
    /*
    -- Brute Force O(N^2)
    For each seat, get the closest occupied seat. then get the seat with the biggest gap -> O(N^2)

    -- Map per seat O(NlogN)
    Each Seat -> maintain closest occupied seat (ordered map). get closest one(O(1)), compute distance, Pick a seat with smallest distance(O(N)) => O(N). Then push the newly occupied seat to each seat number, O(NlogN).

    EX) 5 -> (6,1) (4,1) (7,2) (3,2)
    When leave : push that seat (O(N)) // push for each seat
    When sit : remove that seat (O(N*logN)) // remove for each seat

    --
    O(N) solution. Sweep -> and <- to get the distance from the nearest occupied seat.
    Then, do one more sweep to get the farthest seat
    --
    O(logN) solution. Think in the perspective of largest interval

    problem: When the seat is added/removed, how do we update distances for each available seats?

    What we want: place student at a seat that is farthest from the other.
    == For a longest non-overlapping interval, place it in the middle.
    ex) 0 4 9 is placed. we compare 0 -4 vs 4 -9 (not 0-9 since overlapping)
    Since 4-9 > 0-4, we place in the middle. (4+9)/2 = 6
    4 5 6 7 8 9
    After placed, we divide that interval. remove (4-9), push (4-6), (6-9) Order based on distance / 2

    How to deal with remove seats? O(logN)
    Interval should be merged. ex) (4-6) + (6-9) = (4-9) when 6 leaves.
    => if "p" leaves the seat,
    the interval that should be merges is, (prev number of p - p) + (p - next number of p)
    Since when we are pushing elements to set, we are splitting intervals, so those intervals
    should exists.
    */
    struct Interval
    {
        int first;
        int second;
        int n;
    };

    class Comp
    {
    public:
        static int getDistance(const Interval &i)
        {
            if (i.first == -1)
                return i.second; // Nothing before, dont divide!
            else if (i.second == i.n)
                return i.n - i.first - 1; // Nothing after dont divide!
            return (i.second - i.first) / 2;
        }
        const bool operator()(const Interval &a, const Interval &b) const
        {
            int distA = getDistance(a), distB = getDistance(b);
            if (distA > distB)
                return true;
            else if (distA == distB)
                return a.first < b.first; // prioritize lower seat number
            return false;
        };
    };
    set<Interval, Comp> intervalSet;
    set<int> seats;
    int N;
    ExamRoom(int n) : N(n)
    {
        intervalSet.insert({-1, N, N});
    }
    int seat()
    {
        Interval i = *intervalSet.begin(); // interval with largest Gap.
        intervalSet.erase(intervalSet.begin());
        int next;
        if (i.first == -1)
            next = 0;
        else if (i.second == N)
            next = N - 1;
        else
            next = (i.first + i.second) / 2;

        seats.insert(next);
        if (next - i.first > 1) // if it can contain any seat between
            intervalSet.insert({i.first, next, N});
        if (i.second - next > 1)
            intervalSet.insert({next, i.second, N});
        return next;
    }
    void leave(int p)
    {
        auto pos = seats.find(p);
        int l = -1, r = N; // initially, if there is no smaller or bigger elem exist,
                           // l and r can be each -1 or N based on our initialization setting
        if (pos != seats.begin())
        {
            l = *prev(pos, 1);
        }
        intervalSet.erase({l, p, N}); // erase interval that includes p
        if (pos != prev(seats.end(), 1))
        {
            r = *next(pos, 1);
        }
        intervalSet.erase({p, r, N}); // erase interval that includes r
        seats.erase(p);
        intervalSet.insert({l, r, N});
    }
};
