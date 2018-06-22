////////////////////////////////////////////////////////////////////////////

#include "smath.h"
#include <math.h> //for sqrt
#include <stdio.h> //for sqrt

#ifdef WIN32
//#include <qdatetime.h>
#endif
//###########################################################################
void SVector2::zero()
{
  int i;
  for (i = 0; i < 2; i++)
    m_data[i] = 0;
}
SVector2::SVector2()
{
  zero();
}

SVector2::SVector2(SFLOAT x, SFLOAT y)
{
  m_data[0] = x;
  m_data[1] = y;
}

SFLOAT SVector2::dotProduct(SVector2& a, SVector2& b)
{
  return a.x() * b.x() + a.y() * b.y();
}

SFLOAT SVector2::length()
{
  return sqrt( m_data[0]* m_data[0]+ m_data[1]* m_data[1]);
}
void SVector2::normalize()
{
   SFLOAT l = length();
   if (l == 0)
        return;
    m_data[0] /= l;
    m_data[1] /= l;
}

SVector2& SVector2::operator =(const SVector2& vec)
{
  if (this == &vec)
    return *this;

  m_data[0] = vec.m_data[0];
  m_data[1] = vec.m_data[1];
  return *this;
}

SVector2& SVector2::operator +=(const SVector2& vec)
{
  m_data[0] += vec.m_data[0];
  m_data[1] += vec.m_data[1];
  return *this;
}
SVector2& SVector2::operator -=(const SVector2& vec)
{
  m_data[0] -= vec.m_data[0];
  m_data[1] -= vec.m_data[1];
  return *this;
}
SVector2& SVector2::operator +=(const SFLOAT& f)
{
  m_data[0] += f;
  m_data[1] += f;
  return *this;
}
SVector2& SVector2::operator -=(const SFLOAT& f)
{
  m_data[0] -= f;
  m_data[1] -= f;
  return *this;
}

const SVector2 SVector2::operator +(const SVector2& vec) const
{
    SVector2 result = *this;
    result += vec;
    return result;
}

const SVector2 SVector2::operator -(const SVector2& vec) const
{
    SVector2 result = *this;
    result -= vec;
    return result;
}

const SVector2 SVector2::operator +(const SFLOAT& f) const
{
    SVector2 result = *this;
    result += f;
    return result;
}

const SVector2 SVector2::operator -(const SFLOAT& f) const
{
    SVector2 result = *this;
    result -= f;
    return result;
}

void SVector2::display()
{
  printf("data: (%f,%f)\n", m_data[0],m_data[1]);
}

//############################################################################

void SVector3::zero()
{
    for (int i = 0; i < 3; i++)
        m_data[i] = 0;
}

SVector3::SVector3()
{
    zero();
}

SVector3::SVector3(SFLOAT x, SFLOAT y, SFLOAT z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}


SVector3& SVector3::operator =(const SVector3& vec)
{
   if (this == &vec)
     return *this;

    m_data[0] = vec.m_data[0];
    m_data[1] = vec.m_data[1];
    m_data[2] = vec.m_data[2];

    return *this;
}

const SVector3& SVector3::operator +=(const SFLOAT& f)
{
    for (int i = 0; i < 3; i++)
        m_data[i] += f;
    return *this;
}

const SVector3& SVector3::operator +=(const SVector3& vec)
{
    for (int i = 0; i < 3; i++)
        m_data[i] += vec.m_data[i];
    return *this;
}

const SVector3& SVector3::operator -=(const SFLOAT& f)
{
    for (int i = 0; i < 3; i++)
        m_data[i] -= f;
    return *this;
}

const SVector3& SVector3::operator -=(const SVector3& vec)
{
    for (int i = 0; i < 3; i++)
        m_data[i] -= vec.m_data[i];
    return *this;
}

const SVector3 SVector3::operator +(const SVector3& vec) const
{
    SVector3 result = *this;
    result += vec;
    return result;
}

const SVector3 SVector3::operator -(const SVector3& vec) const
{
    SVector3 result = *this;
    result -= vec;
    return result;
}

const SVector3 SVector3::operator +(const SFLOAT& f) const
{
    SVector3 result = *this;
    result += f;
    return result;
}

const SVector3 SVector3::operator -(const SFLOAT& f) const
{
    SVector3 result = *this;
    result -= f;
    return result;
}


SFLOAT SVector3::dotProduct(const SVector3& a, const SVector3& b)
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

//Return d --> [ax,ay,az] X [bx,by,bz] = [aybz-byaz, -1*(axbz-bxaz), axby-bxay]
void SVector3::crossProduct(const SVector3& a, const SVector3& b, SVector3& d)
{
    d.setX(a.y() * b.z() - a.z() * b.y());
    d.setY(a.z() * b.x() - a.x() * b.z());
    d.setZ(a.x() * b.y() - a.y() * b.x());
}

void SVector3::normalize()
{
    SFLOAT length = sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] +
            m_data[2] * m_data[2]);

    if (length == 0)
        return;

    m_data[0] /= length;
    m_data[1] /= length;
    m_data[2] /= length;
}

SFLOAT SVector3::length()
{
    return sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] +
            m_data[2] * m_data[2]);
}

void SVector3::display()
{
  printf("data: (%f,%f,%f)\n", m_data[0],m_data[1],m_data[2]);
}

//############################################################################

void SMatrix4x4::fill(SFLOAT f)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] = f;
}
SMatrix4x4::SMatrix4x4()
{
  fill(0);
}

void SMatrix4x4::display()
{
  printf("Data:\n");
  for (int row = 0; row < 4; row++){
  printf("[");
    for (int col = 0; col < 4; col++)
      printf("%f ", m_data[row][col]);
    printf("]\n");
  }
}

void SMatrix4x4::setAsIdentity()
{
    fill(0);
    m_data[0][0] = 1;
    m_data[1][1] = 1;
    m_data[2][2] = 1;
    m_data[3][3] = 1;
}

SMatrix4x4 SMatrix4x4::transposed()
{
    SMatrix4x4 result;
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            result.m_data[col][row] = m_data[row][col];
    return result;
}

SMatrix4x4& SMatrix4x4::operator =(const SMatrix4x4& mat)
{
  if (this == &mat)
        return *this;
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] = mat.m_data[row][col];
  return *this;
}

SMatrix4x4& SMatrix4x4::operator +=(const SMatrix4x4& mat)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] += mat.m_data[row][col];
  return *this;
}

SMatrix4x4& SMatrix4x4::operator -=(const SMatrix4x4& mat)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] -= mat.m_data[row][col];
  return *this;
}

SMatrix4x4& SMatrix4x4::operator *=(const SFLOAT f)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] *= f;
    return *this;
}

SMatrix4x4& SMatrix4x4::operator +=(const SFLOAT f)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] += f;
  return *this;
}

SMatrix4x4& SMatrix4x4::operator -=(const SFLOAT f)
{
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      m_data[row][col] -= f;
  return *this;
}

const SMatrix4x4 SMatrix4x4::operator +(const SMatrix4x4& mat) const
{
  SMatrix4x4 result = *this;
  result += mat;
  return result;
}

const SMatrix4x4 SMatrix4x4::operator -(const SMatrix4x4& mat) const
{
  SMatrix4x4 result = *this;
  result -= mat;
  return result;
}

const SMatrix4x4 SMatrix4x4::operator +(const SFLOAT f) const
{
  SMatrix4x4 result = *this;
  result += f;
  return result;
}
const SMatrix4x4 SMatrix4x4::operator -(const SFLOAT f) const
{
  SMatrix4x4 result = *this;
  result -= f;
  return result;
}

const SMatrix4x4 SMatrix4x4::operator *(const SFLOAT f) const
{
  SMatrix4x4 result = *this;
  result *= f;
  return result;
}

SMatrix4x4& SMatrix4x4::operator *=(const SMatrix4x4& mat)
{
  SMatrix4x4 tmp = SMatrix4x4();
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      tmp.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col] +
                    m_data[row][2] * mat.m_data[2][col] +
                    m_data[row][3] * mat.m_data[3][col];
    *this = tmp;
    return *this;
}

const SMatrix4x4 SMatrix4x4::operator *(const SMatrix4x4& mat) const
{
  //sigma(Air*Brj) , here r=0 to 3
  SMatrix4x4 result = *this;
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            result.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col] +
                    m_data[row][2] * mat.m_data[2][col] +
                    m_data[row][3] * mat.m_data[3][col];
  return result;
}

SFLOAT SMatrix4x4::minorMatrix(const int row, const int col)
{
    //  [1 2 3]
    //  [0 2 3]
    //  [0 1 3]
    //  [0 1 2]
    static int map[] = {1, 2, 3, 0, 2, 3, 0, 1, 3, 0, 1, 2};

    int *rc;
    int *cc;
    SFLOAT res = 0;

    rc = map + row * 3;
    cc = map + col * 3;

    res += m_data[rc[0]][cc[0]] * m_data[rc[1]][cc[1]] * m_data[rc[2]][cc[2]];
    res -= m_data[rc[0]][cc[0]] * m_data[rc[1]][cc[2]] * m_data[rc[2]][cc[1]];
    res -= m_data[rc[0]][cc[1]] * m_data[rc[1]][cc[0]] * m_data[rc[2]][cc[2]];
    res += m_data[rc[0]][cc[1]] * m_data[rc[1]][cc[2]] * m_data[rc[2]][cc[0]];
    res += m_data[rc[0]][cc[2]] * m_data[rc[1]][cc[0]] * m_data[rc[2]][cc[1]];
    res -= m_data[rc[0]][cc[2]] * m_data[rc[1]][cc[1]] * m_data[rc[2]][cc[0]];
  
    return res;
}

SFLOAT SMatrix4x4::determinant()
{
    SFLOAT det = 0;
    det += m_data[0][0] * minorMatrix(0, 0);
    det -= m_data[0][1] * minorMatrix(0, 1);
    det += m_data[0][2] * minorMatrix(0, 2);
    det -= m_data[0][3] * minorMatrix(0, 3);
    return det;
}

SMatrix4x4 SMatrix4x4::inverted()
{
    SMatrix4x4 res = SMatrix4x4();

    SFLOAT det = determinant();

    if (det == 0) {
        res.setAsIdentity();
        return res;
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if ((row + col) & 1)
                //[col][row] --> [row,col] transposed, only (0,0) (1,1) (2,2) (3,3) no change
                res.m_data[col][row] = -minorMatrix(row, col) / det;
            else
                res.m_data[col][row] = minorMatrix(row, col) / det;
        }
    }
    return res;
}

//############################################################################

void SMatrix2x2::fill(SFLOAT f)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] = f;
}

SMatrix2x2::SMatrix2x2()
{
  fill(0);
}

void SMatrix2x2::display()
{
  printf("Data:\n");
  for (int row = 0; row < 2; row++){
    printf("[");
    for (int col = 0; col < 2; col++)
      printf("%f ", m_data[row][col]);
    printf("]\n");
  }
}

void SMatrix2x2::setAsIdentity()
{
  fill(0);
  m_data[0][0] = 1;
  m_data[1][1] = 1;
}

SMatrix2x2 SMatrix2x2::transposed()
{
  SMatrix2x2 result;
  for (int row = 0; row < 2; row++){
    for (int col = 0; col < 2; col++)
      result.m_data[col][row] = m_data[row][col];
  }
  return result;
}

SMatrix2x2& SMatrix2x2::operator =(const SMatrix2x2& mat)
{
  if (this == &mat)
    return *this;
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] = mat.m_data[row][col];
  return *this;
}

SMatrix2x2& SMatrix2x2::operator +=(const SMatrix2x2& mat)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] += mat.m_data[row][col];
  return *this;
}

SMatrix2x2& SMatrix2x2::operator -=(const SMatrix2x2& mat)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] -= mat.m_data[row][col];
  return *this;
}

SMatrix2x2& SMatrix2x2::operator *=(const SFLOAT f)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] *= f;
  return *this;
}

SMatrix2x2& SMatrix2x2::operator +=(const SFLOAT f)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] += f;
  return *this;
}

SMatrix2x2& SMatrix2x2::operator -=(const SFLOAT f)
{
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      m_data[row][col] -= f;
  return *this;  
}

const SMatrix2x2 SMatrix2x2::operator +(const SMatrix2x2& mat) const
{
  SMatrix2x2 result = *this;
  result += mat;  
  return result;
}

const SMatrix2x2 SMatrix2x2::operator -(const SMatrix2x2& mat) const
{
  SMatrix2x2 result = *this;
  result -= mat;  
  return result; 
}

const SMatrix2x2 SMatrix2x2::operator +(const SFLOAT f) const
{
  SMatrix2x2 result = *this;
  result += f;  
  return result; 
}
  
const SMatrix2x2 SMatrix2x2::operator -(const SFLOAT f) const
{
  SMatrix2x2 result = *this;
  result -= f;  
  return result; 
}

const SMatrix2x2 SMatrix2x2::operator *(const SFLOAT f) const
{
  SMatrix2x2 result = *this;
  result *= f;
  return result;
}

SMatrix2x2& SMatrix2x2::operator *=(const SMatrix2x2& mat)
{
  SMatrix2x2 tmp = SMatrix2x2();
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      tmp.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col];
    *this = tmp;
    return *this;
}

const SMatrix2x2 SMatrix2x2::operator *(const SMatrix2x2& mat) const
{
  SMatrix2x2 result = *this;
  for (int row = 0; row < 2; row++)
    for (int col = 0; col < 2; col++)
      result.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col];
  return result;
}


//minorMatrix(0, 0) = d
//minorMatrix(1, 1) = a
//minorMatrix(0, 1) = b
//minorMatrix(1, 0) = c
SFLOAT SMatrix2x2::minorMatrix(const int row, const int col)
{
  static int map[] = {1,0};
  //A[a b]
  // [c d]  (0,0) -> (1,1)d, (0,1) -> (0,1) b , (1,0) -> (1,0) c, (1,1) -> (0,0) a
  int* rc;
  int* cc;
  rc = map + row * 1;
  cc = map + col * 1;

  SFLOAT res = 0;

  res += m_data[rc[0]][cc[0]];
  return res;
}

SFLOAT SMatrix2x2::determinant()
{
  SFLOAT det = 0;
  det += m_data[0][0] * m_data[1][1];
  det -= m_data[0][1] * m_data[1][0];
  return det;
}

SMatrix2x2 SMatrix2x2::inverted()
{
  // A = [a b]  inverted = 1/det(A) * [d  -b]
  //     [c d]                        [-c  a]
  // det(A) = a*d - b*c
  //
  SMatrix2x2 result = SMatrix2x2();;
  SFLOAT det = determinant();
  if (det == 0) {
    result.setAsIdentity();
    return result;
  }
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 2; col++) {
      if ((row + col) & 1)
        //[col][row]  <==> [row][cp;] transposed
        result.m_data[col][row] = -minorMatrix(row, col) / det;
      else
        result.m_data[col][row] = minorMatrix(row, col) / det;
      }
    }
    return result;
}

//############################################################################
/*
class SMatrix3x3
{
public:
    SFLOAT minorMatrix(const int row, const int col);
    SFLOAT determinant();
    SMatrix3x3 inverted();

};
*/
void SMatrix3x3::fill(SFLOAT f)
{
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      m_data[row][col] = f;
}

SMatrix3x3::SMatrix3x3()
{
  fill(0);
}

void SMatrix3x3::display()
{
  printf("Data:\n");
  for (int row = 0; row < 3; row++){
    printf("[");
    for (int col = 0; col < 3; col++)
      printf("%f ", m_data[row][col]);
    printf("]\n");
  }
}

void SMatrix3x3::setAsIdentity()
{
  fill(0);
  for (int i = 0; i < 3; i++)
    m_data[i][i] = 1;
}

SMatrix3x3 SMatrix3x3::transposed()
{
  SMatrix3x3 result;
  for (int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++)
      result.m_data[col][row] = m_data[row][col];
  }
  return result;
}

SMatrix3x3& SMatrix3x3::operator =(const SMatrix3x3& mat)
{
  if (this == &mat)
    return *this;
   for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] = mat.m_data[row][col];
   }
  return *this;
}

SMatrix3x3& SMatrix3x3::operator +=(const SMatrix3x3& mat)
{
  for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] += mat.m_data[row][col];
  }
  return *this;
}

SMatrix3x3& SMatrix3x3::operator -=(const SMatrix3x3& mat)
{
  for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] -= mat.m_data[row][col];
  }
  return *this;
}

SMatrix3x3& SMatrix3x3::operator *=(const SFLOAT f)
{
  for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] *= f;
  }
  return *this;
}

SMatrix3x3& SMatrix3x3::operator +=(const SFLOAT f)
{
  for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] += f;
  }
  return *this;
}
SMatrix3x3& SMatrix3x3::operator -=(const SFLOAT f)
{
  for (int row = 0; row < 3; row++){
     for (int col = 0; col < 3; col++)
       m_data[row][col] -= f;
  }
  return *this;
}
SMatrix3x3& SMatrix3x3::operator *=(const SMatrix3x3& mat)
{
  SMatrix3x3 tmp = SMatrix3x3();
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      tmp.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col] +
                    m_data[row][2] * mat.m_data[2][col];
  *this = tmp;
  return *this;
}

const SMatrix3x3 SMatrix3x3::operator +(const SMatrix3x3& mat) const
{
  SMatrix3x3 result = *this;
  result += mat;
  return result;
}

const SMatrix3x3 SMatrix3x3::operator -(const SMatrix3x3& mat) const
{
  SMatrix3x3 result = *this;
  result -= mat;
  return result;
}

const SMatrix3x3 SMatrix3x3::operator +(const SFLOAT f) const
{
  SMatrix3x3 result = *this;
  result += f;
  return result;
}

const SMatrix3x3 SMatrix3x3::operator -(const SFLOAT f) const
{
  SMatrix3x3 result = *this;
  result -= f;
  return result;
}

const SMatrix3x3 SMatrix3x3::operator *(const SFLOAT f) const
{
  SMatrix3x3 result = *this;
  result *= f;
  return result;
}

const SMatrix3x3 SMatrix3x3::operator *(const SMatrix3x3& mat) const
{
  SMatrix3x3 result = *this;
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      result.m_data[row][col] =
                    m_data[row][0] * mat.m_data[0][col] +
                    m_data[row][1] * mat.m_data[1][col] +
                    m_data[row][2] * mat.m_data[2][col];
  return result;
}

SFLOAT SMatrix3x3::minorMatrix(const int row, const int col)
{
  static int map[] = {1,2,
                      0,2,
                      0,1};
  //A[a b c]
  // [d e f]           [e f]
  // [g h i]  (0,0) -> [g i]
  int* rc;
  int* cc;
  rc = map + row * 2;
  cc = map + col * 2;

  SFLOAT res = 0;

  res += m_data[rc[0]][cc[0]] * m_data[rc[1]][cc[1]];
  res -= m_data[rc[0]][cc[1]] * m_data[rc[1]][cc[0]];
  return res;
}

SFLOAT SMatrix3x3::determinant()
{
  SFLOAT det = 0;
  //A[a b c]
  // [d e f]          
  // [g h i]  det(A) = a*e*i + b*f*g + c*d*h 
  det += m_data[0][0] * m_data[1][1] * m_data[2][2];
  det += m_data[0][1] * m_data[1][2] * m_data[2][0];
  det += m_data[0][2] * m_data[1][0] * m_data[2][1];
  det -= m_data[0][0] * m_data[1][2] * m_data[2][1];
  det -= m_data[0][1] * m_data[1][0] * m_data[2][2];
  det -= m_data[0][2] * m_data[1][1] * m_data[2][0];
  return det;
}

SMatrix3x3 SMatrix3x3::inverted()
{
  SMatrix3x3 result = SMatrix3x3();;
  SFLOAT det = determinant();
  if (det == 0) {
    result.setAsIdentity();
    return result;
  }
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if ((row + col) & 1)
        //[col][row]  <==> [row][cp;] transposed
        result.m_data[col][row] = -minorMatrix(row, col) / det;
      else
        result.m_data[col][row] = minorMatrix(row, col) / det;
      }
    }
    return result;
}

//############################################################################

/*
    
    
    const SMatrix2x2 operator *(const SMatrix2x2& mat) const;
*/

//############################################################################
//  Strings are put here. So the display functions are no re-entrant!
/*
char RTMath::m_string[1000];

uint64_t RTMath::currentUSecsSinceEpoch()
{
#ifdef WIN32
#include <qdatetime.h>
    return QDateTime::currentMSecsSinceEpoch();
#else
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec;
#endif
}

const char *RTMath::displayRadians(const char *label, RTVector3& vec)
{
    sprintf(m_string, "%s: x:%f, y:%f, z:%f\n", label, vec.x(), vec.y(), vec.z());
    return m_string;
}

const char *RTMath::displayDegrees(const char *label, RTVector3& vec)
{
    sprintf(m_string, "%s: roll:%f, pitch:%f, yaw:%f", label, vec.x() * RTMATH_RAD_TO_DEGREE,
            vec.y() * RTMATH_RAD_TO_DEGREE, vec.z() * RTMATH_RAD_TO_DEGREE);
    return m_string;
}

const char *RTMath::display(const char *label, RTQuaternion& quat)
{
    sprintf(m_string, "%s: scalar: %f, x:%f, y:%f, z:%f\n", label, quat.scalar(), quat.x(), quat.y(), quat.z());
    return m_string;
}

const char *RTMath::display(const char *label, RTMatrix4x4& mat)
{
    sprintf(m_string, "%s(0): %f %f %f %f\n%s(1): %f %f %f %f\n%s(2): %f %f %f %f\n%s(3): %f %f %f %f\n",
            label, mat.val(0,0), mat.val(0,1), mat.val(0,2), mat.val(0,3),
            label, mat.val(1,0), mat.val(1,1), mat.val(1,2), mat.val(1,3),
            label, mat.val(2,0), mat.val(2,1), mat.val(2,2), mat.val(2,3),
            label, mat.val(3,0), mat.val(3,1), mat.val(3,2), mat.val(3,3));
    return m_string;
}

//  convertPressureToHeight() - the conversion uses the formula:
//
//  h = (T0 / L0) * ((p / P0)**(-(R* * L0) / (g0 * M)) - 1)
//
//  where:
//  h  = height above sea level
//  T0 = standard temperature at sea level = 288.15
//  L0 = standard temperatur elapse rate = -0.0065
//  p  = measured pressure
//  P0 = static pressure = 1013.25 (but can be overridden)
//  g0 = gravitational acceleration = 9.80665
//  M  = mloecular mass of earth's air = 0.0289644
//  R* = universal gas constant = 8.31432
//
//  Given the constants, this works out to:
//
//  h = 44330.8 * (1 - (p / P0)**0.190263)

RTFLOAT RTMath::convertPressureToHeight(RTFLOAT pressure, RTFLOAT staticPressure)
{
    return 44330.8 * (1 - pow(pressure / staticPressure, (RTFLOAT)0.190263));
}


RTVector3 RTMath::poseFromAccelMag(const RTVector3& accel, const RTVector3& mag)
{
    RTVector3 result;
    RTQuaternion m;
    RTQuaternion q;

    accel.accelToEuler(result);

//  q.fromEuler(result);
//  since result.z() is always 0, this can be optimized a little

    RTFLOAT cosX2 = cos(result.x() / 2.0f);
    RTFLOAT sinX2 = sin(result.x() / 2.0f);
    RTFLOAT cosY2 = cos(result.y() / 2.0f);
    RTFLOAT sinY2 = sin(result.y() / 2.0f);

    q.setScalar(cosX2 * cosY2);
    q.setX(sinX2 * cosY2);
    q.setY(cosX2 * sinY2);
    q.setZ(-sinX2 * sinY2);
//    q.normalize();

    m.setScalar(0);
    m.setX(mag.x());
    m.setY(mag.y());
    m.setZ(mag.z());

    m = q * m * q.conjugate();
    result.setZ(-atan2(m.y(), m.x()));
    return result;
}

void RTMath::convertToVector(unsigned char *rawData, RTVector3& vec, RTFLOAT scale, bool bigEndian)
{
    if (bigEndian) {
        vec.setX((RTFLOAT)((int16_t)(((uint16_t)rawData[0] << 8) | (uint16_t)rawData[1])) * scale);
        vec.setY((RTFLOAT)((int16_t)(((uint16_t)rawData[2] << 8) | (uint16_t)rawData[3])) * scale);
        vec.setZ((RTFLOAT)((int16_t)(((uint16_t)rawData[4] << 8) | (uint16_t)rawData[5])) * scale);
    } else {
        vec.setX((RTFLOAT)((int16_t)(((uint16_t)rawData[1] << 8) | (uint16_t)rawData[0])) * scale);
        vec.setY((RTFLOAT)((int16_t)(((uint16_t)rawData[3] << 8) | (uint16_t)rawData[2])) * scale);
        vec.setZ((RTFLOAT)((int16_t)(((uint16_t)rawData[5] << 8) | (uint16_t)rawData[4])) * scale);
     }
}



//----------------------------------------------------------
//
//  The RTVector3 class

void RTVector3::accelToEuler(RTVector3& rollPitchYaw) const
{
    RTVector3 normAccel = *this;

    normAccel.normalize();

    rollPitchYaw.setX(atan2(normAccel.y(), normAccel.z()));
    rollPitchYaw.setY(-atan2(normAccel.x(), sqrt(normAccel.y() * normAccel.y() + normAccel.z() * normAccel.z())));
    rollPitchYaw.setZ(0);
}


void RTVector3::accelToQuaternion(RTQuaternion& qPose) const
{
    RTVector3 normAccel = *this;
    RTVector3 vec;
    RTVector3 z(0, 0, 1.0);

    normAccel.normalize();

    RTFLOAT angle = acos(RTVector3::dotProduct(z, normAccel));
    RTVector3::crossProduct(normAccel, z, vec);
    vec.normalize();

    qPose.fromAngleVector(angle, vec);
}

//----------------------------------------------------------
//
//  The RTQuaternion class

RTQuaternion::RTQuaternion()
{
    zero();
}

RTQuaternion::RTQuaternion(RTFLOAT scalar, RTFLOAT x, RTFLOAT y, RTFLOAT z)
{
    m_data[0] = scalar;
    m_data[1] = x;
    m_data[2] = y;
    m_data[3] = z;
}

RTQuaternion& RTQuaternion::operator =(const RTQuaternion& quat)
{
    if (this == &quat)
        return *this;

    m_data[0] = quat.m_data[0];
    m_data[1] = quat.m_data[1];
    m_data[2] = quat.m_data[2];
    m_data[3] = quat.m_data[3];

    return *this;
}



RTQuaternion& RTQuaternion::operator +=(const RTQuaternion& quat)
{
    for (int i = 0; i < 4; i++)
        m_data[i] += quat.m_data[i];
    return *this;
}

RTQuaternion& RTQuaternion::operator -=(const RTQuaternion& quat)
{
    for (int i = 0; i < 4; i++)
        m_data[i] -= quat.m_data[i];
    return *this;
}

RTQuaternion& RTQuaternion::operator -=(const RTFLOAT val)
{
    for (int i = 0; i < 4; i++)
        m_data[i] -= val;
    return *this;
}

RTQuaternion& RTQuaternion::operator *=(const RTQuaternion& qb)
{
    RTQuaternion qa;

    qa = *this;

    m_data[0] = qa.scalar() * qb.scalar() - qa.x() * qb.x() - qa.y() * qb.y() - qa.z() * qb.z();
    m_data[1] = qa.scalar() * qb.x() + qa.x() * qb.scalar() + qa.y() * qb.z() - qa.z() * qb.y();
    m_data[2] = qa.scalar() * qb.y() - qa.x() * qb.z() + qa.y() * qb.scalar() + qa.z() * qb.x();
    m_data[3] = qa.scalar() * qb.z() + qa.x() * qb.y() - qa.y() * qb.x() + qa.z() * qb.scalar();

    return *this;
}


RTQuaternion& RTQuaternion::operator *=(const RTFLOAT val)
{
    m_data[0] *= val;
    m_data[1] *= val;
    m_data[2] *= val;
    m_data[3] *= val;

    return *this;
}


const RTQuaternion RTQuaternion::operator *(const RTQuaternion& qb) const
{
    RTQuaternion result = *this;
    result *= qb;
    return result;
}

const RTQuaternion RTQuaternion::operator *(const RTFLOAT val) const
{
    RTQuaternion result = *this;
    result *= val;
    return result;
}


const RTQuaternion RTQuaternion::operator -(const RTQuaternion& qb) const
{
    RTQuaternion result = *this;
    result -= qb;
    return result;
}

const RTQuaternion RTQuaternion::operator -(const RTFLOAT val) const
{
    RTQuaternion result = *this;
    result -= val;
    return result;
}


void RTQuaternion::zero()
{
    for (int i = 0; i < 4; i++)
        m_data[i] = 0;
}

void RTQuaternion::normalize()
{
    RTFLOAT length = sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] +
            m_data[2] * m_data[2] + m_data[3] * m_data[3]);

    if ((length == 0) || (length == 1))
        return;

    m_data[0] /= length;
    m_data[1] /= length;
    m_data[2] /= length;
    m_data[3] /= length;
}

void RTQuaternion::toEuler(RTVector3& vec)
{
    vec.setX(atan2(2.0 * (m_data[2] * m_data[3] + m_data[0] * m_data[1]),
            1 - 2.0 * (m_data[1] * m_data[1] + m_data[2] * m_data[2])));

    vec.setY(asin(2.0 * (m_data[0] * m_data[2] - m_data[1] * m_data[3])));

    vec.setZ(atan2(2.0 * (m_data[1] * m_data[2] + m_data[0] * m_data[3]),
            1 - 2.0 * (m_data[2] * m_data[2] + m_data[3] * m_data[3])));
}

void RTQuaternion::fromEuler(RTVector3& vec)
{
    RTFLOAT cosX2 = cos(vec.x() / 2.0f);
    RTFLOAT sinX2 = sin(vec.x() / 2.0f);
    RTFLOAT cosY2 = cos(vec.y() / 2.0f);
    RTFLOAT sinY2 = sin(vec.y() / 2.0f);
    RTFLOAT cosZ2 = cos(vec.z() / 2.0f);
    RTFLOAT sinZ2 = sin(vec.z() / 2.0f);

    m_data[0] = cosX2 * cosY2 * cosZ2 + sinX2 * sinY2 * sinZ2;
    m_data[1] = sinX2 * cosY2 * cosZ2 - cosX2 * sinY2 * sinZ2;
    m_data[2] = cosX2 * sinY2 * cosZ2 + sinX2 * cosY2 * sinZ2;
    m_data[3] = cosX2 * cosY2 * sinZ2 - sinX2 * sinY2 * cosZ2;
    normalize();
}

RTQuaternion RTQuaternion::conjugate() const
{
    RTQuaternion q;
    q.setScalar(m_data[0]);
    q.setX(-m_data[1]);
    q.setY(-m_data[2]);
    q.setZ(-m_data[3]);
    return q;
}

void RTQuaternion::toAngleVector(RTFLOAT& angle, RTVector3& vec)
{
    RTFLOAT halfTheta;
    RTFLOAT sinHalfTheta;

    halfTheta = acos(m_data[0]);
    sinHalfTheta = sin(halfTheta);

    if (sinHalfTheta == 0) {
        vec.setX(1.0);
        vec.setY(0);
        vec.setZ(0);
    } else {
        vec.setX(m_data[1] / sinHalfTheta);
        vec.setY(m_data[1] / sinHalfTheta);
        vec.setZ(m_data[1] / sinHalfTheta);
    }
    angle = 2.0 * halfTheta;
}

void RTQuaternion::fromAngleVector(const RTFLOAT& angle, const RTVector3& vec)
{
    RTFLOAT sinHalfTheta = sin(angle / 2.0);
    m_data[0] = cos(angle / 2.0);
    m_data[1] = vec.x() * sinHalfTheta;
    m_data[2] = vec.y() * sinHalfTheta;
    m_data[3] = vec.z() * sinHalfTheta;
}



//----------------------------------------------------------
//
//  The RTMatrix4x4 class

const RTQuaternion RTMatrix4x4::operator *(const RTQuaternion& q) const
{
    RTQuaternion res;

    res.setScalar(m_data[0][0] * q.scalar() + m_data[0][1] * q.x() + m_data[0][2] * q.y() + m_data[0][3] * q.z());
    res.setX(m_data[1][0] * q.scalar() + m_data[1][1] * q.x() + m_data[1][2] * q.y() + m_data[1][3] * q.z());
    res.setY(m_data[2][0] * q.scalar() + m_data[2][1] * q.x() + m_data[2][2] * q.y() + m_data[2][3] * q.z());
    res.setZ(m_data[3][0] * q.scalar() + m_data[3][1] * q.x() + m_data[3][2] * q.y() + m_data[3][3] * q.z());

    return res;
}

*/
