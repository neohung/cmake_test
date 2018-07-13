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

// ============ Determinant =========

template <size_t rows, size_t cols, typename T> class Matrix;

template <size_t dim, typename T> struct Determinant
{
  static T determinant(const Matrix<dim,dim,T>& m){
    T ret = 0;
    for(size_t i=0;i<dim;i++){
      ret += m[0][i] * m.cofactor(0,i);
    }
    return ret; 
  }
};

template <typename T> struct Determinant<1,T>{
  static T determinant(const Matrix<1,1,T>& m){
    return m[0][0];
  }
};

// ==================================

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

  T cofactor(size_t row, size_t col) const {
    //row+col=0, return 1, row+col=1 return -1, row+col=2 row+col=0.... 
    //return minor_matrix(row,col).det()*((row+col)%2 ? -1 : 1);
  }


  T det(void) const {
    //cal Determinant()
    assert(rows==cols);
    //return dt<dim_rows,T>::det(*this);
  }

};

/*
template <size_t dim, typename T>
Vector<dim, T>& operator+(Vector<dim, T> lhs, const Vector<dim, T>& rhs){};
*/

struct NEO
{
  NEO(){};
  //NEO& operator+(NEO lhs, NEO& rhs)
  //{
  //}
  NEO& operator+(NEO& rhs)
  {
  }
};
/*
NEO& operator+(NEO lhs, NEO& rhs)
{
}
*/
#endif
