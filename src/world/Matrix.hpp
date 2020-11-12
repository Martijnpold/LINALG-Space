#pragma once

#include <vector>

namespace space::world {

    class Matrix {
    private:
        unsigned int _width;
        std::vector<float> _values;

    public:
        Matrix(unsigned int width, unsigned int height);

        float get(unsigned int x, unsigned int y) const;
        void set(unsigned int x, unsigned int y, float value);

    private:
        unsigned int to_index(unsigned int x, unsigned int y) const;
    };

} // namespace space::world