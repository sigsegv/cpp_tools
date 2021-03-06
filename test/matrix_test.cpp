#include <ssv/matrix.hpp>
#include "utils.hpp"
#include "catch.hpp"

TEST_CASE("matrix41f default constructor", "[matrix41f]")
{
    ssv::matrix41f m0;
    REQUIRE(m0[0].size() == 1);
    REQUIRE(m0[0][0] == 0.f);
    REQUIRE(m0[1][0] == 0.f);
    REQUIRE(m0[2][0] == 0.f);
    REQUIRE(m0[3][0] == 0.f);
}

TEST_CASE("matrix41f modify", "[matrix41f]")
{
    ssv::matrix41f m0;
    m0[2][0] = 4.f;
    REQUIRE(m0[2][0] == 4.f);
}

TEST_CASE("matrix41f initializer list", "[matrix41f]")
{
    ssv::matrix41f m0 = {1.f, 2.f, 3.f, 4.f};
    REQUIRE(m0[0][0] == 1.f);
    REQUIRE(m0[1][0] == 2.f);
    REQUIRE(m0[2][0] == 3.f);
    REQUIRE(m0[3][0] == 4.f);
}

TEST_CASE("matrix41f identity", "[matrix41f]")
{
    ssv::matrix41f m0 = ssv::matrix41f::identity();
    REQUIRE(m0[0][0] == 1.f);
    REQUIRE(m0[1][0] == 0.f);
    REQUIRE(m0[2][0] == 0.f);
    REQUIRE(m0[3][0] == 0.f);
}

TEST_CASE("matrix44f identity", "[matrix44f]")
{
    ssv::matrix44f m0 = ssv::matrix44f::identity();
    REQUIRE(m0[0][0] == 1.f);
    REQUIRE(m0[1][1] == 1.f);
    REQUIRE(m0[2][2] == 1.f);
    REQUIRE(m0[3][3] == 1.f);
    REQUIRE(m0[3][2] == 0.f);
}

TEST_CASE("matrix44f initializer list", "[matrix44f]")
{
    ssv::matrix44f m0 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    REQUIRE(m0[0][0] == 1.f);
    REQUIRE(m0[0][1] == 2.f);
    REQUIRE(m0[0][2] == 3.f);
    REQUIRE(m0[0][3] == 4.f);
    REQUIRE(m0[1][0] == 5.f);
    REQUIRE(m0[1][1] == 6.f);
    REQUIRE(m0[1][2] == 0.f);
}

TEST_CASE("multiply vector4 by 4x4", "[general]")
{
    ssv::matrix44f a = ssv::matrix44f::identity();
    a[1][1] = 2.f;
    ssv::matrix41f b = {1.f, 2.f, 3.f, 4.f};
    auto c = a*b;
    REQUIRE(c[0][0] == 1.f);
    REQUIRE(c[1][0] == 4.f);
    REQUIRE(c[2][0] == 3.f);
    REQUIRE(c[3][0] == 4.f);
}

TEST_CASE("multiply two 44 matrices", "[general]")
{
    ssv::matrix44f a = ssv::matrix44f::identity();
    a[1][1] = 2.f;
    ssv::matrix44f b = ssv::matrix44f::identity();
    b[1][1] = 2.f;
    b[2][1] = 5.f;
    b[2][2] = 3.f;
    b[3][3] = 4.f;
    auto c = a*b;
    REQUIRE(c[0][0] == 1.f);
    REQUIRE(c[1][1] == 4.f);
    REQUIRE(c[2][1] == 5.f);
    REQUIRE(c[2][2] == 3.f);
    REQUIRE(c[3][3] == 4.f);
    REQUIRE(c[2][3] == 0.f);
}

TEST_CASE("multiply two 44 matrices again", "[general]")
{
    ssv::matrix44f a = {300.f, 0.f, -100.f, 400.f, 0.f, 300.f, -100.f, 400.f, 0.f, 0.f, 95.625f, 127.5f, 0.f, 0.f, -0.25f, 1.f};
    ssv::matrix41f b = {0.131261f, -0.132153f, 0.49872f, 1.f};
    auto c = a*b;
    REQUIRE(equals_approx(c[0][0], 389.506f));
    REQUIRE(equals_approx(c[1][0], 310.482f));
    REQUIRE(equals_approx(c[2][0], 175.19f));
    REQUIRE(equals_approx(c[3][0], 0.87532f));
}

TEST_CASE("transpose a 3x2 matrix", "[transpose]")
{
    using matrix32f = ssv::matrix<float, 3, 2>;
    matrix32f a = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    auto c = a.transpose();
    REQUIRE(c[0][0] == 1.f);
    REQUIRE(c[0][1] == 3.f);
    REQUIRE(c[0][2] == 5.f);
    REQUIRE(c[1][0] == 2.f);
    REQUIRE(c[1][1] == 4.f);
    REQUIRE(c[1][2] == 6.f);
}

TEST_CASE("submatrix of a matrix", "[minor]")
{
    using matrix33f = ssv::matrix<float, 3, 3>;
    matrix33f a = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    auto b = a.submatrix(1, 1);
    REQUIRE(b[0][0] == 1.f);
    REQUIRE(b[0][1] == 3.f);
    REQUIRE(b[1][0] == 7.f);
    REQUIRE(b[1][1] == 9.f);
}

TEST_CASE("equality", "[general]")
{
    using matrix33f = ssv::matrix<float, 3, 3>;
    using matrix22f = ssv::matrix<float, 2, 2>;
    matrix33f a = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    auto b = a.submatrix(1, 1);
    matrix22f c = {1.f, 3.f, 7.f, 9.f};
    REQUIRE(b == c);
}

TEST_CASE("scalar multiply", "[general]")
{
    using matrix33f = ssv::matrix<float, 3, 3>;
    matrix33f a = matrix33f::identity();
    auto b = a * 3.f;
    matrix33f c = {3.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 3.f};
    REQUIRE(b == c);
    
    auto d = 3.f * a;
    REQUIRE(d == c);
}

TEST_CASE("determinant", "[general]")
{
    using matrix22f = ssv::matrix<float, 2,2 >;
    matrix22f a = {4.f, 6.f, 3.f, 8.f};
    REQUIRE(a.determinant() == 14.f);
    using matrix33f = ssv::matrix<float, 3, 3>;
    matrix33f b = {6.f, 1.f, 1.f, 4.f, -2.f, 5.f, 2.f, 8.f, 7.f};
    REQUIRE(b.determinant() == -306.f);
}

TEST_CASE("inverse 2x2 matrix", "[general]")
{
    using matrix22f = ssv::matrix<float, 2,2 >;
    matrix22f a = {4.f, 7.f, 2.f, 6.f};
    auto b = a.inverse();
    matrix22f c = {0.6f, -0.7f, -0.2f, 0.4f};
    REQUIRE(b == c);
}

TEST_CASE("inverse 3x3 matrix", "[general]")
{
    using matrix33f = ssv::matrix<float, 3, 3>;
    matrix33f a = {3.f, 0.f, 2.f, 2.f, 0.f, -2.f, 0.f, 1.f, 1.f};
    auto b = a.inverse();
    matrix33f c = {0.2f, 0.2f, 0.f, -0.2f, 0.3f, 1.f, 0.2f, -0.3f, 0.f};
    REQUIRE(b == c);
}

TEST_CASE("double inverse on 2x2 matrix", "[general]")
{
    using matrix22f = ssv::matrix<float, 2,2 >;
    matrix22f a = {4.f, 7.f, 2.f, 6.f};
    auto b = a.inverse();
    auto c = b.inverse();
    for(unsigned row = 0; row < 2; ++row)
    {
        for(unsigned col = 0; col < 2; ++col)
        {
            REQUIRE(equals_approx(a[row][col], c[row][col]));
        }
    }
}

TEST_CASE("double inverse on 3x3 matrix", "[general]")
{
    using matrix33f = ssv::matrix<float, 3, 3>;
    matrix33f a = {3.f, 0.f, 2.f, 2.f, 0.f, -2.f, 0.f, 1.f, 1.f};
    auto b = a.inverse();
    matrix33f c = b.inverse();
    for(unsigned row = 0; row < 3; ++row)
    {
        for(unsigned col = 0; col < 3; ++col)
        {
            REQUIRE(equals_approx(a[row][col], c[row][col]));
        }
    }
}

TEST_CASE("test set_col", "[general]")
{
    using matrix32f = ssv::matrix<float, 3, 2>;
    using matrix13f = ssv::matrix<float, 1, 3>;
    matrix32f a = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    matrix13f b = {9.f, 8.f, 7.f};
    matrix32f expected = {1.f, 9.f, 3.f, 8.f, 5.f, 7.f};
    a.set_col(1, b);
    for(unsigned row = 0; row < 3; ++row)
    {
        for(unsigned col = 0; col < 3; ++col)
        {
            REQUIRE(equals_approx(a[row][col], expected[row][col]));
        }
    }
}
