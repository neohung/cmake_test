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

class SVector3;
class SMatrix4x4;
//class SQuaternion;

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


class SVector3
{
public:
    void zero();
    SVector3();
    SVector3(SFLOAT x, SFLOAT y, SFLOAT z);
    SVector3& operator =(const SVector3& vec);
    const SVector3& operator +=(SFLOAT& f);
    const SVector3& operator +=(SVector3& vec);
    const SVector3& operator -=(SFLOAT& f);
    const SVector3& operator -=(SVector3& vec);
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

private:
    SFLOAT m_data[3];
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
*/
class SMatrix4x4
{
public:
    SMatrix4x4();

    //SMatrix4x4& operator +=(const SMatrix4x4& mat);
    //SMatrix4x4& operator -=(const SMatrix4x4& mat);
    //SMatrix4x4& operator *=(const SFLOAT val);

    //SMatrix4x4& operator =(const SMatrix4x4& vec);
    //const SQuaternion operator *(const SQuaternion& q) const;
    //const SMatrix4x4 operator *(const SFLOAT val) const;
    //const SMatrix4x4 operator *(const SMatrix4x4& mat) const;
    //const SMatrix4x4 operator +(const SMatrix4x4& mat) const;

    inline SFLOAT val(int row, int col) const { return m_data[row][col]; }
    inline void setVal(int row, int col, SFLOAT val) { m_data[row][col] = val; }
    //void fill(SFLOAT val);
    //void setToIdentity();

    //SMatrix4x4 inverted();
    //SMatrix4x4 transposed();

private:
    SFLOAT m_data[4][4];                                   // row, column

    //SFLOAT matDet();
    //SFLOAT matMinor(const int row, const int col);
};

#endif /* _SMATH_H_ */
