//
//  Matrix.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//


#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class Matrix
{
    vector<vector<T>> matrix;
    
public:
    Matrix(int r = 1, int c = 1)
    {
        if (r < 1 || c < 1)
            throw("Matrix size too small");
        matrix.resize(r, vector<T>(c, (T)0));
    }
    
    Matrix<T> operator * (const Matrix<T>& rhs) {
        if (cols() != rhs.rows()) {
            throw("Size Mistmatch ! Error in matrix multiplication");
        }
        
        Matrix<T> A(rows(), rhs.cols());
        
        for (int i=0; i < A.rows(); i++)
            for (int j = 0; j < A.cols(); j++) {
                A[i][j] = 0;
                for (int k = 0; k < cols(); k++) {
                    A[i][j] += (*this)[i][k] * rhs[k][j];
                }
            }
        return A;
    }
    
    Matrix<T> operator * (const double& constant) {
        Matrix<T> A(rows(), cols());
        
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                A[i][j] = (*this)[i][j] * constant;
        
        return A;
    }
    
    T conv (const Matrix<T>& rhs) {
        if (cols() != rhs.cols() && rows() != rhs.rows()) {
            throw ("Size Mismatch ! Convolution");
        }
        
        T sum = (T)0;
        
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++) {
                sum += (*this)[i][j] * rhs[i][j];
            }
        
        return sum;
    }
    
    Matrix<T> convVertOneD (const Matrix<T>& rhs) {
        if (rows() != rhs.rows() || rhs.cols() != 1) {
            throw ("Size Mismatch ! Convolution");
        }
        
        Matrix<T> A(1, cols());
        
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++) {
                A[0][j] += (*this)[i][j] * rhs[j][0];
            }
        
        return A;
    }
    
    
    
    int rows() const {
        return matrix.size();
    }
    
    int cols() const {
        return matrix[0].size();
    }
    
    vector<T>& operator[] (int index) {
        return matrix[index];
    }
    
    const vector<T>& operator [](int index) const {
        return matrix[index];
    }
    
    
};

#endif // MATRIX_H

