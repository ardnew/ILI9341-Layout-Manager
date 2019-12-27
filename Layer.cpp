/*******************************************************************************
 *
 *  name: Layer.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "Layer.h"
#include "Screen.h"
#include "Frame.h"

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

void Layer::draw(Screen const &screen, Touch const &touch)
{
  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      it->draw(screen, touch);
      ++it;
    }
  }
}

void Layer::clearPanels(Screen const &screen)
{
  if (!_panel.empty()) {

    _panel.clear();
  }
}

void Layer::setNeedsUpdate(Screen const &screen)
{
  __UNUSED__(screen)

  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      it->setNeedsUpdate();
      ++it;
    }
  }
}

std::vector<Panel *> Layer::panelsOverlappingFrame(Screen const &screen, Frame const &frame)
{
  __UNUSED__(screen)

  std::vector<Panel *> vec;

  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      if (it->frame().overlaps(frame)) {
        vec.push_back(&(*it));
      }
      ++it;
    }
  }

  return vec;
}

// -------------------------------------------------------- private functions --

/* nothing */
