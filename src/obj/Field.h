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

#include <Adafruit_GFX.h>

#include "obj/Primitive.h"
#include "obj/Frame.h"

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
  uint16_t _lineSpacing;
  uint8_t _sizeText;
  GFXfont *_font;
  Color _colorText;
  Color _colorTextTouched;
  Color _colorTextSelected;

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
    _lineSpacing(0U),
    _sizeText(FIELD_TEXT_SIZE_DEFAULT),
    _font(nullptr),
    _colorText(FIELD_TEXT_COLOR_DEFAULT),
    _colorTextTouched(FIELD_TEXT_COLOR_DEFAULT),
    _colorTextSelected(FIELD_TEXT_COLOR_DEFAULT)
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
    _lineSpacing(0U),
    _sizeText(sizeText),
    _font(nullptr),
    _colorText(colorText),
    _colorTextTouched(colorText),
    _colorTextSelected(colorText)
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
    _lineSpacing(0U),
    _sizeText(sizeText),
    _font(nullptr),
    _colorText(colorText),
    _colorTextTouched(colorTextTouched),
    _colorTextSelected(colorTextTouched)
  {
    _lineCount = lineCount(text);
  }

  Field(
      Frame const frame,
      std::string const text,
      uint8_t const sizeText,
      GFXfont * const font,
      Color const colorText
  ):
    _frame(frame),
    _framePositioned(false),
    _text(text),
    _lineCount(0U),
    _lineSpacing(0U),
    _sizeText(sizeText),
    _font(font),
    _colorText(colorText),
    _colorTextTouched(colorText),
    _colorTextSelected(colorText)
  {
    _lineCount = lineCount(text);
  }

  Field(
      Frame const frame,
      std::string const text,
      uint8_t const sizeText,
      GFXfont * const font,
      Color const colorText,
      Color const colorTextTouched
  ):
    _frame(frame),
    _framePositioned(false),
    _text(text),
    _lineCount(0U),
    _lineSpacing(0U),
    _sizeText(sizeText),
    _font(font),
    _colorText(colorText),
    _colorTextTouched(colorTextTouched),
    _colorTextSelected(colorTextTouched)
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

  bool isMomentary(void) const
    { return _frame.isMomentary(); }
  void setIsMomentary(bool const isMomentary)
    { _frame.setIsMomentary(isMomentary); }
  bool isSelected(void) const
    { return _frame.isSelected(); }
  void setIsSelected(bool const isSelected)
    { _frame.setIsSelected(isSelected); }

  std::string text(void) const { return _text; }
  void setText(std::string const text)
  {
    if (0 != _text.compare(text)) {
      _text = text;
      _lineCount = lineCount(text);
      _frame.setNeedsUpdate();
    }
  }

  uint8_t lineCount(void) const { return _lineCount; }

  uint16_t lineSpacing(void) const { return _lineSpacing; }
  void setLineSpacing(uint16_t const lineSpacing)
    { _lineSpacing = lineSpacing; }

  uint8_t sizeText(void) const { return _sizeText; }
  void setSizeText(uint8_t const size)
    { _sizeText = size; _frame.setNeedsUpdate(); }

  GFXfont *font(void) const { return _font; }
  void setFont(GFXfont * const font)
    { _font = font; _frame.setNeedsUpdate(); }

  Color colorText(void) const { return _colorText; }
  void setColorText(Color const color)
    { if (color != _colorText)
      { _colorText = color; _frame.setNeedsUpdate(); } }

  Color colorTextTouched(void) const { return _colorTextTouched; }
  void setColorTextTouched(Color const color)
    { if (color != _colorTextTouched)
      { _colorTextTouched = color; _frame.setNeedsUpdate(); } }

  Color colorTextSelected(void) const { return _colorTextSelected; }
  void setColorTextSelected(Color const color)
    { if (color != _colorTextSelected)
      { _colorTextSelected = color; _frame.setNeedsUpdate(); } }

  void setColor(Color const color)
    { _frame.setColor(color); }
  void setColorTouched(Color const color)
    { _frame.setColorTouched(color); }
  void setColorSelected(Color const color)
    { _frame.setColorSelected(color); }
  void setColorBorder(Color const color)
    { _frame.setColorBorder(color); }
  void setColorBorderTouched(Color const color)
    { _frame.setColorBorderTouched(color); }
  void setColorBorderSelected(Color const color)
    { _frame.setColorBorderSelected(color); }

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
