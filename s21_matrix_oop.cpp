#include "s21_matrix_oop.h"

void S21Matrix::CreateMatrix(int rows, int cols) {
    Free();
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}


S21Matrix::S21Matrix(int rows, int cols) : rows_(0), cols_(0), matrix_(nullptr) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными.");
    }
    CreateMatrix(rows, cols);
}
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(0), cols_(0), matrix_(nullptr) {
    if (other.rows_ > 0 && other.cols_ > 0) {
        CreateMatrix(other.rows_, other.cols_);
        for (int i = 0; i < other.rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
}

S21Matrix S21Matrix::get_minor(int row, int col) {
    S21Matrix minor(rows_ - 1, cols_ - 1); 
    for (int i = 0, mi = 0; i < rows_; ++i) {
        for (int j = 0, mj = 0; j < cols_; ++j) {
            if (i != row && j != col) {
                minor.matrix_[mi][mj++] = matrix_[i][j];
                if (mj == cols_ - 1) {
                    mj = 0;
                    ++mi;
                }
            }
        }
    }
    return minor;
}
S21Matrix::S21Matrix(S21Matrix&& other) noexcept : 
    rows_(other.rows_), 
    cols_(other.cols_), 
    matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}
S21Matrix::~S21Matrix() noexcept {
    Free();
}
void S21Matrix::Free() noexcept {
    if (matrix_ != nullptr) {  
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}
bool S21Matrix::EqMatrix(const S21Matrix& other) {

    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Несовместимые размеры матриц для сложения.");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }  
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}
void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Несовместимые размеры матриц для умножения.");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            result.matrix_[i][j] = 0;
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = result; 
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix res(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            res.matrix_[j][i] = matrix_[i][j];
        }
    }
    return res;
}
S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_){
        return S21Matrix(); 
    } 
    S21Matrix res(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            S21Matrix minor = get_minor(i, j);
            res.matrix_[i][j] = pow(-1.0, i + j) * minor.Determinant();
        }
    }
    return res;
}

double S21Matrix::Determinant() {
    if (rows_ != cols_) {
        return 0;
    } 
    double det = 0;
    if (rows_ == 1) {
        return matrix_[0][0];
    }
    for (int i = 0; i < rows_; i++) {
        S21Matrix minor = get_minor(0, i);
        if (i % 2 == 0) {
            det += matrix_[0][i] * minor.Determinant();
        } 
        else {
            det -= matrix_[0][i] * minor.Determinant();
        }
    }
    return det;
}

S21Matrix S21Matrix::InverseMatrix() {
    double det = Determinant();
    if (det == 0){
        return S21Matrix();
    }
    S21Matrix complements = CalcComplements();
    S21Matrix res(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            res.matrix_[j][i] = complements.matrix_[i][j] / det;
        }
    }
    return res;
}


S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.MulNumber(num);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        Free(); 
        if (other.rows_ > 0 && other.cols_ > 0) {
            CreateMatrix(other.rows_, other.cols_);
            for (int i = 0; i < other.rows_; i++) {
                for (int j = 0; j < other.cols_; j++) {
                    matrix_[i][j] = other.matrix_[i][j];
                }
            }
        }
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

double& S21Matrix::operator()(int i, int j) {
    return matrix_[i][j];
}
