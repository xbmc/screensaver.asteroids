////////////////////////////////////////////////////////////////////////////
// This contains the types and math classes that I'm used to work with.
// They have been stipped of most unneeded stuff that isn't needed in 
// the screensaver
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdint.h>
#include <math.h>

/***************************** D E F I N E S *******************************/

typedef signed char      s8;
typedef unsigned char    u8;
typedef signed short     s16;
typedef unsigned short   u16;
typedef signed long      s32;
typedef unsigned long    u32;
typedef int64_t          s64;
typedef uint64_t         u64;
typedef float            f32;
typedef double           f64;
#define null        0

const f32 PI              = 3.14159265358979323846f;
const f32 FLOATEPSILON    = 0.00001f;

/****************************** M A C R O S ********************************/

#define SAFE_DELETE(_p)        { if(_p) { delete _p;     _p=NULL; } }
#define SAFE_DELETE_ARRAY(_p)  { if(_p) { delete [] _p;  _p=NULL; } }
#define SAFE_RELEASE(_p)       { if(_p) { _p->Release(); _p=NULL; } }

// Direct 3d verify
#define DVERIFY( _func )         \
  {                              \
    HRESULT _retCode = _func;    \
    if( _retCode !=  D3D_OK)     \
    {                            \
      return false;              \
    }                            \
  }

//      char buf[2000];        \
//      sprintf(buf, "\""#_func"\" returned 0x%lx in\n" __FILE__ "(%ld)\n", _retCode, __LINE__);  \
//      OutputDebugString(buf);    \

#define SQR(_x)          ((_x)*(_x))
#define DEGTORAD(d)      ((d)*(PI / 180.0f))
#define RADTODEG(r)      ((r)*(180.0f / PI))
#define assert(_x)

/***************************** C L A S S E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
class CRGBA
{
public:
  union
  {
    f32 col[4];
    struct
    {
      f32 r,g,b,a;
    };
  };

  CRGBA()
  {
    col[0] = col[1] = col[2] = 0.0f;
    col[3] = 1.0f;
  }

  CRGBA(f32 R, f32 G, f32 B, f32 A)
  {
    col[0] = R;
    col[1] = G;
    col[2] = B;
    col[3] = A;
  }

  u32 RenderColor(void) const;

  void Set(f32 R, f32 G, f32 B, f32 A)
  {
    col[0] = R;
    col[1] = G;
    col[2] = B;
    col[3] = A;
  }

  CRGBA& operator = (const CRGBA& c)
  {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
    return *this;
  }
};

////////////////////////////////////////////////////////////////////////////
//
class CVector
{
public:
  CVector() { }
  CVector(f32 _x, f32 _y, f32 _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  void Zero()
  {
    x = y = z = 0.0f;
  }

  void Set(f32 _x, f32 _y, f32 _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  f32 x;
  f32 y;
  f32 z;
};

////////////////////////////////////////////////////////////////////////////
//
class CVector2
{
public:
  f32 x, y;

  CVector2() { }
  CVector2(f32 _x, f32 _y) { x = _x; y = _y; }

  void Zero() { x = y = 0.0f;  }
  void Set(f32 _x, f32 _y) { x = _x; y = _y; }
  CVector2 Rotate(f32 angel);

  CVector2& operator += (const CVector2& v)
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  friend CVector2 operator - (const CVector2& v1, const CVector2& v2)
  {
    return CVector2(v1.x-v2.x, v1.y-v2.y);
  }

  friend CVector2 operator + (const CVector2& v1, const CVector2& v2)
  {
    return CVector2(v1.x+v2.x, v1.y+v2.y);
  }

  friend CVector2 operator * (const CVector2& v, f32 s)
  {
    return CVector2(s*v.x, s*v.y);
  }

  friend CVector2 operator / (const CVector2& v, f32 s)
  {
    f32 oneOver = 1.0f/s;
    return CVector2(oneOver*v.x, oneOver*v.y);
  }
};

/***************************** G L O B A L S *******************************/
/***************************** I N L I N E S *******************************/

inline f32 Clamp(f32 x, f32 min, f32 max)      { return (x <= min ? min : (x >= max ? max : x)); }
inline f32 RandFloat(void)                     { return (1.0f / RAND_MAX) * ((f32)rand());  }
inline f32 RandSFloat(void)                    { return (RandFloat()*2.0f)-1.0f;  }
inline f32 RandFloat(f32 min, f32 max)         { return min + ((max-min)*RandFloat()); }
inline int Rand(int max)                       { return rand() % max; }
inline f32 SquareMagnitude(const CVector2& v)  { return v.x*v.x + v.y*v.y;  }


////////////////////////////////////////////////////////////////////////////
//
inline CVector2 CVector2::Rotate(f32 angleDeg)
{
  CVector2  v;
  f32 rad = DEGTORAD(angleDeg);
  v.x = x * cos(rad) +  y * sin(rad);
  v.y = y * cos(rad) -  x * sin(rad);
  return v;
}


////////////////////////////////////////////////////////////////////////////
//
inline f32 DotProduct(const CVector& v1, const CVector& v2)
{
  return v1.x*v2.x + v1.y * v2.y + v1.z*v2.z;
}

////////////////////////////////////////////////////////////////////////////
//
inline f32 DotProduct(const CVector2& v1, const CVector2& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

////////////////////////////////////////////////////////////////////////////
//
inline CVector2 Normalized(const CVector2& v)
{
  f32 length = sqrtf(v.x*v.x + v.y*v.y);
  if (length < FLOATEPSILON)
    return CVector2(0.0f, 0.0f);
  return v/length;
}

////////////////////////////////////////////////////////////////////////////
//
inline f32 InterpolateFloat(f32 v1, f32 v2, f32 t, bool linear)
{
  assert((t >= 0.0f) && (t <= 1.0f));
  if (linear)
  {
    return v1 + t*(v2 - v1);
  }

  // Compute Hermite spline coefficients for t, where 0 <= t <= 1.
  f32 t2 = t * t;
  f32 t3 = t * t2;
  f32 z = 3.0f * t2 - t3 - t3;
  return v1*(1.0f - z) + v2*z;
}

