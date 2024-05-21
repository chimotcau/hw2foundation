#include <memory>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    int rows, cols;
    std::unique_ptr<std::vector<std::vector<int>>> data;
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(std::make_unique<std::vector<std::vector<int>>>(rows, std::vector<int>(cols))) {}

    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(std::make_unique<std::vector<std::vector<int>>>(*other.data)) {}

    // Move constructor
    Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(std::move(other.data)) {
        other.rows = 0;
        other.cols = 0;
    }

    // Getter and setter
    int& operator()(int row, int col) { return (*data)[row][col]; }
    const int& operator()(int row, int col) const { return (*data)[row][col]; }

    // Matrix operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices are not of same size");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices are not of same size");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrices are not compatible for multiplication");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}
// Function to calculate trace
int trace(Matrix& mat) {
    if (mat.getRows() != mat.getCols()) {
        throw std::invalid_argument("Matrix is not square");
    }

    int trace = 0;
    for (int i = 0; i < mat.getRows(); ++i) {
        trace += mat(i, i);
    }
    return trace;
}
// Lambda to transpose matrix
auto transpose = [](Matrix& mat) -> Matrix {
    Matrix trans(mat.getCols(), mat.getRows());
    for (int i = 0; i < mat.getRows(); ++i) {
        for (int j = 0; j < mat.getCols(); ++j) {
            trans(j, i) = mat(i, j);
        }
    }
    return trans;
};
