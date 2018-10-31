//
// Created by nova on 2018/10/30.
//

#include "game.hpp"


namespace game{


    element::element(point p, int v):pos(p), value(v){
        for(int i = 1; i <= 9; i++){
            _maybe_values.push_back(i);
        }
    }

    element::element(){
        for(int i = 1; i <= 9; i++){
            _maybe_values.push_back(i);
        }
    }

    void element::remove_value(int value){
        _maybe_values.remove(value);
    }

    bool element::check(){
        if(_maybe_values.size() == 1){
            value = *_maybe_values.begin();
            return  true;
        }
        return false;
    }

    bool element::is_consider(){
        if(_maybe_values.size() == 0){
            return  true;
        }
        return false;
    }

    void element::remove_all(){
        _maybe_values.clear();
    }


    /////////////////////////////////////////////////
    ////////////////////  frame /////////////////////
    /////////////////////////////////////////////////



    frame::frame(int size):_size(size){

        for(int i = 0; i <  _size * _size; i++){
            element el;
            el.pos.x = i % 9;
            if(i < 9){
                el.pos.y = 0;
            }
            else{
                el.pos.y = i / 9;
            }

            _values.push_back(el);
        }

    }

    void frame::init(const std::vector<element> &data){
        for(auto &d : data){
            _values[d.pos.y * _size + d.pos.x].value = d.value;
            _values[d.pos.y * _size + d.pos.x].remove_all();
        }
    }

    void frame::start(){
        while(!is_complete()){

        }

    }

    void frame::print_map(bool map){

            for (int i = 0; i < _size; ++i) {
                for (int j = 0; j < _size; ++j) {
                    if(!map){
                        std::cout << _values[i * _size + j].value << " ";
                    }
                    else {
                        std::cout << _values[i * _size + j].pos.x << "." << _values[i * _size + j].pos.y << "  ";
                    }

                    if(j % 3 == 2){
                        std::cout << " ";
                    }
                }
                if(i % 3 == 2){
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
    }



    bool frame::is_complete(){
        for(auto &e : _values){
            if(!e.is_consider()){
                return false;
            }
        }
        return true;
    }


    void frame::remove_unit(){
        for(int i = 0; i < _size; i++){
            std::vector<int> consider = get_unit_consider(i);

        }
    }

    void frame::remove_line(){

    }


    //查找单元确认
    std::vector<int> frame::get_unit_consider(int i) {
        static std::vector<int> pos = {
                0, 1, 2,
                9, 10, 11,
                18, 19, 20
        };
        std::vector<int> ret;
        int move = 0;
        if(i <= 2){
            move = i * 3;
        }
        else{
            move = (i / 3) * 27 + i % 3 * 3;
        }

        for(auto &p : pos){
            auto &el = _values[p + move];
            if(el.is_consider()){
                ret.push_back(el.value);
            }

        }
        return ret;
    }


    // 查看垂直确认
    std::vector<int> frame::get_ver_consider(int i) {
        std::vector<int> ret;
        for(auto &el : _values){
            if(el.pos.x == i){
                ret.push_back(el.value);
            }
        }
        return ret;
    }

    // 查询水平确认
    std::vector<int> frame::get_hor_consider(int i) {
        std::vector<int> ret;
        for(auto &el : _values){
            if(el.pos.y == i){
                ret.push_back(el.value);
            }
        }
        return ret;
    }
}
