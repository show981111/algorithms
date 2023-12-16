class MovieRentingSystem
{
public:
    struct PriceShop
    {
        int price;
        int shop;

        bool operator<(const PriceShop &rhs) const
        {
            if (this->price < rhs.price)
                return true;
            else if (this->price == rhs.price)
                return this->shop < rhs.shop;
            return false;
        };
    };
    struct Info
    { // 0,1,3 < 0,4,3
        int shop;
        int movie;
        int price;

        bool operator<(const Info &rhs) const
        {
            if (this->price < rhs.price)
                return true;
            if (this->price == rhs.price && this->shop < rhs.shop)
                return true;
            if (this->price == rhs.price && this->shop == rhs.shop)
                return this->movie < rhs.movie;
            return false;
        };
    };

    // movie -> Set<Price & Shop>(5)
    unordered_map<int, set<PriceShop>> unrented;

    set<Info> rented;

    // shop -> movie -> price
    vector<unordered_map<int, int>> prices;

    MovieRentingSystem(int n, vector<vector<int>> &entries)
    {
        prices.resize(n);
        for (const auto &e : entries)
        {
            unrented[e[1]].insert({e[2], e[0]});
            prices[e[0]][e[1]] = e[2];
        }
    }

    vector<int> search(int movie)
    {
        // get cheapest 5 shops that have an unrented copy of a given movie
        vector<int> shops;
        if (unrented.count(movie) == 0)
            return shops;

        for (auto &item : unrented[movie])
        {
            shops.push_back(item.shop);
            if (shops.size() == 5)
                break;
        }
        return shops;
    }

    void rent(int shop, int movie)
    {
        unrented[movie].erase({prices[shop][movie], shop});
        rented.insert({shop, movie, prices[shop][movie]});
    }

    void drop(int shop, int movie)
    {
        rented.erase({shop, movie, prices[shop][movie]});
        unrented[movie].insert({prices[shop][movie], shop});
    }

    vector<vector<int>> report()
    {
        // return cheapest 5 rented movies as a 2D list, res[j] = [shopj, moviej] ascending
        vector<vector<int>> rep;
        for (auto &item : rented)
        {
            rep.push_back({item.shop, item.movie});
            if (rep.size() == 5)
                break;
        }

        return rep;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */