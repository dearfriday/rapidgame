//
// Created by nova on 2018/10/30.
//



#pragma  once

#include <vector>
#include <iostream>
#include <list>
namespace  game{

    struct  point{
        int x = 0;
        int y = 0;
    };

    struct  element{
        element(point p, int v);
        element();
        void remove_value(int value);
        bool check();
        bool is_consider();
        void remove_all();

        point   pos;
        int     value = 0;
        std::list<int> _maybe_values;
    };


    struct  frame {
        frame(int size = 9);

        void init(const std::vector<element> &data);
        void start();
        void print_map(bool map =false);
        bool is_complete();

        void remove_unit();
        void remove_line();

        std::vector<int>    get_unit_consider(int i);
        std::vector<int>    get_ver_consider(int i);
        std::vector<int>    get_hor_consider(int i);


        std::vector<element>   _values;
        int _size;
    };

}