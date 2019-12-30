/*******************************************************************************
 *
 *  name: Panel.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "Panel.h"
#include "Screen.h"
#include "Layer.h"

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

/* nothing */

// -------------------------------------------------------- private variables --

/* nothing */

// ---------------------------------------------- private function prototypes --

/* nothing */

// ------------------------------------------------------- exported functions --

void Panel::draw(Screen const &screen, Touch const &touch)
{
  bool panelUpdate = _frame.draw(screen, touch);

  uint16_t numFields = fieldCount();
  if (numFields > 0U) {

    switch (_axis) {
      case LayoutAxis::Horizontal:
        {
          uint16_t fieldIndex = 0U;
          uint16_t fieldWidth =
            (_frame.size().width() - 2U * _margin - (numFields - 1U) * _padding)
              / numFields;

          auto it = _field.begin();
          while (it != _field.end()) {

            if (!it->framePositioned()) {
              it->setPosition(
                  Point(
                      _frame.left() + _margin +
                        fieldIndex * (_padding + fieldWidth),
                      _frame.top() + _margin
                  ),
                  Size(
                      fieldWidth,
                      _frame.size().height() - 2U * _margin
                  ));
            }

            Frame *fieldFrame = (Frame *)it->frame();
            if (panelUpdate)
              { fieldFrame->setNeedsUpdate(); }
            bool fieldUpdate = fieldFrame->draw(screen, touch);
            if (fieldUpdate) {

              Color colorText = it->colorText();
              if (fieldFrame->canTouch()) {
                if (fieldFrame->touch().isTouched()) {
                  colorText = it->colorTextTouched();
                }
              }

              screen.paintText(
                  Point(
                      (uint16_t)
                        ((float)(fieldFrame->left() + fieldFrame->right())
                          / 2.0F + 0.5F),
                      (uint16_t)
                        ((float)(fieldFrame->top() + fieldFrame->bottom())
                          / 2.0F + 0.5F)
                  ),
                  it->text(), it->lineCount(), it->sizeText(), colorText
              );
            }

            ++fieldIndex;
            ++it;
          }
        }
        break;

      case LayoutAxis::Vertical:
        {

          uint16_t lineCount;
          if (_proportional) {
            lineCount = 0U;
            auto it = _field.begin();
            while (it != _field.end()) {
              lineCount += it->lineCount();
              ++it;
            }
          }
          else {
            lineCount = numFields;
          }

          uint16_t fieldIndex = 0U;
          uint16_t lineHeight =
            (uint16_t)((float)(_frame.size().height() -
                2U * _margin - (numFields - 1) * _padding)
              / lineCount + 0.5F);

          uint16_t lineTop = _frame.top() + _margin;

          auto it = _field.begin();
          while (it != _field.end()) {

            if (!it->framePositioned()) {
              uint16_t fieldLineCount = it->lineCount();
              if (!_proportional)
                { fieldLineCount = 1U; }
              it->setPosition(
                  Point(
                      _frame.left() + _margin,
                      lineTop
                  ),
                  Size(
                      _frame.size().width() - 2U * _margin,
                      lineHeight * fieldLineCount
                  ));
            }
            lineTop += it->frame()->size().height() + _padding;

            Frame *fieldFrame = (Frame *)it->frame();
            if (panelUpdate)
              { fieldFrame->setNeedsUpdate(); }
            bool fieldUpdate = fieldFrame->draw(screen, touch);
            if (fieldUpdate) {

              Color colorText = it->colorText();
              if (fieldFrame->canTouch()) {
                if (fieldFrame->touch().isTouched()) {
                  colorText = it->colorTextTouched();
                }
              }

              screen.paintText(
                  Point(
                      (uint16_t)
                        ((float)(fieldFrame->left() + fieldFrame->right())
                          / 2.0F + 0.5F),
                      (uint16_t)
                        ((float)(fieldFrame->top() + fieldFrame->bottom())
                          / 2.0F + 0.5F)
                  ),
                  it->text(), it->lineCount(), it->sizeText(), colorText
              );
            }

            ++fieldIndex;
            ++it;
          }
        }
        break;

      default:
        break;
    }
  }
}
bool Panel::needsUpdate() const
{
  if (_frame.needsUpdate())
    { return true; }

  if (!_field.empty()) {
    auto it = _field.begin();
    while (it != _field.end()) {
      if (it->frame()->needsUpdate())
        { return true; }
      ++it;
    }
  }

  return false;
}

void Panel::setNeedsUpdate()
{
  _frame.setNeedsUpdate();

  if (!_field.empty()) {
    auto it = _field.begin();
    while (it != _field.end()) {
      ((Frame *)(it->frame()))->setNeedsUpdate();
      ++it;
    }
  }
}

void Panel::setNeedsRemove()
{
  _frame.setNeedsRemove();

  if (!_field.empty()) {
    auto it = _field.begin();
    while (it != _field.end()) {
      ((Frame *)(it->frame()))->setNeedsRemove();
      ++it;
    }
  }
}

// -------------------------------------------------------- private functions --

