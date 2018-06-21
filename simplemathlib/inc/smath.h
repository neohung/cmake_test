////////////////////////////////////////////////////////////////////////////
#ifndef _SMATH_H_
#define _SMATH_H_

#ifdef USE_DOUBLE
  typedef double SFLOAT;
#else
  typedef float SFLOAT;
#endif

#include <string.h> //for memcpy
//#include <math.h> //for sqrt
//  Useful constants

#define	SMATH_PI  3.1415926535
#define	SMATH_DEGREE_TO_RAD		(SMATH_PI / 180.0)
#define	SMATH_RAD_TO_DEGREE		(180.0 / SMATH_PI)

class SVector2;
class SVector3;
class SMatrix4x4;
//class SQuaternion;

class SVector2
{
public:
  void zero();
  SVector2();
  SVector2(SFLOAT x, SFLOAT y);
  inline SFLOAT x() const { return m_data[0]; }
  inline SFLOAT y() const { return m_data[1]; }
  inline void setX(const SFLOAT val) {  m_data[0] = val; }
  inline void setY(const SFLOAT val) {  m_data[1] = val; }
  static SFLOAT dotProduct(SVector2& a, SVector2& b);
  SFLOAT length();
  void normalize();
  SVector2& operator =(const SVector2& vec);
  SVector2& operator +=(const SVector2& vec);
  SVector2& operator -=(const SVector2& vec);
  SVector2& operator +=(const SFLOAT& f);
  SVector2& operator -=(const SFLOAT& f);
  const SVector2 operator +(const SVector2& vec) const;
  const SVector2 operator -(const SVector2& vec) const;
  const SVector2 operator +(const SFLOAT& f) const;
  const SVector2 operator -(const SFLOAT& f) const;
  void display();
private:
  SFLOAT m_data[2];
};

class SVector3
{
public:
    void zero();
    SVector3();
    SVector3(SFLOAT x, SFLOAT y, SFLOAT z);
    SVector3& operator =(const SVector3& vec);
    const SVector3& operator +=(const SFLOAT& f);
    const SVector3& operator +=(const SVector3& vec);
    const SVector3& operator -=(const SFLOAT& f);
    const SVector3& operator -=(const SVector3& vec);
    
    const SVector3 operator +(const SVector3& vec) const;
    const SVector3 operator -(const SVector3& vec) const;
    const SVector3 operator +(const SFLOAT& f) const;
    const SVector3 operator -(const SFLOAT& f) const;

    static SFLOAT dotProduct(const SVector3& a, const SVector3& b);
    static void crossProduct(const SVector3& a, const SVector3& b, SVector3& d);

    SFLOAT length();
    void normalize();

    //void accelToEuler(SVector3& rollPitchYaw) const;
    //void accelToQuaternion(SQuaternion& qPose) const;

    inline SFLOAT x() const { return m_data[0]; }
    inline SFLOAT y() const { return m_data[1]; }
    inline SFLOAT z() const { return m_data[2]; }
    inline SFLOAT data(const int i) const { return m_data[i]; }

    inline void setX(const SFLOAT val) { m_data[0] = val; }
    inline void setY(const SFLOAT val) { m_data[1] = val; }
    inline void setZ(const SFLOAT val) { m_data[2] = val; }
    inline void setData(const int i, SFLOAT val) { m_data[i] = val; }
    //Copy data from array pointer
    inline void fromArray(SFLOAT *val) { memcpy(m_data, val, 3 * sizeof(SFLOAT)); }
    //copy data to array pointer
    inline void toArray(SFLOAT *val) const { memcpy(val, m_data, 3 * sizeof(SFLOAT)); }
    void display();
private:
    SFLOAT m_data[3];
};


class SMatrix2x2
{
public:
    void fill(SFLOAT f);
    SMatrix2x2();
    inline SFLOAT val(int row, int col) const { return m_data[row][col]; }
    inline void setVal(int row, int col, SFLOAT val) { m_data[row][col] = val; }
    void display();
    void setAsIdentity();
    SMatrix2x2 transposed();
    SMatrix2x2& operator =(const SMatrix2x2& mat);
    SMatrix2x2& operator +=(const SMatrix2x2& mat);
    SMatrix2x2& operator -=(const SMatrix2x2& mat);
    SMatrix2x2& operator *=(const SFLOAT f);
    SMatrix2x2& operator +=(const SFLOAT f);
    SMatrix2x2& operator -=(const SFLOAT f);
    const SMatrix2x2 operator +(const SMatrix2x2& mat) const;
    const SMatrix2x2 operator -(const SMatrix2x2& mat) const;
    const SMatrix2x2 operator +(const SFLOAT f) const;
    const SMatrix2x2 operator -(const SFLOAT f) const;
    SMatrix2x2& operator *=(const SMatrix2x2& mat);
    const SMatrix2x2 operator *(const SFLOAT f) const;
    const SMatrix2x2 operator *(const SMatrix2x2& mat) const;
    SFLOAT minorMatrix(const int row, const int col);
    SFLOAT determinant();
    SMatrix2x2 inverted();

private:
    SFLOAT m_data[2][2];
};

class SMatrix3x3
{
public:
    void fill(SFLOAT f);
    SMatrix3x3();
    inline SFLOAT val(int row, int col) const { return m_data[row][col]; }
    inline void setVal(int row, int col, SFLOAT val) { m_data[row][col] = val; }
    void display();
    void setAsIdentity();
    SMatrix3x3 transposed();
    SMatrix3x3& operator =(const SMatrix3x3& mat);
    SMatrix3x3& operator +=(const SMatrix3x3& mat);
    SMatrix3x3& operator -=(const SMatrix3x3& mat);
    SMatrix3x3& operator *=(const SFLOAT f);
    SMatrix3x3& operator +=(const SFLOAT f);
    SMatrix3x3& operator -=(const SFLOAT f);
    const SMatrix3x3 operator +(const SMatrix3x3& mat) const;
    const SMatrix3x3 operator -(const SMatrix3x3& mat) const;
    const SMatrix3x3 operator +(const SFLOAT f) const;
    const SMatrix3x3 operator -(const SFLOAT f) const;
    SMatrix3x3& operator *=(const SMatrix3x3& mat);
    const SMatrix3x3 operator *(const SFLOAT f) const;
    const SMatrix3x3 operator *(const SMatrix3x3& mat) const;
    SFLOAT minorMatrix(const int row, const int col);
    SFLOAT determinant();
    SMatrix3x3 inverted();

private:
    SFLOAT m_data[3][3];
};

class SMatrix4x4
{
public:
    void fill(SFLOAT f);
    SMatrix4x4();
    inline SFLOAT val(int row, int col) const { return m_data[row][col]; }
    inline void setVal(int row, int col, SFLOAT val) { m_data[row][col] = val; }
    void display();
    void setAsIdentity();
    SMatrix4x4 transposed();
    SMatrix4x4& operator =(const SMatrix4x4& mat);
    SMatrix4x4& operator +=(const SMatrix4x4& mat);
    SMatrix4x4& operator -=(const SMatrix4x4& mat);
    SMatrix4x4& operator *=(const SFLOAT f);
    SMatrix4x4& operator +=(const SFLOAT f);
    SMatrix4x4& operator -=(const SFLOAT f);
    const SMatrix4x4 operator +(const SMatrix4x4& mat) const;
    const SMatrix4x4 operator -(const SMatrix4x4& mat) const;
    const SMatrix4x4 operator +(const SFLOAT f) const;
    const SMatrix4x4 operator -(const SFLOAT f) const;
    SMatrix4x4& operator *=(const SMatrix4x4& mat);
    const SMatrix4x4 operator *(const SFLOAT f) const;

    //const SQuaternion operator *(const SQuaternion& q) const;
    const SMatrix4x4 operator *(const SMatrix4x4& mat) const;

    SMatrix4x4 inverted();
private:
    SFLOAT m_data[4][4];                                   // row, column

    SFLOAT minorMatrix(const int row, const int col);
    SFLOAT determinant();
};

/*
class SQuaternion
{
public:
    SQuaternion();
    SQuaternion(SFLOAT scalar, SFLOAT x, SFLOAT y, SFLOAT z);

    SQuaternion& operator +=(const SQuaternion& quat);
    SQuaternion& operator -=(const SQuaternion& quat);
    SQuaternion& operator *=(const SQuaternion& qb);
    SQuaternion& operator *=(const SFLOAT val);
    SQuaternion& operator -=(const SFLOAT val);

    SQuaternion& operator =(const SQuaternion& quat);
    const SQuaternion operator *(const SQuaternion& qb) const;
    const SQuaternion operator *(const SFLOAT val) const;
    const SQuaternion operator -(const SQuaternion& qb) const;
    const SQuaternion operator -(const SFLOAT val) const;

    void normalize();
    void toEuler(SVector3& vec);
    void fromEuler(SVector3& vec);
    RTQuaternion conjugate() const;
    void toAngleVector(SFLOAT& angle, SVector3& vec);
    void fromAngleVector(const SFLOAT& angle, const SVector3& vec);

    void zero();
    const char *display();

    inline SFLOAT scalar() const { return m_data[0]; }
    inline SFLOAT x() const { return m_data[1]; }
    inline SFLOAT y() const { return m_data[2]; }
    inline SFLOAT z() const { return m_data[3]; }
    inline SFLOAT data(const int i) const { return m_data[i]; }

    inline void setScalar(const SFLOAT val) { m_data[0] = val; }
    inline void setX(const SFLOAT val) { m_data[1] = val; }
    inline void setY(const SFLOAT val) { m_data[2] = val; }
    inline void setZ(const SFLOAT val) { m_data[3] = val; }
    inline void setData(const int i, SFLOAT val) { m_data[i] = val; }
    inline void fromArray(SFLOAT *val) { memcpy(m_data, val, 4 * sizeof(SFLOAT)); }
    inline void toArray(SFLOAT *val) const { memcpy(val, m_data, 4 * sizeof(SFLOAT)); }

private:
    SFLOAT m_data[4];
};


class SMath
{
public:
    // convenient display routines
    //static const char *displayRadians(const char *label, SVector3& vec);
    //static const char *displayDegrees(const char *label, SVector3& vec);
    //static const char *display(const char *label, SQuaternion& quat);
    //static const char *display(const char *label, SMatrix4x4& mat);
    //static uint64_t currentUSecsSinceEpoch();
    //  poseFromAccelMag generates pose Euler angles from measured settings
    //static RTVector3 poseFromAccelMag(const RTVector3& accel, const RTVector3& mag);
    //  Takes signed 16 bit data from a char array and converts it to a vector of scaled RTFLOATs
    //static void convertToVector(unsigned char *rawData, RTVector3& vec, RTFLOAT scale, bool bigEndian);
    //  Takes a pressure in hPa and returns height above sea level in meters
    //static RTFLOAT convertPressureToHeight(RTFLOAT pressure, RTFLOAT staticPressure = 1013.25);

private:
    //static char m_string[1000];                             // for the display routines
};
*/

#endif /* _SMATH_H_ */
