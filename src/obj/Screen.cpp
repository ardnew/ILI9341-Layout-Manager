/*******************************************************************************
 *
 *  name: Screen.cpp
 *  date: Dec 24, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

// ----------------------------------------------------------------- includes --

#include "obj/Screen.h"

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ------------------------------------------------------------ private types --

/* nothing */

// ------------------------------------------------------- exported variables --

uint16_t const COORD_INVALID          = 0xFFFF;
uint16_t const DIMNS_INVALID          = 0xFFFF;
Pressure const PRESSURE_INVALID       = 0xFF;
Radius   const NO_RADIUS              = 0x00;

Point const POINT_INVALID(COORD_INVALID, COORD_INVALID);
Touch const NO_TOUCH(false);

uint8_t  const LAYER_INDEX_INVALID    = 0xFF;

// -------------------------------------------------------- private variables --

// default touchscreen calibration values used if none provided.
static TS_Point const CAL_A_SCR(   13,   11 );
static TS_Point const CAL_B_SCR(  312,  113 );
static TS_Point const CAL_C_SCR(  167,  214 );
static TS_Point const CAL_A_TCH( 3795, 3735 );
static TS_Point const CAL_B_TCH(  482, 2200 );
static TS_Point const CAL_C_TCH( 2084,  583 );

// ---------------------------------------------- private function prototypes --

/* nothing */

// ------------------------------------------------------- exported functions --

bool Screen::begin(void)
{
  if (!initDisplay())
    { return false; }

  if (!_calibration.defined) {
    // set default calibration values if none provided
    _calibration = TS_Calibration(
        CAL_A_SCR, CAL_A_TCH,
        CAL_B_SCR, CAL_B_TCH,
        CAL_C_SCR, CAL_C_TCH,
        _width, _height
    );
  }

  if (!initTouchScreen(_calibration))
    { return false; }

  return true;
}

void Screen::draw(void)
{
  if (!_layer.empty()) {

    Touch touch = touched();
    Layer *layer;

    // screen touch events. see class Frame for component event handlers.
    if (!_touch.isTouched() && touch.isTouched()) {
      if (nullptr != _touchBegin)
        { _touchBegin(*this, touch); }
      _touch = touch;
    }

    if (_refresh) {

      // if we are refreshing the screen, walk over the layers in forward
      // direction to draw lowest layer first, then subsequent layers on top.
      auto it = _layer.begin();
      while (it != _layer.end()) {
        layer = it;
        layer->draw(*this, touch);
        ++it;
      }
      _refresh = false;
    }
    else {

      // if we are not refreshing the screen, only redraw the top-most layer
      layer = &(_layer[_layerIndexTop]);
      layer->draw(*this, touch);
    }

    // screen touch events. see class Frame for component event handlers.
    if (_touch.isTouched() && !touch.isTouched()) {
      // use the last-read touch, since the current one is not touched
      if (nullptr != _touchEnd)
        { _touchEnd(*this, _touch); }
      _touch = touch;
    }
  }
}

void Screen::paintFrame(
    Point const &origin,
    Size const &size,
    Radius const radiusCorner,
    Color const color
) const
{
  tft()->startWrite();

  fillFrame(origin, size, radiusCorner, 0, color);

  tft()->endWrite();
}

void Screen::paintFrame(
    Point const &origin,
    Size const &size,
    Radius const radiusCorner,
    Color const color,
    Radius const radiusBorder,
    int8_t const marginBorder,
    Color const colorBorder
) const
{
  tft()->startWrite();

  uint16_t offset;
  if (marginBorder < 0) {
    offset = 0;
  }
  else {
    offset = marginBorder;
  }

  fillFrame(origin, size, radiusCorner, marginBorder, color);

  tft()->writeFastHLine(
      origin.x() + radiusBorder + offset,
      origin.y() + offset,
      size.width() - 2 * (radiusBorder + offset),
      colorBorder
  );
  tft()->writeFastHLine(
      origin.x() + radiusBorder + offset,
      origin.y() + size.height() - offset - 1,
      size.width() - 2 * (radiusBorder + offset),
      colorBorder
  );
  tft()->writeFastVLine(
      origin.x() + offset,
      origin.y() + radiusBorder + offset,
      size.height() - 2 * (radiusBorder + offset),
      colorBorder
  );
  tft()->writeFastVLine(
      origin.x() + size.width() - offset - 1,
      origin.y() + radiusBorder + offset,
      size.height() - 2 * (radiusBorder + offset),
      colorBorder
  );

  if (radiusBorder > 0) {
    drawQuarterCircle(
        origin.x() + radiusBorder + offset,
        origin.y() + radiusBorder + offset,
        radiusBorder, 1, colorBorder
    );
    drawQuarterCircle(
        origin.x() + size.width() - (radiusBorder + offset) - 1,
        origin.y() + radiusBorder + offset,
        radiusBorder, 2, colorBorder
    );
    drawQuarterCircle(
        origin.x() + size.width() - (radiusBorder + offset) - 1,
        origin.y() + size.height() - (radiusBorder + offset) - 1,
        radiusBorder, 4, colorBorder
    );
    drawQuarterCircle(
        origin.x() + radiusBorder + offset,
        origin.y() + size.height() - (radiusBorder + offset) - 1,
        radiusBorder, 8, colorBorder
    );
  }

  tft()->endWrite();
}

void Screen::paintText(
    Point const &center,
    GFXfont const *font,
    std::string const text,
    uint8_t const lineCount,
    uint16_t const lineSpacing,
    uint8_t const sizeText,
    Color const colorText
) const
{
  int16_t boundsX, boundsY;
  uint16_t blockWidth, blockHeight;
  uint16_t lineWidth, lineHeight;
  uint16_t textX, textY;

  tft()->setFont(font/* maybe NULL */);
  tft()->setTextSize(sizeText);
  tft()->setTextColor(colorText);

  tft()->getTextBounds(
      text.c_str(), 0, 0, &boundsX, &boundsY, &blockWidth, &blockHeight);

  float perLineHeight = (float)blockHeight / lineCount + 0.5F;

  uint16_t currLine = 0U;

  size_t start = 0;
  size_t end = text.find_first_of('\n');

  std::string line;

  while (end <= std::string::npos)
  {
    line = text.substr(start, end - start);

    tft()->getTextBounds(
        line.c_str(), 0, 0, &boundsX, &boundsY, &lineWidth, &lineHeight);

    textX = center.x() - (uint16_t)((float)lineWidth / 2.0F + 0.5F);
    textY = center.y() - (uint16_t)(
        (float)blockHeight / 2.0F + 0.5F + lineSpacing
      ) + currLine * (uint16_t)(perLineHeight + (lineSpacing / 2.0F + 0.5F));

    if (nullptr != font) {
      // "6" comes from Adafruit_GFX docs -- a fixed offset applied to Y coord
      // when calling setCursor() with a custom font
      textY += (6U / lineCount + (perLineHeight + lineSpacing) / 2.0F + 0.5F);
    }

    tft()->setCursor(textX, textY);
    tft()->print(line.c_str());

    ++currLine;

    if (end == std::string::npos)
      { break; }

    start = end + 1;
    end = text.find_first_of('\n', start);
  }
}

void Screen::setLayerIndexTop(uint8_t const index)
{
  if (index < _layerIndexTop) {

    // first, gather a list of all panels that will be removed (among all
    // layers above the new top layer) to determine which regions of the screen
    // that need to be repainted
    std::vector<Panel *> panelsRemoving;
    for (uint8_t i = index + 1; i < _MAX_LAYERS; ++i) {
      std::vector<Panel *> panels = _layer[i].panels(*this);
      // append this layer's panels to vector containing all layers' panels
      panelsRemoving.insert(
          std::end(panelsRemoving), std::begin(panels), std::end(panels));
      _layer[i].setNeedsRemove(*this);
    }

    // (DEBUG) color removed frames instead of removing them
    //Color colorRemoved = COLOR_PINK;
    Color colorRemoved = _color;

    if (!panelsRemoving.empty()) {
      // _refresh forces consideration of all layers for repaint on next draw
      // cycle (not just the top layer)
      _refresh = true;
      auto pRem = panelsRemoving.begin();
      while (pRem != panelsRemoving.end()) {
        // paint over the frames being removed
        paintFrame(
            (*pRem)->frame()->origin(),
            (*pRem)->frame()->size(),
            0U, colorRemoved, 0U, 0U, colorRemoved);
        updateOverlappingPanels(index, *pRem);
        ++pRem;
      }
    }
  }
  if (index < _MAX_LAYERS)
    { _layerIndexTop = index; }
}

uint8_t Screen::layerIndexAbove(uint8_t const index) const
{
  if (index < _layerIndexTop) {
    for (uint8_t i = index + 1; i <= _layerIndexTop; ++i) {
      if (_layer[i].panelCount() > 0U)
        { return i; }
    }
  }
  return LAYER_INDEX_INVALID;
}

uint8_t Screen::layerIndexBelow(uint8_t const index) const
{
  if (index > 0U) {
    // exit condition must check for underflow, since 0..TOP-1 are valid values
    for (uint8_t i = index - 1; i < _layerIndexTop; --i) {
      if (_layer[i].panelCount() > 0U)
        { return i; }
    }
  }
  return LAYER_INDEX_INVALID;
}

// -------------------------------------------------------- private functions --

bool Screen::initDisplay()
{
  _tft.begin();
  _tft.setRotation((uint8_t)_orientation);
  _tft.fillScreen((uint16_t)_color);
  _tft.setTextWrap(false);
  return true;
}

bool Screen::initTouchScreen(TS_Calibration const &cal)
{
  _ts.begin();
  _ts.setRotation((uint8_t)_orientation);
  _ts.calibrate(cal);
  return true;
}

Touch Screen::touched()
{
  uint16_t x, y;
  uint8_t z;

  if (_ts.tirqTouched()) {
    if (_ts.touched()) {
      _ts.readData(&x, &y, &z);
      return Touch(true, Point(x, y), (Pressure)z);
    }
  }
  return NO_TOUCH;
}

void Screen::updateOverlappingPanels(
    uint8_t const layerIndexTop, Panel * const panel
)
{
  if (nullptr != panel) {
    panel->setNeedsUpdate();
    for (uint8_t i = 0; i <= layerIndexTop; ++i) {
      std::vector<Panel *> overlapping =
          _layer[i].panelsOverlappingFrame(*this, *(panel->frame()));
      if (!overlapping.empty()) {
        auto pit = overlapping.begin();
        while (pit != overlapping.end()) {
          if (!(*pit)->needsUpdate())
            { updateOverlappingPanels(layerIndexTop, *pit); }
          ++pit;
        }
      }
    }
  }
}

void Screen::fillFrame(
    Point const &origin,
    Size const &size,
    Radius const radiusCorner,
    int8_t const margin,
    Color const color
) const
{
  uint16_t offset = 0U;
  if (margin < 0)
    { offset = abs(margin); }

  tft()->writeFillRect(
      origin.x() + radiusCorner + offset,
      origin.y() + offset,
      size.width() - 2 * (radiusCorner + offset),
      size.height() - 2 * offset,
      color
  );

  if (radiusCorner > 0) {

    fillQuarterCircle(
        origin.x() + size.width() - (radiusCorner + offset) - 1,
        origin.y() + radiusCorner + offset,
        radiusCorner,
        1,
        size.height() - 2 * (radiusCorner + offset) - 1,
        color
    );
    fillQuarterCircle(
        origin.x() + radiusCorner + offset,
        origin.y() + radiusCorner + offset,
        radiusCorner,
        2,
        size.height() - 2 * (radiusCorner + offset) - 1,
        color
    );

  }
}

void Screen::drawQuarterCircle(
    int16_t const x0, int16_t const y0, int16_t const r,
    uint8_t const corner, uint16_t const color
) const
{
  int16_t f  = 1 - r;
  int16_t fx = 1;
  int16_t fy = -2 * r;
  int16_t x  = 0;
  int16_t y  = r;

  while (x < y) {

    if (f >= 0) {
      --y;
      fy += 2;
      f  += fy;
    }
    ++x;
    fx += 2;
    f  += fx;

    if (corner & 0x4) {
      tft()->writePixel(x0 + x, y0 + y, color);
      tft()->writePixel(x0 + y, y0 + x, color);
    }
    if (corner & 0x2) {
      tft()->writePixel(x0 + x, y0 - y, color);
      tft()->writePixel(x0 + y, y0 - x, color);
    }
    if (corner & 0x8) {
      tft()->writePixel(x0 - y, y0 + x, color);
      tft()->writePixel(x0 - x, y0 + y, color);
    }
    if (corner & 0x1) {
      tft()->writePixel(x0 - y, y0 - x, color);
      tft()->writePixel(x0 - x, y0 - y, color);
    }
  }
}

void Screen::fillQuarterCircle(
    int16_t const x0, int16_t const y0, int16_t const r,
    uint8_t const corner, int16_t const delta, uint16_t const color
) const
{
  int16_t f  =  1 - r;
  int16_t d  = delta + 1;
  int16_t fx = 1;
  int16_t fy = -2 * r;
  int16_t x  = 0;
  int16_t y  = r;
  int16_t px = x;
  int16_t py = y;

  while (x < y) {

    if (f >= 0) {
      --y;
      fy += 2;
      f  += fy;
    }
    ++x;
    fx += 2;
    f  += fx;

    if (x < (y + 1)) {
      if (corner & 1)
        { tft()->writeFastVLine(x0 + x, y0 - y, 2 * y + d, color); }
      if (corner & 2)
        { tft()->writeFastVLine(x0 - x, y0 - y, 2 * y + d, color); }
    }
    if (y != py) {
      if (corner & 1)
        { tft()->writeFastVLine(x0 + py, y0 - px, 2 * px + d, color); }
      if (corner & 2)
        { tft()->writeFastVLine(x0 - py, y0 - px, 2 * px + d, color); }
      py = y;
    }

    px = x;
  }
}
