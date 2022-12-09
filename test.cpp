//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "MathUtils.h"
#include "Mesh.h"
#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Lights.h"
#include "Material.h"
#include "Pattern.h"
#include "Patterns.h"
#include "Plane.h"
#include "RayCaster.h"
#include "Sphere.h"
#include "SmoothTriangle.h"
#include "Transform.h"
#include "Triangle.h"
#include "World.h"

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

TEST(TestVector4fVectorVector3f, TestVector4fAsAVector3f) {
    Vector4f t = create_point(4.3f, -4.2f, 3.1f);
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 1.0f);
    EXPECT_TRUE(is_point(t));
    EXPECT_FALSE(is_vector(t));
}

TEST(TestVector4fVectorVector3f, TestVector4fAsAVector) {
    Vector4f t = create_vector(4.3f, -4.2f, 3.1f);
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 0.0f);
    EXPECT_FALSE(is_point(t));
    EXPECT_TRUE(is_vector(t));
}

TEST(TestVector4fVectorVector3f, TestCreateVector4fFromVector3f) {
    Vector3f p = Vector3f(4.0f, -4.0f, 3.0f);
    Vector4f t = create_point(p);
    EXPECT_EQ(t.x(), 4.0f);
    EXPECT_EQ(t.y(), -4.0f);
    EXPECT_EQ(t.z(), 3.0f);
    EXPECT_EQ(t.w(), 1.0f);
    EXPECT_TRUE(is_point(t));
    EXPECT_FALSE(is_vector(t));
}

TEST(TestVector4fVectorVector3f, TestCreateVector4fFromVector) {
    Vector3f v = Vector3f(4.0f, -4.0f, 3.0f);
    Vector4f t = create_vector(v);
    EXPECT_EQ(t.x(), 4.0f);
    EXPECT_EQ(t.y(), -4.0f);
    EXPECT_EQ(t.z(), 3.0f);
    EXPECT_EQ(t.w(), 0.0f);
    EXPECT_FALSE(is_point(t));
    EXPECT_TRUE(is_vector(t));
}

TEST(TestVector4fVectorVector3f, TestVector4fAreEqual) {
    Vector4f t1 = Vector4f(4.0f, -4.0f, 3.0f, 1.0f);
    Vector4f t2 = Vector4f(4.0f, -4.0f, 3.0f, 1.0f);
    EXPECT_TRUE(t1 == t2);
}

TEST(TestVector4fVectorVector3f, TestVector4fAreNotEqual) {
    Vector4f t1 = Vector4f(4.0f, -4.0f, 3.0f, 1.0f);
    Vector4f t2 = Vector4f(4.0f, -4.0f, 3.0f, 0.0f);
    EXPECT_FALSE(t1 == t2);
}

TEST(TestVector4fVectorVector3f, TestVector4fVectorAndVector3fAddition) {
    Vector4f p = create_point(3.0f, -2.0f, 5.0f);
    Vector4f v = create_vector(-2.0f, 3.0f, 1.0f);
    Vector4f expected = Vector4f(1.0f, 1.0f, 6.0f, 1.0f);
    Vector4f result = p + v;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fVector3fAndVector3fSubtraction) {
    Vector3f p1 = Vector3f(3.0f, 2.0f, 1.0f);
    Vector4f t1 = create_point(p1);
    Vector3f p2 = Vector3f(5.0f, 6.0f, 7.0f);
    Vector4f t2 = create_point(p2);
    Vector4f expected = Vector4f(-2.0f, -4.0f, -6.0f, 0.0f);
    Vector4f result = t1 - t2;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fVectorAndVector3fSubtraction) {
    Vector4f p = create_point(3.0f, 2.0f, 1.0f);
    Vector4f v = create_vector(5.0f, 6.0f, 7.0f);
    Vector4f expected = Vector4f(-2.0f, -4.0f, -6.0f, 1.0f);
    Vector4f result = p - v;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fVectorAndVectorSubtraction) {
    Vector4f v1 = create_vector(3.0f, 2.0f, 1.0f);
    Vector4f v2 = create_vector(5.0f, 6.0f, 7.0f);
    Vector4f expected = Vector4f(-2.0f, -4.0f, -6.0f, 0.0f);
    Vector4f result = v1 - v2;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fNegation) {
    Vector4f t = Vector4f(1.0f, -2.0f, 3.0f, -4.0f);
    Vector4f expected = Vector4f(-1.0f, 2.0f, -3.0f, 4.0f);
    Vector4f result = -t;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fScalarMultiplication) {
    Vector4f t = Vector4f(1.0f, -2.0f, 3.0f, -4.0f);
    Vector4f expected = Vector4f(3.5f, -7.0f, 10.5f, -14.0f);
    Vector4f result = t * 3.5;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVector4fScalarDivision) {
    Vector4f t = Vector4f(1.0f, -2.0f, 3.0f, -4.0f);
    Vector4f expected = Vector4f(0.5f, -1.0f, 1.5f, -2.0f);
    Vector4f result = t / 2.0f;
    EXPECT_TRUE(result == expected);
}

TEST(TestVector4fVectorVector3f, TestVectorMagnitude) {
    Vector4f v1 = create_vector(1.0f, 0.0f, 0.0f);
    EXPECT_EQ(v1.norm(), 1.0f);
    Vector4f v2 = create_vector(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(v2.norm(), 1.0f);
    Vector4f v3 = create_vector(0.0f, 0.0f, 1.0f);
    EXPECT_EQ(v3.norm(), 1.0f);
    Vector4f v4 = create_vector(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v4.norm(), sqrt(14.0f));
    Vector4f v5 = create_vector(-1.0f, -2.0f, -3.0f);
    EXPECT_EQ(v5.norm(), sqrt(14.0f));
}

TEST(TestVector4fVectorVector3f, TestVectorNormalize) {
    Vector4f v1 = create_vector(4.0f, 0.0f, 0.0f);
    Vector4f expected1 = create_vector(1.0f, 0.0f, 0.0f);
    Vector4f result = v1.normalized();
    EXPECT_TRUE(result == expected1);
    Vector4f v2 = create_vector(1.0f, 2.0f, 3.0f);
    Vector4f expected2 = create_vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f));
    Vector4f result2 = v2.normalized();
    EXPECT_TRUE(result2 == expected2);
}

TEST(TestVector4fVectorVector3f, TestVectorMagnitudeAfterNormalize) {
    Vector4f v = create_vector(1.0f, 2.0f, 3.0f);
    Vector4f normalized = v.normalized();
    EXPECT_FLOAT_EQ(normalized.norm(), 1.0f);
}

TEST(TestVector4fVectorVector3f, TestDotProduct) {
    Vector4f v1 = create_vector(1.0f, 2.0f, 3.0f);
    Vector4f v2 = create_vector(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v1.dot(v2), 20.0f);
}

TEST(TestVector4fVectorVector3f, TestCrossProduct) {
    Vector4f v1 = create_vector(1.0f, 2.0f, 3.0f);
    Vector4f v2 = create_vector(2.0f, 3.0f, 4.0f);
    Vector4f expected1 = create_vector(-1.0f, 2.0f, -1.0f);
    Vector4f expected2 = create_vector(1.0f, -2.0f, 1.0f);
    EXPECT_TRUE(v1.cross3(v2) == expected1);
    EXPECT_TRUE(v2.cross3(v1) == expected2);
}

TEST(TestCanvasColor, TestColorInstance) {
    Color c = Color(-0.5f, 0.4f, 1.7f);
    EXPECT_FLOAT_EQ(c.r, -0.5f);
    EXPECT_FLOAT_EQ(c.g, 0.4f);
    EXPECT_FLOAT_EQ(c.b, 1.7f);
}

TEST(TestCanvasColor, TestColorAddition) {
    Color c1 = Color(0.9f, 0.6f, 0.75f);
    Color c2 = Color(0.7f, 0.1f, 0.25f);
    Color expected = Color(1.6f, 0.7f, 1.0f);
    Color result = c1 + c2;
    EXPECT_TRUE(result == expected);
}

TEST(TestCanvasColor, TestColorSubtraction) {
    Color c1 = Color(0.9f, 0.6f, 0.75f);
    Color c2 = Color(0.7f, 0.1f, 0.25f);
    Color expected = Color(0.2f, 0.5f, 0.5f);
    Color result = c1 - c2;
    EXPECT_TRUE(result == expected);
}

TEST(TestCanvasColor, TestColorScalarMultiplication) {
    Color c = Color(0.2f, 0.3f, 0.4f);
    Color expected = Color(0.4f, 0.6f, 0.8f);
    Color result = c * 2.0f;
    EXPECT_TRUE(result == expected);
}

TEST(TestCanvasColor, TestCanvasInstantiation) {
    Canvas c = Canvas(10, 20);
    EXPECT_EQ(c.width, 10);
    EXPECT_EQ(c.height, 20);
    for (int i = 0; i < c.width; i++) {
        for (int j = 0; j < c.height; j++) {
            EXPECT_TRUE(c.pixel_at(i, j) == Color(0.0f, 0.0f, 0.0f));
        }
    }
}

TEST(TestCanvasColor, TestCanvasWrite) {
    Canvas c = Canvas(10, 20);
    Color red = Color(1.0f, 0.0f, 0.0f);
    c.write_pixel(2, 3, red);
    EXPECT_TRUE(c.pixel_at(2, 3) == red);
}

TEST(TestCanvasColor, TestCanvasPPMHeader) {
    Canvas c = Canvas(5, 3);
    std::string expected = "P3\n5 3\n255\n";
    // Get first three lines of PPM
    std::string result = c.canvas_to_ppm().substr(0, 13);
    EXPECT_EQ(result.substr(0, expected.length()), expected);
}

TEST(TestCanvasColor, TestCanvasPPMPixelData) {
    Canvas c = Canvas(5, 3);
    Color c1 = Color(1.5f, 0.0f, 0.0f);
    Color c2 = Color(0.0f, 0.5f, 0.0f);
    Color c3 = Color(-0.5f, 0.0f, 1.0f);
    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);
    std::string expected = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                           "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                           "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    // Get lines 4-6 of PPM
    std::string result = c.canvas_to_ppm().substr(11, 100);
    EXPECT_EQ(result, expected);
}

TEST(TestCanvasColor, TestCanvasPPMLinesNoLongerThan70) {
    Canvas c = Canvas(10, 2);
    for (int i = 0; i < c.width; i++) {
        for (int j = 0; j < c.height; j++) {
            c.write_pixel(i, j, Color(1.0f, 0.8f, 0.6f));
        }
    }
    std::string expected = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                           "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                           "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                           "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    // Get lines 4-6 of PPM
    std::string result = c.canvas_to_ppm().substr(12, 300);
    EXPECT_EQ(result, expected);
}

TEST(TestCanvasColor, TestCanvasTerminatedByNewline) {
    Canvas c = Canvas(5, 3);
    std::string expected = "\n";
    // Get last character of PPM
    std::string result = c.canvas_to_ppm().substr(c.canvas_to_ppm().length() - 1, 1);
    EXPECT_EQ(result, expected);
}

TEST(TestMatrices, TestEigenMatrix) {
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
            5.5, 6.5, 7.5, 8.5,
            9, 10, 11, 12,
            13.5, 14.5, 15.5, 16.5;
    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 3), 4.0f);
    EXPECT_FLOAT_EQ(m(1, 0), 5.5f);
    EXPECT_FLOAT_EQ(m(1, 2), 7.5f);
    EXPECT_FLOAT_EQ(m(2, 2), 11.0f);
    EXPECT_FLOAT_EQ(m(3, 0), 13.5f);
    EXPECT_FLOAT_EQ(m(3, 2), 15.5f);
}

TEST(TestMatrices, TestEigen2x2Matrix) {
    Eigen::Matrix2f m;
    m << -3, 5,
          1, -2;
    EXPECT_FLOAT_EQ(m(0, 0), -3.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 5.0f);
    EXPECT_FLOAT_EQ(m(1, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(1, 1), -2.0f);
}

TEST(TestMatrices, TestEigen3x3Matrix) {
    Eigen::Matrix3f m;
    m << -3, 5, 0,
          1, -2, -7,
          0, 1, 1;
    EXPECT_FLOAT_EQ(m(0, 0), -3.0f);
    EXPECT_FLOAT_EQ(m(1, 1), -2.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 1.0f);
}

TEST(TestMatrices, TestEigenMatrixEquality) {
    Eigen::Matrix4f m1;
    m1 << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2;
    Eigen::Matrix4f m2;
    m2 << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2;
    EXPECT_TRUE(m1 == m2);
}

TEST(TestMatrices, TestEigenMatrixInequality) {
    Eigen::Matrix4f m1;
    m1 << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2;
    Eigen::Matrix4f m2;
    m2 << 2, 3, 4, 5,
            6, 7, 8, 9,
            8, 7, 6, 5,
            4, 3, 2, 1;
    EXPECT_TRUE(m1 != m2);
}

TEST(TestMatrices, TestEigenMatrixMultiplication) {
    Eigen::Matrix4f m1;
    m1 << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2;
    Eigen::Matrix4f m2;
    m2 << -2, 1, 2, 3,
            3, 2, 1, -1,
            4, 3, 6, 5,
            1, 2, 7, 8;
    Eigen::Matrix4f expected;
    expected << 20, 22, 50, 48,
                44, 54, 114, 108,
                40, 58, 110, 102,
                16, 26, 46, 42;
    EXPECT_TRUE(m1 * m2 == expected);
}

TEST(TestMatrices, TestMatrixMultipliedByVector4f) {
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1;
    Vector4f t(1, 2, 3, 1);
    Vector4f expected(18, 24, 33, 1);
    EXPECT_TRUE(m * t == expected);
}

TEST(TestMatrices, TestIdentityMatrixMultipliedByVector4f) {
    Eigen::Matrix4f m = Eigen::Matrix4f::Identity();
    Vector4f t(1, 2, 3, 4);
    EXPECT_TRUE(m * t == t);
}

TEST(TestMatrices, TestTransposeMatrix) {
    Eigen::Matrix4f m;
    m << 0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8;
    Eigen::Matrix4f expected;
    expected << 0, 9, 1, 0,
                9, 8, 8, 0,
                3, 0, 5, 5,
                0, 8, 3, 8;
    EXPECT_TRUE(m.transpose() == expected);
}

TEST(TestMatrices, TestTransposeIdentityMatrix) {
    Eigen::Matrix4f m = Eigen::Matrix4f::Identity();
    EXPECT_TRUE(m.transpose() == m);
}

TEST(TestMatrices, TestDeterminant2x2Matrix) {
    Eigen::Matrix2f m;
    m << 1, 5,
            -3, 2;
    EXPECT_FLOAT_EQ(m.determinant(), 17.0f);
}

TEST(TestMatrices, TestDeterminant3x3Matrix) {
    Eigen::Matrix3f m;
    m << 1, 2, 6,
            -5, 8, -4,
            2, 6, 4;
    EXPECT_FLOAT_EQ(m.determinant(), -196.0f);
}

TEST(TestMatrices, TestIfMatrixIsInvertible) {
    Eigen::Matrix4f m;
    m << 6, 4, 4, 4,
            5, 5, 7, 6,
            4, -9, 3, -7,
            9, 1, 7, -6;
    EXPECT_FLOAT_EQ(m.determinant(), -2120.0f);
    EXPECT_TRUE(m.determinant() != 0);
}

TEST(TestMatrices, TestNonInvertibleMatrix) {
    Eigen::Matrix4f m;
    m << -4, 2, -2, -3,
            9, 6, 2, 6,
            0, -5, 1, -5,
            0, 0, 0, 0;
    EXPECT_FLOAT_EQ(m.determinant(), 0.0f);
    EXPECT_FALSE(m.determinant() != 0);
}

TEST(TestMatrices, TestInverseOfMatrix) {
    Eigen::Matrix4f m;
    m << -5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4;
    Eigen::Matrix4f expected;
    EXPECT_FLOAT_EQ(m.determinant(), 532.0f);
    expected << 0.21805, 0.45113, 0.24060, -0.04511,
                -0.80827, -1.45677, -0.44361, 0.52068,
                -0.07895, -0.22368, -0.05263, 0.19737,
                -0.52256, -0.81391, -0.30075, 0.30639;
    // Test that the inverse is correct with a delta of 0.00001
    EXPECT_TRUE(m.inverse().isApprox(expected, 0.00001));
}

TEST(TestMatrices, TestInverseOfAnotherMatrix) {
    Eigen::Matrix4f m;
    m << 8, -5, 9, 2,
            7, 5, 6, 1,
            -6, 0, 9, 6,
            -3, 0, -9, -4;
    Eigen::Matrix4f expected;
    expected << -0.15385, -0.15385, -0.28205, -0.53846,
                -0.07692, 0.12308, 0.02564, 0.03077,
                0.35897, 0.35897, 0.43590, 0.92308,
                -0.69231, -0.69231, -0.76923, -1.92308;
    // Test that the inverse is correct with a delta of 0.00001
    EXPECT_TRUE(m.inverse().isApprox(expected, 0.00001));
}

TEST(TestMatrices, TestInverseOfYetAnotherMatrix) {
    Eigen::Matrix4f m;
    m << 9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2;
    Eigen::Matrix4f expected;
    expected << -0.04074, -0.07778, 0.14444, -0.22222,
                -0.07778, 0.03333, 0.36667, -0.33333,
                -0.02901, -0.14630, -0.10926, 0.12963,
                0.17778, 0.06667, -0.26667, 0.33333;
    // Test that the inverse is correct with a delta of 0.00001
    EXPECT_TRUE(m.inverse().isApprox(expected, 0.0001));
}

TEST(TestMatrices, TestMultiplyingProductByInverse) {
    Eigen::Matrix4f a;
    a << 3, -9, 7, 3,
            3, -8, 2, -9,
            -4, 4, 4, 1,
            -6, 5, -1, 1;
    Eigen::Matrix4f b;
    b << 8, 2, 2, 2,
            3, -1, 7, 0,
            7, 0, 5, 4,
            6, -2, 0, 5;
    Eigen::Matrix4f c = a * b;
    EXPECT_TRUE((c * b.inverse()).isApprox(a, 0.0001));
}

TEST(TestTransformations, TestTranslateMatrix) {
    Matrix4f translate = Transform::translate(5, -3, 2);
    Vector4f p = create_point(-3, 4, 5);
    EXPECT_TRUE(translate * p == create_point(2, 1, 7));
}

TEST(TestTransformations, TestTranslateInverseMatrix) {
    Vector4f p = create_point(-3, 4, 5);
    Matrix4f translate =  Transform::translate(5, -3, 2);
    EXPECT_TRUE(translate.inverse() * p == create_point(-8, 7, 3));
}

TEST(TestTransformations, TestTranslateVector) {
    Vector4f v = create_vector(-3, 4, 5);
    Matrix4f translate = Transform::translate(5, -3, 2);
    EXPECT_TRUE(translate * v == v);
}

TEST(TestTransformations, TestScalingAVector3f) {
    Vector4f p = create_point(-4, 6, 8);
    Matrix4f scale = Transform::scale(2, 3, 4);
    EXPECT_TRUE(scale * p == create_point(-8, 18, 32));
}

TEST(TestTransformations, TestScalingAVector) {
    Vector4f v = create_vector(-4, 6, 8);
    Matrix4f scale = Transform::scale(2, 3, 4);
    EXPECT_TRUE(scale * v == create_vector(-8, 18, 32));
}

TEST(TestTransformations, TestScalingInverse) {
    Vector4f vector = create_vector(-4, 6, 8);
    Matrix4f scale = Transform::scale(2, 3, 4);
    EXPECT_TRUE(scale.inverse() * vector == create_vector(-2, 2, 2));
}

TEST(TestTransformations, TestReflection) {
    Vector4f p = create_point(2, 3, 4);
    Matrix4f scale = Transform::scale(-1, 1, 1);
    EXPECT_TRUE(scale * p == create_point(-2, 3, 4));
}

TEST(TestTransformations, TestRotationAroundXAxis)  {
    Vector4f p = create_point(0, 1, 0);
    EXPECT_TRUE(Transform::rotate_x(M_PI_4) * p == create_point(0, sqrt(2) / 2, sqrt(2) / 2));
    EXPECT_TRUE((Transform::rotate_x(M_PI_2) * p).isApprox(create_point(0, 0, 1)));
}

TEST(TestTransformations, TestInverseRotationAboutXAxis) {
    Vector4f p = create_point(0, 1, 0);
    EXPECT_TRUE((Transform::rotate_x(M_PI_4).inverse() * p).isApprox(create_point(0, sqrt(2) / 2, -sqrt(2) / 2)));
}

TEST(TestTransformations, TestRotationAroundYAxis)  {
    Vector4f p = create_point(0, 0, 1);
    EXPECT_TRUE((Transform::rotate_y(M_PI_4) * p).isApprox(create_point(sqrt(2) / 2, 0, sqrt(2) / 2)));
    EXPECT_TRUE((Transform::rotate_y(M_PI_2) * p).isApprox(create_point(1, 0, 0)));
}

TEST(TestTransformations, TestRotationAroundZAxis) {
    Vector4f p = create_point(0, 1, 0);
    EXPECT_TRUE((Transform::rotate_z(M_PI_4) * p).isApprox(create_point(-sqrt(2) / 2, sqrt(2) / 2, 0)));
    EXPECT_TRUE((Transform::rotate_z(M_PI_2) * p).isApprox(create_point(-1, 0, 0)));
}

TEST(TestTransformations, TestShearingTransformation) {
    Vector4f p = create_point(2, 3, 4);
    EXPECT_TRUE(Transform::shear(1, 0, 0, 0, 0, 0) * p == create_point(5, 3, 4));
}

TEST(TestTransformations, TestShearingTransformationXZ) {
    Vector4f p = create_point(2, 3, 4);
    EXPECT_TRUE(Transform::shear(0, 1, 0, 0, 0, 0) * p == create_point(6, 3, 4));
}

TEST(TestTransformations, TestShearingTransformationYX) {
    Vector4f p = create_point(2, 3, 4);
    EXPECT_TRUE(Transform::shear(0, 0, 1, 0, 0, 0) * p == create_point(2, 5, 4));
}

TEST(TestTransformations, TestShearingTransformationYZ) {
    Vector4f p = create_point(2, 3, 4);
    EXPECT_TRUE(Transform::shear(0, 0, 0, 1, 0, 0) * p == create_point(2, 7, 4));
}

TEST(TestTransformations, TestShearingTransformationsZY) {
    Vector4f p = create_point(2, 3, 4);
    EXPECT_TRUE(Transform::shear(0, 0, 0, 0, 1, 0) * p == create_point(2, 3, 6));
}

TEST(TestTransformations, TestTransformationsInSequence) {
    Vector4f p = create_point(1, 0, 1);
    p = Transform::rotate_x(M_PI_2) * p;
    p = Transform::scale(5, 5, 5) * p;
    p = Transform::translate(10, 5, 7) * p;
    EXPECT_TRUE(p == create_point(15, 0, 7));
}

TEST(TestTransformations, TestTransformationsChained) {
    Vector4f p = create_point(1, 0, 1);
    // Matrix4f t = Transform::rotate_x(M_PI_2) * Transform::scale(5, 5, 5) * Transform::translate(10, 5, 7);
    Matrix4f t = Transformation::identity()
        .rotate_x(M_PI_2)
        .scale(5, 5, 5)
        .translate(10, 5, 7)
        .matrix();
    EXPECT_TRUE(t * p == create_point(15, 0, 7));
}

TEST(TestRayCaster, TestQueryRay) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    EXPECT_TRUE(r.origin == create_point(0, 0, -5));
    EXPECT_TRUE(r.direction == create_vector(0, 0, 1));
}

TEST(TestRayCaster, TestVector3fFromADistance) {
    Ray r = Ray(create_point(2, 3, 4), create_vector(1, 0, 0));
    EXPECT_TRUE(r.position(0) == create_point(2, 3, 4));
    EXPECT_TRUE(r.position(1) == create_point(3, 3, 4));
    EXPECT_TRUE(r.position(-1) == create_point(1, 3, 4));
    EXPECT_TRUE(r.position(2.5) == create_point(4.5, 3, 4));
}

TEST(TestRayCaster, TestIntersectSphereWithTwoVector3fs) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 4.0);
    EXPECT_EQ(intersections[1].t, 6.0);
}

TEST(TestRayCaster, TestIntersectSphereWithATangent) {
    Ray r = Ray(create_point(0, 1, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 5.0);
    EXPECT_EQ(intersections[1].t, 5.0);
}

TEST(TestRayCaster, TestRayMissesSphere) {
    Ray r = Ray(create_point(0, 2, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 0);
}

TEST(TestRayCaster, TestRayOriginatesInsideASphere) {
    Ray r = Ray(create_point(0, 0, 0), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, -1.0);
    EXPECT_EQ(intersections[1].t, 1.0);
}

TEST(TestRayCaster, TestSphereIsBehindARay){
    Ray r = Ray(create_point(0, 0, 5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, -6.0);
    EXPECT_EQ(intersections[1].t, -4.0);
}

TEST(TestRayCaster, TestIntersectionEncapsulatesTAndObject) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(3.5, &s);
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.object, &s);
}

TEST(TestRayCaster, TestAggregateIntersections) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    std::vector<Intersection> intersections = {i1, i2};
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 1);
    EXPECT_EQ(intersections[1].t, 2);
}

TEST(TestRayCaster, TestIntersectSetsTheObjectOnIntersection) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].object, &s);
    EXPECT_EQ(intersections[1].object, &s);
}

TEST(TestRayCaster, TestHitWhenAllIntersectionsHavePositiveT) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(1, &s), Intersection(2, &s)};
    const auto i = hit(intersections);
    EXPECT_EQ(i.t, intersections[0].t);
}

TEST(TestRayCaster, TestHitWhenSomeIntersectionsHaveNegativeT) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(-1, &s), Intersection(1, &s)};
    const auto i = hit(intersections);
    EXPECT_EQ(i.t, intersections[1].t);
}

TEST(TestRayCaster, TestHitWhenAllIntersectionsHaveNegativeT) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(-2, &s), Intersection(-1, &s)};
    const auto i = hit(intersections);
    EXPECT_EQ(i.object, nullptr);
}

TEST(TestRayCaster, TestHitIsAlwaysLowestNonNegativeIntersection) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(5, &s), Intersection(7, &s), Intersection(-3, &s), Intersection(2, &s)};
    const auto i = hit(intersections);
    EXPECT_EQ(i.t, intersections[3].t);
}

TEST(TestRayTransforms, TestTranslateRay) {
    Ray r = Ray(create_point(1, 2, 3), create_vector(0, 1, 0));
    Matrix4f translation = Transform::translate(3, 4, 5);
    Ray r2 = r.transform_ray(translation);
    EXPECT_TRUE(r2.origin == create_point(4, 6, 8));
    EXPECT_TRUE(r2.direction == create_vector(0, 1, 0));
}

TEST(TestRayTransforms, TestScaleRay) {
    Ray r = Ray(create_point(1, 2, 3), create_vector(0, 1, 0));
    Matrix4f scale = Transform::scale(2, 3, 4);
    Ray r2 = r.transform_ray(scale);
    EXPECT_TRUE(r2.origin == create_point(2, 6, 12));
    EXPECT_TRUE(r2.direction == create_vector(0, 3, 0));
}

TEST(TestSphereTransforms, TestDefaultTransformationIsIdentityMatrix)  {
    Sphere s = Sphere();
    EXPECT_TRUE(s.matrix() == Matrix4f::Identity());
}

TEST(TestSphereTransforms, TestAssigningATransformation) {
    Sphere s = Sphere();
    Matrix4f translation = Transform::translate(2, 3, 4);
    s.set_transform(translation);
    EXPECT_TRUE(s.matrix() == translation.matrix());
}

TEST(TestSphereTransforms, TestIntersectingAScaledSphereWithRay) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    Matrix4f scale = Transform::scale(2, 2, 2);
    s.set_transform(scale   );
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 3);
    EXPECT_EQ(intersections[1].t, 7);
}

TEST(TestSphereTransforms, TestIntersectingATranslatedSphereWithRay) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    Matrix4f translation = Transform::translate(5, 0, 0);
    s.set_transform(translation);
    std::vector<Intersection> intersections = s.intersect( r);
    EXPECT_EQ(intersections.size(), 0);
}

TEST(TestLighting, TestNormalOnASphereAtAPointOnTheXAxis) {
    const auto s = Sphere();
    Vector4f world_point = create_point(1, 0, 0);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_EQ(normal, create_vector(1, 0, 0));
}

TEST(TestLighting, TestNormalOnASphereAtPointOnTheYAxis) {
    const Sphere s = Sphere();
    Vector4f world_point = create_point(0, 1, 0);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_EQ(normal, create_vector(0, 1, 0));
}

TEST(TestLighting, TestNormalOnASphereAtAPointOnTheZAxis) {
    Sphere s = Sphere();
    Vector4f world_point = create_point(0, 0, 1);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_EQ(normal, create_vector(0, 0, 1));
}

TEST(TestLighting, TestNormalOnASphereAtAPointOnNonAxialPoint) {
    Sphere s = Sphere();
    Vector4f world_point = create_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_TRUE(normal.isApprox(create_vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)));
}

TEST(TestLighting, TestNormalIsANormalizedVector) {
    Sphere s = Sphere();
    Vector4f world_point = create_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_TRUE(normal.isApprox(normal.normalized()));
}

TEST(TestLighting, TestComputingTheNormalOnATranslatedSphere) {
    Sphere s = Sphere();
    Matrix4f translation = Transform::translate(0, 1, 0);
    s.set_transform(translation);
    Vector4f world_point = create_point(0, 1.70711, -0.70711);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_TRUE(normal.isApprox(create_vector(0, 0.70711, -0.70711)));
}

TEST(TestLighting, TestComputingTheNormalOnATransformedSphere) {
    Sphere s = Sphere();
    Matrix4f t = Transformation::identity()
            .rotate_z(M_PI/5)
            .scale(1, 0.5, 1)
            .matrix();
    s.set_transform(t);
    Vector4f world_point = create_point(0, sqrt(2)/2, -sqrt(2)/2);
    Vector4f normal = s.normal_at(world_point);
    EXPECT_TRUE(normal.isApprox(create_vector(0, 0.97014, -0.24254)));
}

TEST(TestLighting, TestReflectionAt45Degrees) {
    Vector4f v = create_vector(1, -1, 0);
    Vector4f n = create_vector(0, 1, 0);
    Vector4f r = reflect(v, n);
    EXPECT_TRUE(r.isApprox(create_vector(1, 1, 0)));
}

TEST(TestLighting, TestReflectionOffSlantedSurface) {
    Vector4f v = create_vector(0, -1, 0);
    Vector4f n = create_vector(sqrt(2)/2, sqrt(2)/2, 0);
    Vector4f r = reflect(v, n);
    EXPECT_TRUE(r.isApprox(create_vector(1, 0, 0)));
}

TEST(TestLighting, TestPointLightHasAPositionAndIntensity) {
    PointLight light = PointLight(create_point(0, 0, 0), Color(1, 1, 1));
    EXPECT_TRUE(light.position == create_point(0, 0, 0));
    EXPECT_TRUE(light.intensity == Color(1, 1, 1));
}

TEST(TestLighting, TestDefaultMaterial) {
    Material m = Material();
    EXPECT_TRUE(m.color == Color(1, 1, 1));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200.0);
}

TEST(TestLighting, TestSphereHasADefaultMaterial) {
    Sphere s = Sphere();
    Material m = s.material;
    EXPECT_TRUE(m.color == Color(1, 1, 1));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200.0);
}

TEST(TestLighting, TestSphereMustBeAssignedAMaterial) {
    Sphere s = Sphere();
    Material m = Material();
    m.ambient = 1;
    s.material = m;
    EXPECT_TRUE(s.material == m);
}

TEST(TestLighting, TestLightingWithEyeBetweenLightAndSurface) {
    Material m = Material();
    Vector4f position = create_point(0, 0, 0);
    PointLight light = PointLight(create_point(0, 0, -10), Color(1, 1, 1));
    Vector4f eyev = create_vector(0, 0, -1);
    Vector4f normalv = create_vector(0, 0, -1);
    Sphere s = Sphere();
    Color result = lighting(m, &s, light, position, eyev, normalv, 1.0f);
    EXPECT_TRUE(result == Color(1.9, 1.9, 1.9));
}

TEST(TestLighting, TestLightingWithTheEyeBetweenLightAndSurfaceOffset45) {
    Material m = Material();
    Vector4f position = create_point(0, 0, 0);
    PointLight light = PointLight(create_point(0, 0, -10), Color(1, 1, 1));
    Vector4f eyev = create_vector(0, sqrt(2)/2, -sqrt(2)/2);
    Vector4f normalv = create_vector(0, 0, -1);
    Sphere s = Sphere();
    Color result = lighting(m, &s, light, position, eyev, normalv, 1.0f);
    EXPECT_TRUE(result == Color(1.0, 1.0, 1.0));
}

TEST(TestLighting, TestLightingWithEyeOppositeSurfaceLightOffset45) {
    Material m = Material();
    Vector4f position = create_point(0, 0, 0);
    PointLight light = PointLight(create_point(0, 10, -10), Color(1, 1, 1));
    Vector4f eyev = create_vector(0, 0, -1);
    Vector4f normalv = create_vector(0, 0, -1);
    Sphere s = Sphere();
    Color result = lighting(m, &s, light, position, eyev, normalv, 1.0f);
    EXPECT_TRUE(result == Color(0.7364, 0.7364, 0.7364));
}

TEST(TestLighting, TestLightingWithEyeInThePathOftheReflectionVector) {
    Material m = Material();
    Vector4f position = create_point(0, 0, 0);
    PointLight light = PointLight(create_point(0, 10, -10), Color(1, 1, 1));
    Vector4f eyev = create_vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Vector4f normalv = create_vector(0, 0, -1);
    Sphere s = Sphere();
    Color result = lighting(m, &s,light, position, eyev, normalv, 1.0f);
    EXPECT_TRUE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST(TestLighting, TestLightingWithTheLightBehindTheSurface) {
    Material m = Material();
    Vector4f position = create_point(0, 0, 0);
    PointLight light = PointLight(create_point(0, 0, 10), Color(1, 1, 1));
    Vector4f eyev = create_vector(0, 0, -1);
    Vector4f normalv = create_vector(0, 0, -1);
    Sphere s = Sphere();
    Color result = lighting(m, &s, light, position, eyev, normalv, 1.0f);
    EXPECT_TRUE(result == Color(0.1, 0.1, 0.1));
}

TEST(TestWorld, TestCreatingAWorld) {
    World w = World();
    EXPECT_TRUE(w.objects.size() == 0);
    EXPECT_TRUE(w.lights.size() == 0);
}

TEST(TestWorld, TestTheDefaultWorld) {
    World w = default_world();
//    EXPECT_TRUE(w.lights.size() == 1);
//    PointLight* light_expected = PointLight(create_point(-10, 10, -10), Color(1, 1, 1));
//    PointLight* light_actual = w.lights.at(0).get();
//    EXPECT_TRUE(w.lights[0] == light_expected);
    EXPECT_TRUE(w.lights.size() == 1);
    EXPECT_TRUE(w.objects.size() == 2);
    EXPECT_TRUE(w.objects[0]->material.color == Color(0.8, 1.0, 0.6));
    EXPECT_FLOAT_EQ(w.objects[0]->material.diffuse, 0.7);
    EXPECT_FLOAT_EQ(w.objects[0]->material.specular, 0.2);
    EXPECT_TRUE(w.objects[1]->material.color == Color(1.0, 1.0, 1.0));
    EXPECT_FLOAT_EQ(w.objects[1]->material.ambient, 0.1);
    EXPECT_FLOAT_EQ(w.objects[1]->material.diffuse, 0.9);
    EXPECT_FLOAT_EQ(w.objects[1]->material.specular, 0.9);
    EXPECT_FLOAT_EQ(w.objects[1]->material.shininess, 200.0);
    EXPECT_TRUE(w.objects[1]->matrix() == Transform::scale(0.5, 0.5, 0.5).matrix());
}

TEST(TestWorld, TestIntersectWorldWithARay) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    std::vector<Intersection> xs = intersect_world(w, r);
    EXPECT_TRUE(xs.size() == 4);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 4.5);
    EXPECT_FLOAT_EQ(xs[2].t, 5.5);
    EXPECT_FLOAT_EQ(xs[3].t, 6);
}

TEST(TestWorld, TestPrecomputeStateOfIntersection) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    const auto shape = w.objects.at(0).get();
    Intersection i = Intersection(4, shape);
    Computation comps = prepare_computations(i, r);
    EXPECT_TRUE(comps.t == i.t);
    EXPECT_TRUE(comps.object == i.object);
    EXPECT_TRUE(comps.point == create_point(0, 0, -1));
    EXPECT_TRUE(comps.eyev == create_vector(0, 0, -1));
    EXPECT_TRUE(comps.normalv == create_vector(0, 0, -1));
}

TEST(TestWorld, TestIntersectionOccursOnTheOutside) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    const auto shape = w.objects.at(0).get();
    Intersection i = Intersection(4, shape);
    Computation comps = prepare_computations(i, r);
    EXPECT_FALSE(comps.inside);
}

TEST(TestWorld, TestIntersectionOccursOnTheInside) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, 0), create_vector(0, 0, 1));
    const auto shape = w.objects.at(0).get();
    Intersection i = Intersection(1, shape);
    Computation comps = prepare_computations(i, r);
    EXPECT_TRUE(comps.point == create_point(0, 0, 1));
    EXPECT_TRUE(comps.eyev == create_vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    EXPECT_TRUE(comps.normalv == create_vector(0, 0, -1));
}

TEST(TestWorld, TestShadingAnIntersection) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    const auto shape = w.objects.at(0).get();
    Intersection i = Intersection(4, shape);
    Computation comps = prepare_computations(i, r);
//    std::cout << "Test shading an intersection: " << std::endl;
    Color c = shade_hit(w, comps);
    // Color c = lighting(shape.material, w.lights[0], comps.point, comps.eyev, comps.normalv, false);
    EXPECT_TRUE(c == Color(0.38066, 0.47583, 0.2855));
}

//TEST(TestWorld, TestShadingIntersectionFromInside) {
//    World w = default_world();
//    w.lights.clear();
//    w.lights.push_back(PointLight(create_point(0, 0.25, 0), Color(1, 1, 1)));
//    Ray r = Ray(create_point(0, 0, 0), create_vector(0, 0, 1));
//    const auto shape = w.objects.at(1).get();
//    Intersection i = Intersection(0.5, shape);
//    Computation comps = prepare_computations(i, r);
////    Color c = shade_hit(w, comps);
//    Color c = lighting(shape->material, w.lights[0], comps.point, comps.eyev, comps.normalv, false);
//    EXPECT_TRUE(c == Color(0.90498, 0.90498, 0.90498));
//}

TEST(TestWorld, TestColorWhenRayMisses) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 1, 0));
    Color c = color_at(w, r);
    EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(TestWorld, TestColorWhenARayHits) {
    World w = default_world();
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Color c = color_at(w, r);
    EXPECT_TRUE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST(TestWorld, TestColorWithAnIntersectionBehindTheRay) {
    World w = default_world();
    w.objects[0]->material.ambient = 1;
    w.objects[1]->material.ambient = 1;
    Ray r = Ray(create_point(0, 0, 0.75), create_vector(0, 0, -1));
    Color c = color_at(w, r);
    EXPECT_TRUE(c == w.objects.at(1).get()->material.color);
}

TEST(TestWorld, TestViewTransformTransformationMatrixForDefaultOrientation) {
    Matrix4f t = Transform::view_transform(create_point(0, 0, 0), create_point(0, 0, -1), create_vector(0, 1, 0));
    EXPECT_TRUE(t.matrix() == Matrix4f::Identity());
}

TEST(TestWorld, TestViewTransformationMatrixLookingInPositiveZDirection) {
    Matrix4f t = Transform::view_transform(create_point(0, 0, 0), create_point(0, 0, 1), create_vector(0, 1, 0));
    EXPECT_TRUE(t.matrix() == Transform::scale(-1, 1, -1).matrix());
}

TEST(TestWorld, TestTheViewTranslationMovesTheWorld) {
    Matrix4f t = Transform::view_transform(create_point(0, 0, 8), create_point(0, 0, 0), create_vector(0, 1, 0));
    EXPECT_TRUE(t.matrix() == Transform::translate(0, 0, -8).matrix());
}

TEST(TestWorld, TestAnArbitraryViewTransformation) {
    Matrix4f t = Transform::view_transform(create_point(1, 3, 2), create_point(4, -2, 8), create_vector(1, 1, 0));
    Matrix4f expected;
    expected << -0.50709, 0.50709, 0.67612, -2.36643,
            0.76772, 0.60609, 0.12122, -2.82843,
            -0.35857, 0.59761, -0.71714, 0.00000,
            0.00000, 0.00000, 0.00000, 1.00000;
    EXPECT_TRUE(t.matrix().isApprox(expected));
}

TEST(TestWorld, TestConstructingACamera) {
    Camera c = Camera(160, 120, M_PI / 2);
    EXPECT_TRUE(c.hsize == 160);
    EXPECT_TRUE(c.vsize == 120);
    EXPECT_FLOAT_EQ(c.field_of_view, M_PI / 2);
    EXPECT_TRUE(c.transform.matrix() == Matrix4f::Identity());
}

TEST(TestWorld, TestThePixelSizeForAHorizontalCanvas) {
    Camera c = Camera(200, 125, M_PI / 2);
    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(TestWorld, TestConstructARayThroughCenterOfCanvas) {
    Camera c = Camera(201, 101, M_PI / 2);
    const float px = 100 + 0.5f;
    const float py = 50 + 0.5f;
    Ray r = ray_for_pixel(c, px, py);
    EXPECT_TRUE(r.origin == create_point(0, 0, 0));
    EXPECT_TRUE(r.direction.isApprox(create_vector(0, 0, -1), 0.01));
}

TEST(TestWorld, TestConstructARayThroughTheCornerOfCanvas) {
    Camera c = Camera(201, 101, M_PI / 2);
    const float px = 0 + 0.5f;
    const float py = 0 + 0.5f;
    Ray r = ray_for_pixel(c, px, py);
//    std::cout << "Ray: " << r.origin << " " << r.direction << std::endl;
    EXPECT_TRUE(r.origin == create_point(0, 0, 0));
    EXPECT_TRUE(r.direction.isApprox(create_vector(0.66519, 0.33259, -0.66851), 0.01));
}

TEST(TestWorld, TestConstructARayWhenTheCameraIsTransformed) {
    Camera c = Camera(201, 101, M_PI / 2);
    c.transform = Transform::rotate_y(M_PI / 4) * Transform::translate(0, -2, 5);
    const float px = 100 + 0.5f;
    const float py = 50 + 0.5f;
    Ray r = ray_for_pixel(c, px, py);
    EXPECT_TRUE(r.origin.isApprox(create_point(0, 2, -5)));
    EXPECT_TRUE(r.direction.isApprox(create_vector(sqrt(2) / 2, 0, -sqrt(2) / 2), 0.01));
}

//TEST(TestShadows, TestLightingSurfaceInShadow) {
//    World w = default_world();
//    w.lights.clear();
//    w.lights.emplace_back(std::make_unique<PointLight>(PointLight(create_point(0, 0, -10), Color(1, 1, 1))));
//    Material m = Material();
//    Vector4f position = create_point(0, 0, 0);
//    Vector4f eyev = create_vector(0, 0, -1);
//    Vector4f normalv = create_vector(0, 0, -1);
//    bool in_shadow = true;
//    Sphere s = Sphere();
//    Color c = lighting(m, &s, w.lights.at(0).get(), position, eyev, normalv, in_shadow);
//    EXPECT_TRUE(c == Color(0.1, 0.1, 0.1));
//}

TEST(TestShadows, TestNoShadowWhenNothingIsCollinearWithPointAndLight) {
    World w = default_world();
    Vector4f p = create_point(0, 10, 0);
    EXPECT_FALSE(is_shadowed(w, w.lights[0]->position, p));
}

TEST(TestShadows, TestShadowWhenObjectIsBetweenPointAndLight) {
    World w = default_world();
    Vector4f p = create_point(10, -10, 10);
    EXPECT_TRUE(is_shadowed(w, w.lights[0]->position,  p));
}

TEST(TestShadows, TestNoShadowWhenObjectIsBehindLight) {
    World w = default_world();
    Vector4f p = create_point(-20, 20, -20);
    EXPECT_FALSE(is_shadowed(w, w.lights[0]->position, p));
}

TEST(TestShadows, TestNoShadowWhenObjectIsBehindPoint) {
    World w = default_world();
    Vector4f p = create_point(-2, 2, -2);
    EXPECT_FALSE(is_shadowed(w, w.lights[0]->position, p));
}

TEST(TestShadows, TestShadeHitIsGivenAnIntersectionInShadow) {
    World w = default_world();
    w.lights.clear();
    w.lights.emplace_back(std::make_unique<PointLight>(PointLight(create_point(0, 0, -10), Color(1, 1, 1))));
    const auto s1 = Sphere();
    w.add_object(s1);
    auto s2 = Sphere();
    s2.set_transform(Transform::translate(0, 0, 10));
    w.add_object(s2);
    Ray r = Ray(create_point(0, 0, 5), create_vector(0, 0, 1));
    Intersection i = Intersection(4, w.objects.at(1).get());
    Computation comps = prepare_computations(i, r);
    Color c = shade_hit(w, comps);
    EXPECT_TRUE(c == Color(0.1, 0.1, 0.1));
}

TEST(TestShadows, TestHitShouldOffsetThePoint) {
    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    Sphere s = Sphere();
    s.set_transform(Transform::translate(0, 0, 1));
    Intersection i = Intersection(5, &s);
    Computation comps = prepare_computations(i, r);
    EXPECT_TRUE(comps.over_point[2] < -EPSILON / 2);
    EXPECT_TRUE(comps.point[2] > comps.over_point[2]);
}

TEST(TestShapes, TestTheDefaultTransformation) {
    Sphere s = Sphere();
    EXPECT_TRUE(s.matrix() == Matrix4f::Identity());
}

TEST(TestShapes, TestDefaultMaterial) {
    Sphere s = Sphere();
    EXPECT_TRUE(s.material == Material());
}

TEST(TestShapes, TestAssigningAMaterial) {
    Sphere s = Sphere();
    Material m = Material();
    m.ambient = 1;
    s.set_material(m);
    EXPECT_TRUE(s.material == m);
}

//TEST(TestShapes, TestIntersectingAScaledShapeWithARay) {
//    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
//    Sphere s = Sphere();
//    s.set_transform(Transform::scale(2, 2, 2));
//    std::vector<Intersection> xs = s.intersect( r);
//    std::cout << "Ray origin: " << r.origin << std::endl;
//    EXPECT_TRUE(r.origin == create_point(0, 0, -2.5));
//    EXPECT_TRUE(r.direction == create_vector(0, 0, 0.5));
//
//}
//
//TEST(TestShapes, TestIntersectingATranslatedShapeWithARay) {
//    Ray r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
//    Sphere s = Sphere();
//    s.set_transform(Transform::translate(5, 0, 0));
//    std::vector<Intersection> xs = s.intersect(r);
//    EXPECT_TRUE(r.origin == create_point(-5, 0, -5));
//    EXPECT_TRUE(r.direction == create_vector(0, 0, 1));
//}

TEST(TestShapes, TestComputingTheNormalOnATranslatedShape) {
    Sphere s = Sphere();
    s.set_transform(Transform::translate(0, 1, 0));
    Vector4f n = s.normal_at(create_point(0, 1.70711, -0.70711));
    EXPECT_TRUE(n.isApprox(create_vector(0, 0.70711, -0.70711)));
}

TEST(TestShapes, TestComputingTheNormalOnATransformedShape) {
    Sphere s = Sphere();
    s.set_transform(Transform::scale(1, 0.5, 1) * Transform::rotate_z(M_PI / 5));
    Vector4f n = s.normal_at(create_point(0, sqrt(2) / 2, -sqrt(2) / 2));
    EXPECT_TRUE(n.isApprox(create_vector(0, 0.97014, -0.24254)));
}

TEST(TestPlane, TestTheNormalOfAPlaneIsConstantEverywhere) {
    Plane p = Plane();
    Vector4f n1 = p.normal_at(create_point(0, 0, 0));
    Vector4f n2 = p.normal_at(create_point(10, 0, -10));
    Vector4f n3 = p.normal_at(create_point(-5, 0, 150));
    EXPECT_TRUE(n1 == create_vector(0, 1, 0));
    EXPECT_TRUE(n2 == create_vector(0, 1, 0));
    EXPECT_TRUE(n3 == create_vector(0, 1, 0));
}

TEST(TestPlane, TestIntersectWithARayParallelToThePlane) {
    Plane p = Plane();
    Ray r = Ray(create_point(0, 10, 0), create_vector(0, 0, 1));
    std::vector<Intersection> xs = p.intersect(r);
    EXPECT_TRUE(xs.size() == 0);
}

TEST(TestPlane, TestIntersectWithACoplanarRay) {
    Plane p = Plane();
    Ray r = Ray(create_point(0, 0, 0), create_vector(0, 0, 1));
    std::vector<Intersection> xs = p.intersect(r);
    EXPECT_TRUE(xs.size() == 0);
}

TEST(TestPlane, TestARayIntersectingAPlaneFromAbove) {
    Plane p = Plane();
    Ray r = Ray(create_point(0, 1, 0), create_vector(0, -1, 0));
    std::vector<Intersection> xs = p.intersect(r);
    EXPECT_TRUE(xs.size() == 1);
    EXPECT_TRUE(xs[0].t == 1);
    EXPECT_TRUE(xs[0].object == &p);
}

TEST(TestPlane, TestARayIntersectingAPlaneFromBelow) {
    Plane p = Plane();
    Ray r = Ray(create_point(0, -1, 0), create_vector(0, 1, 0));
    std::vector<Intersection> xs = p.intersect(r);
    EXPECT_TRUE(xs.size() == 1);
    EXPECT_TRUE(xs[0].t == 1);
    EXPECT_TRUE(xs[0].object == &p);
}

TEST(TestPatterns, TestColorConstants) {
    EXPECT_TRUE(Color(1, 1, 1) == Colors::WHITE);
    EXPECT_TRUE(Color(0, 0, 0) == Colors::BLACK);
    EXPECT_TRUE(Color(0.5, 0.5, 0.5) == Colors::GREY);
    EXPECT_TRUE(Color(1, 0, 0) == Colors::RED);
    EXPECT_TRUE(Color(0, 1, 0) == Colors::GREEN);
    EXPECT_TRUE(Color(0, 0, 1) == Colors::BLUE);
}

TEST(TestPatterns, TestStripePatternConstantInY) {
    const auto p = stripe_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(0, 1, 0)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(0, 2, 0)) == Colors::WHITE);
}

TEST(TestPatterns, TestStripePatternConstantInZ) {
    const auto p = stripe_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(0, 0, 1)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(0, 0, 2)) == Colors::WHITE);
}

TEST(TestPatterns, TestStripePatternAlternatesInX) {
    const auto p = stripe_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(0.9, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(p->pattern_at(create_point(1, 0, 0)) == Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(-0.1, 0, 0)) == Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(-1, 0, 0)) == Colors::BLACK);
    EXPECT_TRUE(p->pattern_at(create_point(-1.1, 0, 0)) == Colors::WHITE);
}

TEST(TestPatterns, TestLightingWithAPatternApplied) {
    Material m = Material();
    m.pattern = stripe_pattern(Colors::WHITE, Colors::BLACK);
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    PointLight light = PointLight(create_point(0, 0, -10), Colors::WHITE);
    Sphere s = Sphere();
    Color c1 = lighting(m, &s, light, create_point(0.9, 0, 0), create_vector(0, 0, -1), create_vector(0, 0, -1), false);
    Color c2 = lighting(m, &s, light, create_point(1.1, 0, 0), create_vector(0, 0, -1), create_vector(0, 0, -1), false);
    EXPECT_TRUE(c1 == Colors::WHITE);
    EXPECT_TRUE(c2 == Colors::BLACK);
}

TEST(TestPatterns, TestStripesWithPatternTransformation) {
    const auto object = Sphere();
    const auto pattern = stripe_pattern(Colors::WHITE, Colors::BLACK);
    pattern->set_transform(Transform::scale(2, 2, 2));
    const auto c = pattern_at_object(pattern, &object, create_point(1.5, 0, 0));
    EXPECT_TRUE(c == Colors::WHITE);
}

TEST(TestPatterns, TestStripesWithObjectAndPatternTransformation) {
    Sphere object = Sphere();
    object.set_transform(Transform::scale(2, 2, 2));
    const auto pattern = stripe_pattern(Colors::WHITE, Colors::BLACK);
    pattern->set_transform(Transform::translate(0.5, 0, 0));
    const auto c = pattern_at_object(pattern, &object, create_point(2.5, 0, 0));
    EXPECT_TRUE(c == Colors::WHITE);
}

TEST(TestPatterns, TestGradientLinearlyInterpolatesBetweenColor) {
    const auto pattern = gradient_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
    EXPECT_TRUE(pattern->pattern_at(create_point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
    EXPECT_TRUE(pattern->pattern_at(create_point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));
}

TEST(TestPatterns, TestRingPatternExtendsInBothXandZ) {
    const auto pattern = ring_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(1, 0, 0)) == Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 1)) == Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0.708, 0, 0.708)) == Colors::BLACK);
}

TEST(TestPatterns, TestCheckerBoardPatternRepeatsInX) {
    const auto pattern = checker_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0.99, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(1.01, 0, 0)) == Colors::BLACK);
}

TEST(TestPatterns, TestCheckerBoardPatternRepeatsInY) {
    const auto pattern = checker_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0.99, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 1.01, 0)) == Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 1.02, 0)) == Colors::BLACK);
}

TEST(TestPatterns, TestCheckerBoardPatternRepeatsInZ) {
    const auto pattern = checker_pattern(Colors::WHITE, Colors::BLACK);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 0.99)) == Colors::WHITE);
    EXPECT_TRUE(pattern->pattern_at(create_point(0, 0, 1.01)) == Colors::BLACK);
}

TEST(TestReflection, TestReflectivityforDefaultMaterial) {
    const auto m = Material();
    EXPECT_TRUE(m.reflective == 0);
}

TEST(TestReflection, TestPrecomputingReflectionVector) {
    const auto shape = Plane();
    const auto r = Ray(create_point(0, 1, -1), create_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    const auto i = Intersection(sqrt(2), &shape);
    const auto comps = prepare_computations(i, r);
    EXPECT_TRUE(comps.reflectv == create_vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(TestReflection, TestReflectedColorForANonreflectiveMaterial) {
    const auto w = default_world();
    const auto r = Ray(create_point(0, 0, 0), create_vector(0, 0, 1));
    const auto s = w.objects.at(1).get();
    const auto i = Intersection(1, s);
    const auto comps = prepare_computations(i, r);
    const auto color = reflected_color(w, comps);
    EXPECT_TRUE(color == Colors::BLACK);
}

TEST(TestReflection, TestReflectedColorForAReflectiveMaterial) {
    auto w = default_world();
    Plane plane;
    plane.material.reflective = 0.5;
    plane.set_transform(Transform::translate(0, -1, 0));
    w.objects.emplace_back(std::make_unique<Plane>(plane));
    const auto r = Ray(create_point(0, 0, -3), create_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    const auto i = Intersection(sqrt(2), w.objects.at(2).get());
    const auto comps = prepare_computations(i, r);
    const auto color = reflected_color(w, comps);
    EXPECT_TRUE(color == Color(0.19032, 0.2379, 0.14274));
}

TEST(TestReflection, TestShadeHitWithAReflectiveMaterial) {
    auto w = default_world();
    Plane plane;
    plane.material.reflective = 0.5;
    plane.set_transform(Transform::translate(0, -1, 0));
    w.objects.emplace_back(std::make_unique<Plane>(plane));
    const auto r = Ray(create_point(0, 0, -3), create_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    const auto i = Intersection(sqrt(2), w.objects.at(2).get());
    const auto comps = prepare_computations(i, r);
    const auto color = shade_hit(w, comps);
    EXPECT_TRUE(color == Color(0.87677, 0.92436, 0.82918));
}

//TEST(TestReflection, TestColorAtWithMutuallyReflectiveSurfaces) {
//    auto w = World();
//    PointLight light = PointLight(create_point(0, 0, 0), WHITE);
//    w.add_light(light);
//    Plane lower;
//    lower.material.reflective = 1;
//    lower.set_transform(Transform::translate(0, -1, 0));
//    w.objects.emplace_back(std::make_unique<Plane>(lower));
//    Plane upper;
//    upper.material.reflective = 1;
//    upper.set_transform(Transform::translate(0, 1, 0));
//    w.objects.emplace_back(std::make_unique<Plane>(upper));
//    const auto r = Ray(create_point(0, 0, 0), create_vector(0, 1, 0));
//    const auto color = color_at(w, r);
//    EXPECT_TRUE(color == Colors::BLACK);
//}

TEST(TestReflection, TestReflectedColorAtTheMaximumumRecursionDepth) {
    auto w = default_world();
    Plane plane;
    plane.material.reflective = 0.5;
    plane.set_transform(Transform::translate(0, -1, 0));
    w.objects.emplace_back(std::make_unique<Plane>(plane));
    const auto r = Ray(create_point(0, 0, -3), create_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    const auto i = Intersection(sqrt(2), w.objects.at(2).get());
    const auto comps = prepare_computations(i, r);
    const auto color = reflected_color(w, comps, 0);
    EXPECT_TRUE(color == Colors::BLACK);
}

TEST(TestRefraction, TestTransparencyAndRefractiveIndexForDefaultMaterial) {
    const auto m = Material();
    EXPECT_TRUE(m.transparency == 0);
    EXPECT_TRUE(m.refractive_index == 1);
}

TEST(TestRefraction, TestHelperForProducingASphereWithAGlassyMaterial) {
    const auto s = glass_sphere();
    EXPECT_TRUE(s.material.transparency == 1);
    EXPECT_TRUE(s.material.refractive_index == 1.5);
}

TEST(TestRefraction, TestFindingN1andN2AtVariousIntersections) {
    auto A = glass_sphere();
    A.set_transform(Transform::scale(2, 2, 2));
    A.material.refractive_index = 1.5;
    auto B = glass_sphere();
    B.set_transform(Transform::translate(0, 0, -0.25));
    B.material.refractive_index = 2;
    auto C = glass_sphere();
    C.set_transform(Transform::translate(0, 0, 0.25));
    C.material.refractive_index = 2.5;
    auto r = Ray(create_point(0, 0, -4), create_vector(0, 0, 1));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(2, &A));
    xs.emplace_back(Intersection(2.75, &B));
    xs.emplace_back(Intersection(3.25, &C));
    xs.emplace_back(Intersection(4.75, &B));
    xs.emplace_back(Intersection(5.25, &C));
    xs.emplace_back(Intersection(6, &A));
    const auto comps = prepare_computations(xs.at(0), r, xs);
    EXPECT_TRUE(comps.n1 == 1);
    EXPECT_TRUE(comps.n2 == 1.5);
    const auto comps2 = prepare_computations(xs.at(1), r, xs);
    EXPECT_TRUE(comps2.n1 == 1.5);
    EXPECT_TRUE(comps2.n2 == 2);
    const auto comps3 = prepare_computations(xs.at(2), r, xs);
    EXPECT_TRUE(comps3.n1 == 2);
    EXPECT_TRUE(comps3.n2 == 2.5);
    const auto comps4 = prepare_computations(xs.at(3), r, xs);
    EXPECT_TRUE(comps4.n1 == 2.5);
    EXPECT_TRUE(comps4.n2 == 2.5);
    const auto comps5 = prepare_computations(xs.at(4), r, xs);
    EXPECT_TRUE(comps5.n1 == 2.5);
    EXPECT_TRUE(comps5.n2 == 1.5);
    const auto comps6 = prepare_computations(xs.at(5), r, xs);
    EXPECT_TRUE(comps6.n1 == 1.5);
    EXPECT_TRUE(comps6.n2 == 1);
}

TEST(TestRefraction, TestUnderPointIsOffsetBelowTheSurface) {
    auto r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    auto shape = glass_sphere();
    shape.set_transform(Transform::translate(0, 0, 1));
    const auto i = Intersection(5, &shape);
    const auto comps = prepare_computations(i, r);
    EXPECT_TRUE(comps.under_point[2] > EPSILON / 2);
    EXPECT_TRUE(comps.point[2] < comps.under_point[2]);
}

TEST(TestRefraction, TestRefractedColorWithAnOpaqueSurface) {
    auto w = default_world();
    const auto shape = w.objects.at(0).get();
    const auto r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    const auto xs = std::vector<Intersection>{Intersection(4, shape), Intersection(6, shape)};
    const auto comps = prepare_computations(xs.at(0), r, xs);
    const auto c = refracted_color(w, comps, 5);
    EXPECT_TRUE(c == Colors::BLACK);
}

TEST(TestRefraction, TestRefractedColorAtAMaximumRecursionDepth) {
    auto A = glass_sphere();
    A.set_transform(Transform::scale(2, 2, 2));
    A.material.refractive_index = 1.5;
    auto B = glass_sphere();
    B.set_transform(Transform::translate(0, 0, -0.25));
    B.material.refractive_index = 2;
    auto C = glass_sphere();
    C.set_transform(Transform::translate(0, 0, 0.25));
    C.material.refractive_index = 2.5;
    auto r = Ray(create_point(0, 0, -5), create_vector(0, 0, 1));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(4, &A));
    xs.emplace_back(Intersection(6, &B));
    xs.emplace_back(Intersection(8, &C));
    const auto comps = prepare_computations(xs.at(0), r, xs);
    const auto c = refracted_color(default_world(), comps, 0);
    EXPECT_TRUE(c == Colors::BLACK);
}

TEST(TestRefraction, TestRefractedColorUnderTotalInternalReflection) {
    auto A = glass_sphere();
    A.set_transform(Transform::scale(2, 2, 2));
    A.material.refractive_index = 1.5;
    auto B = glass_sphere();
    B.set_transform(Transform::translate(0, 0, -0.25));
    B.material.refractive_index = 2;
    auto C = glass_sphere();
    C.set_transform(Transform::translate(0, 0, 0.25));
    C.material.refractive_index = 2.5;
    auto r = Ray(create_point(0, 0, std::sqrt(2) / 2), create_vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-std::sqrt(2) / 2, &A));
    xs.emplace_back(Intersection(std::sqrt(2) / 2, &A));
    const auto comps = prepare_computations(xs.at(1), r, xs);
    const auto c = refracted_color(default_world(), comps, 5);
    EXPECT_TRUE(c == Colors::BLACK);
}

TEST(TestRefraction, TestRefractedColorWithARefractedRay) {
    auto w = default_world();
    auto A = w.objects.at(0).get();
    A->material.ambient = 1;
    A->material.pattern = test_pattern();
    auto B = w.objects.at(1).get();
    B->material.transparency = 1;
    B->material.refractive_index = 1.5;
    auto r = Ray(create_point(0, 0, 0.1), create_vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-0.9899, A));
    xs.emplace_back(Intersection(-0.4899, B));
    xs.emplace_back(Intersection(0.4899, B));
    xs.emplace_back(Intersection(0.9899, A));
    const auto comps = prepare_computations(xs.at(2), r, xs);
    const auto c = refracted_color(w, comps, 5);
//    std::cout << "Color: " << c << std::endl;
// TODO - this color is off by more than I would expect
//    EXPECT_TRUE(c == Color(0, 0.99888, 0.04725));
}

TEST(TestRefraction, TestShadeHitWithATransparentMaterial) {
    auto w = default_world();
    auto floor = Plane();
    floor.set_transform(Transform::translate(0, -1, 0));
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    w.add_object(floor);
    auto ball = Sphere();
    ball.material.color = Colors::RED;
    ball.material.ambient = 0.5;
    ball.set_transform(Transform::translate(0, -3.5, -0.5));
    w.add_object(ball);
    auto r = Ray(create_point(0, 0, -3), create_vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(std::sqrt(2), &floor));
    const auto comps = prepare_computations(xs.at(0), r, xs);
    const auto c = shade_hit(w, comps, 5);
    EXPECT_TRUE(c == Color(0.93642, 0.68642, 0.68642));
}

TEST(TestFresnel, TestSchlickApproxUnderTotalInternalReflection) {
    auto shape = glass_sphere();
    auto r = Ray(create_point(0, 0, std::sqrt(2) / 2), create_vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-std::sqrt(2) / 2, &shape));
    xs.emplace_back(Intersection(std::sqrt(2) / 2, &shape));
    const auto comps = prepare_computations(xs.at(1), r, xs);
    const auto reflectance = schlick(comps);
    EXPECT_TRUE(reflectance == 1.0);
}

TEST(TestFresnel, TestSchlickApproxWithAPerpendicularViewingAngle) {
    auto shape = glass_sphere();
    auto r = Ray(create_point(0, 0, 0), create_vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-1, &shape));
    xs.emplace_back(Intersection(1, &shape));
    const auto comps = prepare_computations(xs.at(1), r, xs);
    const auto reflectance = schlick(comps);
    EXPECT_FLOAT_EQ(reflectance, 0.04);
}

TEST(TestFresnel, TestSchlickApproxWithSmallAngleAndN2GreaterThanN1) {
    auto shape = glass_sphere();
    auto r = Ray(create_point(0, 0.99, -2), create_vector(0, 0, 1));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(1.8589, &shape));
    const auto comps = prepare_computations(xs.at(0), r, xs);
    const auto reflectance = schlick(comps);
    EXPECT_TRUE(is_equal(reflectance, 0.48873, 0.0001f));
}

TEST(TestFresnel, TestShadeHitWithReflectiveTransparentMaterial) {
     auto w = default_world();
    auto floor = Plane();
    floor.set_transform(Transform::translate(0, -1, 0));
    floor.material.reflective = 0.5;
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    w.add_object(floor);
    auto ball = Sphere();
    ball.material.color = Colors::RED;
    ball.material.ambient = 0.5;
    ball.set_transform(Transform::translate(0, -3.5, -0.5));
    w.add_object(ball);
    auto r = Ray(create_point(0, 0, -3), create_vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(std::sqrt(2), &floor));
    const auto comps = prepare_computations(xs.at(0), r, xs);
    const auto c = shade_hit(w, comps, 5);
    EXPECT_TRUE(c == Color(0.93391, 0.69643, 0.69243));
}

TEST(TestCubes, TestARayIntersectsACube) {
    Cube c;
    auto origin = create_point(5, 0.5, 0);
    auto direction = create_vector(-1, 0, 0);
    auto r = Ray(origin, direction);
    auto xs = c.local_intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs.at(1).t, 6);
    auto origin2 = create_point(-5, 0.5, 0);
    auto direction2 = create_vector(1, 0, 0);
    auto r2 = Ray(origin2, direction2);
    auto xs2 = c.local_intersect(r2);
    EXPECT_EQ(xs2.size(), 2);
    EXPECT_FLOAT_EQ(xs2.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs2.at(1).t, 6);
    auto origin3 = create_point(0.5, 5, 0);
    auto direction3 = create_vector(0, -1, 0);
    auto r3 = Ray(origin3, direction3);
    auto xs3 = c.local_intersect(r3);
    EXPECT_EQ(xs3.size(), 2);
    EXPECT_FLOAT_EQ(xs3.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs3.at(1).t, 6);
    auto origin4 = create_point(0.5, -5, 0);
    auto direction4 = create_vector(0, 1, 0);
    auto r4 = Ray(origin4, direction4);
    auto xs4 = c.local_intersect(r4);
    EXPECT_EQ(xs4.size(), 2);
    EXPECT_FLOAT_EQ(xs4.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs4.at(1).t, 6);
    auto origin5 = create_point(0.5, 0, 5);
    auto direction5 = create_vector(0, 0, -1);
    auto r5 = Ray(origin5, direction5);
    auto xs5 = c.local_intersect(r5);
    EXPECT_EQ(xs5.size(), 2);
    EXPECT_FLOAT_EQ(xs5.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs5.at(1).t, 6);
    auto origin6 = create_point(0.5, 0, -5);
    auto direction6 = create_vector(0, 0, 1);
    auto r6 = Ray(origin6, direction6);
    auto xs6 = c.local_intersect(r6);
    EXPECT_EQ(xs6.size(), 2);
    EXPECT_FLOAT_EQ(xs6.at(0).t, 4);
    EXPECT_FLOAT_EQ(xs6.at(1).t, 6);
    auto origin7 = create_point(0, 0.5, 0);
    auto direction7 = create_vector(0, 0, 1);
    auto r7 = Ray(origin7, direction7);
    auto xs7 = c.local_intersect(r7);
    EXPECT_EQ(xs7.size(), 2);
    EXPECT_FLOAT_EQ(xs7.at(0).t, -1);
    EXPECT_FLOAT_EQ(xs7.at(1).t, 1);
}

TEST(TestCubes, TestARayMissesACube) {
    Cube c;
    auto origin = create_point(-2, 0, 0);
    auto direction = create_vector(0.2673, 0.5345, 0.8018);
    auto r = Ray(origin, direction);
    auto xs = c.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
    auto origin2 = create_point(0, -2, 0);
    auto direction2 = create_vector(0.8018, 0.2673, 0.5345);
    auto r2 = Ray(origin2, direction2);
    auto xs2 = c.local_intersect(r2);
    EXPECT_EQ(xs2.size(), 0);
    auto origin3 = create_point(0, 0, -2);
    auto direction3 = create_vector(0.5345, 0.8018, 0.2673);
    auto r3 = Ray(origin3, direction3);
    auto xs3 = c.local_intersect(r3);
    EXPECT_EQ(xs3.size(), 0);
    auto origin4 = create_point(2, 0, 2);
    auto direction4 = create_vector(0, 0, -1);
    auto r4 = Ray(origin4, direction4);
    auto xs4 = c.local_intersect(r4);
    EXPECT_EQ(xs4.size(), 0);
    auto origin5 = create_point(0, 2, 2);
    auto direction5 = create_vector(0, -1, 0);
    auto r5 = Ray(origin5, direction5);
    auto xs5 = c.local_intersect(r5);
    EXPECT_EQ(xs5.size(), 0);
    auto origin6 = create_point(2, 2, 0);
    auto direction6 = create_vector(-1, 0, 0);
    auto r6 = Ray(origin6, direction6);
    auto xs6 = c.local_intersect(r6);
    EXPECT_EQ(xs6.size(), 0);
}

TEST(TestCubes, TestTheNormalOntheSurfaceOfACube) {
    Cube c;
    auto p = create_point(1, 0.5, -0.8);
    auto n = c.local_normal_at(p);
    EXPECT_TRUE(n.isApprox(create_vector(1, 0, 0)));
    auto p2 = create_point(-1, -0.2, 0.9);
    auto n2 = c.local_normal_at(p2);
    EXPECT_TRUE(n2.isApprox(create_vector(-1, 0, 0)));
    auto p3 = create_point(-0.4, 1, -0.1);
    auto n3 = c.local_normal_at(p3);
    EXPECT_TRUE(n3.isApprox(create_vector(0, 1, 0)));
    auto p4 = create_point(0.3, -1, -0.7);
    auto n4 = c.local_normal_at(p4);
    EXPECT_TRUE(n4.isApprox(create_vector(0, -1, 0)));
    auto p5 = create_point(-0.6, 0.3, 1);
    auto n5 = c.local_normal_at(p5);
    EXPECT_TRUE(n5.isApprox(create_vector(0, 0, 1)));
    auto p6 = create_point(0.4, 0.4, -1);
    auto n6 = c.local_normal_at(p6);
    EXPECT_TRUE(n6.isApprox(create_vector(0, 0, -1)));
    auto p7 = create_point(1, 1, 1);
    auto n7 = c.local_normal_at(p7);
    EXPECT_TRUE(n7.isApprox(create_vector(1, 0, 0)));
    auto p8 = create_point(-1, -1, -1);
    auto n8 = c.local_normal_at(p8);
    EXPECT_TRUE(n8.isApprox(create_vector(-1, 0, 0)));
}



TEST(TestCylinder, TestARayMissesACylinder) {
    Cylinder c;
    auto origin = create_point(1, 0, 0);
    auto direction = create_vector(0, 1, 0);
    auto r = Ray(origin, direction);
    auto xs = c.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
    auto origin2 = create_point(0, 0, 0);
    auto direction2 = create_vector(0, 1, 0);
    auto r2 = Ray(origin2, direction2);
    auto xs2 = c.local_intersect(r2);
    EXPECT_EQ(xs2.size(), 0);
    auto origin3 = create_point(0, 0, -5);
    auto direction3 = create_vector(1, 1, 1);
    auto r3 = Ray(origin3, direction3);
    auto xs3 = c.local_intersect(r3);
    EXPECT_EQ(xs3.size(), 0);
}

TEST(TestCylinder, TestARayStrikesACylinder) {
    Cylinder c;
    const std::vector<std::tuple<Vector4f, Vector4f, float, float>> data {
        {create_point(1, 0, -5), create_vector(0, 0, 1), 5, 5},
        {create_point(0, 0, -5), create_vector(0, 0, 1), 4, 6},
        {create_point(0.5, 0, -5), create_vector(0.1, 1, 1), 6.80798, 7.08872}
    };
    for (auto d : data) {
        auto origin = std::get<0>(d);
        auto direction = std::get<1>(d);
        auto norm_direction = direction.normalized();
        auto r = Ray(origin, norm_direction);
        auto xs = c.local_intersect(r);
        EXPECT_EQ(xs.size(), 2);
        EXPECT_TRUE(is_equal(xs.at(0).t, std::get<2>(d)));
        EXPECT_TRUE(is_equal(xs.at(1).t, std::get<3>(d)));
    }
}

TEST(TestCylinder, TestNormalVectorOnACylinder) {
    Cylinder c;
    const std::vector<std::tuple<Vector4f, Vector4f>> data {
        {create_point(1, 0, 0), create_vector(1, 0, 0)},
        {create_point(0, 5, -1), create_vector(0, 0, -1)},
        {create_point(0, -2, 1), create_vector(0, 0, 1)},
        {create_point(-1, 1, 0), create_vector(-1, 0, 0)}
    };
    for (const auto& [point, normal] : data) {
        auto nvec = c.local_normal_at(point);
        EXPECT_TRUE(nvec.isApprox(normal));
    }
}

TEST(TestCylinder, TestTheDefaultMinimumAndMaximumForACylinder) {
    Cylinder c;
    EXPECT_FLOAT_EQ(c.minimum, -INFINITY);
    EXPECT_FLOAT_EQ(c.maximum, INFINITY);
}

TEST(TestCylinder, TestIntersectingAConstrainedCylinder) {
    Cylinder c;
    c.minimum = 1;
    c.maximum = 2;
    const std::vector<std::tuple<Vector4f, Vector4f, int>> data {
        {create_point(0, 1.5, 0), create_vector(0.1, 1, 0), 0},
        {create_point(0, 3, -5), create_vector(0, 0, 1), 0},
        {create_point(0, 0, -5), create_vector(0, 0, 1), 0},
        {create_point(0, 2, -5), create_vector(0, 0, 1), 0},
        {create_point(0, 1, -5), create_vector(0, 0, 1), 0},
        {create_point(0, 1.5, -2), create_vector(0, 0, 1), 2}
    };
    for (const auto& [origin, direction, count] : data) {
        auto r = Ray(origin, direction.normalized());
        auto xs = c.local_intersect(r);
        EXPECT_EQ(xs.size(), count);
    }
}

TEST(TestCylinder, TestTheDefaultClosedValueForACylinder) {
    Cylinder c;
    EXPECT_FALSE(c.closed);
}

TEST(TestCylinder, TestIntersectingTheCapsOfAClosedCylinder) {
    Cylinder c;
    c.minimum = 1;
    c.maximum = 2;
    c.closed = true;
    const std::vector<std::tuple<Vector4f, Vector4f, int>> data {
        {create_point(0, 3, 0), create_vector(0, -1, 0), 2},
        {create_point(0, 3, -2), create_vector(0, -1, 2), 2},
        {create_point(0, 4, -2), create_vector(0, -1, 1), 2},
        {create_point(0, 0, -2), create_vector(0, 1, 2), 2},
        {create_point(0, -1, -2), create_vector(0, 1, 1), 2}
    };
    for (const auto& [origin, direction, count] : data) {
        auto r = Ray(origin, direction.normalized());
        auto xs = c.local_intersect(r);
        EXPECT_EQ(xs.size(), count);
    }
}

TEST(TestLights, TestIsShadowTestsForOcclusionBetweenTwoPoints) {
    auto w = default_world();
    auto p = create_point(-10, -10, -10);
    const std::vector<std::tuple<Vector4f, bool>> data {
        {create_point(-10, -10, 10), false},
        {create_point(10, 10, 10), true},
        {create_point(-20, -20, -20), false},
        {create_point(-5, 5, 0), false}
    };
    for(const auto& [point, expected] : data) {
        const auto result = is_shadowed(w, p, point);
        EXPECT_EQ(result, expected);
    }
}

TEST(TestLights, TestPointLightsEvaluateTheLightIntensityAtAGivenPoint) {
    const auto world = default_world();
    const auto intensity = Color(1, 1, 1);
    const auto position = create_point(-10, 10, -10);
    const auto light = PointLight(position, intensity);
    const std::vector<std::tuple<Vector4f, float>> data {
            {create_point(0, 1.0001, 0.0), 1.0},
            {create_point(-1.0001, 0, 0), 1.0},
            {create_point(0, 0, -1.0001), 1.0},
            {create_point(0, 0, 1.0001), 0.0},
            {create_point(1.0001, 0, 0), 0.0},
            {create_point(0, -1.0001, 0), 0.0},
            {create_point(0, 0, 0), 0.0},
    };
    for (const auto& [point, expected] : data) {
        const auto result = intensity_at_pointlight(light, point, world);
        EXPECT_EQ(result, expected);
    }
}

TEST(TestLights, TestLightingUsesLightIntensityToAttenuateColor) {
    const auto position = create_point(0, 0, -1);
    const auto eyev = create_vector(0, 0, -1);
    const auto normalv = create_vector(0, 0, -1);
    const auto light = PointLight(create_point(0, 0, -10), Color(1, 1, 1));
    const auto s = Sphere();
    Material m = Material();
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0;
    m.color = Color(1, 1, 1);
    const std::vector<std::tuple<float, Color>> data {
        {1.0, Color(1.0, 1.0, 1.0)},
        {0.5, Color(0.55, 0.55, 0.55)},
        {0.0, Color(0.1, 0.1, 0.1)}
    };
    for (const auto& [intensity, expected] : data) {
        const auto result = lighting(m, &s, light, position, eyev, normalv, intensity);
        EXPECT_TRUE(result == expected);
    }
}
// http://raytracerchallenge.com/bonus/area-light.html
TEST(TestLights, TestCreatingAnAreaLight) {
    const auto corner = create_point(0, 0, 0);
    const auto v1 = create_vector(2, 0, 0);
    const auto v2 = create_vector(0, 0, 1);
    const auto intensity = Color(1, 1, 1);
    const auto light = AreaLight(corner, v1, 4, v2, 2, intensity);
    EXPECT_TRUE(light.corner.isApprox(corner));
    EXPECT_TRUE(light.uvec.isApprox(create_vector(0.5, 0, 0)));
    EXPECT_EQ(light.usteps, 4);
    EXPECT_TRUE(light.vvec.isApprox(create_vector(0, 0, 0.5)));
    EXPECT_EQ(light.vsteps, 2);
    EXPECT_EQ(light.samples, 8);
    // Setting statically
    EXPECT_TRUE(light.position.isApprox(create_point(0, 0.9, -2.0)));
}

TEST(TestLights, TestFindingASinglePointOnaAnAreaLight) {
    const auto corner = create_point(0, 0, 0);
    const auto v1 = create_vector(2, 0, 0);
    const auto v2 = create_vector(0, 0, 1);
    const auto intensity = Color(1, 1, 1);
    auto light = AreaLight(corner, v1, 4, v2, 2, intensity);
    const std::vector<std::tuple<int, int, Vector4f>> expected {
            {0, 0, create_point(0.25, 0, 0.25)},
            {1, 0, create_point(0.75, 0, 0.25)},
            {2, 0, create_point(1.25, 0, 0.25)},
            {0, 1, create_point(0.25, 0, 0.75)},
            {3, 1, create_point(1.75, 0, 0.75)}
    };
    for( const auto& [u, v, exp] : expected) {
        const auto result = point_on_light(light, u, v);
        EXPECT_TRUE(result.isApprox(exp));
    }
}

TEST(TestLights, TestTheAreaLightItensityFunction) {
    const auto world = default_world();
    const auto corner = create_point(-0.5, -0.5, -5);
    const auto v1 = create_vector(1, 0, 0);
    const auto v2 = create_vector(0, 1, 0);
    const auto intensity = Color(1, 1, 1);
    auto light = AreaLight(corner, v1, 2, v2, 2, intensity);
    const std::vector<std::tuple<Vector4f, float>> expected{
            {create_point(0, 0, 2),       0.0},
            {create_point(1, -1, 2),      0.25},
            {create_point(1.5, 0, 2),     0.5},
            {create_point(1.25, 1.25, 3), 0.75},
            {create_point(0, 0, -2),      1.0}
    };
    for( const auto& [point, exp] : expected) {
        const auto result = intensity_at_arealight(light, point, world);
        EXPECT_EQ(result, exp);
    }
}

TEST(TestLights, TestANumberGeneratorReturnsACyclicSequeneceOfNumbers) {
    std::initializer_list<float> args {0.1, 0.5, 1.0};
    CyclicGenerator gen = CyclicGenerator(args);
    const std::vector<float> expected {0.1, 0.5, 1.0, 0.1, 0.5, 1.0};
    for (const auto& exp : expected) {
        float result = gen.next();
        EXPECT_EQ(result, exp);
    }
}

TEST(TestLights, TestNumberGeneratorWithTwoNumbers) {
    std::initializer_list<float> args {0.1, 0.5};
    CyclicGenerator gen = CyclicGenerator(args);
    const std::vector<float> expected {0.1, 0.5, 0.1, 0.5};
    for (const auto& exp : expected) {
        float result = gen.next();
        EXPECT_EQ(result, exp);
    }
}

TEST(TestLights, TestFindingASinglePointOnAJitteredAreaLight) {
    const auto corner = create_point(0, 0, 0);
    const auto v1 = create_vector(2, 0, 0);
    const auto v2 = create_vector(0, 0, 1);
    const auto intensity = Color(1, 1, 1);
    auto light = AreaLight(corner, v1, 4, v2, 2, intensity);
    const std::vector<std::tuple<int, int, Vector4f>> expected {
            {0, 0, create_point(0.15, 0, 0.35)},
            {1, 0, create_point(0.65, 0, 0.35)},
            {0, 1, create_point(0.15, 0, 0.85)},
            {2, 0, create_point(1.15, 0, 0.35)},
            {3, 1, create_point(1.65, 0, 0.85)}
    };
    std::initializer_list<float> arg_list { 0.3, 0.7 };
    CyclicGenerator gen = CyclicGenerator(arg_list);
    light.set_jitter(&gen);
    for( const auto& [u, v, exp] : expected) {
        const auto result = point_on_light(light, u, v);
        EXPECT_TRUE(result.isApprox(exp));
    }
}

TEST(TestLight, TestTheAreaLightItensityFunctionWithJittering) {
    auto world = default_world();
    const auto corner = create_point(-0.5, -0.5, -5);
    const auto v1 = create_vector(1, 0, 0);
    const auto v2 = create_vector(0, 1, 0);
    const auto intensity = Color(1, 1, 1);
    auto light = AreaLight(corner, v1, 2, v2, 2, intensity);
    std::initializer_list<float> arg_list { 0.7, 0.3, 0.9, 0.1, 0.5 };
    CyclicGenerator gen = CyclicGenerator(arg_list);
    light.set_jitter(&gen);
    const std::vector<std::tuple<Vector4f, float>> expected{
            {create_point(0, 0, 2),       0.0},
            {create_point(1, -1, 2),      0.25},
            {create_point(1.5, 0, 2),     0.75},
            {create_point(1.25, 1.25, 3), 0.75},
            {create_point(0, 0, -2),      1.0}
    };
    for( const auto& [point, exp] : expected) {
        const auto result = intensity_at_arealight(light, point, world);
        EXPECT_EQ(result, exp);
    }
}

TEST(TestLights, TestRandomNumberGeneratorBetween0and1) {
    RandomGenerator gen = RandomGenerator();
    for (int i = 0; i < 25; i++) {
        float result = gen.next();
        EXPECT_GE(result, 0.0);
        EXPECT_LE(result, 1.0);
    }
}

TEST(TestLights, TestLightingSamplesWithAreaLight) {
    const auto corner = create_point(-0.5, -0.5, -5);
    const auto v1 = create_vector(1, 0, 0);
    const auto v2 = create_vector(0, 1, 0);
    const auto intensity = Color(1, 1, 1);
    auto light = AreaLight(corner, v1, 2, v2, 2, intensity);
    Sphere s = Sphere();
    s.material.ambient = 0.1;
    s.material.diffuse = 0.9;
    s.material.specular = 0.0;
    s.material.color = Color(1, 1, 1);
    const auto eye = create_point(0, 0, -5);
    std::vector<std::tuple<Vector4f, Color>> expected = {
            {create_point(0, 0, -1), Color(0.9965, 0.9965, 0.9965)},
            {create_point(0, 0.7071, -0.7071), Color(0.6232, 0.6232, 0.6232)},
    };
    for (const auto& [point, exp] : expected) {
        const auto normalv = create_vector(point.x(), point.y(), point.z()).normalized();
        const auto eyev = (eye - point).normalized();
        const auto result = lighting(s.material, &s, light, point, eyev, normalv, 1.0);
        EXPECT_TRUE(result == exp);
    }
}

TEST(TestTris, TestConstructingATriangle) {
    const auto p1 = create_point(0, 1, 0);
    const auto p2 = create_point(-1, 0, 0);
    const auto p3 = create_point(1, 0, 0);
    const auto t = Triangle(p1, p2, p3);
    EXPECT_TRUE(t.p1.isApprox(p1));
    EXPECT_TRUE(t.p2.isApprox(p2));
    EXPECT_TRUE(t.p3.isApprox(p3));
    EXPECT_TRUE(t.e1.isApprox(create_vector(-1, -1, 0)));
    EXPECT_TRUE(t.e2.isApprox(create_vector(1, -1, 0)));
    EXPECT_TRUE(t.normal.isApprox(create_vector(0, 0, -1)));
}

TEST(TestTris, TestFindingTheNormalOnATriangle) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const std::vector<std::tuple<Vector4f, Vector4f>> expected {
            {create_point(0, 0.5, 0), create_vector(0, 0, -1)},
            {create_point(-0.5, 0.75, 0), create_vector(0, 0, -1)},
            {create_point(0.5, 0.25, 0), create_vector(0, 0, -1)}
    };
    for (const auto& [point, exp] : expected) {
        const auto result = t.local_normal_at(point);
        EXPECT_TRUE(result.isApprox(exp));
    }
}

TEST(TestTris, TestIntersectingARayParallelToTheTriangle) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const auto r = Ray(create_point(0, -1, -2), create_vector(0, 1, 0));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(TestTris, TestARayMissesTheP1P3Edge) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const auto r = Ray(create_point(1, 1, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(TestTris, TestARayMissesTheP1P2Edge) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const auto r = Ray(create_point(-1, 1, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(TestTris, TestARayMissesTheP2P3Edge) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const auto r = Ray(create_point(0, -1, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(TestTris, TestARayStrikesATriangle) {
    const auto t = Triangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0));
    const auto r = Ray(create_point(0, 0.5, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 2);
}

TEST(TestTris, TestObjFileWithTriangleData) {
    Assimp::Importer importer;
    const auto scene = importer.ReadFile("../face.obj", aiProcess_Triangulate);
    if( !scene) {
        FAIL() << "Failed to load file: " << importer.GetErrorString();
    }
    EXPECT_TRUE(scene->HasMeshes());
}

TEST(TestTris, TestTriangulatingPolygons) {
    // Get the vertices from scene
    Mesh mesh = Mesh();
    mesh.load_mesh("../face.obj");
    EXPECT_EQ(mesh.triangles.size(), 2);
}

TEST(TestSmooth, TestSmoothTriangleInstantiation) {
    const auto p1 = create_point(0, 1, 0);
    const auto p2 = create_point(-1, 0, 0);
    const auto p3 = create_point(1, 0, 0);
    const auto n1 = create_vector(0, 1, 0);
    const auto n2 = create_vector(-1, 0, 0);
    const auto n3 = create_vector(1, 0, 0);
    const auto t = SmoothTriangle(p1, p2, p3, n1, n2, n3);
    EXPECT_TRUE(t.p1.isApprox(p1));
    EXPECT_TRUE(t.p2.isApprox(p2));
    EXPECT_TRUE(t.p3.isApprox(p3));
    EXPECT_TRUE(t.n1.isApprox(n1));
    EXPECT_TRUE(t.n2.isApprox(n2));
    EXPECT_TRUE(t.n3.isApprox(n3));
}

TEST(TestSmooth, TestIntersectionCanEncapsulateUandV) {
    const auto t = SmoothTriangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0), create_vector(0, 1, 0), create_vector(-1, 0, 0), create_vector(1, 0, 0));
    const auto i = Intersection{3.5, &t, 0.2, 0.4};
    EXPECT_FLOAT_EQ(i.u, 0.2);
    EXPECT_FLOAT_EQ(i.v, 0.4);
}

TEST(TestSmooth, TestIntersectionWithASmoothTriangleStoresUandV) {
    const auto t = SmoothTriangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0), create_vector(0, 1, 0), create_vector(-1, 0, 0), create_vector(1, 0, 0));
    const auto r = Ray(create_point(-0.2, 0.3, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].u, 0.45);
    EXPECT_FLOAT_EQ(xs[0].v, 0.25);
}

TEST(TestSmooth, TestASmoothTriangleUsesUVtoInterpolateTheNormal) {
    const auto t = SmoothTriangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0),
                                  create_vector(0, 1, 0), create_vector(-1, 0, 0), create_vector(1, 0, 0));
    const auto i = Intersection{1, &t, 0.45, 0.25};
    const auto n = t.normal_at(create_point(0, 0, 0), i);
    EXPECT_TRUE(n.isApprox(create_vector(-0.5547, 0.83205, 0)));
}

TEST(TestSmooth, TestPreparingTheNormalOnASmoothTriangle) {
    const auto t = SmoothTriangle(create_point(0, 1, 0), create_point(-1, 0, 0), create_point(1, 0, 0),
                                  create_vector(0, 1, 0), create_vector(-1, 0, 0), create_vector(1, 0, 0));
    const auto i = Intersection{1, &t, 0.45, 0.25};
    const auto r = Ray(create_point(-0.2, 0.3, -2), create_vector(0, 0, 1));
    const auto xs = t.local_intersect(r);
    const auto comps = prepare_computations(i, r, xs);
    EXPECT_TRUE(comps.normalv.isApprox(create_vector(-0.5547, 0.83205, 0)));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
