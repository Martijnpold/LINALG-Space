#include "Matrix.hpp"

namespace space::world {

    Matrix::Matrix(unsigned int width, unsigned int height)
        : _values {std::vector<float>(width * height)}, _width {width}, _height {height} {
    }

    Matrix::Matrix(unsigned int width, unsigned int height, const std::vector<float>& values) : Matrix(width, height) {
        fill(values);
    }

    Matrix Matrix::operator+(const Matrix& matrix) const {
        if (width() != matrix.width() || height() != matrix.height()) {
            throw std::logic_error {"Can not add differently sized Matrices together"};
        }

        Matrix dest {_width, _height};

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                float a = get(x, y);
                float b = matrix.get(x, y);
                dest.set(x, y, a + b);
            }
        }

        return dest;
    }

    Matrix Matrix::operator-(const Matrix& matrix) const {
        if (width() != matrix.width() || height() != matrix.height()) {
            throw std::logic_error {"Can not subtract differently sized Matrices together"};
        }

        Matrix dest {_width, _height};

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                float a = get(x, y);
                float b = matrix.get(x, y);
                dest.set(x, y, a - b);
            }
        }

        return dest;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const {
        throw std::logic_error {"Not implemented"}; // TODO
    }

    Matrix Matrix::operator*(const Vector& vector) const {
        throw std::logic_error {"Not implemented"}; // TODO
    }

    //#region getters / setters

    unsigned int Matrix::width() const {
        return _width;
    }

    unsigned int Matrix::height() const {
        return _height;
    }

    unsigned int Matrix::size() const {
        return _width * _height;
    }

    float Matrix::get(unsigned int x, unsigned int y) const {
        return _values.at(to_index(x, y));
    }

    void Matrix::set(unsigned int x, unsigned int y, float value) {
        _values[to_index(x, y)] = value;
    }

    void Matrix::fill(const std::vector<float>& values) {
        if (values.size() != size()) {
            throw std::logic_error {"Size of the list of values does not match the size of the Matrix"};
        }
        _values = values;
    }

    unsigned int Matrix::to_index(unsigned int x, unsigned int y) const {
        return y * _width + x;
    }

    //#endregion

    //#region printing

    std::string Matrix::to_string() const {
        std::string result;
        result += "Matrix(";

        for (int y = 0; y < _height; ++y) {
            result += "\n  ";
            for (int x = 0; x < _width; ++x) {
                if (x != 0) {
                    result += ", ";
                }
                result += std::to_string(get(x, y));
            }
        }

        result += "\n)";
        return result;
    }

    std::ostream& operator<<(std::ostream& strm, const Matrix& matrix) {
        return strm << matrix.to_string();
    }

    //#endregion

} // namespace space::world