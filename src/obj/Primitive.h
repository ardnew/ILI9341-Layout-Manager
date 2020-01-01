/*******************************************************************************
 *
 *  name: Primitive.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

// ----------------------------------------------------------------- includes --

#include <Arduino.h>

#if defined(min) || defined(max)
#undef min // Arduino.h defines these, while the STL has actual functions with
#undef max // these names we need to let it use. remove the macros beforehand.
#endif

#include <string>

// ------------------------------------------------------------------ defines --

// the following one-liner will convert "R,G,B" triplets to 565 encoding:
//   $ perl -le 'for(@ARGV){($r,$g,$b)=(split/,/g);printf"0x%04X$/",(($r&0xF8)<<8)|(($g&0xFC)<<3)|(($b&0xF8)>>3)}' 173,255,41 255,127,0
//   0xAFE5
//   0xFBE0
#define COLOR_BLACK       0x0000  // {   0,   0,   0 }
#define COLOR_NAVY        0x000F  // {   0,   0, 123 }
#define COLOR_DARKGREEN   0x03E0  // {   0, 125,   0 }
#define COLOR_DARKCYAN    0x03EF  // {   0, 125, 123 }
#define COLOR_MAROON      0x7800  // { 123,   0,   0 }
#define COLOR_PURPLE      0x780F  // { 123,   0, 123 }
#define COLOR_OLIVE       0x7BE0  // { 123, 125,   0 }
#define COLOR_LIGHTGREY   0xC618  // { 198, 195, 198 }
#define COLOR_DARKGREY    0x7BEF  // { 123, 125, 123 }
#define COLOR_BLUE        0x001F  // {   0,   0, 255 }
#define COLOR_GREEN       0x07E0  // {   0, 255,   0 }
#define COLOR_CYAN        0x07FF  // {   0, 255, 255 }
#define COLOR_RED         0xF800  // { 255,   0,   0 }
#define COLOR_MAGENTA     0xF81F  // { 255,   0, 255 }
#define COLOR_YELLOW      0xFFE0  // { 255, 255,   0 }
#define COLOR_WHITE       0xFFFF  // { 255, 255, 255 }
#define COLOR_ORANGE      0xFD20  // { 255, 165,   0 }
#define COLOR_GREENYELLOW 0xAFE5  // { 173, 255,  41 }
#define COLOR_PINK        0xFC18  // { 255, 130, 198 }

// equality comparison tolerance between two floats
#define FLOAT32_ABSTOL 5.0e-6  // 32-bit
#define FLOAT64_ABSTOL 5.0e-14 // 64-bit

// ------------------------------------------------------------------- macros --

#define __UNUSED__(x) ; ((void)(x)) ;

// if C++17 is available, this should be replaced with std::invoke(). until
// then, however, use this definition when calling ANY member function.
#define INVOKE_MEMBER_METHOD(obj,mth) ((obj).*(mth))

// ----------------------------------------------------------- exported types --

class LayoutManagerVersion {
protected:
  constexpr static uint8_t const _strSize = 12U;
  char _str[_strSize] = { '\0' };
  uint8_t const _major;
  uint8_t const _minor;
  uint8_t const _revision;
  uint32_t const _base256;

public:
  LayoutManagerVersion(
      uint8_t const major,
      uint8_t const minor,
      uint8_t const revision
  ):
    _major(major),
    _minor(minor),
    _revision(revision),
    _base256(((major << 16U) | (minor << 8U) | revision) & 0x00FFFFFF)
  {
    sprintf(_str, "%u.%u.%u", _major, _minor, _revision);
  }
  char const *str() const
    { return _str; }
  inline bool operator==(LayoutManagerVersion const &version)
    { return _base256 == version._base256; }
  inline bool operator!=(LayoutManagerVersion const &version)
    { return _base256 != version._base256; }
  inline bool operator<(LayoutManagerVersion const &version)
    { return _base256 < version._base256; }
};

class Point {
protected:
  uint16_t _x;
  uint16_t _y;

public:
  constexpr Point(void):
    _x(0U), _y(0U) {}
  constexpr Point(uint16_t const x, uint16_t const y):
    _x(x), _y(y) {}

  bool operator==(Point const &p) const { return (p._x == _x) && (p._y == _y); }
  bool operator!=(Point const &p) const { return (p._x != _x) || (p._y != _y); }

  constexpr uint16_t x(void) const { return _x; }
  constexpr uint16_t y(void) const { return _y; }
};

class Size {
protected:
  uint16_t _width;
  uint16_t _height;

public:
  constexpr Size(void):
    _width(0U), _height(0U) {}
  constexpr Size(uint16_t const width, uint16_t const height):
    _width(width), _height(height) {}

  inline bool operator==(Size const &s) const
    { return (s._width == _width) && (s._height == _height); }
  inline bool operator!=(Size const &s) const
    { return (s._width != _width) || (s._height != _height); }

  constexpr uint16_t width(void) const { return _width; }
  constexpr uint16_t height(void) const { return _height; }
};

typedef uint16_t Color;
typedef uint8_t Pressure;
typedef uint8_t Radius;

class Touch {
protected:
  bool _isTouched;
  Point _position;
  Pressure _pressure;

public:
  constexpr Touch(void):
    _isTouched(false),
    _position(),
    _pressure(0U)
  {}
  constexpr Touch(bool const isTouched):
    _isTouched(isTouched),
    _position(),
    _pressure(0U)
  {}
  constexpr Touch(
      bool const isTouched,
      Point const &position,
      Pressure const pressure
  ):
    _isTouched(isTouched),
    _position(position),
    _pressure(pressure)
  {}

  bool operator==(Touch const &t) const
  {
    return
      (t._isTouched == _isTouched) &&
      ( t._position ==  _position) &&
      ( t._pressure ==  _pressure) ;
  }
  bool operator!=(Touch const &t) const
  {
    return
      (t._isTouched != _isTouched) ||
      ( t._position !=  _position) ||
      ( t._pressure !=  _pressure) ;
  }

  bool isTouched(void) const { return _isTouched; }
  Point position(void) const { return _position; }
  uint16_t x(void) const { return _position.x(); }
  uint16_t y(void) const { return _position.y(); }
  Pressure pressure(void) const { return _pressure; }
};

enum class Orientation {
  // orientation is based on position of board pins when looking at the screen
  NONE                  = -1,
  Bottom, Portrait      = Bottom, // = 0
  Right,  Landscape     = Right,  // = 1
  Top,    PortraitFlip  = Top,    // = 2
  Left,   LandscapeFlip = Left,   // = 3
  COUNT                           // = 4
};

enum class LayoutAxis {
  // orientation is based on position of board pins when looking at the screen
  NONE = -1,
  Horizontal, // = 0
  Vertical,   // = 1
  COUNT       // = 2
};

// ------------------------------------------------------- exported variables --

extern uint16_t const COORD_INVALID;
extern uint16_t const DIMNS_INVALID;
extern Pressure const PRESSURE_INVALID;
extern Radius   const NO_RADIUS;
extern Point    const POINT_INVALID;
extern Touch    const NO_TOUCH;

// ------------------------------------------------------- exported functions --

inline bool equals_float32(float a, float b)
  { return fabsf(a - b) <= FLOAT32_ABSTOL; }

inline bool equals_float64(double a, double b)
  { return fabsf(a - b) <= FLOAT64_ABSTOL; }

inline bool in_range_u8(uint8_t val, uint8_t min, uint8_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_i8(int8_t val, int8_t min, int8_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_u16(uint16_t val, uint16_t min, uint16_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_i16(int16_t val, int16_t min, int16_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_u32(uint32_t val, uint32_t min, uint32_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_i32(int32_t val, int32_t min, int32_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_u64(uint64_t val, uint64_t min, uint64_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_i64(int64_t val, int64_t min, int64_t max)
  { return (val >= min) && (val <= max); }

inline bool in_range_float32(float val, float min, float max)
  { return ((val > min) || (equals_float32(val, min)))
            &&
           ((val < max) || (equals_float32(val, max))); }

inline bool in_range_float64(double val, double min, double max)
  { return ((val > min) || (equals_float64(val, min)))
            &&
           ((val < max) || (equals_float64(val, max))); }

#endif // __PRIMITIVE_H__
