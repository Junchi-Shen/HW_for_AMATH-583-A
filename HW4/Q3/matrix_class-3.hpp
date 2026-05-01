// AMATH 483-583 row major Matrix class template starter
// write the methods for:
// transpose
// infinityNorm
// operator*
// operator+

#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

template <typename T>
class Matrix
{
public:
    Matrix(int numRows, int numCols)
        : num_rows(numRows), num_cols(numCols), data(numRows * numCols) {}

    T &operator()(int i, int j)
    {
        return data[i * num_cols + j];
    }

    const T &operator()(int i, int j) const
    {
        return data[i * num_cols + j];
    }

    Matrix<T> operator*(const Matrix<T> &other) const
    {

        int m = num_rows;
        int p = num_cols;        
        int n = other.num_cols;


        Matrix<T> result(m, n, 0.0);


        for (int k = 0; k < p; ++k) {
            for (int i = 0; i < m; ++i) {

                T aik = this->data[i * p + k]; 
                for (int j = 0; j < n; ++j) {
                    // C[i][j] += A[i][k] * B[k][j]
                    result.data[i * n + j] += aik * other.data[k * n + j];
                }
            }
        }

        return result;

        // temporary line so the starter compiles before implementation
        throw std::logic_error("operator* not implemented");
    }

    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> transpose() const
    {

        Matrix<T> AT(num_cols, num_rows); 

        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {

                AT._data[j * num_rows + i] = data[i * num_cols + j];
            }
        }
        return AT;
        // temporary line so the starter compiles before implementation
        throw std::logic_error("transpose not implemented");
    }

    int numRows() const
    {
        return num_rows;
    }

    int numCols() const
    {
        return num_cols;
    }

    T infinityNorm() const
    {
        T norm = 0;

        for (int i = 0; i < num_rows; ++i) { 
            T current_row_sum = 0; 
            
            for (int j = 0; j < num_cols; ++j) { 

                current_row_sum += std::abs(data[i * num_cols + j]); 
            }
    

            if (current_row_sum > norm) {
                norm = current_row_sum;
            }
        }
        return norm;
     
    }


    void print() const
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                std::cout << (*this)(i, j) << " ";
            }

            std::cout << "\n";
        }
    }

private:
    int num_rows;
    int num_cols;
    std::vector<T> data;
};

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{

    if (num_rows != other.num_rows || num_cols != other.num_cols) {
        std::cout <<"Wrong Shape!" << std::cout;
    }


    Matrix<T> result(num_rows, num_cols);

    for (int i = 0; i < num_rows * num_cols; ++i) {
        result.data[i] = this->data[i] + other.data[i];
    }

    return result;
}

#endif // MATRIX_CLASS_HPP

