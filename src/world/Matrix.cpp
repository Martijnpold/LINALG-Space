#include "Matrix.hpp"

#include <cmath>

namespace space::world {

    Matrix::Matrix(unsigned int width, unsigned int height)
        : _values {std::vector<float>(width * height)}, _width {width}, _height {height} {
    }

    Matrix::Matrix(unsigned int width, unsigned int height, const std::vector<float>& values) : Matrix(width, height) {
        fill(values);
    }

    Matrix Matrix::createScalingMatrix(float xScale, float yScale, float zScale) {
        return Matrix {4, 4, {xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, zScale, 0, 0, 0, 0, 1}};
    }

    Matrix Matrix::createTranslationMatrix(float xTranslation, float yTranslation, float zTranslation) {
        return Matrix {4, 4, {1, 0, 0, xTranslation, 0, 1, 0, yTranslation, 0, 0, 1, zTranslation, 0, 0, 0, 1}};
    }

    Matrix Matrix::createRotationMatrixZ(float angle) {
        return Matrix(4, 4,
                      {std::cos(angle), -std::sin(angle), 0, 0, std::sin(angle), std::cos(angle), 0, 0, 0, 0, 1, 0, 0,
                       0, 0, 1});
    }

    Matrix Matrix::operator+(const Matrix& other) const {
        if (width() != other.width() || height() != other.height()) {
            throw std::logic_error {"Can not add differently sized Matrices together"};
        }

        Matrix dest {_width, _height};

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                float a = get(x, y);
                float b = other.get(x, y);
                dest.set(x, y, a + b);
            }
        }

        return dest;
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        if (width() != other.width() || height() != other.height()) {
            throw std::logic_error {"Can not subtract differently sized Matrices together"};
        }

        Matrix dest {_width, _height};

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                float a = get(x, y);
                float b = other.get(x, y);
                dest.set(x, y, a - b);
            }
        }

        return dest;
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        if (width() != other.height()) {
            throw std::logic_error {"Can not multiply Matrix of width: " + std::to_string(width()) +
                                    " with Matrix of height: " + std::to_string(other.height())};
        }

        Matrix dest {other.width(), height()};
        unsigned int multiplicationRowSize = width();

        for (int y = 0; y < height(); ++y) {
            for (int x = 0; x < other.width(); ++x) {
                float value = 0;

                for (int i = 0; i < multiplicationRowSize; ++i) {
                    float a = get(i, y);
                    float b = other.get(x, i);
                    value += a * b;
                }

                dest.set(x, y, value);
            }
        }

        return dest;
    }

    Vector Matrix::operator*(const Vector& vector) const {
        Matrix vectorAsMatrix {1, 4, {vector.x, vector.y, vector.z, 1}};
        Matrix result = *this * vectorAsMatrix;
        return Vector {result.get(0, 0), result.get(0, 1), result.get(0, 2)};
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