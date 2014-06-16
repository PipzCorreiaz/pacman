#ifndef __STATS_H__
#define __STATS_H__

class Stats {

public:
    ~Stats();

    static Stats& getInstance() {
        static Stats instance;
        return instance;
    }

    void setBalls(int value);
    void incGhosts();
    void incZombies();
    void dump();

private:

    Stats() {};
    Stats(Stats const&);
    void operator= (Stats const&);

    int _balls;
    int _ghosts;
    int _zombies;

};

#endif