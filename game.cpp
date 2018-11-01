//
// Created by nova on 2018/10/30.
//

#include "game.hpp"


namespace game {


element::element(point p, int v): pos(p), value(v) {
    for (int i = 1; i <= 9; i++) {
        _maybe_values.push_back(i);
    }
}

// element::element() {
//     for (int i = 1; i <= 9; i++) {
//         _maybe_values.push_back(i);
//     }
// }

void element::remove_values(const std::vector<int> &values) {
    for (auto v : values) {
        _maybe_values.remove(v);
    }
    // check();

}

bool element::check() {
    if (_maybe_values.size() == 1) {
        value = *_maybe_values.begin();
        _maybe_values.clear();
        return  true;
    }
    return false;
}

bool element::is_consider() {
    if (_maybe_values.size() == 0) {

        return  true;
    }
    return false;
}

void element::remove_all() {
    _maybe_values.clear();
}

bool element::has_values(int i)
{
    return false;
}

/////////////////////////////////////////////////
////////////////////  frame /////////////////////
/////////////////////////////////////////////////



frame::frame(int size): _size(size) {

    for (int i = 0; i <  _size * _size; i++) {
        element el({0, 0}, 0);
        el.pos.x = i % 9;
        if (i < 9) {
            el.pos.y = 0;
        }
        else {
            el.pos.y = i / 9;
        }

        _values.push_back(el);
    }

}

void frame::init(const std::vector<element> &data) {
    for (auto &d : data) {
        if(d.value == 0){
            continue;
        }
        _values[d.pos.y * _size + d.pos.x].value = d.value;
        _values[d.pos.y * _size + d.pos.x].remove_all();
    }
}

void frame::start() {
    int i = 0;
    while (i++ < 100) {
        remove_unit();
        remove_line();
        consider_only_one();
        check_element();
    }

}

void frame::print_map(int type) {

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            auto &e = _values[i * _size + j];
            if (type == 0) {
                std::cout << e.value << " ";
            }
            else if (type == 1) {
                std::cout << e.pos.x << "." << e.pos.y << "  ";
            }
            else if (type == 2) {
                std::cout << i * _size + j << " ";
            }
            else if (type == 3) {
                std::cout << "(";
                for (auto v : e._maybe_values) {
                    std::cout << v << ",";
                }
                std::cout << ")";
            }



            if (j % 3 == 2) {
                std::cout << " ";
            }
        }
        if (i % 3 == 2) {
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

bool frame::is_complete() {
    for (auto &e : _values) {
        if (!e.is_consider()) {
            return false;
        }
    }
    return true;
}


void frame::remove_unit() {
    for (int i = 0; i < _size; i++) {
        std::vector<int> consider_values = get_unit_consider_values(i);
        std::vector<int> unit_pos = get_pos_unit(i);
        for (auto p : unit_pos) {
            _values[p].remove_values(consider_values);
        }
    }

}

void frame::remove_line() {
    for (int i = 0; i < _size; i++) {
        auto ver_consider_values = get_ver_consider(i);
        auto ver_pos = get_ver_line_pos(i);
        for (auto p : ver_pos) {
            _values[p].remove_values(ver_consider_values);
        }
    }

    for (int i = 0; i < _size; i++) {
        auto hor_consider_values = get_hor_consider(i);
        auto hor_pos = get_hor_line_pos(i);
        for (auto p : hor_pos) {
            if (!_values[p].is_consider()) {
                _values[p].remove_values(hor_consider_values);
            }

        }
    }

}

void frame::consider_only_one()
{
    for (int i = 0; i < _size; i++) {
        // std::vector<int> consider_values = get_unit_consider_values(i);
        std::vector<int> unit_pos = get_pos_unit(i);
        for (auto pos : unit_pos) {
            auto &e = _values[pos];
            if (e.is_consider()) {
                continue;
            }
            //
            std::vector<int> others;
            for (auto &cp : unit_pos) {     //copy other position.
                if (cp != pos) {
                    others.push_back(cp);
                }
            }

            for (auto value : e._maybe_values) {
                if (!find_other_value_on_unit(others, value)) {
                    e.value = value;
                    e.remove_all();
                    break;
                }
            }


        }
        // for (auto p : unit_pos) {
        //     _values[p].remove_values(consider_values);
        // }

    }
}


//查找单元确认
std::vector<int> frame::get_unit_consider_values(int i) {

    std::vector<int> ret;
    std::vector<int> pos = get_pos_unit(i);
    for (auto &p : pos) {
        auto &el = _values[p];
        if (el.is_consider()) {
            ret.push_back(el.value);
        }

    }
    return ret;
}


// 查看垂直确认
std::vector<int> frame::get_ver_consider(int column) {
    std::vector<int> pos = get_ver_line_pos(column);
    std::vector<int> ret;
    for (auto &p : pos) {
        if (_values[p].is_consider()) {
            ret.push_back(_values[p].value);
        }
    }
    return ret;
}

// 查询水平确认
std::vector<int> frame::get_hor_consider(int row) {
    std::vector<int> pos = get_hor_line_pos(row);
    std::vector<int> ret;
    for (auto &p : pos) {
        if (_values[p].is_consider()) {
            ret.push_back(_values[p].value);
        }
    }
    return ret;
}

std::vector<int> frame::get_pos_unit(int i)
{
    static std::vector<int> pos = {
        0, 1, 2,
        9, 10, 11,
        18, 19, 20
    };
    std::vector<int> ret;
    int move = 0;
    if (i <= 2) {
        move = i * 3;
    }
    else {
        move = (i / 3) * 27 + i % 3 * 3;
    }


    for (auto p : pos) {
        ret.push_back(move + p);
    }
    return ret;
}

std::vector<int> frame::get_ver_line_pos(int column)
{
    std::vector<int> ret;
    for (int i = 0; i < _size; i++) {
        ret.push_back(i * 9 + column);
    }
    return ret;
}


std::vector<int> frame::get_hor_line_pos(int row)
{
    std::vector<int> ret;
    for (int i = 0; i < _size; i++) {
        ret.push_back(row * 9 + i);
    }
    return ret;
}


void frame::check_element()
{
    for (auto &e : _values) {
        if (e.check()) {
            break;
        }
    }
}


bool frame::find_other_value_on_unit(std::vector<int> others, int value)
{
    for (auto p : others) {
        auto & maybe = _values[p]._maybe_values;
        for (auto &v : _values[p]._maybe_values) {
            if (v == value) {
                return true;
            }
        }
    }
    return false;
}


}
