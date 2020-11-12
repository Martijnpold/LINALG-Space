#include "Matrix.hpp"

namespace space::world {

    Matrix::Matrix(unsigned int width, unsigned int height) : _values {std::vector<float>(width * height)}, _width { width } {
    }

    float Matrix::get(unsigned int x, unsigned int y) const {
        return _values.at(to_index(x, y));
    }

    void Matrix::set(unsigned int x, unsigned int y, float value) {
        _values[to_index(x, y)] = value;
    }

    unsigned int Matrix::to_index(unsigned int x, unsigned int y) const {
        return y * _width + x;
    }

}