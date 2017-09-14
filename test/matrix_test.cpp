#include <ssv/matrix.hpp>
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
