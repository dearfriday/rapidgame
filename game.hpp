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
        element() = delete;
        void remove_values(const std::vector<int> &values);
        bool check();
        bool is_consider();
        void remove_all();
        bool has_values(int i);

        point   pos;
        int     value = 0;
        std::list<int> _maybe_values;
    };


    struct  frame {
        frame(int size);

        void init(const std::vector<element> &data);
        void start();

        //@param 0, 1, 2
        // 0  value;
        // 1  point;
        // 2 position in values
        // 3  may value
        void print_map(int type = 0);
        bool is_complete();

        void remove_unit();
        void remove_line();
        void consider_only_one();
        bool find_other_value_on_unit(std::vector<int> others, int value);

        std::vector<int>    get_unit_consider_values(int i);
        std::vector<int>    get_ver_consider(int i);
        std::vector<int>    get_hor_consider(int i);


        std::vector<element>   _values;
        int _size;


    // private:
        //get someone unit position
        std::vector<int>    get_pos_unit(int i);
        //get someone ver line position
        std::vector<int>    get_ver_line_pos(int i);
        std::vector<int>    get_hor_line_pos(int i);
        void check_element();
    };

}