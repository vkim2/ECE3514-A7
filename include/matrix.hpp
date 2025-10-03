//include/matrix.hpp
#pragma once

#include "vector.hpp"
#include <stdexcept>  // std::out_of_range

namespace dsa{

class Matrix {
private:
    int rows{0};
    int cols{0};
    dsa::Vector<dsa::Vector<int>> data;

public:
    /*
    if r < 0 OR c < 0 
        throw std::out_of_range("Negative dimensions");
    rows = r
    cols = c
    for i from 0 to rows-1
        declare row vector of ints
        for j from 0 to cols-1
            append 0 to row  // initialize each element with 0
        append row to data
    */
    Matrix(int r, int c){
        // ToDo
        if (r < 0 || c < 0) {
            throw std::out_of_range("Negative dimensions");
        }
        rows = r;
        cols = c;

        for(int i = 0; i < rows; i++) {
            dsa::Vector<int> row; // new row each i
            for (int j = 0; j < cols; j++) {
                row.push_back(0);
            }
            data.push_back(row);
        }
    }

    //data.at(i).at(j)
    int& operator()(int i, int j) {
        // ToDo
        return data.at(i).at(j);
    }

    // throw std::out_of_range("dimensions must match")
    // result(i, j) = (*this)(i, j) + other(i, j)
    Matrix operator+(Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::out_of_range("dimensions must match"); //must match dimensions for matrix addition
        }
        Matrix result(rows, cols); //alloc new matrix for sum

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result; // think why - ans for chaining
    }

    int getRows() const { return rows; } //accessors for tests
    int getCols() const { return cols; }

};

}