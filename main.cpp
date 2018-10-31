#include <iostream>


#include "game.hpp"


using namespace game;


std::vector<element> init_data(){
    std::vector<element> ret;

    element e1[] = {
            {{0, 0}, 3}, {{2, 0}, 2}, {{3, 0}, 7}, {{8, 0}, 9},
            {{2, 1}, 8}, {{7, 1}, 4}, {{8, 1}, 5},
            {{2, 2}, 4}, {{5, 2}, 1}, {{6, 2}, 3},
            {{4, 3}, 5}, {{5, 3}, 9},
            {{1, 4}, 9}, {{4, 4}, 3}, {{7, 4}, 6},
            {{3, 5}, 2}, {{4, 5}, 6},
            {{2, 6}, 1}, {{3, 6}, 4}, {{6, 6}, 2},
            {{0, 7}, 2}, {{1, 7}, 6}, {{6, 7}, 1},
            {{0, 8}, 4}, {{5, 8}, 2}, {{6, 8}, 5}, {{8, 8}, 3}
            };
    for(int i = 0; i < sizeof(e1) / sizeof(element); i++){
        ret.push_back(e1[i]);
    }
    return ret;
}
int main() {
    std::cout << "Hello, World!" << std::endl;


    frame ff;
    ff.init(init_data());
    ff.print_map(false);

    for(auto i : ff.get_unit_consider(8)){
        std::cout << i << " ";
    }
    std::cout << std::endl;
//    ff.start();

    return 0;
}