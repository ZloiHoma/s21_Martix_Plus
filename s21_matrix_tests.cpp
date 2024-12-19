#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(S21MatrixTest, ConstructorTest) {
  S21Matrix m(2, 2);
  EXPECT_NO_THROW(S21Matrix m1(3, 3));
  EXPECT_THROW(S21Matrix m2(0, 0), std::invalid_argument);
}

TEST(S21MatrixTest, DefaultConstructor) {
    S21Matrix mat;
    EXPECT_EQ(mat.get_rows(), 0);
    EXPECT_EQ(mat.get_cols(), 0);
}

TEST(S21MatrixTest, SumMatrixTest) {
    S21Matrix mat1(2, 2);
    S21Matrix mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;
    mat2(0, 0) = 5; mat2(0, 1) = 6;
    mat2(1, 0) = 7; mat2(1, 1) = 8;

    S21Matrix result = mat1 + mat2;
    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

TEST(S21MatrixTest, SubMatrix) {
    S21Matrix mat1(2, 2);
    S21Matrix mat2(2, 2);
    mat1(0, 0) = 5; mat1(0, 1) = 6;
    mat1(1, 0) = 7; mat1(1, 1) = 8;
    mat2(0, 0) = 1; mat2(0, 1) = 2;
    mat2(1, 0) = 3; mat2(1, 1) = 4;

    S21Matrix result = mat1 - mat2;
    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 4);
}

TEST(S21MatrixTest, MulNumber) {
    S21Matrix mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;

    S21Matrix result = mat * 2;
    EXPECT_EQ(result(0, 0), 2);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 6);
    EXPECT_EQ(result(1, 1), 8);
}

TEST(S21MatrixTest, MulMatrix) {
    S21Matrix mat1(2, 3);
    S21Matrix mat2(3, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2; mat1(0, 2) = 3;
    mat1(1, 0) = 4; mat1(1, 1) = 5; mat1(1, 2) = 6;
    mat2(0, 0) = 7; mat2(0, 1) = 8;
    mat2(1, 0) = 9; mat2(1, 1) = 10;
    mat2(2, 0) = 11; mat2(2, 1) = 12;

    S21Matrix result = mat1 * mat2;
    EXPECT_EQ(result(0, 0), 58);
    EXPECT_EQ(result(0, 1), 64);
    EXPECT_EQ(result(1, 0), 139);
    EXPECT_EQ(result(1, 1), 154);
}

TEST(S21MatrixTest, Transpose) {
    S21Matrix mat(2, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

    S21Matrix result = mat.Transpose();
    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 2);
    EXPECT_EQ(result(1, 1), 5);
    EXPECT_EQ(result(2, 0), 3);
    EXPECT_EQ(result(2, 1), 6);
}

TEST(S21MatrixTest, Determinant) {
    S21Matrix mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;

    EXPECT_EQ(mat.Determinant(), -2);
}

TEST(S21MatrixTest, EqMatrix) {
    S21Matrix mat1(2, 2);
    S21Matrix mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;

    mat2(0, 0) = 1; mat2(0, 1) = 2;
    mat2(1, 0) = 3; mat2(1, 1) = 4;

    EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, CalcComplements) {
    S21Matrix mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;

    S21Matrix result = mat.CalcComplements();
    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), -3);
    EXPECT_EQ(result(1, 0), -2);
    EXPECT_EQ(result(1, 1), 1);
}

TEST(S21MatrixTest, InverseMatrix) {
    S21Matrix mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;

    S21Matrix result = mat.InverseMatrix();
    EXPECT_EQ(result(0, 0), -2);
    EXPECT_EQ(result(0, 1), 1);
    EXPECT_EQ(result(1, 0), 1.5);
    EXPECT_EQ(result(1, 1), -0.5);
}

TEST(S21MatrixTest, EmptyMatrix) {
    S21Matrix mat;
    EXPECT_EQ(mat.get_rows(), 0);
    EXPECT_EQ(mat.get_cols(), 0);
}
