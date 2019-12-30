/*******************************************************************************
 *
 *  name: Layer.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "obj/Layer.h"
#include "obj/Screen.h"
#include "obj/Frame.h"

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
  if (_remove) {
    clearPanels(screen);
    _remove = false;
  }
  else {
    if (!_panel.empty()) {
      auto it = _panel.begin();
      while (it != _panel.end()) {
        it->draw(screen, touch);
        ++it;
      }
    }
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

void Layer::setNeedsRemove(Screen const &screen)
{
  __UNUSED__(screen)

  _remove = true;

  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      it->setNeedsRemove();
      ++it;
    }
  }
}

std::vector<Panel *> Layer::panels(Screen const &screen)
{
  __UNUSED__(screen)

  std::vector<Panel *> vec;

  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      vec.push_back(&(*it));
      ++it;
    }
  }

  return vec;
}

std::vector<Panel *> Layer::panelsOverlappingFrame(
    Screen const &screen, Frame const &frame)
{
  __UNUSED__(screen)

  std::vector<Panel *> vec;

  if (!_panel.empty()) {
    auto it = _panel.begin();
    while (it != _panel.end()) {
      if (it->frame()->overlaps(frame))
        { vec.push_back(&(*it)); }
      ++it;
    }
  }

  return vec;
}

// -------------------------------------------------------- private functions --

void Layer::clearPanels(Screen const &screen)
{
  __UNUSED__(screen)

  // this modifies the actual Panel list, which should not be performed at just
  // any time during the draw cycle -- only during times outside of the Layer
  // and Panel list painting iterations.
  if (!_panel.empty())
    { _panel.clear(); }
}

