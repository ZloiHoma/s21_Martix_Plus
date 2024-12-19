#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

#define SUCCESS 0
#define FAILURE 1
#define WRONG 2
#define EPSILON 1e-7

class S21Matrix {
private:
  int rows_, cols_;
  double **matrix_;

public:
  
  S21Matrix();  
  S21Matrix(int rows, int cols);  
  S21Matrix(const S21Matrix& other);  
  S21Matrix(S21Matrix&& other) noexcept;  
  
  
  ~S21Matrix();  

  int get_rows() const { return rows_; }
  int get_cols() const { return cols_; }
  void Free() noexcept;

  void CreateMatrix(int rows, int cols);
  
  
  S21Matrix get_minor(int rows, int cols);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other); 
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  S21Matrix operator*=(const S21Matrix& other);
  double& operator()(int i, int j);  

private:
    
    
    
};
#endif