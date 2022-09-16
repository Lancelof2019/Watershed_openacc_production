#include<iostream>

using namespace std;

struct Pixel {
    int val;
    int x;
    int y;

    Pixel(int val, int x, int y) : val(val), x(x), y(y) {}

    friend ostream &operator<<(ostream &os, const Pixel &pixel) {
        os << "val: " << pixel.val << " x: " << pixel.x << " y: " << pixel.y;
        return os;

    }
};


struct Compare{

   bool operator()(Pixel &para1, Pixel &para2) {
        return para1.val < para2.val;
    }

};