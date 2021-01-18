#ifndef TESTER_H
#define TESTER_H

#include "media_player.h"
#include <vector>

class Tester;

typedef int (Tester::* Function)();

class Tester
{
public:
    Tester(media_player* m_);

    void add_test(Function, QString name);

    int run_tests();

    int metadata_tests();

    int playlist_tests();

private:
    media_player* m;
    std::vector<std::pair<Function, QString>> test_functions;
};

#endif // TESTER_H
