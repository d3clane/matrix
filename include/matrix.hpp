#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <initializer_list>
#include <memory>

namespace MyStd
{


template<typename T>
class Matrix
{
    struct ProxyValue
    {
        const Matrix& firstMatrix;
        const Matrix& secondMatrix;

        size_t lineIndex;

        ProxyValue(const Matrix& firstMatrix, const Matrix& secondMatrix, size_t lineIndex)
            : firstMatrix(firstMatrix), secondMatrix(secondMatrix), lineIndex(lineIndex) {}

        T operator[](size_t column);
    };

    struct ProxyString
    {
        const Matrix& firstMatrix;
        const Matrix& secondMatrix;

        ProxyString(const Matrix& firstMatrix, const Matrix& secondMatrix) 
            : firstMatrix(firstMatrix), secondMatrix(secondMatrix) {}

        ProxyValue operator[](size_t line);
    };

    using MatrixVector = std::vector<std::vector<T> >;

    MatrixVector data;
    size_t rows;
    size_t columns;

public:
    Matrix(size_t rows, size_t columns);
    Matrix(size_t rows, size_t columns, std::initializer_list<std::initializer_list<T> > init);

    Matrix operator+=(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    
    Matrix operator*=(const T& coeff);
    Matrix operator/=(const T& coeff);

    friend ProxyString operator*(const Matrix& a, const Matrix& b)
    {
        assert(a.columns == b.rows);
        return ProxyString(a, b);
    }
};

// --------------------------Implementation---------------------------------

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), columns(columns), data(rows, std::vector<T>(columns))
{
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, std::initializer_list<std::initializer_list<T> > init) 
    : Matrix(rows, columns)
{
    assert(init.size() == rows);
    size_t i = 0;
    for (auto& row : init)
    {
        assert(row.size() == columns);

        const T* rowData = std::data(row);
        for (size_t j = 0; j < columns; ++j)
        {
            data[i][j] = rowData[j];
        }

        i++;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix& other)
{
    assert(rows == other.rows && columns == other.columns);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix& other)
{
    assert(rows == other.rows && columns == other.columns);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const T& coeff)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            data[i][j] *= coeff;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator/=(const T& coeff)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            data[i][j] /= coeff;
        }
    }
    return *this;
}

template<typename T>
typename Matrix<T>::ProxyValue Matrix<T>::ProxyString::operator[](size_t line)
{
    return ProxyValue(firstMatrix, secondMatrix, line);
}

template<typename T>
T Matrix<T>::ProxyValue::operator[](size_t column)
{
    T result = 0;
    for (size_t i = 0; i < firstMatrix.columns; ++i)
    {
        result += firstMatrix.data[lineIndex][i] * secondMatrix.data[i][column];
    }

    return result;
}

} // namespace MyStd

#endif // MATRIX_HPP