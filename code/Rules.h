#ifndef _RULES_H_
#define _RULES_H_

#include <vector>

struct Rules
{
public:
    const std::vector<int> NUMBER_OF_LIVE_NEIGHBOURS_FOR_LIVE_TO_SURVIVE {2, 3};
    const std::vector<int> NUMBER_OF_LIVE_NEIGHBOURS_FOR_DEAD_TO_LIVE {3};
};

#endif