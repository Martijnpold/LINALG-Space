#pragma once

#include <vector>
#include <string>

namespace space::world {

    class Matrix {
    private:
        unsigned int _width;
        unsigned int _height;

        std::vector<float> _values;

    public:
        Matrix(unsigned int width, unsigned int height);
        Matrix(unsigned int width, unsigned int height, const std::vector<float>& values);

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
        [[nodiscard]] unsigned int size() const;

        [[nodiscard]] std::string to_string() const;

        friend std::ostream& operator<<(std::ostream& outputStream, const Matrix& matrix);

    private:
        unsigned int to_index(unsigned int x, unsigned int y) const;
    };

} // namespace space::world