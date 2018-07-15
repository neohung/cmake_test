#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <assert.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

template <size_t dim, typename T> struct Vector
{
protected:
  T data[dim];
public:
  Vector(){
    for(size_t i=0;i<dim;i++)data[i]=T();
  }
  T& operator[](const size_t i){assert(i<dim);return data[i];}
  const T& operator[](const size_t i) const {assert(i<dim);return data[i];}
  Vector<dim, T>& operator=(const Vector<dim, T>& vec){
    if (this == &vec)
      return *this;
    memcpy(data,&vec[0],sizeof(data));
    return *this;
  }
  Vector<dim, T>& operator+=(const Vector<dim, T>& vec){
    for(size_t i=0;i<dim;i++) data[i] += vec[i];
    return *this;
  }

  const Vector<dim, T> operator+(const Vector<dim, T>& vec) const{
    Vector<dim, T> ret = *this;
    ret += vec;
    return ret;
  }

  Vector<dim, T>& operator-=(const Vector<dim, T>& vec){
    for(size_t i=0;i<dim;i++) data[i] -= vec[i];
    return *this;
  }

  const Vector<dim, T> operator-(const Vector<dim, T>& vec) const{
    Vector<dim, T> ret = *this;
    ret -= vec;
    return ret;
  }
 
  Vector<dim, T>& operator*=(const T v){
    for(size_t i=0;i<dim;i++) data[i] *= v;
    return *this;
  }

  const Vector<dim, T> operator*(const T v) const{
    Vector<dim, T> ret = *this;
    ret *= v;
    return ret;
  }

  float norm() { 
    float sum = 0; 
    for(size_t i=0;i<dim;i++) sum += (data[i]* data[i]);
    return sqrt(sum);
  }
  
  Vector<dim, T>&  normalize(){
    float n = 1/norm();
    for(size_t i=0;i<dim;i++) {
      data[i] *= n;
    }
    return *this;
  }
  const T operator*(const Vector<dim, T>& vec) const{
    T sum = 0;
    for(size_t i=0;i<dim;i++) {
      sum += data[i] * vec[i];
    }
    return sum;
  }
  //int size() {return dim;}
};

template <size_t rows, size_t cols, typename T> class Matrix{
protected:
  Vector<cols,T> data[rows];
public:
  void zero(){
    for(size_t j=0;j<rows;j++)
      for(size_t i=0;i<cols;i++)
        data[j][i] = T();
  }
  Matrix(){ zero(); }
  Vector<cols,T>& operator[](const size_t j){assert(j<rows);return data[j];}
  const Vector<cols,T>& operator[](const size_t j) const {assert(j<rows);return data[j];}
  //
  Matrix<rows,cols,T>& operator*=(const T v){
    for(size_t j=0;j<rows;j++)
      for(size_t i=0;i<cols;i++)
        data[j][i] *= v;
    return *this;
  }
  const Matrix<rows,cols,T> operator*(const T v) const{
    Matrix<rows,cols,T> ret = *this;
    ret *= v;
    return ret;
  }
  //Return col vector
  Vector<rows,T> col(const size_t i){
    assert(i < cols);
    Vector<rows,T> ret;
    for(size_t j=0;j<rows;j++){
      ret[j] = data[j][i];
    }
    return ret;
  }
  void set_col(size_t i, Vector<rows,T> r){
    assert(i < cols);
    for(size_t j=0;j<rows;j++){
      data[j][i] = r[j];
    }
  }
  //Static function to return A Identity matrix
  static Matrix<rows,cols,T> identity(void){
    Matrix<rows,cols,T> ret;
    for(size_t j=0;j<rows;j++)
      for(size_t i=0;i<cols;i++)
        ret[j][i] = (i==j);
    return ret;
  }
  // Transpose
  Matrix<rows,cols,T> transpose(void) {
    Matrix<rows,cols,T> ret;
    for(size_t j=0;j<rows;j++)
      ret[j] = this->col(j);
    return ret;
  }
  //get_minor(row, col)
  // ex [1,2,3] get_minor(0,0) --> [5 6], get_minor(0, 1) --> [4 6]
  //    [4,5,6]                    [8 9]                      [7 9]
  //    [7,8,9]
  Matrix<rows-1,cols-1,T> minor_matrix(size_t row, size_t col) {
    Matrix<rows-1,cols-1,T> ret;
    for(size_t j=0;j<rows-1;j++)
      for(size_t i=0;i<cols-1;i++)
        ret[j][i] = data[j<row?j:j+1][i<col?i:i+1];
    return ret;
  }
  // det| 3, 2,-5| = -54, det| 1,2,3,4 | = -101, det| 2,2,5 | = 6
  //    |-1, 0,-2|           | 2,1,4,4 |            |-2,1,2 |
  //    | 3,-4, 1|           | 3,4,1,5 |            | 6,3,9 |
  //                         | 4,2,5,1 |
  T determinant(){
    assert(rows == cols);
    T sum = T();
    for(int i=0;i<rows;i++){
      sum += data[0][i]*minor_matrix(0,i).determinant() * ((i)%2 ? -1 : 1);
    }
    return sum;
  }

  Matrix<rows,cols,T> adjugate() {
    Matrix<rows,cols,T> ret;
    for(size_t j=0;j<rows;j++)
      for(size_t i=0;i<cols;i++)
        ret[j][i] = minor_matrix(j,i).determinant() * ((i+j)%2 ? -1 : 1);
    return ret;
  }

  Matrix<rows,cols,T> invert_transpose() {
    Matrix<rows,cols,T> ret = adjugate();
    //T tmp = ret[0]*col(0); <-- wrong
    T tmp = ret[0]*data[0];
    return ret*(1/tmp);
    //return ret;
  }
 // A[ 2,2,5]->A-1=[0.5,-0.5,-0.167]  , A[ 3, 2,-5]->A-1=[0.148148  -0.333333  0.074074]
  // [-2,1,2]     [5.0,-2.0,-2.333]      [-1, 0,-2]      [0.092593  -0.333333 -0.203704]
  // [ 6,3,9]     [ -2, 1.0, 1.0  ]      [ 3,-4, 1]      [-0.074074 -0.333333 -0.037037]
  //A[1,2,3,4]->A-1=[ -0.712871,  0.415842,  0.227723,  0.049505 ]
  // [2,1,4,4]      [  0.633663, -0.702970,  0.019802,  0.178218 ]
  // [3,4,1,5]      [  0.346535, -0.118812, -0.207921,  0.128713 ]
  // [4,2,5,1]      [ -0.148515,  0.336634,  0.089109, -0.198020 ]
  Matrix<rows,cols,T> invert() {
    return invert_transpose().transpose();
  }
};

template <typename T> class Matrix<1,1,T>{
protected:
 Vector<1,T> data[1];
public:
  Vector<1,T>& operator[](const size_t i){assert(i==0);return data[i];}
  const Vector<1,T>& operator[](const size_t i) const {assert(i==0);return data[i];}
  T determinant(){
    return data[0][0];
  }
};

#endif
