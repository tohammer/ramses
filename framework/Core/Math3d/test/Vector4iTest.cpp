//  -------------------------------------------------------------------------
//  Copyright (C) 2013 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "Math3d/Vector4i.h"
#include "framework_common_gmock_header.h"
#include "PlatformAbstraction/PlatformMath.h"
#include "IOStreamTester.h"
#include "gmock/gmock.h"

class Vector4iTest: public testing::Test
{
public:
    ramses_internal::Vector4i vec1{1, 2, 3, 4};
};

TEST_F(Vector4iTest, DefaultConstructor)
{
    ramses_internal::Vector4i vec2;
    EXPECT_EQ(0, vec2.x);
    EXPECT_EQ(0, vec2.y);
    EXPECT_EQ(0, vec2.z);
    EXPECT_EQ(0, vec2.w);
}

TEST_F(Vector4iTest, CopyConstructor)
{
    ramses_internal::Vector4i vec2 = vec1;
    EXPECT_EQ(1, vec2.x);
    EXPECT_EQ(2, vec2.y);
    EXPECT_EQ(3, vec2.z);
    EXPECT_EQ(4, vec2.w);
}

TEST_F(Vector4iTest, ValueConstructor)
{
    EXPECT_EQ(1, vec1.x);
    EXPECT_EQ(2, vec1.y);
    EXPECT_EQ(3, vec1.z);
    EXPECT_EQ(4, vec1.w);
}

TEST_F(Vector4iTest, ScalarValueConstructor)
{
    ramses_internal::Vector4i vec2(2);
    EXPECT_EQ(2, vec2.x);
    EXPECT_EQ(2, vec2.y);
    EXPECT_EQ(2, vec2.z);
    EXPECT_EQ(2, vec2.w);
}

TEST_F(Vector4iTest, AssignmentOperator)
{
    ramses_internal::Vector4i vec2;
    vec2 = vec1;
    EXPECT_EQ(1, vec2.x);
    EXPECT_EQ(2, vec2.y);
    EXPECT_EQ(3, vec2.z);
    EXPECT_EQ(4, vec2.w);
}

TEST_F(Vector4iTest, AddOperator)
{
    ramses_internal::Vector4i vec2(4, 5, 6, 7);
    ramses_internal::Vector4i vec3 = vec1 + vec2;
    EXPECT_EQ(5, vec3.x);
    EXPECT_EQ(7, vec3.y);
    EXPECT_EQ(9, vec3.z);
    EXPECT_EQ(11, vec3.w);
}

TEST_F(Vector4iTest, AddAssignOperator)
{
    ramses_internal::Vector4i vec2(4, 5, 6, 7);
    vec2 += vec1;
    EXPECT_EQ(5, vec2.x);
    EXPECT_EQ(7, vec2.y);
    EXPECT_EQ(9, vec2.z);
    EXPECT_EQ(11, vec2.w);
}

TEST_F(Vector4iTest, SubOperator)
{
    ramses_internal::Vector4i vec2(4, 5, 6, 7);
    ramses_internal::Vector4i vec3 = vec1 - vec2;
    EXPECT_EQ(-3, vec3.x);
    EXPECT_EQ(-3, vec3.y);
    EXPECT_EQ(-3, vec3.z);
    EXPECT_EQ(-3, vec3.w);
}

TEST_F(Vector4iTest, SubAssignOperator)
{
    ramses_internal::Vector4i vec2(4, 5, 6, 7);
    vec1 -= vec2;
    EXPECT_EQ(-3, vec1.x);
    EXPECT_EQ(-3, vec1.y);
    EXPECT_EQ(-3, vec1.z);
    EXPECT_EQ(-3, vec1.w);
}

TEST_F(Vector4iTest, MulOperator)
{
    ramses_internal::Vector4i vec2 = vec1 * 2;

    EXPECT_EQ(2, vec2.x);
    EXPECT_EQ(4, vec2.y);
    EXPECT_EQ(6, vec2.z);
    EXPECT_EQ(8, vec2.w);
}

TEST_F(Vector4iTest, MulFriendOperator)
{
    ramses_internal::Vector4i vec2 = 2 * vec1;

    EXPECT_EQ(2, vec2.x);
    EXPECT_EQ(4, vec2.y);
    EXPECT_EQ(6, vec2.z);
    EXPECT_EQ(8, vec2.w);
}

TEST_F(Vector4iTest, MulAssignOperator)
{
    vec1 *= 2;

    EXPECT_EQ(2, vec1.x);
    EXPECT_EQ(4, vec1.y);
    EXPECT_EQ(6, vec1.z);
    EXPECT_EQ(8, vec1.w);
}

TEST_F(Vector4iTest, MulVector)
{
    ramses_internal::Vector4i vec2(1, 2, 3, 4);
    ramses_internal::Vector4i vec3 = vec1 * vec2;

    EXPECT_EQ(1, vec3.x);
    EXPECT_EQ(4, vec3.y);
    EXPECT_EQ(9, vec3.z);
    EXPECT_EQ(16, vec3.w);
}

TEST_F(Vector4iTest, MulAssignVector)
{
    ramses_internal::Vector4i vec2(1, 2, 3, 4);
    vec1 *= vec2;

    EXPECT_EQ(1, vec1.x);
    EXPECT_EQ(4, vec1.y);
    EXPECT_EQ(9, vec1.z);
    EXPECT_EQ(16, vec1.w);
}

TEST_F(Vector4iTest, Equality)
{
    ramses_internal::Vector4i vec2(1, 2, 3, 4);
    bool equal = vec1 == vec2;

    EXPECT_EQ(true, equal);
}

TEST_F(Vector4iTest, UnEquality)
{
    ramses_internal::Vector4i vec2(0, 2, 3, 4);
    bool unequal = vec1 != vec2;

    EXPECT_EQ(true, unequal);
}

TEST_F(Vector4iTest, Dot)
{
    ramses_internal::Vector4i vec2(4, 5, 6, 7);
    ramses_internal::Int32 scalar = vec1.dot(vec2);
    EXPECT_EQ(60, scalar);
}

TEST_F(Vector4iTest, Cross)
{
    ramses_internal::Vector4i vec2(4, 3, 2, 1);

    ramses_internal::Vector4i vec3 = vec1.cross(vec2);
    EXPECT_EQ(-20 , vec3.x);
    EXPECT_EQ(20 , vec3.y);
    EXPECT_EQ(20 , vec3.z);
    EXPECT_EQ(-20 , vec3.w);
}

TEST_F(Vector4iTest, Length)
{
    ramses_internal::Vector4i vec2(2, 2, 2, 2);
    ramses_internal::Float length = vec2.length();
    EXPECT_FLOAT_EQ(4, length);
}

TEST_F(Vector4iTest, Angle)
{
    ramses_internal::Vector4i vec2(1, 0, 0, 0);
    ramses_internal::Vector4i vec3(0, 1, 0, 0);
    ramses_internal::Float angle = ramses_internal::PlatformMath::Rad2Deg(vec2.angle(vec3));
    EXPECT_FLOAT_EQ(90, angle);
}

TEST_F(Vector4iTest, SetSingleValues)
{
    vec1.set(3, 4, 7, 5);
    ramses_internal::Vector4i vec2(3, 4, 7, 5);

    EXPECT_EQ(vec2, vec1);
}

TEST_F(Vector4iTest, SetAllValues)
{
    vec1.set(5);
    ramses_internal::Vector4i vec2(5, 5, 5, 5);

    EXPECT_EQ(vec2, vec1);
}

TEST_F(Vector4iTest, CanPrintToString)
{
    EXPECT_EQ("[1 2 3 4]", fmt::to_string(vec1));
    EXPECT_EQ("[1 2 3 4]", ramses_internal::StringOutputStream::ToString(vec1));
}

TEST_F(Vector4iTest, canBinarySerializeDeserialize)
{
    ramses_internal::IOStreamTesterBase::expectSame(ramses_internal::Vector4i());
    ramses_internal::IOStreamTesterBase::expectSame(ramses_internal::Vector4i(1, 2, 3, 4));
    ramses_internal::IOStreamTesterBase::expectSame(ramses_internal::Vector4i(std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()-1, std::numeric_limits<int32_t>::min()+1));
}
