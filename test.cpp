//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "MathUtils.h"
#include "Canvas.h"

TEST(TestTupleVectorPoint, TestSample) {
    EXPECT_EQ(1, 1);
}

TEST(TestTupleVectorPoint, TestTupleAsAPoint) {
    Tuple t = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    EXPECT_EQ(t.x, 4.3f);
    EXPECT_EQ(t.y, -4.2f);
    EXPECT_EQ(t.z, 3.1f);
    EXPECT_EQ(t.w, 1.0f);
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TestTupleVectorPoint, TestTupleAsAVector) {
    Tuple t = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
    EXPECT_EQ(t.x, 4.3f);
    EXPECT_EQ(t.y, -4.2f);
    EXPECT_EQ(t.z, 3.1f);
    EXPECT_EQ(t.w, 0.0f);
    EXPECT_FALSE(t.isPoint());
    EXPECT_TRUE(t.isVector());
}

TEST(TestTupleVectorPoint, TestCreateTupleFromPoint) {
    Point p = Point(4.0f, -4.0f, 3.0f);
    Tuple t = Tuple(p);
    EXPECT_EQ(t.x, 4.0f);
    EXPECT_EQ(t.y, -4.0f);
    EXPECT_EQ(t.z, 3.0f);
    EXPECT_EQ(t.w, 1.0f);
    EXPECT_TRUE(t.isPoint());
    EXPECT_FALSE(t.isVector());
}

TEST(TestTupleVectorPoint, TestCreateTupleFromVector) {
    Vector v = Vector(4.0f, -4.0f, 3.0f);
    Tuple t = Tuple(v);
    EXPECT_EQ(t.x, 4.0f);
    EXPECT_EQ(t.y, -4.0f);
    EXPECT_EQ(t.z, 3.0f);
    EXPECT_EQ(t.w, 0.0f);
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
    EXPECT_EQ(v1.magnitude(), 1.0f);
    Vector v2 = Vector(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(v2.magnitude(), 1.0f);
    Vector v3 = Vector(0.0f, 0.0f, 1.0f);
    EXPECT_EQ(v3.magnitude(), 1.0f);
    Vector v4 = Vector(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v4.magnitude(), sqrt(14.0f));
    Vector v5 = Vector(-1.0f, -2.0f, -3.0f);
    EXPECT_EQ(v5.magnitude(), sqrt(14.0f));
}

TEST(TestTupleVectorPoint, TestVectorNormalize) {
    Vector v1 = Vector(4.0f, 0.0f, 0.0f);
    Vector expected1 = Vector(1.0f, 0.0f, 0.0f);
    Vector result1 = v1.normalize();
    EXPECT_TRUE(result1 == expected1);
    Vector v2 = Vector(1.0f, 2.0f, 3.0f);
    Vector expected2 = Vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f));
    Vector result2 = v2.normalize();
    EXPECT_TRUE(result2 == expected2);
}

TEST(TestTupleVectorPoint, TestVectorMagnitudeAfterNormalize) {
    Vector v = Vector(1.0f, 2.0f, 3.0f);
    Vector normalized = v.normalize();
    EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
