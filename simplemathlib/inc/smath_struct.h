#ifndef _SMATH_STRUCT_H_
#define _SMATH_STRUCT_H_

#include <assert.h>
#include <string>

template <size_t dim, typename T> struct vec{
  vec(){
    for (size_t i=dim; i--; data[i] = T());
  }
  T& operator[](const size_t i)       { assert(i<dim); return data[i];}
  const T& operator[](const size_t i) const { assert(i<dim); return data[i];}
private:
  T data[dim];
};

template <typename T> struct vec<2,T>{
  vec(){
    for (size_t i=2; i--; data[i] = T());
  }
  vec(T i, T j){
    data[0] = i;
    data[1] = j;
  }
  T& operator[](const size_t i)       { assert(i<2); return data[i];}
  const T& operator[](const size_t i) const { assert(i<2); return data[i];}
  T& x(){return data[0];} 
  T& y(){return data[1];} 
  //template <class U> vec<2,T>(const vec<2,U> &v);
private:
  T data[2];
};
template <typename T> struct vec<3,T>{
  vec(){
    for (size_t i=3; i--; data[i] = T());
  }
  vec(T i, T j, T k){
    data[0] = i;
    data[1] = j;
    data[2] = k;
  }
  T& operator[](const size_t i)       { assert(i<3); return data[i];}
  const T& operator[](const size_t i) const { assert(i<3); return data[i];}
  T& x(){return data[0];}
  T& y(){return data[1];}
  T& z(){return data[2];}
private:
  T data[3];
};

template <typename T> struct vec<4,T>{
  vec(){
    for (size_t i=4; i--; data[i] = T());
  }
  vec(T i, T j, T k, T l){
    data[0] = i;
    data[1] = j;
    data[2] = k;
    data[3] = l;
  }
  T& operator[](const size_t i)       { assert(i<4); return data[i];}
  const T& operator[](const size_t i) const { assert(i<4); return data[i];}
  T& x(){return data[0];}
  T& y(){return data[1];}
  T& z(){return data[2];}
  T& w(){return data[3];}
private:
  T data[4];
};

//OPERATOR+
template <size_t dim, typename T> vec<dim, T> operator+ (vec<dim, T> lhs, const vec<dim, T>& rhs)
{
  for (size_t i=dim; i--; lhs[i]+=rhs[i]);
  return lhs;
}
 
//OPERATOR-
template <size_t dim, typename T> vec<dim, T> operator- (vec<dim, T> lhs, const vec<dim, T>& rhs)
{
  for (size_t i=dim; i--; lhs[i]-=rhs[i]);
  return lhs;
}

//OPERATOR+
template <size_t dim, typename T> T operator* (const vec<dim, T>& lhs, const vec<dim, T>& rhs)
{ 
  T ret = T();
  for (size_t i=dim; i--; ret += lhs[i]*rhs[i]);
  return ret;
}

template <typename T> vec<3,T> cross_dot(vec<3,T> v1, vec<3,T> v2) {
    return vec<3,T>(v1.y()*v2.z() - v1.z()*v2.y(), 
                    v1.z()*v2.x() - v1.x()*v2.z(), 
                    v1.x()*v2.y() - v1.y()*v2.x());
}

typedef vec<2,float> Vec2f;
typedef vec<2,int>   Vec2i;
typedef vec<3,float> Vec3f;
typedef vec<3,int>   Vec3i;
typedef vec<4,float> Vec4f;
//##############################################################

template<size_t dim_rows,size_t dim_cols,typename T> class mat;
//
template<size_t DIM,typename T> struct dt {
    static T det(const mat<DIM,DIM,T>& src) {
        T ret=0;
        //MAT Need to implement cofactor(row,col) function
        for (size_t i=DIM; i--; ret += src[0][i]*src.cofactor(0,i));
        return ret;
    }
};

template<typename T> struct dt<1,T> {
  static T det(const mat<1,1,T>& src) {
    return src[0][0];
  }
};

//##############################################################
//CLASS mat(Matrix)
template<size_t dim_rows,size_t dim_cols,typename T> class mat{
protected:
  vec<dim_cols,T> rows[dim_rows];
public:
  void zero(){
    for (size_t i=dim_rows; i--;)
      for (size_t j=dim_cols;j--; rows[i][j]=0);
  }
  mat() {
    zero();
  }
  // mat[i] would return i`th row
  vec<dim_cols,T>& operator[] (size_t i){assert(i<dim_rows); return rows[i];};
  const vec<dim_cols,T>& operator[] (size_t i) const {assert(i<dim_rows); return rows[i];};
  static mat<dim_rows,dim_cols,T> identity() {
    mat<dim_rows,dim_cols,T> ret;
    for (size_t i=dim_rows; i--;)
      for (size_t j=dim_cols;j--; ret[i][j]=(i==j));
    return ret;
  }
  //mat.col(i) would return i`th col
  vec<dim_rows,T> col(const size_t i) const {
    assert(i<dim_cols);
    vec<dim_rows,T> ret;
    for (size_t j=dim_rows; j--; ret[j]=rows[j][i]);
    return ret;
  }
  void set_col(size_t i, vec<dim_rows,T> v) {
    assert(i<dim_cols);
    for (size_t j=dim_rows; j--; rows[j][i]=v[j]);
  }
  
  mat<dim_cols,dim_rows,T> transpose() {
    mat<dim_cols,dim_rows,T> ret;
    //Set row from col
    for (size_t i=dim_rows; i--; ret[i]=this->col(i));
    return ret;
  }
  
  void display(const char* str){
    printf("%s:\n", str);
    for (size_t i=dim_rows; i--;){
      for (size_t j=dim_cols;j--;){
        //std::string s = "" + std::sstr("",rows[i][j]);
        //printf("%s ", s.c_str());
        printf("%d ", rows[i][j]);
      }
      printf("\n");
    }
  }
  //get_minor(row, col)
  // ex [1,2,3] get_minor(0,0) --> [5 6], get_minor(0, 1) --> [4 6]
  //    [4,5,6]                    [8 9]                      [7 9]
  //    [7,8,9]
  mat<dim_rows-1,dim_cols-1,T> get_minor(size_t row, size_t col) const {
    mat<dim_rows-1,dim_cols-1,T> ret;
    for (size_t i=dim_rows-1; i--; )
      for (size_t j=dim_cols-1;j--; ret[i][j]=rows[i<row?i:i+1][j<col?j:j+1]);
    return ret;
  }

  //cofactor
  T cofactor(size_t row, size_t col) const {
    //row+col=0, return 1, row+col=1 return -1, row+col=2 row+col=0.... 
    return get_minor(row,col).det()*((row+col)%2 ? -1 : 1);
  }

  T det() const {
    //cal Determinant()
    assert(dim_rows==dim_cols);
    return dt<dim_rows,T>::det(*this);
  }
  //adjugate matrix
  // [a b]  adj [d -b]       
  // [c d]      [-c a]       
  mat<dim_rows,dim_cols,T> adjugate() const {
    mat<dim_rows,dim_cols,T> ret;
    for (size_t i=dim_rows; i--; )
      for (size_t j=dim_cols; j--; ret[i][j]=cofactor(i,j));
    return ret;
  }

  mat<dim_rows,dim_cols,T> invert_transpose() {
    mat<dim_rows,dim_cols,T> ret = adjugate();
    T tmp = ret[0]*rows[0];
    return ret/tmp;
  }

  mat<dim_rows,dim_cols,T> invert() {
    return invert_transpose().transpose();
  }

};

template<size_t row1,size_t col,size_t col2,typename T> mat<row1,col2,T> operator*(const mat<row1,col,T>& lhs, const mat<col,col2,T>& rhs) {
  mat<row1,col2,T> ret;
  for (size_t i=row1; i--; )
    for (size_t j=col2; j--; ret[i][j]=lhs[i]*rhs.col(j));
  return ret;
}
#endif
