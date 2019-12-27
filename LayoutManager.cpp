/*******************************************************************************
 *
 *  name: LayoutManager.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "LayoutManager.h"
#include "Layer.h"
#include "Panel.h"

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

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color, Color const colorTouched)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color, colorTouched
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color,
    Radius const radiusBorder,
    Color const colorBorder)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color,
        radiusBorder,
        colorBorder
    )));
  }
  return nullptr;
}

Panel *LayoutManager::addPanel(
    uint8_t const layerIndex,
    uint16_t const x, uint16_t const y,
    uint16_t const width, uint16_t const height,
    Radius const radiusCorner,
    Color const color, Color const colorTouched,
    Radius const radiusBorder,
    Color const colorBorder, Color const colorBorderTouched)
{
  Layer *layer = _screen.layer(layerIndex);
  if (layerIndex > _screen.layerIndexTop())
    { _screen.setLayerIndexTop(layerIndex); }
  if (nullptr != layer) {
    return layer->addPanel(Panel(Frame(
        layerIndex,
        Point(x, y),
        Size(width, height),
        radiusCorner,
        color, colorTouched,
        radiusBorder,
        colorBorder, colorBorderTouched
    )));
  }
  return nullptr;
}

void LayoutManager::removeTopLayer()
{
  uint8_t indexTop = _screen.layerIndexTop();
  if (indexTop > 0U) {
    _screen.setLayerIndexTop(indexTop - 1U);
  }
}

// -------------------------------------------------------- private functions --

