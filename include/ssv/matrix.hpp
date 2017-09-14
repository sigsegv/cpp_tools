#pragma once

#include <cassert>
#include <array>
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
     * Create matrix from initializer list
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
     * @return row i
     */
    std::array<T, kCols>& operator[](size_t i)
    {
        assert(i < kRows);
        return m[i];
    }
    
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
    
private:
    std::array< std::array<T, kCols>, kRows> m;
};
 
using matrix41f = matrix<float, 4, 1>;
using matrix44f = matrix<float, 4, 4>;
    
}
