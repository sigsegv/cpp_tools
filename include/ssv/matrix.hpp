#pragma once

#include <cassert>
#include <array>
#include <iostream>
#include <initializer_list>

namespace ssv
{
template<typename T, unsigned kRows, unsigned kCols>
class matrix
{
public:
    /**
     * Create empty matrix
     */
    matrix() : m{}
    {
        
    }
    
    /**
     * Create matrix from initializer list. Values are set row first. Unset values are zero.
     */
    matrix(std::initializer_list<T> l) : m{}
    {
        assert(l.size() <= (kRows * kCols));
        unsigned row = 0, col = 0;
        for(auto v : l)
        {
            m[row][col] = v;
            ++col;
            if(col == kCols)
            {
                ++row;
                col = 0;
            }
        }
    }
    
    /**
     * Create identity matrix
     */
    static matrix identity()
    {
        matrix m;
        for(unsigned c = 0; c < kCols; ++c)
        {
            m[c][c] = 1.f;
        }
        return m;
    }
    
    /**
     * Return a matrix that represents this matrix flipped over its diagonal.
     */
    matrix<T, kCols, kRows> transpose() const
    {
        matrix<T, kCols, kRows> result;
        for(unsigned r = 0; r < kRows; ++r)
        {
            for(unsigned c = 0; c < kCols; ++c)
            {
                result[c][r] = m[r][c];
            }
        }
        return result;
    }
    
    //template<unsigned kRows - 1, unsigned kCols - 1>
    matrix<T, kRows - 1, kCols -1> minor(unsigned row, unsigned col) const
    {
        matrix<T, kRows - 1, kCols -1> result;
        for(unsigned r = 0; r < kRows; ++r)
        {
            if(r == row) continue;
            unsigned new_row = r > row ? r - 1 : r;
            for(unsigned c = 0; c < kCols; ++c)
            {
                if(c == col) continue;
                unsigned new_col = c > col ? c - 1 : c;
                result[new_row][new_col] = m[r][c];
            }
        }
        return result;
    }
    
    /**
     * @return row i
     */
    std::array<T, kCols>& operator[](size_t i)
    {
        assert(i < kRows);
        return m[i];
    }
    
    /**
     * @return row i
     */
    const std::array<T, kCols>& operator[](size_t i) const
    {
        assert(i < kRows);
        return m[i];
    }
    
    template<unsigned kRhsRows, unsigned kRhsCols>
    matrix<T, kRows, kRhsCols> operator*(const matrix<T, kRhsRows, kRhsCols>& rhs) const
    {
        if(kCols != kRhsRows) throw std::runtime_error("columns must equal other's rows");
        matrix<T, kRows, kRhsCols> result;
        for(unsigned r = 0; r < kRows; ++r)
        {
            for(unsigned c = 0; c < kRhsCols; ++c)
            {
                T y = T(0);
                for(unsigned i = 0; i < kRhsRows; ++i)
                {
                    y += m[r][i] * rhs[i][c];
                }
                result[r][c] = y;
            }
        }
        return result;
    }
    
    template<unsigned kRhsRows, unsigned kRhsCols>
    constexpr bool operator==(const matrix<T, kRhsRows, kRhsCols>& rhs) const
    {
        if(kRhsRows != kRows) return false;
        if(kRhsCols != kCols) return false;
        for(unsigned r = 0; r < kRows; ++r)
        {
            for(unsigned c = 0; c < kCols; ++c)
            {
                if(m[r][c] != rhs[r][c]) return false;
            }
        }
        return true;
    }
    
private:
    std::array< std::array<T, kCols>, kRows> m;
};

template<typename T, unsigned kRows, unsigned kCols>
std::ostream& operator<<(std::ostream& os, const matrix<T, kRows, kCols>& m)
{
    for(unsigned r = 0; r < kRows; ++r)
    {
        os << "[";
        for(unsigned c = 0; c < kCols; ++c)
        {
            os << m[r][c];
            if(c + 1 < kCols) os << ", ";
        }
        os << "]";
        if(r + 1 < kRows) os << "\n";
    }
    return os;
}

using matrix41f = matrix<float, 4, 1>;
using matrix44f = matrix<float, 4, 4>;

}
