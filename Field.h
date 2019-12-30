/*******************************************************************************
 *
 *  name: Field.h
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#ifndef __FIELD_H__
#define __FIELD_H__

// ----------------------------------------------------------------- includes --

#include <string>

#include <Arduino.h>

#include "Primitive.h"
#include "Frame.h"

// ------------------------------------------------------------------ defines --

#define FIELD_TEXT_COLOR_DEFAULT           COLOR_WHITE
#define FIELD_TEXT_SIZE_DEFAULT            1U

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------- forward declarations --

class Screen;

// ----------------------------------------------------------- exported types --

class Field {
protected:
  Frame _frame;
  bool _framePositioned;
  std::string _text;
  uint8_t _lineCount;
  uint8_t _sizeText;
  Color _colorText;
  Color _colorTextTouched;

  uint8_t lineCount(std::string const s)
  {
    uint8_t count = 1U;
    uint8_t len = s.length();
    for (uint8_t i = 0; i < len; ++i)
      { if ('\n' == s[i]) { ++count; } }
    return count;
  }

public:
  Field(void):
    _frame(),
    _framePositioned(false),
    _text(),
    _lineCount(0U),
    _sizeText(FIELD_TEXT_SIZE_DEFAULT),
    _colorText(FIELD_TEXT_COLOR_DEFAULT),
    _colorTextTouched(FIELD_TEXT_COLOR_DEFAULT)
  {}
  Field(
      Frame const frame,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText
  ):
    _frame(frame),
    _framePositioned(false),
    _text(text),
    _lineCount(0U),
    _sizeText(sizeText),
    _colorText(colorText),
    _colorTextTouched(colorText)
  {
    _lineCount = lineCount(text);
  }
  Field(
      Frame const frame,
      std::string const text,
      uint8_t const sizeText,
      Color const colorText,
      Color const colorTextTouched
  ):
    _frame(frame),
    _framePositioned(false),
    _text(text),
    _lineCount(0U),
    _sizeText(sizeText),
    _colorText(colorText),
    _colorTextTouched(colorTextTouched)
  {
    _lineCount = lineCount(text);
  }

  Frame const *frame(void) const { return &_frame; }

  bool framePositioned(void) const { return _framePositioned; }
  void setPosition(Point const origin, Size const size)
  {
    _frame.setOrigin(origin);
    _frame.setSize(size);
    _framePositioned = true;
  }

  std::string text(void) const { return _text; }
  void setText(std::string const text)
    { _text = text; _lineCount = lineCount(text); _frame.setNeedsUpdate(); }

  uint8_t lineCount(void) const { return _lineCount; }

  uint8_t sizeText(void) const { return _sizeText; }
  void setSizeText(uint8_t const size)
    { _sizeText = size; _frame.setNeedsUpdate(); }

  Color colorText(void) const { return _colorText; }
  void setColorText(Color const color)
    { _colorText = color; _frame.setNeedsUpdate(); }

  Color colorTextTouched(void) const { return _colorTextTouched; }
  void setColorTextTouched(Color const color)
    { _colorTextTouched = color; _frame.setNeedsUpdate(); }

  void setTouchBegin(FrameTouchCallback const callback)
    { _frame.setTouchBegin(callback); }
  void setTouchEnd(FrameTouchCallback const callback)
    { _frame.setTouchEnd(callback); }
  void setTouchPress(FrameTouchCallback const callback)
    { _frame.setTouchPress(callback); }
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

/* nothing */

#endif // __FIELD_H__
