//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "MathUtils.h"
#include "Canvas.h"
#include "RayCaster.h"

// using Tuple = Eigen::Vector4f;

TEST(TestTupleVectorPoint, TestSample) {
    EXPECT_EQ(1, 1);
}

TEST(TestTupleVectorPoint, TestTupleAsAPoint) {
    Tuple t = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 1.0f);
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TestTupleVectorPoint, TestTupleAsAVector) {
    Tuple t = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
    EXPECT_EQ(t.x(), 4.3f);
    EXPECT_EQ(t.y(), -4.2f);
    EXPECT_EQ(t.z(), 3.1f);
    EXPECT_EQ(t.w(), 0.0f);
    EXPECT_FALSE(t.isPoint());
    EXPECT_TRUE(t.isVector());
}

TEST(TestTupleVectorPoint, TestCreateTupleFromPoint) {
    Point p = Point(4.0f, -4.0f, 3.0f);
    Tuple t = Tuple(p);
    EXPECT_EQ(t.x(), 4.0f);
    EXPECT_EQ(t.y(), -4.0f);
    EXPECT_EQ(t.z(), 3.0f);
    EXPECT_EQ(t.w(), 1.0f);
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TestTupleVectorPoint, TestCreateTupleFromVector) {
    Vector v = Vector(4.0f, -4.0f, 3.0f);
    Tuple t = Tuple(v);
    EXPECT_EQ(t.x(), 4.0f);
    EXPECT_EQ(t.y(), -4.0f);
    EXPECT_EQ(t.z(), 3.0f);
    EXPECT_EQ(t.w(), 0.0f);
    EXPECT_FALSE(t.isPoint());
    EXPECT_TRUE(t.isVector());
}

TEST(TestTupleVectorPoint, TestTupleAreEqual) {
    Tuple t1 = Tuple(4.0f, -4.0f, 3.0f, 1.0f);
    Tuple t2 = Tuple(4.0f, -4.0f, 3.0f, 1.0f);
    EXPECT_TRUE(t1 == t2);
}

TEST(TestTupleVectorPoint, TestTupleAreNotEqual) {
    Tuple t1 = Tuple(4.0f, -4.0f, 3.0f, 1.0f);
    Tuple t2 = Tuple(4.0f, -4.0f, 3.0f, 0.0f);
    EXPECT_FALSE(t1 == t2);
}

TEST(TestTupleVectorPoint, TestTupleVectorAndPointAddition) {
    Point p = Point(3.0f, -2.0f, 5.0f);
    Tuple t1 = Tuple(p);
    Vector v = Vector(-2.0f, 3.0f, 1.0f);
    Tuple t2 = Tuple(v);
    Tuple expected = Tuple(1.0f, 1.0f, 6.0f, 1.0f);
    Tuple result = t1 + t2;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTuplePointAndPointSubtraction) {
    Point p1 = Point(3.0f, 2.0f, 1.0f);
    Tuple t1 = Tuple(p1);
    Point p2 = Point(5.0f, 6.0f, 7.0f);
    Tuple t2 = Tuple(p2);
    Tuple expected = Tuple(-2.0f, -4.0f, -6.0f, 0.0f);
    Tuple result = t1 - t2;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTupleVectorAndPointSubtraction) {
    Point p = Point(3.0f, 2.0f, 1.0f);
    Tuple t1 = Tuple(p);
    Vector v = Vector(5.0f, 6.0f, 7.0f);
    Tuple t2 = Tuple(v);
    Tuple expected = Tuple(-2.0f, -4.0f, -6.0f, 1.0f);
    Tuple result = t1 - t2;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTupleVectorAndVectorSubtraction) {
    Vector v1 = Vector(3.0f, 2.0f, 1.0f);
    Tuple t1 = Tuple(v1);
    Vector v2 = Vector(5.0f, 6.0f, 7.0f);
    Tuple t2 = Tuple(v2);
    Tuple expected = Tuple(-2.0f, -4.0f, -6.0f, 0.0f);
    Tuple result = t1 - t2;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTupleNegation) {
    Tuple t = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    Tuple expected = Tuple(-1.0f, 2.0f, -3.0f, 4.0f);
    Tuple result = -t;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTupleScalarMultiplication) {
    Tuple t = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    Tuple expected = Tuple(3.5f, -7.0f, 10.5f, -14.0f);
    Tuple result = t * 3.5;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestTupleScalarDivision) {
    Tuple t = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    Tuple expected = Tuple(0.5f, -1.0f, 1.5f, -2.0f);
    Tuple result = t / 2.0f;
    EXPECT_TRUE(result == expected);
}

TEST(TestTupleVectorPoint, TestVectorMagnitude) {
    Vector v1 = Vector(1.0f, 0.0f, 0.0f);
    EXPECT_EQ(v1.norm(), 1.0f);
    Vector v2 = Vector(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(v2.norm(), 1.0f);
    Vector v3 = Vector(0.0f, 0.0f, 1.0f);
    EXPECT_EQ(v3.norm(), 1.0f);
    Vector v4 = Vector(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v4.norm(), sqrt(14.0f));
    Vector v5 = Vector(-1.0f, -2.0f, -3.0f);
    EXPECT_EQ(v5.norm(), sqrt(14.0f));
}

TEST(TestTupleVectorPoint, TestVectorNormalize) {
    Vector v1 = Vector(4.0f, 0.0f, 0.0f);
    Vector expected1 = Vector(1.0f, 0.0f, 0.0f);
    Vector result = v1.normalized();
    EXPECT_TRUE(result == expected1);
    Vector v2 = Vector(1.0f, 2.0f, 3.0f);
    Vector expected2 = Vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f));
    Vector result2 = v2.normalized();
    EXPECT_TRUE(result2 == expected2);
}

TEST(TestTupleVectorPoint, TestVectorMagnitudeAfterNormalize) {
    Vector v = Vector(1.0f, 2.0f, 3.0f);
    Vector normalized = v.normalized();
    EXPECT_FLOAT_EQ(normalized.norm(), 1.0f);
}

TEST(TestTupleVectorPoint, TestDotProduct) {
    Vector v1 = Vector(1.0f, 2.0f, 3.0f);
    Vector v2 = Vector(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v1.dot(v2), 20.0f);
}

TEST(TestTupleVectorPoint, TestCrossProduct) {
    Vector v1 = Vector(1.0f, 2.0f, 3.0f);
    Vector v2 = Vector(2.0f, 3.0f, 4.0f);
    Vector expected1 = Vector(-1.0f, 2.0f, -1.0f);
    Vector expected2 = Vector(1.0f, -2.0f, 1.0f);
    EXPECT_TRUE(v1.cross(v2) == expected1);
    EXPECT_TRUE(v2.cross(v1) == expected2);
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

TEST(TestMatrices, TestMatrixMultipliedByTuple) {
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1;
    Tuple t(1, 2, 3, 1);
    Tuple expected(18, 24, 33, 1);
    EXPECT_TRUE(m * t == expected);
}

TEST(TestMatrices, TestIdentityMatrixMultipliedByTuple) {
    Eigen::Matrix4f m = Eigen::Matrix4f::Identity();
    Tuple t(1, 2, 3, 4);
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
    Point p = Point(-3, 4, 5);
    Eigen::Vector3f translation(5, -3, 2);
    Tuple t = Tuple(p).translate(translation);
    Tuple expected = Tuple(Point(2, 1, 7));
    EXPECT_TRUE(t == expected);
}

TEST(TestTransformations, TestTranslateInverseMatrix) {
    Point p = Point(-3, 4, 5);
    Tuple t = Tuple(p);
    Eigen::Vector3f translation(5, -3, 2);
    t = t.translate_inv(translation);
    EXPECT_TRUE(t == Tuple(Point(-8, 7, 3)));
}

TEST(TestTransformations, TestTranslateVector) {
    Vector v = Vector(-3, 4, 5);
    Tuple vector = Tuple(v);
    Eigen::Vector3f translation(5, -3, 2);
    Tuple t = vector.translate(translation);
    EXPECT_TRUE(t == Tuple(v));
}

TEST(TestTransformations, TestScalingAPoint) {
    Point p = Point(-4, 6, 8);
    Tuple point = Tuple(p);
    Eigen::Vector3f scale(2, 3, 4);
    EXPECT_TRUE(point.scale(scale) == Tuple(Point(-8, 18, 32)));
}

TEST(TestTransformations, TestScalingAVector) {
    Vector v = Vector(-4, 6, 8);
    Tuple vector = Tuple(v);
    Eigen::Vector3f scale(2, 3, 4);
    EXPECT_TRUE(vector.scale(scale) == Tuple(Vector(-8, 18, 32)));
}

TEST(TestTransformations, TestScalingInverse) {
    Vector v = Vector(-4, 6, 8);
    Tuple vector = Tuple(v);
    Eigen::Vector3f scale(2, 3, 4);
    EXPECT_TRUE(vector.scale_inv(scale) == Tuple(Vector(-2, 2, 2)));
}

TEST(TestTransformations, TestReflection) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Vector3f scale(-1, 1, 1);
    EXPECT_TRUE(point.scale(scale) == Tuple(Point(-2, 3, 4)));
}

TEST(TestTransformations, TestRotationAroundXAxis)  {
    Point p = Point(0, 1, 0);
    Tuple point = Tuple(p);
    EXPECT_TRUE(point.rotate_x(M_PI / 4) == Tuple(Point(0, sqrt(2) / 2, sqrt(2) / 2)));
    EXPECT_TRUE(point.rotate_x(M_PI / 2) == Tuple(Point(0, 0, 1)));
}

TEST(TestTransformations, TestInverseRotationAboutXAxis) {
    Point p = Point(0, 1, 0);
    Tuple point = Tuple(p);
    EXPECT_TRUE(point.rotate_x_inv(M_PI / 4).isApprox(Tuple(Point(0, sqrt(2) / 2, -sqrt(2) / 2)), 0.0001));
}

TEST(TestTransformations, TestRotationAroundYAxis)  {
    Point p = Point(0, 0, 1);
    Tuple point = Tuple(p);
    EXPECT_TRUE(point.rotate_y(M_PI_4).isApprox(Tuple(Point(sqrt(2) / 2, 0, sqrt(2) / 2)), 0.0001));
    EXPECT_TRUE(point.rotate_y(M_PI_2).isApprox(Tuple(Point(1, 0, 0)), 0.0001));
}

TEST(TestTransformations, TestRotationAroundZAxis) {
    Point p = Point(0, 1, 0);
    Tuple point = Tuple(p);
    EXPECT_TRUE(point.rotate_z(M_PI_4).isApprox(Tuple(Point(-sqrt(2) / 2, sqrt(2) / 2, 0)), 0.0001));
    EXPECT_TRUE(point.rotate_z(M_PI_2).isApprox(Tuple(Point(-1, 0, 0)), 0.0001));
}

TEST(TestTransformations, TestShearingTransformation) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Transform<float, 3, Eigen::Affine> t = shear3d(1, 0, 0, 0, 0, 0);
    EXPECT_TRUE(t * point == Tuple(Point(5, 3, 4)));
}

TEST(TestTransformations, TestShearingTransformationXZ) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Transform<float, 3, Eigen::Affine> t = shear3d(0, 1, 0, 0, 0, 0);
    EXPECT_TRUE(t * point == Tuple(Point(6, 3, 4)));
}

TEST(TestTransformations, TestShearingTransformationYX) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Transform<float, 3, Eigen::Affine> t = shear3d(0, 0, 1, 0, 0, 0);
    EXPECT_TRUE(t * point == Tuple(Point(2, 5, 4)));
}

TEST(TestTransformations, TestShearingTransformationYZ) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Transform<float, 3, Eigen::Affine> t = shear3d(0, 0, 0, 1, 0, 0);
    EXPECT_TRUE(t * point == Tuple(Point(2, 7, 4)));
}

TEST(TestTransformations, TestShearingTransformationsZY) {
    Point p = Point(2, 3, 4);
    Tuple point = Tuple(p);
    Eigen::Transform<float, 3, Eigen::Affine> t = shear3d(0, 0, 0, 0, 1, 0);
    EXPECT_TRUE(t * point == Tuple(Point(2, 3, 6)));
}

TEST(TestTransformations, TestTransformationsInSequence) {
    Point p = Point(1, 0, 1);
    Tuple point = Tuple(p);
    point = point.rotate_x(M_PI_2);
    point = point.scale(Eigen::Vector3f(5, 5, 5));
    point = point.translate(Eigen::Vector3f(10, 5, 7));
    EXPECT_TRUE(point == Tuple(Point(15, 0, 7)));
}

TEST(TestTransformations, TestTransformationsChained) {
    Point p = Point(1, 0, 1);
    Tuple point = Tuple(p);
    point = point.rotate_x(M_PI_2).scale(Eigen::Vector3f(5, 5, 5)).translate(Eigen::Vector3f(10, 5, 7));
    EXPECT_TRUE(point  == Tuple(Point(15, 0, 7)));
}

TEST(TestRayCaster, TestQueryRay) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    EXPECT_TRUE(r.origin == Tuple(Point(0, 0, -5)));
    EXPECT_TRUE(r.direction == Tuple(Vector(0, 0, 1)));
}

TEST(TestRayCaster, TestPointFromADistance) {
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
    EXPECT_TRUE(r.position(0) == Tuple(Point(2, 3, 4)));
    EXPECT_TRUE(r.position(1) == Tuple(Point(3, 3, 4)));
    EXPECT_TRUE(r.position(-1) == Tuple(Point(1, 3, 4)));
    EXPECT_TRUE(r.position(2.5) == Tuple(Point(4.5, 3, 4)));
}

TEST(TestRayCaster, TestIntersectSphereWithTwoPoints) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = r.intersect(&s);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 4.0);
    EXPECT_EQ(intersections[1].t, 6.0);
}

TEST(TestRayCaster, TestIntersectionEncapsulatesTAndObject) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(3.5, &s);
    EXPECT_EQ(i.t, 3.5);
    EXPECT_EQ(i.object, &s);
}

TEST(TestRayCaster, TestAggregateIntersections) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    std::vector<Intersection> intersections = {i1, i2};
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 1);
    EXPECT_EQ(intersections[1].t, 2);
}

TEST(TestRayCaster, TestHitWhenAllIntersectionsHavePositiveT) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(1, &s), Intersection(2, &s)};
    Intersection i = hit(intersections);
    EXPECT_EQ(i.t, intersections[0].t);
}

TEST(TestRayCaster, TestHitWhenSomeIntersectionsHaveNegativeT) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(-1, &s), Intersection(1, &s)};
    Intersection i = hit(intersections);
    EXPECT_EQ(i.t, intersections[1].t);
}

TEST(TestRayCaster, TestHitWhenAllIntersectionsHaveNegativeT) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(-2, &s), Intersection(-1, &s)};
    Intersection i = hit(intersections);
    EXPECT_EQ(i.object, nullptr);
}

TEST(TestRayCaster, TestHitIsAlwaysLowestNonNegativeIntersection) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    std::vector<Intersection> intersections = {Intersection(5, &s), Intersection(7, &s), Intersection(-3, &s), Intersection(2, &s)};
    Intersection i = hit(intersections);
    EXPECT_EQ(i.t, intersections[3].t);
}

TEST(TestRayTransforms, TestTranslateRay) {
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    Eigen::Vector3f translation = Eigen::Vector3f(3, 4, 5);
    Ray r2 = r.translate(translation);
    EXPECT_TRUE(r2.origin == Tuple(Point(4, 6, 8)));
    EXPECT_TRUE(r2.direction == Tuple(Vector(0, 1, 0)));
}

TEST(TestRayTransforms, TestScaleRay) {
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    Eigen::Vector3f scale = Eigen::Vector3f(2, 3, 4);
    Ray r2 = r.scale(scale);
    EXPECT_TRUE(r2.origin == Tuple(Point(2, 6, 12)));
    EXPECT_TRUE(r2.direction == Tuple(Vector(0, 3, 0)));
}

TEST(TestSphereTransforms, TestDefaultTransformationIsIdentityMatrix)  {
    Sphere s = Sphere();
    EXPECT_TRUE(s.transform == Eigen::Matrix4f::Identity());
}

TEST(TestSphereTransforms, TestAssigningATransformation) {
    Sphere s = Sphere();
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.translate(Eigen::Vector3f(2, 3, 4));
    s.set_transform(t);
    EXPECT_TRUE(s.transform == t.matrix());
    EXPECT_TRUE(s.center == Tuple(Point(2, 3, 4)));
    EXPECT_TRUE(s.radius == 1.0f);
}

TEST(TestSphereTransforms, TestIntersectingAScaledSphereWithRay) {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.scale(Eigen::Vector3f(2, 2, 2));
    s.set_transform(t);
    std::vector<Intersection> intersections = r.intersect(&s);
    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 3);
    EXPECT_EQ(intersections[1].t, 7);
    EXPECT_TRUE(s.radius == 2.0f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
