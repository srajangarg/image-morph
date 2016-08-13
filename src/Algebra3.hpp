/****************************************************************
*                                                               *
* C++ Vector and Matrix Algebra routines                        *
* Author: Jean-Francois DOUE                                    *
* Version 3.1 --- October 1993                                  *
*                                                               *
****************************************************************/
//
//  From "Graphics Gems IV / Edited by Paul S. Heckbert
//  Academic Press, 1994, ISBN 0-12-336156-9
//  "You are free to use and modify this code in any way
//  you like." (p. xv)
//
//  Modified by J. Nagle, March 1997
//  -   All functions are inline.
//  -   All functions are const-correct.
//  -   All checking is via the standard "assert" macro.
//  -   Stream I/O is disabled for portability, but can be
//      re-enabled by defining ALGEBRA3IOSTREAMS.
//
//  Modified by S. Chaudhuri, Aug 2016
//  -   Enable Stream I/O by default (disable with ALGEBRA3_NO_ISTREAMS)
//  -   Remove VX, VY, VZ, VW indices from global namespace, add x(), y(),
//      z(), w() member fns
//  -   Class names start with uppercase
//  -   Use std::min and std::max instead of defining MIN and MAX
//  -   Use standard C++ headers
//  -   Formatting cleanup
//
#ifndef __Algebra3_hpp__
#define __Algebra3_hpp__

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>

// this line defines a new type: pointer to a function which returns
// double and takes as argument a double
typedef double (*ALG3_FCT_PTR)(double);

// error handling macro
#define ALG3_ERROR(E) { assert(false); }

class Vec2;
class Vec3;
class Vec4;
class Mat3;
class Mat4;

//
//  PI
//
#ifndef M_PI
double const M_PI = (double) 3.14159265358979323846;
#endif

#ifndef M_PI_2
double const M_PI_2 = (M_PI / 2.0);       // PI/2
#endif

#ifndef M2_PI
double const M2_PI = (M_PI * 2.0);        // PI*2
#endif

/****************************************************************
*                                                               *
*               2D Vector                                       *
*                                                               *
****************************************************************/

class Vec2
{
  protected:

    double n[2];

  public:

    // Constructors

    Vec2();
    Vec2(double const x, double const y);
    explicit Vec2(double const d);
    Vec2(Vec2 const & v);                // copy constructor
    Vec2(Vec3 const & v);                // cast v3 to v2
    Vec2(Vec3 const & v, int dropAxis);  // cast v3 to v2

    // Assignment operators

    Vec2 & operator  = (Vec2 const & v);     // assignment of a Vec2
    Vec2 & operator += (Vec2 const & v);     // incrementation by a Vec2
    Vec2 & operator -= (Vec2 const & v);     // decrementation by a Vec2
    Vec2 & operator *= (double const d);     // multiplication by a constant
    Vec2 & operator /= (double const d);     // division by a constant
    double & operator [] (int i);            // indexing
    double operator [] (int i) const;        // read-only indexing

    double & x();         // indexing by axis name
    double & y();
    double x() const;     // read-only indexing by axis name
    double y() const;

    // special functions

    double length() const;            // length of a Vec2
    double length2() const;           // squared length of a Vec2
    Vec2 & normalize() ;              // normalize a Vec2 in place
    Vec2 & apply(ALG3_FCT_PTR fct);   // apply a func. to each component
    Vec2 perp() const;                // perpendicular of same length, going ccw

    // friends

    friend Vec2 operator - (Vec2 const & v);                      // -v1
    friend Vec2 operator + (Vec2 const & a, Vec2 const & b);      // v1 + v2
    friend Vec2 operator - (Vec2 const & a, Vec2 const & b);      // v1 - v2
    friend Vec2 operator * (Vec2 const & a, double const d);      // v1 * 3.0
    friend Vec2 operator * (double const d, Vec2 const & a);      // 3.0 * v1
    friend Vec2 operator * (Mat3 const & a, Vec2 const & v);      // M . v
    friend Vec2 operator * (Vec2 const & v, Mat3 const & a);      // v . M
    friend double operator * (Vec2 const & a, Vec2 const & b);    // dot product
    friend Vec2 operator / (Vec2 const & a, double const d);      // v1 / 3.0
    friend Vec3 operator ^ (Vec2 const & a, Vec2 const & b);      // cross product
    friend bool operator == (Vec2 const & a, Vec2 const & b);     // v1 == v2 ?
    friend bool operator != (Vec2 const & a, Vec2 const & b);     // v1 != v2 ?

    #ifndef ALGEBRA3_NO_ISTREAMS
    friend std::ostream & operator << (std::ostream & s, Vec2 const & v);   // output to stream
    friend std::istream & operator >> (std::istream & s, Vec2 & v);         // input from stream
    #endif // !ALGEBRA3_NO_IOSTREAMS

    friend void swap(Vec2 & a, Vec2 & b);                         // swap v1 & v2
    friend Vec2 min(Vec2 const & a, Vec2 const & b);              // min(v1, v2)
    friend Vec2 max(Vec2 const & a, Vec2 const & b);              // max(v1, v2)
    friend Vec2 prod(Vec2 const & a, Vec2 const & b);             // term by term *

    // necessary friend declarations

    friend class Vec3;

}; // class Vec2


/****************************************************************
*                                                               *
*               3D Vector                                       *
*                                                               *
****************************************************************/

class Vec3
{
  protected:

    double n[3];

  public:

    // Constructors

    Vec3();
    Vec3(double const x, double const y, double const z);
    explicit Vec3(double const d);
    Vec3(Vec3 const & v);                    // copy constructor
    Vec3(Vec2 const & v);                    // cast v2 to v3
    Vec3(Vec2 const & v, double d);          // cast v2 to v3
    Vec3(Vec4 const & v);                    // cast v4 to v3
    Vec3(Vec4 const & v, int dropAxis);      // cast v4 to v3

    // Assignment operators

    Vec3 & operator  = (Vec3 const & v);     // assignment of a Vec3
    Vec3 & operator += (Vec3 const & v);     // incrementation by a Vec3
    Vec3 & operator -= (Vec3 const & v);     // decrementation by a Vec3
    Vec3 & operator *= (double const d);     // multiplication by a constant
    Vec3 & operator /= (double const d);     // division by a constant
    double & operator [] (int i);            // indexing
    double operator[] (int i) const;         // read-only indexing

    double & x();         // indexing by axis name
    double & y();
    double & z();
    double x() const;     // read-only indexing by axis name
    double y() const;
    double z() const;

    // special functions

    double length() const;              // length of a Vec3
    double length2() const;             // squared length of a Vec3
    Vec3 & normalize();                 // normalize a Vec3 in place
    Vec3 & apply(ALG3_FCT_PTR fct);      // apply a func. to each component

    // friends

    friend Vec3 operator   - (Vec3 const & v);                      // -v1
    friend Vec3 operator   + (Vec3 const & a, Vec3 const & b);      // v1 + v2
    friend Vec3 operator   - (Vec3 const & a, Vec3 const & b);      // v1 - v2
    friend Vec3 operator   * (Vec3 const & a, double const d);      // v1 * 3.0
    friend Vec3 operator   * (double const d, Vec3 const & a);      // 3.0 * v1
    friend Vec3 operator   * (Mat4 const & a, Vec3 const & v);      // M . v
    friend Vec3 operator   * (Vec3 const & v, Mat4 const & a);      // v . M
    friend double operator * (Vec3 const & a, Vec3 const & b);      // dot product
    friend Vec3 operator   / (Vec3 const & a, double const d);      // v1 / 3.0
    friend Vec3 operator   ^ (Vec3 const & a, Vec3 const & b);      // cross product
    friend bool operator   == (Vec3 const & a, Vec3 const & b);     // v1 == v2 ?
    friend bool operator   != (Vec3 const & a, Vec3 const & b);     // v1 != v2 ?

    #ifndef ALGEBRA3_NO_ISTREAMS
    friend std::ostream & operator << (std::ostream & s, Vec3 const & v);     // output to stream
    friend std::istream & operator >> (std::istream & s, Vec3 & v);           // input from stream
    #endif // !ALGEBRA3_NO_IOSTREAMS

    friend void swap(Vec3 & a, Vec3 & b);                     // swap v1 & v2
    friend Vec3 min(Vec3 const & a, Vec3 const & b);          // min(v1, v2)
    friend Vec3 max(Vec3 const & a, Vec3 const & b);          // max(v1, v2)
    friend Vec3 prod(Vec3 const & a, Vec3 const & b);         // term by term *

    // necessary friend declarations

    friend class Vec2;
    friend class Vec4;
    friend class Mat3;
    friend Vec2 operator * (Mat3 const & a, Vec2 const & v);  // homogenous linear transform
    friend Vec3 operator * (Mat3 const & a, Vec3 const & v);  //
    friend Mat3 operator * (Mat3 const & a, Mat3 const & b);  // matrix 3 product

}; // class Vec3


/****************************************************************
*                                                               *
*               4D Vector                                       *
*                                                               *
****************************************************************/

class Vec4
{
  protected:

    double n[4];

  public:

    // Constructors

    Vec4();
    Vec4(double const x, double const y, double const z, double const w);
    explicit Vec4(double const d);
    Vec4(Vec4 const & v);                        // copy constructor
    Vec4(Vec3 const & v);                        // cast Vec3 to Vec4
    Vec4(Vec3 const & v, double const d);        // cast Vec3 to Vec4

    // Assignment operators

    Vec4 & operator  = (Vec4 const & v);       // assignment of a Vec4
    Vec4 & operator += (Vec4 const & v);       // incrementation by a Vec4
    Vec4 & operator -= (Vec4 const & v);       // decrementation by a Vec4
    Vec4 & operator *= (double const d);       // multiplication by a constant
    Vec4 & operator /= (double const d);       // division by a constant
    double & operator [] (int i);              // indexing
    double operator[] (int i) const;           // read-only indexing

    double & x();         // indexing by axis name
    double & y();
    double & z();
    double & w();
    double x() const;     // read-only indexing by axis name
    double y() const;
    double z() const;
    double w() const;

    // special functions

    double length() const;             // length of a Vec4
    double length2() const;            // squared length of a Vec4
    Vec4 & normalize();                // normalize a Vec4 in place
    Vec4 & apply(ALG3_FCT_PTR fct);    // apply a func. to each component

    // friends

    friend Vec4 operator   - (Vec4 const & v);                      // -v1
    friend Vec4 operator   + (Vec4 const & a, Vec4 const & b);      // v1 + v2
    friend Vec4 operator   - (Vec4 const & a, Vec4 const & b);      // v1 - v2
    friend Vec4 operator   * (Vec4 const & a, double const d);      // v1 * 3.0
    friend Vec4 operator   * (double const d, Vec4 const & a);      // 3.0 * v1
    friend Vec4 operator   * (Mat4 const & a, Vec4 const & v);      // M . v
    friend Vec4 operator   * (Vec4 const & v, Mat4 const & a);      // v . M
    friend double operator * (Vec4 const & a, Vec4 const & b);      // dot product
    friend Vec4 operator   / (Vec4 const & a, double const d);      // v1 / 3.0
    friend bool operator   == (Vec4 const & a, Vec4 const & b);     // v1 == v2 ?
    friend bool operator   != (Vec4 const & a, Vec4 const & b);     // v1 != v2 ?

    #ifndef ALGEBRA3_NO_ISTREAMS
    friend std::ostream & operator << (std::ostream & s, Vec4 const & v);     // output to stream
    friend std::istream & operator >> (std::istream & s, Vec4 & v);           // input from stream
    #endif // !ALGEBRA3_NO_IOSTREAMS

    friend void swap(Vec4 & a, Vec4 & b);                     // swap v1 & v2
    friend Vec4 min(Vec4 const & a, Vec4 const & b);          // min(v1, v2)
    friend Vec4 max(Vec4 const & a, Vec4 const & b);          // max(v1, v2)
    friend Vec4 prod(Vec4 const & a, Vec4 const & b);         // term by term *

    // necessary friend declarations

    friend class Vec3;
    friend class Mat4;
    friend Vec3 operator * (Mat4 const & a, Vec3 const & v);  // linear transform
    friend Mat4 operator * (Mat4 const & a, Mat4 const & b);  // matrix 4 product

}; // class Vec4


/****************************************************************
*                                                               *
*              3x3 Matrix                                       *
*                                                               *
****************************************************************/

class Mat3
{
  protected:

    Vec3 v[3];

  public:

    // Constructors

    Mat3();
    Mat3(Vec3 const & v0, Vec3 const & v1, Vec3 const & v2);
    explicit Mat3(double const d);
    Mat3(Mat3 const & m);

    // Assignment operators

    Mat3 & operator  = (Mat3 const & m);        // assignment of a Mat3
    Mat3 & operator += (Mat3 const & m);        // incrementation by a Mat3
    Mat3 & operator -= (Mat3 const & m);        // decrementation by a Mat3
    Mat3 & operator *= (double const d);        // multiplication by a constant
    Mat3 & operator /= (double const d);        // division by a constant
    Vec3 & operator [] (int i);                 // indexing
    Vec3 const & operator [] (int i) const;     // read-only indexing

    // special functions

    Mat3 transpose() const;             // transpose
    Mat3 inverse() const;               // inverse
    Mat3 & apply(ALG3_FCT_PTR fct);     // apply a func. to each element

    // friends

    friend Mat3 operator - (Mat3 const & a);                      // -m1
    friend Mat3 operator + (Mat3 const & a, Mat3 const & b);      // m1 + m2
    friend Mat3 operator - (Mat3 const & a, Mat3 const & b);      // m1 - m2
    friend Mat3 operator * (Mat3 const & a, Mat3 const & b);      // m1 * m2
    friend Mat3 operator * (Mat3 const & a, double const d);      // m1 * 3.0
    friend Mat3 operator * (double const d, Mat3 const & a);      // 3.0 * m1
    friend Mat3 operator / (Mat3 const & a, double const d);      // m1 / 3.0
    friend bool operator == (Mat3 const & a, Mat3 const & b);     // m1 == m2 ?
    friend bool operator != (Mat3 const & a, Mat3 const & b);     // m1 != m2 ?

    #ifndef ALGEBRA3_NO_ISTREAMS
    friend std::ostream & operator << (std::ostream & s, Mat3 const & m);    // output to stream
    friend std::istream & operator >> (std::istream & s, Mat3 & m);          // input from stream
    #endif // !ALGEBRA3_NO_IOSTREAMS

    friend void swap(Mat3 & a, Mat3 & b);                         // swap m1 & m2

    // necessary friend declarations

    friend Vec3 operator * (Mat3 const & a, Vec3 const & v);      // linear transform
    friend Vec2 operator * (Mat3 const & a, Vec2 const & v);      // linear transform

}; // class Mat3


/****************************************************************
*                                                               *
*              4x4 Matrix                                       *
*                                                               *
****************************************************************/

class Mat4
{
  protected:

    Vec4 v[4];

  public:

    // Constructors

    Mat4();
    Mat4(Vec4 const & v0, Vec4 const & v1, Vec4 const & v2, Vec4 const & v3);
    explicit Mat4(double const d);
    Mat4(Mat4 const & m);

    // Assignment operators

    Mat4 & operator  = (Mat4 const & m);        // assignment of a Mat4
    Mat4 & operator += (Mat4 const & m);        // incrementation by a Mat4
    Mat4 & operator -= (Mat4 const & m);        // decrementation by a Mat4
    Mat4 & operator *= (double const d);        // multiplication by a constant
    Mat4 & operator /= (double const d);        // division by a constant
    Vec4 & operator [] (int i);                 // indexing
    Vec4 const & operator [] (int i) const;     // read-only indexing

    // special functions

    Mat4 transpose() const;                     // transpose
    Mat4 inverse() const;                       // inverse
    Mat4 & apply(ALG3_FCT_PTR fct);             // apply a func. to each element

    // friends

    friend Mat4 operator - (Mat4 const & a);                      // -m1
    friend Mat4 operator + (Mat4 const & a, Mat4 const & b);      // m1 + m2
    friend Mat4 operator - (Mat4 const & a, Mat4 const & b);      // m1 - m2
    friend Mat4 operator * (Mat4 const & a, Mat4 const & b);      // m1 * m2
    friend Mat4 operator * (Mat4 const & a, double const d);      // m1 * 4.0
    friend Mat4 operator * (double const d, Mat4 const & a);      // 4.0 * m1
    friend Mat4 operator / (Mat4 const & a, double const d);      // m1 / 3.0
    friend bool operator == (Mat4 const & a, Mat4 const & b);     // m1 == m2 ?
    friend bool operator != (Mat4 const & a, Mat4 const & b);     // m1 != m2 ?

    #ifndef ALGEBRA3_NO_ISTREAMS
    friend std::ostream & operator << (std::ostream & s, Mat4 const & m);    // output to stream
    friend std::istream & operator >> (std::istream & s, Mat4 & m);          // input from stream
    #endif // !ALGEBRA3_NO_IOSTREAMS

    friend void swap(Mat4 & a, Mat4 & b);                          // swap m1 & m2

    // necessary friend declarations

    friend Vec4 operator * (Mat4 const & a, Vec4 const & v);      // linear transform
    friend Vec3 operator * (Mat4 const & a, Vec3 const & v);      // linear transform

}; // class Mat4


/****************************************************************
*                                                               *
*          2D functions and 3D functions                        *
*                                                               *
****************************************************************/

Mat3 identity2D();                                              // identity 2D
Mat3 translation2D(Vec2 const & v);                             // translation 2D
Mat3 rotation2D(Vec2 const & Center, double const angleDeg);    // rotation 2D
Mat3 scaling2D(Vec2 const & scaleVector);                       // scaling 2D
Mat4 identity3D();                                              // identity 3D
Mat4 translation3D(Vec3 const & v);                             // translation 3D
Mat4 rotation3D(Vec3 axis, double const angleDeg);              // rotation 3D
Mat4 scaling3D(Vec3 const & scaleVector);                       // scaling 3D
Mat4 perspective3D(double const d);                             // perspective 3D


//
//  Implementation
//

/****************************************************************
*                                                               *
*           Vec2 Member functions                               *
*                                                               *
****************************************************************/

// CONSTRUCTORS

inline Vec2::Vec2() {}

inline Vec2::Vec2(double const x, double const y)
{ n[0] = x; n[1] = y; }

inline Vec2::Vec2(double const d)
{ n[0] = n[1] = d; }

inline Vec2::Vec2(Vec2 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; }

inline Vec2::Vec2(Vec3 const & v) // it is up to caller to avoid divide-by-zero
{ n[0] = v.n[0]/v.n[2]; n[1] = v.n[1]/v.n[2]; };

inline Vec2::Vec2(Vec3 const & v, int dropAxis)
{
  switch (dropAxis)
  {
    case 0: n[0] = v.n[1]; n[1] = v.n[2]; break;
    case 1: n[0] = v.n[0]; n[1] = v.n[2]; break;
    default: n[0] = v.n[0]; n[1] = v.n[1]; break;
  }
}


// ASSIGNMENT OPERATORS

inline Vec2 & Vec2::operator = (Vec2 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; return *this; }

inline Vec2 & Vec2::operator += (Vec2 const & v)
{ n[0] += v.n[0]; n[1] += v.n[1]; return *this; }

inline Vec2 & Vec2::operator -= (Vec2 const & v)
{ n[0] -= v.n[0]; n[1] -= v.n[1]; return *this; }

inline Vec2 & Vec2::operator *= (double const d)
{ n[0] *= d; n[1] *= d; return *this; }

inline Vec2 & Vec2::operator /= (double const d)
{ double d_inv = 1./d; n[0] *= d_inv; n[1] *= d_inv; return *this; }

inline double & Vec2::operator [] (int i)
{
  assert(!(i < 0 || i > 1));        // subscript check
  return n[i];
}

inline double Vec2::operator [] (int i) const
{
  assert(!(i < 0 || i > 1));
  return n[i];
}

inline double & Vec2::x() { return n[0]; }
inline double & Vec2::y() { return n[1]; }
inline double Vec2::x() const { return n[0]; }
inline double Vec2::y() const { return n[1]; }


// SPECIAL FUNCTIONS

inline double Vec2::length() const
{ return sqrt(length2()); }

inline double Vec2::length2() const
{ return n[0]*n[0] + n[1]*n[1]; }

inline Vec2 & Vec2::normalize() // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

inline Vec2 & Vec2::apply(ALG3_FCT_PTR fct)
{ n[0] = (*fct)(n[0]); n[1] = (*fct)(n[1]); return *this; }

inline Vec2 Vec2::perp() const
{ return Vec2(-n[1], n[0]); }

// FRIENDS

inline Vec2 operator - (Vec2 const & a)
{ return Vec2(-a.n[0],-a.n[1]); }

inline Vec2 operator + (Vec2 const & a, Vec2 const & b)
{ return Vec2(a.n[0]+ b.n[0], a.n[1] + b.n[1]); }

inline Vec2 operator - (Vec2 const & a, Vec2 const & b)
{ return Vec2(a.n[0]-b.n[0], a.n[1]-b.n[1]); }

inline Vec2 operator * (Vec2 const & a, double const d)
{ return Vec2(d*a.n[0], d*a.n[1]); }

inline Vec2 operator * (double const d, Vec2 const & a)
{ return a*d; }

inline Vec2 operator * (Mat3 const & a, Vec2 const & v)
{
  Vec3 av;

  av.n[0] = a.v[0].n[0]*v.n[0] + a.v[0].n[1]*v.n[1] + a.v[0].n[2];
  av.n[1] = a.v[1].n[0]*v.n[0] + a.v[1].n[1]*v.n[1] + a.v[1].n[2];
  av.n[2] = a.v[2].n[0]*v.n[0] + a.v[2].n[1]*v.n[1] + a.v[2].n[2];
  return av;
}

inline Vec2 operator * (Vec2 const & v, Mat3 const & a)
{ return a.transpose() * v; }

inline double operator * (Vec2 const & a, Vec2 const & b)
{ return (a.n[0]*b.n[0] + a.n[1]*b.n[1]); }

inline Vec2 operator / (Vec2 const & a, double const d)
{ double d_inv = 1./d; return Vec2(a.n[0]*d_inv, a.n[1]*d_inv); }

inline Vec3 operator ^ (Vec2 const & a, Vec2 const & b)
{ return Vec3(0.0, 0.0, a.n[0] * b.n[1] - b.n[0] * a.n[1]); }

inline bool operator == (Vec2 const & a, Vec2 const & b)
{ return (a.n[0] == b.n[0]) && (a.n[1] == b.n[1]); }

inline bool operator != (Vec2 const & a, Vec2 const & b)
{ return !(a == b); }

#ifndef ALGEBRA3_NO_ISTREAMS

inline std::ostream & operator << (std::ostream & s, Vec2 const & v)
{ return s << "| " << v.n[0] << ' ' << v.n[1] << " |"; }

inline std::istream & operator >> (std::istream & s, Vec2 & v)
{
  Vec2 v_tmp;
  char c = ' ';

  while (std::isspace(c))
    s >> c;

  // The vectors can be formatted either as x y or | x y |
  if (c == '|')
  {
    s >> v_tmp[0] >> v_tmp[1];
    while (s >> c && std::isspace(c)) ;
    if (c != '|')
      s.setstate(std::ios::badbit);
  }
  else
  {
    s.putback(c);
    s >> v_tmp[0] >> v_tmp[1];
  }

  if (s)
    v = v_tmp;

  return s;
}

#endif // !ALGEBRA3_NO_IOSTREAMS

inline void swap(Vec2 & a, Vec2 & b)
{ Vec2 tmp(a); a = b; b = tmp; }

inline Vec2 min(Vec2 const & a, Vec2 const & b)
{ return Vec2(std::min(a.n[0], b.n[0]), std::min(a.n[1], b.n[1])); }

inline Vec2 max(Vec2 const & a, Vec2 const & b)
{ return Vec2(std::max(a.n[0], b.n[0]), std::max(a.n[1], b.n[1])); }

inline Vec2 prod(Vec2 const & a, Vec2 const & b)
{ return Vec2(a.n[0] * b.n[0], a.n[1] * b.n[1]); }

/****************************************************************
*                                                               *
*           Vec3 Member functions                               *
*                                                               *
****************************************************************/

// CONSTRUCTORS

inline Vec3::Vec3() {}

inline Vec3::Vec3(double const x, double const y, double const z)
{ n[0] = x; n[1] = y; n[2] = z; }

inline Vec3::Vec3(double const d)
{ n[0] = n[1] = n[2] = d; }

inline Vec3::Vec3(Vec3 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; }

inline Vec3::Vec3(Vec2 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = 1.0; }

inline Vec3::Vec3(Vec2 const & v, double d)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = d; }

inline Vec3::Vec3(Vec4 const & v) // it is up to caller to avoid divide-by-zero
{ n[0] = v.n[0] / v.n[3]; n[1] = v.n[1] / v.n[3];
  n[2] = v.n[2] / v.n[3]; }

inline Vec3::Vec3(Vec4 const & v, int dropAxis)
{
  switch (dropAxis)
  {
    case 0: n[0] = v.n[1]; n[1] = v.n[2]; n[2] = v.n[3]; break;
    case 1: n[0] = v.n[0]; n[1] = v.n[2]; n[2] = v.n[3]; break;
    case 2: n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[3]; break;
    default: n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; break;
  }
}


// ASSIGNMENT OPERATORS

inline Vec3 & Vec3::operator = (Vec3 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; return *this; }

inline Vec3 & Vec3::operator += (Vec3 const & v)
{ n[0] += v.n[0]; n[1] += v.n[1]; n[2] += v.n[2]; return *this; }

inline Vec3 & Vec3::operator -= (Vec3 const & v)
{ n[0] -= v.n[0]; n[1] -= v.n[1]; n[2] -= v.n[2]; return *this; }

inline Vec3 & Vec3::operator *= (double const d)
{ n[0] *= d; n[1] *= d; n[2] *= d; return *this; }

inline Vec3 & Vec3::operator /= (double const d)
{ double d_inv = 1./d; n[0] *= d_inv; n[1] *= d_inv; n[2] *= d_inv;
  return *this; }

inline double & Vec3::operator [] (int i)
{
  assert(! (i < 0 || i > 2));
  return n[i];
}

inline double Vec3::operator [] (int i) const
{
  assert(! (i < 0 || i > 2));
  return n[i];
}

inline double & Vec3::x() { return n[0]; }
inline double & Vec3::y() { return n[1]; }
inline double & Vec3::z() { return n[2]; }
inline double Vec3::x() const { return n[0]; }
inline double Vec3::y() const { return n[1]; }
inline double Vec3::z() const { return n[2]; }

// SPECIAL FUNCTIONS

inline double Vec3::length() const
{ return sqrt(length2()); }

inline double Vec3::length2() const
{ return n[0]*n[0] + n[1]*n[1] + n[2]*n[2]; }

inline Vec3 & Vec3::normalize() // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

inline Vec3 & Vec3::apply(ALG3_FCT_PTR fct)
{ n[0] = (*fct)(n[0]); n[1] = (*fct)(n[1]); n[2] = (*fct)(n[2]);
  return *this; }


// FRIENDS

inline Vec3 operator - (Vec3 const & a)
{ return Vec3(-a.n[0],-a.n[1],-a.n[2]); }

inline Vec3 operator + (Vec3 const & a, Vec3 const & b)
{ return Vec3(a.n[0] + b.n[0], a.n[1] + b.n[1], a.n[2] + b.n[2]); }

inline Vec3 operator - (Vec3 const & a, Vec3 const & b)
{ return Vec3(a.n[0] - b.n[0], a.n[1] - b.n[1], a.n[2] - b.n[2]); }

inline Vec3 operator * (Vec3 const & a, double const d)
{ return Vec3(d*a.n[0], d*a.n[1], d*a.n[2]); }

inline Vec3 operator * (double const d, Vec3 const & a)
{ return a*d; }

inline Vec3 operator * (Mat3 const & a, Vec3 const & v)
{
#define ALG3_ROWCOL(i) a.v[i].n[0]*v.n[0] + a.v[i].n[1]*v.n[1] \
                     + a.v[i].n[2]*v.n[2]
  return Vec3(ALG3_ROWCOL(0), ALG3_ROWCOL(1), ALG3_ROWCOL(2));
#undef ALG3_ROWCOL // (i)
}

inline Vec3 operator * (Mat4 const & a, Vec3 const & v)
{ return a * Vec4(v); }

inline Vec3 operator * (Vec3 const & v, Mat4 const & a)
{ return a.transpose() * v; }

inline double operator * (Vec3 const & a, Vec3 const & b)
{ return (a.n[0]*b.n[0] + a.n[1]*b.n[1] + a.n[2]*b.n[2]); }

inline Vec3 operator / (Vec3 const & a, double const d)
{ double d_inv = 1./d; return Vec3(a.n[0]*d_inv, a.n[1]*d_inv,
  a.n[2]*d_inv); }

inline Vec3 operator ^ (Vec3 const & a, Vec3 const & b)
{
  return Vec3(a.n[1]*b.n[2] - a.n[2]*b.n[1],
              a.n[2]*b.n[0] - a.n[0]*b.n[2],
              a.n[0]*b.n[1] - a.n[1]*b.n[0]);
}

inline bool operator == (Vec3 const & a, Vec3 const & b)
{ return (a.n[0] == b.n[0]) && (a.n[1] == b.n[1]) && (a.n[2] == b.n[2]); }

inline bool operator != (Vec3 const & a, Vec3 const & b)
{ return !(a == b); }

#ifndef ALGEBRA3_NO_ISTREAMS
inline std::ostream & operator << (std::ostream & s, Vec3 const & v)
{ return s << "| " << v.n[0] << ' ' << v.n[1] << ' ' << v.n[2] << " |"; }

inline std::istream & operator >> (std::istream & s, Vec3 & v)
{
  Vec3 v_tmp;
  char c = ' ';

  while (std::isspace(c))
    s >> c;

  // The vectors can be formatted either as x y z or | x y z |
  if (c == '|')
  {
    s >> v_tmp[0] >> v_tmp[1] >> v_tmp[2];
    while (s >> c && std::isspace(c)) ;
    if (c != '|')
      s.setstate(std::ios::badbit);
  }
  else
  {
    s.putback(c);
    s >> v_tmp[0] >> v_tmp[1] >> v_tmp[2];
  }

  if (s)
    v = v_tmp;

  return s;
}
#endif // !ALGEBRA3_NO_IOSTREAMS

inline void swap(Vec3 & a, Vec3 & b)
{ Vec3 tmp(a); a = b; b = tmp; }

inline Vec3 min(Vec3 const & a, Vec3 const & b)
{ return Vec3(std::min(a.n[0], b.n[0]), std::min(a.n[1], b.n[1]), std::min(a.n[2],
  b.n[2])); }

inline Vec3 max(Vec3 const & a, Vec3 const & b)
{ return Vec3(std::max(a.n[0], b.n[0]), std::max(a.n[1], b.n[1]), std::max(a.n[2],
  b.n[2])); }

inline Vec3 prod(Vec3 const & a, Vec3 const & b)
{ return Vec3(a.n[0] * b.n[0], a.n[1] * b.n[1], a.n[2] * b.n[2]); }


/****************************************************************
*                                                               *
*           Vec4 Member functions                               *
*                                                               *
****************************************************************/

// CONSTRUCTORS

inline Vec4::Vec4() {}

inline Vec4::Vec4(double const x, double const y, double const z,
                  double const w)
{ n[0] = x; n[1] = y; n[2] = z; n[3] = w; }

inline Vec4::Vec4(double const d)
{  n[0] = n[1] = n[2] = n[3] = d; }

inline Vec4::Vec4(Vec4 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; n[3] = v.n[3]; }

inline Vec4::Vec4(Vec3 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; n[3] = 1.0; }

inline Vec4::Vec4(Vec3 const & v, double const d)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2];  n[3] = d; }


// ASSIGNMENT OPERATORS

inline Vec4 & Vec4::operator = (Vec4 const & v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; n[3] = v.n[3];
return *this; }

inline Vec4 & Vec4::operator += (Vec4 const & v)
{ n[0] += v.n[0]; n[1] += v.n[1]; n[2] += v.n[2]; n[3] += v.n[3];
return *this; }

inline Vec4 & Vec4::operator -= (Vec4 const & v)
{ n[0] -= v.n[0]; n[1] -= v.n[1]; n[2] -= v.n[2]; n[3] -= v.n[3];
return *this; }

inline Vec4 & Vec4::operator *= (double const d)
{ n[0] *= d; n[1] *= d; n[2] *= d; n[3] *= d; return *this; }

inline Vec4 & Vec4::operator /= (double const d)
{ double d_inv = 1./d; n[0] *= d_inv; n[1] *= d_inv; n[2] *= d_inv;
  n[3] *= d_inv; return *this; }

inline double & Vec4::operator [] (int i)
{
  assert(! (i < 0 || i > 3));
  return n[i];
}

inline double Vec4::operator [] (int i) const
{
  assert(! (i < 0 || i > 3));
  return n[i];
}

inline double & Vec4::x() { return n[0]; }
inline double & Vec4::y() { return n[1]; }
inline double & Vec4::z() { return n[2]; }
inline double & Vec4::w() { return n[3]; }
inline double Vec4::x() const { return n[0]; }
inline double Vec4::y() const { return n[1]; }
inline double Vec4::z() const { return n[2]; }
inline double Vec4::w() const { return n[3]; }


// SPECIAL FUNCTIONS

inline double Vec4::length() const
{ return sqrt(length2()); }

inline double Vec4::length2() const
{ return n[0]*n[0] + n[1]*n[1] + n[2]*n[2] + n[3]*n[3]; }

inline Vec4 & Vec4::normalize() // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

inline Vec4 & Vec4::apply(ALG3_FCT_PTR fct)
{ n[0] = (*fct)(n[0]); n[1] = (*fct)(n[1]); n[2] = (*fct)(n[2]);
  n[3] = (*fct)(n[3]); return *this; }


// FRIENDS

inline Vec4 operator - (Vec4 const & a)
{ return Vec4(-a.n[0],-a.n[1],-a.n[2],-a.n[3]); }

inline Vec4 operator + (Vec4 const & a, Vec4 const & b)
{ return Vec4(a.n[0] + b.n[0], a.n[1] + b.n[1], a.n[2] + b.n[2],
  a.n[3] + b.n[3]); }

inline Vec4 operator - (Vec4 const & a, Vec4 const & b)
{  return Vec4(a.n[0] - b.n[0], a.n[1] - b.n[1], a.n[2] - b.n[2],
   a.n[3] - b.n[3]); }

inline Vec4 operator * (Vec4 const & a, double const d)
{ return Vec4(d*a.n[0], d*a.n[1], d*a.n[2], d*a.n[3]); }

inline Vec4 operator * (double const d, Vec4 const & a)
{ return a*d; }

inline Vec4 operator * (Mat4 const & a, Vec4 const & v)
{
#define ALG3_ROWCOL(i) a.v[i].n[0]*v.n[0] + a.v[i].n[1]*v.n[1] \
                     + a.v[i].n[2]*v.n[2] + a.v[i].n[3]*v.n[3]
  return Vec4(ALG3_ROWCOL(0), ALG3_ROWCOL(1), ALG3_ROWCOL(2), ALG3_ROWCOL(3));
#undef ALG3_ROWCOL // (i)
}

inline Vec4 operator * (Vec4 const & v, Mat4 const & a)
{ return a.transpose() * v; }

inline double operator * (Vec4 const & a, Vec4 const & b)
{ return (a.n[0]*b.n[0] + a.n[1]*b.n[1] + a.n[2]*b.n[2] +
  a.n[3]*b.n[3]); }

inline Vec4 operator / (Vec4 const & a, double const d)
{ double d_inv = 1./d; return Vec4(a.n[0]*d_inv, a.n[1]*d_inv, a.n[2]*d_inv,
  a.n[3]*d_inv); }

inline bool operator == (Vec4 const & a, Vec4 const & b)
{ return (a.n[0] == b.n[0]) && (a.n[1] == b.n[1]) && (a.n[2] == b.n[2])
  && (a.n[3] == b.n[3]); }

inline bool operator != (Vec4 const & a, Vec4 const & b)
{ return !(a == b); }

#ifndef ALGEBRA3_NO_ISTREAMS
inline std::ostream & operator << (std::ostream & s, Vec4 const & v)
{ return s << "| " << v.n[0] << ' ' << v.n[1] << ' ' << v.n[2] << ' '
           << v.n[3] << " |"; }

inline std::istream & operator >> (std::istream & s, Vec4 & v)
{
  Vec4 v_tmp;
  char c = ' ';

  while (std::isspace(c))
    s >> c;

  // The vectors can be formatted either as x y z w or | x y z w |

  if (c == '|')
  {
    s >> v_tmp[0] >> v_tmp[1] >> v_tmp[2] >> v_tmp[3];
    while (s >> c && std::isspace(c)) ;
    if (c != '|')
      s.setstate(std::ios::badbit);
  }
  else
  {
    s.putback(c);
    s >> v_tmp[0] >> v_tmp[1] >> v_tmp[2] >> v_tmp[3];
  }

  if (s)
    v = v_tmp;

  return s;
}
#endif // !ALGEBRA3_NO_IOSTREAMS

inline void swap(Vec4 & a, Vec4 & b)
{ Vec4 tmp(a); a = b; b = tmp; }

inline Vec4 min(Vec4 const & a, Vec4 const & b)
{ return Vec4(std::min(a.n[0], b.n[0]), std::min(a.n[1], b.n[1]), std::min(a.n[2],
  b.n[2]), std::min(a.n[3], b.n[3])); }

inline Vec4 max(Vec4 const & a, Vec4 const & b)
{ return Vec4(std::max(a.n[0], b.n[0]), std::max(a.n[1], b.n[1]), std::max(a.n[2],
  b.n[2]), std::max(a.n[3], b.n[3])); }

inline Vec4 prod(Vec4 const & a, Vec4 const & b)
{ return Vec4(a.n[0] * b.n[0], a.n[1] * b.n[1], a.n[2] * b.n[2],
  a.n[3] * b.n[3]); }


/****************************************************************
*                                                               *
*           Mat3 member functions                               *
*                                                               *
****************************************************************/

// CONSTRUCTORS

inline Mat3::Mat3() {}

inline Mat3::Mat3(Vec3 const & v0, Vec3 const & v1, Vec3 const & v2)
{ v[0] = v0; v[1] = v1; v[2] = v2; }

inline Mat3::Mat3(double const d)
{ v[0] = v[1] = v[2] = Vec3(d); }

inline Mat3::Mat3(Mat3 const & m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; }


// ASSIGNMENT OPERATORS

inline Mat3 & Mat3::operator = (Mat3 const & m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; return *this; }

inline Mat3 & Mat3::operator += (Mat3 const & m)
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; return *this; }

inline Mat3 & Mat3::operator -= (Mat3 const & m)
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; return *this; }

inline Mat3 & Mat3::operator *= (double const d)
{ v[0] *= d; v[1] *= d; v[2] *= d; return *this; }

inline Mat3 & Mat3::operator /= (double const d)
{ v[0] /= d; v[1] /= d; v[2] /= d; return *this; }

inline Vec3 & Mat3::operator [] (int i)
{
  assert(! (i < 0 || i > 2));
  return v[i];
}

inline Vec3 const & Mat3::operator [] (int i) const
{
  assert(!(i < 0 || i > 2));
  return v[i];
}

// SPECIAL FUNCTIONS

inline Mat3 Mat3::transpose() const
{
  return Mat3(Vec3(v[0][0], v[1][0], v[2][0]),
              Vec3(v[0][1], v[1][1], v[2][1]),
              Vec3(v[0][2], v[1][2], v[2][2]));
}

inline Mat3 Mat3::inverse() const    // Gauss-Jordan elimination with partial pivoting
{
  Mat3 a(*this),          // As a evolves from original mat into identity
       b(identity2D());   // b evolves from identity into inverse(a)
  int  i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<3; j++)   // Find largest pivot in column j among rows j..2
  {
    i1 = j;         // Row with largest pivot candidate
    for (i=j+1; i<3; i++)
      if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j]))
        i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    swap(a.v[i1], a.v[j]);
    swap(b.v[i1], b.v[j]);

    // Scale row j to have a unit diagonal
    if (a.v[j].n[j]==0.)
      ALG3_ERROR("Mat3::inverse: singular matrix; can't invert\n")

    b.v[j] /= a.v[j].n[j];
    a.v[j] /= a.v[j].n[j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<3; i++)
      if (i!=j)
      {
        b.v[i] -= a.v[i].n[j]*b.v[j];
        a.v[i] -= a.v[i].n[j]*a.v[j];
      }
  }

  return b;
}

inline Mat3 & Mat3::apply(ALG3_FCT_PTR fct)
{
  v[0].apply(fct);
  v[1].apply(fct);
  v[2].apply(fct);
  return *this;
}


// FRIENDS

inline Mat3 operator - (Mat3 const & a)
{ return Mat3(-a.v[0], -a.v[1], -a.v[2]); }

inline Mat3 operator + (Mat3 const & a, Mat3 const & b)
{ return Mat3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); }

inline Mat3 operator - (Mat3 const & a, Mat3 const & b)
{ return Mat3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); }

inline Mat3 operator * (Mat3 const & a, Mat3 const & b)
{
#define ALG3_ROWCOL(i, j) \
    a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
  return Mat3(Vec3(ALG3_ROWCOL(0,0), ALG3_ROWCOL(0,1), ALG3_ROWCOL(0,2)),
              Vec3(ALG3_ROWCOL(1,0), ALG3_ROWCOL(1,1), ALG3_ROWCOL(1,2)),
              Vec3(ALG3_ROWCOL(2,0), ALG3_ROWCOL(2,1), ALG3_ROWCOL(2,2)));
#undef ALG3_ROWCOL // (i, j)
}

inline Mat3 operator * (Mat3 const & a, double const d)
{ return Mat3(a.v[0] * d, a.v[1] * d, a.v[2] * d); }

inline Mat3 operator * (double const d, Mat3 const & a)
{ return a*d; }

inline Mat3 operator / (Mat3 const & a, double const d)
{ return Mat3(a.v[0] / d, a.v[1] / d, a.v[2] / d); }

inline bool operator == (Mat3 const & a, Mat3 const & b)
{ return (a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]); }

inline bool operator != (Mat3 const & a, Mat3 const & b)
{ return !(a == b); }

#ifndef ALGEBRA3_NO_ISTREAMS
inline std::ostream & operator << (std::ostream & s, Mat3 const & m)
{ return s << m.v[0] << '\n' << m.v[1] << '\n' << m.v[2]; }

inline std::istream & operator >> (std::istream & s, Mat3 & m)
{
  Mat3 m_tmp;

  s >> m_tmp[0] >> m_tmp[1] >> m_tmp[2];
  if (s)
    m = m_tmp;

  return s;
}
#endif // !ALGEBRA3_NO_IOSTREAMS

inline void swap(Mat3 & a, Mat3 & b)
{ Mat3 tmp(a); a = b; b = tmp; }


/****************************************************************
*                                                               *
*           Mat4 member functions                               *
*                                                               *
****************************************************************/

// CONSTRUCTORS

inline Mat4::Mat4() {}

inline Mat4::Mat4(Vec4 const & v0, Vec4 const & v1, Vec4 const & v2, Vec4 const & v3)
{ v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3; }

inline Mat4::Mat4(double const d)
{ v[0] = v[1] = v[2] = v[3] = Vec4(d); }

inline Mat4::Mat4(Mat4 const & m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3]; }


// ASSIGNMENT OPERATORS

inline Mat4 & Mat4::operator = (Mat4 const & m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3];
return *this; }

inline Mat4 & Mat4::operator += (Mat4 const & m)
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; v[3] += m.v[3];
return *this; }

inline Mat4 & Mat4::operator -= (Mat4 const & m)
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; v[3] -= m.v[3];
return *this; }

inline Mat4 & Mat4::operator *= (double const d)
{ v[0] *= d; v[1] *= d; v[2] *= d; v[3] *= d; return *this; }

inline Mat4 & Mat4::operator /= (double const d)
{ v[0] /= d; v[1] /= d; v[2] /= d; v[3] /= d; return *this; }

inline Vec4 & Mat4::operator [] (int i)
{
  assert(! (i < 0 || i > 3));
  return v[i];
}

inline Vec4 const & Mat4::operator [] (int i) const
{
  assert(! (i < 0 || i > 3));
  return v[i];
}

// SPECIAL FUNCTIONS;

inline Mat4 Mat4::transpose() const
{
  return Mat4(Vec4(v[0][0], v[1][0], v[2][0], v[3][0]),
              Vec4(v[0][1], v[1][1], v[2][1], v[3][1]),
              Vec4(v[0][2], v[1][2], v[2][2], v[3][2]),
              Vec4(v[0][3], v[1][3], v[2][3], v[3][3]));
}

inline Mat4 Mat4::inverse() const    // Gauss-Jordan elimination with partial pivoting
{
  Mat4 a(*this),          // As a evolves from original mat into identity
       b(identity3D());   // b evolves from identity into inverse(a)
  int i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<4; j++)   // Find largest pivot in column j among rows j..3
  {
    i1 = j;         // Row with largest pivot candidate
    for (i=j+1; i<4; i++)
      if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j]))
        i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    swap(a.v[i1], a.v[j]);
    swap(b.v[i1], b.v[j]);

    // Scale row j to have a unit diagonal
    if (a.v[j].n[j]==0.)
      ALG3_ERROR("Mat4::inverse: singular matrix; can't invert\n");

    b.v[j] /= a.v[j].n[j];
    a.v[j] /= a.v[j].n[j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<4; i++)
      if (i!=j)
      {
        b.v[i] -= a.v[i].n[j]*b.v[j];
        a.v[i] -= a.v[i].n[j]*a.v[j];
      }
  }

  return b;
}

inline Mat4 & Mat4::apply(ALG3_FCT_PTR fct)
{ v[0].apply(fct); v[1].apply(fct); v[2].apply(fct); v[3].apply(fct);
  return *this; }


// FRIENDS

inline Mat4 operator - (Mat4 const & a)
{ return Mat4(-a.v[0], -a.v[1], -a.v[2], -a.v[3]); }

inline Mat4 operator + (Mat4 const & a, Mat4 const & b)
{ return Mat4(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2],
  a.v[3] + b.v[3]);
}

inline Mat4 operator - (Mat4 const & a, Mat4 const & b)
{ return Mat4(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] - b.v[3]); }

inline Mat4 operator * (Mat4 const & a, Mat4 const & b)
{
#define ALG3_ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + \
                          a.v[i].n[2]*b.v[2][j] + a.v[i].n[3]*b.v[3][j]
  return Mat4(
    Vec4(ALG3_ROWCOL(0,0), ALG3_ROWCOL(0,1), ALG3_ROWCOL(0,2), ALG3_ROWCOL(0,3)),
    Vec4(ALG3_ROWCOL(1,0), ALG3_ROWCOL(1,1), ALG3_ROWCOL(1,2), ALG3_ROWCOL(1,3)),
    Vec4(ALG3_ROWCOL(2,0), ALG3_ROWCOL(2,1), ALG3_ROWCOL(2,2), ALG3_ROWCOL(2,3)),
    Vec4(ALG3_ROWCOL(3,0), ALG3_ROWCOL(3,1), ALG3_ROWCOL(3,2), ALG3_ROWCOL(3,3))
  );
#undef ALG3_ROWCOL
}

inline Mat4 operator * (Mat4 const & a, double const d)
{ return Mat4(a.v[0] * d, a.v[1] * d, a.v[2] * d, a.v[3] * d); }

inline Mat4 operator * (double const d, Mat4 const & a)
{ return a*d; }

inline Mat4 operator / (Mat4 const & a, double const d)
{ return Mat4(a.v[0] / d, a.v[1] / d, a.v[2] / d, a.v[3] / d); }

inline bool operator == (Mat4 const & a, Mat4 const & b)
{ return ((a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]) &&
  (a.v[3] == b.v[3])); }

inline bool operator != (Mat4 const & a, Mat4 const & b)
{ return !(a == b); }

#ifndef ALGEBRA3_NO_ISTREAMS
inline std::ostream & operator << (std::ostream & s, Mat4 const & m)
{ return s << m.v[0] << '\n' << m.v[1] << '\n' << m.v[2] << '\n' << m.v[3]; }

inline std::istream & operator >> (std::istream & s, Mat4 & m)
{
  Mat4 m_tmp;

  s >> m_tmp[0] >> m_tmp[1] >> m_tmp[2] >> m_tmp[3];
  if (s)
    m = m_tmp;

  return s;
}
#endif // !ALGEBRA3_NO_IOSTREAMS

inline void swap(Mat4 & a, Mat4 & b)
{ Mat4 tmp(a); a = b; b = tmp; }


/****************************************************************
*                                                               *
*          2D functions and 3D functions                        *
*                                                               *
****************************************************************/

inline Mat3 identity2D()
{ return Mat3(Vec3(1.0, 0.0, 0.0),
              Vec3(0.0, 1.0, 0.0),
              Vec3(0.0, 0.0, 1.0)); }

inline Mat3 translation2D(Vec2 const & v)
{ return Mat3(Vec3(1.0, 0.0, v[0]),
              Vec3(0.0, 1.0, v[1]),
              Vec3(0.0, 0.0, 1.0)); }

inline Mat3 rotation2D(Vec2 const & Center, double const angleDeg)
{
  double angleRad = angleDeg * M_PI / 180.0,
         c = cos(angleRad),
         s = sin(angleRad);

  return Mat3(Vec3(c, -s, Center[0] * (1.0-c) + Center[1] * s),
              Vec3(s, c, Center[1] * (1.0-c) - Center[0] * s),
              Vec3(0.0, 0.0, 1.0));
}

inline Mat3 scaling2D(Vec2 const & scaleVector)
{ return Mat3(Vec3(scaleVector[0], 0.0, 0.0),
              Vec3(0.0, scaleVector[1], 0.0),
              Vec3(0.0, 0.0, 1.0)); }

inline Mat4 identity3D()
{ return Mat4(Vec4(1.0, 0.0, 0.0, 0.0),
              Vec4(0.0, 1.0, 0.0, 0.0),
              Vec4(0.0, 0.0, 1.0, 0.0),
              Vec4(0.0, 0.0, 0.0, 1.0)); }

inline Mat4 translation3D(Vec3 const & v)
{ return Mat4(Vec4(1.0, 0.0, 0.0, v[0]),
              Vec4(0.0, 1.0, 0.0, v[1]),
              Vec4(0.0, 0.0, 1.0, v[2]),
              Vec4(0.0, 0.0, 0.0, 1.0)); }

inline Mat4 rotation3D(Vec3 axis, double const angleDeg)
{
  double angleRad = angleDeg * M_PI / 180.0,
         c = cos(angleRad),
         s = sin(angleRad),
         t = 1.0 - c;

  axis.normalize();
  return Mat4(Vec4(t * axis[0] * axis[0] + c,
                   t * axis[0] * axis[1] - s * axis[2],
                   t * axis[0] * axis[2] + s * axis[1],
                   0.0),
              Vec4(t * axis[0] * axis[1] + s * axis[2],
                   t * axis[1] * axis[1] + c,
                   t * axis[1] * axis[2] - s * axis[0],
                   0.0),
              Vec4(t * axis[0] * axis[2] - s * axis[1],
                   t * axis[1] * axis[2] + s * axis[0],
                   t * axis[2] * axis[2] + c,
                   0.0),
              Vec4(0.0, 0.0, 0.0, 1.0));
}

inline Mat4 scaling3D(Vec3 const & scaleVector)
{ return Mat4(Vec4(scaleVector[0], 0.0, 0.0, 0.0),
              Vec4(0.0, scaleVector[1], 0.0, 0.0),
              Vec4(0.0, 0.0, scaleVector[2], 0.0),
              Vec4(0.0, 0.0, 0.0, 1.0)); }

inline Mat4 perspective3D(double const d)
{ return Mat4(Vec4(1.0, 0.0, 0.0, 0.0),
              Vec4(0.0, 1.0, 0.0, 0.0),
              Vec4(0.0, 0.0, 1.0, 0.0),
              Vec4(0.0, 0.0, 1.0/d, 0.0)); }


#endif // __Algebra3_hpp__
