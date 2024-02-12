#include "pch.h"
#include "../Maths/Vector3.h"


TEST(Vector3_Constructor, AssignsAllComponents) {
	Vector3 v(3, 4, 5);
	EXPECT_EQ(v.x, 3);
	EXPECT_EQ(v.y, 4);
	EXPECT_EQ(v.z, 5);
}

TEST(Vector3_EqualityComparison, Returns_True_For_Equal_Vectors) {
	EXPECT_TRUE(Vector3(3, 4, 5) == Vector3(3, 4, 5));
}


TEST(Vector3_EqualityComparison, Returns_False_For_Inequal_Vectors) {
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(2, 4, 5));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(3, 2, 5));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(3, 4, 2));
	EXPECT_FALSE(Vector3(3, 4, 5) == Vector3(2, 2, 2));
}

TEST(Vector3_Negation, Negate_All_Components) {
	EXPECT_EQ(-Vector3(3, 4, 5), Vector3(-3, -4, -5));
}

TEST(Vector3_InequalityComparison, Returns_True_For_Inequal_Vectors) {
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(2, 4, 5));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 2, 5));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(3, 4, 2));
	EXPECT_TRUE(Vector3(3, 4, 5) != Vector3(2, 2, 2));
}

TEST(Vector3_Adding, Adds_Vector3_To_Vector3) {
	Vector3 result = Vector3(3, 4, 5) + Vector3(3, 4, 5);
	EXPECT_EQ(result, Vector3(6, 8, 10));
}

TEST(Vector3_Subtracting, Subtract_Vector3_To_Vector3) {
	Vector3 result = Vector3(3, 4, 5) - Vector3(3, 4, 5);
	EXPECT_EQ(result, Vector3(0, 0, 0));
}

TEST(Vector3_Multipliying, Multiply_Vector3_By_Scalar) {
	Vector3 result = Vector3(3, 4, 5) * 2;
	EXPECT_EQ(result, Vector3(6, 8, 10));
}

TEST(Vector3_Dividing, Divide_Vector3_By_Scalar) {
	Vector3 result = Vector3(3, 4, 5) / 2;
	EXPECT_EQ(result, Vector3(1.5, 2, 2.5));
}

TEST(Vector3_Magnitud, Calculate_Magnitud) {
	Vector3 result = Vector3(3, 4, 5);
	EXPECT_NEAR(result.magnitude(), 7.0710678118654, 00001);
}

TEST(Vector3_Normalizing, Normalize_Vector3) {
	Vector3 result = Vector3(3.0 / 7.071, 4.0 / 7.071, 5.0 / 7.071);
	EXPECT_NEAR(result.x, 0.424, 0.001);
	EXPECT_NEAR(result.y, 0.566, 0.001);
	EXPECT_NEAR(result.z, 0.707, 0.001);
}

TEST(Vector_Cross_Product, Calculate_Product_Of_Two_Vectors3) {
	Vector3 result = Vector3::Cross(Vector3(3, 4, 5), Vector3(1, 2, 3));
	EXPECT_EQ(result, Vector3(2, -4, 2));
}

TEST(Vector_Distance_Formula, Calculate_Distance_Between_Two_Points) {
	float result = Vector3::Distance(Vector3(3, 4, 5), Vector3(1, 2, 3));
	EXPECT_NEAR(result, 3.46410161514, 0.00001);
}

// ASSERT_EQ(Vector3::Dot(Vector3(1, 2, 3), Vector3(4, 5, 6)), ? ? ? );

// Las dos barras paralelas con una letra en medio, es la magnitud de un vector.



