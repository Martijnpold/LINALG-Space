#pragma once

#include "Vector.hpp"

#include <vector>
#include <string>

namespace space::math {

    class Matrix {
    private:
        unsigned int _width;
        unsigned int _height;

        std::vector<float> _values;

    public:
        Matrix(unsigned int width, unsigned int height);
        Matrix(unsigned int width, unsigned int height, const std::vector<float>& values);

        static Matrix createScalingMatrix(float xScale, float yScale, float zScale);
        static Matrix createTranslationMatrix(const Vector& vector);
        static Matrix createTranslationMatrix(float xTranslation, float yTranslation, float zTranslation);
        static Matrix createRotationMatrixX(float angle);
        static Matrix createRotationMatrixY(float angle);
        static Matrix createRotationMatrixZ(float angle);
        static Matrix createRotationMatrixVec(const Vector& v, float angle);

        bool operator==(const Matrix& matrix) const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& matrix) const;
        Matrix& operator*=(const Matrix& matrix);
        Vector operator*(const Vector& vector) const;

        /**
         * Overwrite all values currently in the Matrix with new ones. This method interprets the provided list of values
         * and separates rows based on the sizing (height/width) of the Matrix. For example, filling a 2x2 Matrix with the
         * list: [1 2 3 4], results in the following Matrix:
         *
         * Matrix(
         *   1 2
         *   3 4
         * )
         *
         * Note that the size of the list of values passed must match up exactly with the size of the Matrix.
         *
         * @param values
         */
        void fill(const std::vector<float>& values);

        void set(unsigned int x, unsigned int y, float value);
        [[nodiscard]] float get(unsigned int x, unsigned int y) const;
        [[nodiscard]] float operator()(unsigned int x, unsigned int y) const;

        [[nodiscard]] unsigned int size() const;
        [[nodiscard]] unsigned int height() const;
        [[nodiscard]] unsigned int width() const;

        [[nodiscard]] std::string to_string() const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Matrix& matrix);

    private:
        [[nodiscard]] unsigned int to_index(unsigned int x, unsigned int y) const;
    };

} // namespace space::world