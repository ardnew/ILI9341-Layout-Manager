/*******************************************************************************
 *
 *  name: ilm-demo.ino
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#include <stdarg.h>

#include <LayoutManager.h>

//#define WAIT_FOR_SERIAL

#define GRAND_CENTRAL_M4
//#define ITSY_BITSY_M4
//#define TEENSY_4_0

//
// TFT Touchscreen GPIO pin definitions
//
#if defined(GRAND_CENTRAL_M4)
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN          7
#define TFT_RST_PIN    /* 3v3 */
#define TFT_DC_PIN          5
#define TFT_MOSI_PIN       51
#define TFT_SCK_PIN        52
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       50
#define TOUCH_CLK_PIN      52
#define TOUCH_CS_PIN        4
#define TOUCH_MOSI_PIN     51
#define TOUCH_MISO_PIN     50
#define TOUCH_IRQ_PIN       3
#elif defined(ITSY_BITSY_M4)
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN          7
#define TFT_RST_PIN        13
#define TFT_DC_PIN         12
#define TFT_MOSI_PIN       25
#define TFT_SCK_PIN        24
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       23
#define TOUCH_CLK_PIN      24
#define TOUCH_CS_PIN       11
#define TOUCH_MOSI_PIN     25
#define TOUCH_MISO_PIN     23
#define TOUCH_IRQ_PIN       9
#elif defined(TEENSY_4_0)
#define TFT_VCC_PIN    /* 3v3 */
#define TFT_GND_PIN    /* GND */
#define TFT_CS_PIN         21
#define TFT_RST_PIN    /* 3v3 */
#define TFT_DC_PIN         15
#define TFT_MOSI_PIN       11
#define TFT_SCK_PIN        13
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       12
#define TOUCH_CLK_PIN      13
#define TOUCH_CS_PIN        9
#define TOUCH_MOSI_PIN     11
#define TOUCH_MISO_PIN     12
#define TOUCH_IRQ_PIN      22

extern "C"{
  int __exidx_start(){ return -1;}
  int __exidx_end(){ return -1; }
}

#endif

#define EXPAND(x) x ## 1
#define DEFINED_VAL(x) 1 != EXPAND(x)

LayoutManager *man = nullptr;
Panel *p1 = nullptr;
Field *p1f1 = nullptr;
Field *p1f2 = nullptr;
Panel *p2 = nullptr;

enum class InfoLevel {
  NONE = -1,
  Info,  // = 0
  Warn,  // = 1
  Error, // = 2
  COUNT  // = 3
};

void info(InfoLevel level, char const *fmt, ...);
void initGPIO(void);
void initPeripherals(void);

void p1_press(Frame const &f, Touch const &t);
void p2_press(Frame const &f, Touch const &t);

void p1f1_begin(Frame const &f, Touch const &t);
void p1f1_end(Frame const &f, Touch const &t);
void p1f1_press(Frame const &f, Touch const &t);

void screenTouchBegin(Screen const &s, Touch const &t);
void screenTouchEnd(Screen const &s, Touch const &t);

void setup()
{
  initGPIO();
  initPeripherals();

  // initialize the screen with all currently defined components
  if (!man->begin()) {
    info(InfoLevel::Error, "failed to start!");
  }
  else {
    info(InfoLevel::Info, "all ok :)");
  }
}

void loop()
{
  static uint16_t time = 0U;
  static uint16_t curr;
  static char buf[32];

  curr = millis();
  if (curr - time > 500U) {
    uint16_t val = curr % 1000U;
    //if (val > 500) {
    //  snprintf(buf, 32, "%u", val);
    //}
    //else {
      snprintf(buf, 32, "%u\n%u", val, val);
    //}
    //snprintf(buf, 32, "%u", val);
    p1f1->setText(buf);
    time = curr;
  }

  // call once per iteration to effeciently update screen content and invoke
  // any user-defined callbacks for requested events
  man->draw();
}

// -------------------------------------------------------- private functions --

static uint16_t const INFO_LENGTH_MAX = 4096;
static char buff[INFO_LENGTH_MAX] = { 0U };

void info(InfoLevel level, char const *fmt, ...)
{
  static char const * const DEBUG_LEVEL_PREFIX[(uint8_t)InfoLevel::COUNT] = {
    "[ ]", "[*]", "[!]"
  };

  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buff, INFO_LENGTH_MAX, fmt, arg);
  va_end(arg);

  Serial.printf("%s %s\r\n", DEBUG_LEVEL_PREFIX[(uint8_t)level], buff);
}

void initGPIO(void)
{

  pinMode(TFT_CS_PIN, OUTPUT);
  pinMode(TFT_DC_PIN, OUTPUT);
  pinMode(TFT_MOSI_PIN, OUTPUT);
  pinMode(TFT_SCK_PIN, OUTPUT);
  pinMode(TFT_MISO_PIN, INPUT);
  pinMode(TOUCH_CLK_PIN, OUTPUT);
  pinMode(TOUCH_CS_PIN, OUTPUT);
  pinMode(TOUCH_MOSI_PIN, OUTPUT);
  pinMode(TOUCH_MISO_PIN, INPUT);
  pinMode(TOUCH_IRQ_PIN, INPUT);

#if DEFINED_VAL(TFT_RST_PIN)
  // TFT reset is active low, i'm choosing to keep it high with a digital pin
  // instead of a fixed pullup so that we can actually reset it if needed.
  pinMode(TFT_RST_PIN, OUTPUT);
  digitalWrite(TFT_RST_PIN, LOW);
  delay(100);
  digitalWrite(TFT_RST_PIN, HIGH);
#endif

}

void initPeripherals(void)
{

#ifdef WAIT_FOR_SERIAL
  while (!Serial) { continue; }
#else
  while (!Serial && millis() < 1000) { continue; }
#endif
  Serial.begin(115200);

  info(InfoLevel::Info, "creating panels (%u)", 2);

  // primary object containing and organizing all components
  man = new LayoutManager(
      // TFT
      TFT_CS_PIN, TFT_DC_PIN,
      // Touchscreen
      TOUCH_CS_PIN, TOUCH_IRQ_PIN,
      // Both
      320, 240, Orientation::Landscape, COLOR_BLACK);
  man->setTouchBegin(screenTouchBegin);
  man->setTouchEnd(screenTouchEnd);

  // add one panel to the first layer
  p1 = man->addPanel(
      0U,        // layer 0 (bottom-most)
      20U,  20U, // origin, top-left (x,y) point
     120U, 120U, // size, width and height
      6U,        // radius of rounded corners of panel, 0 for none (square)
      COLOR_BLACK,// COLOR_GREEN, // panel color, touched color
      6U,        // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_YELLOW//, COLOR_RED  // border color, touched color
   );
  // set some callbacks
  p1->setTouchPress(p1_press);

  p1->setAxis(LayoutAxis::Vertical);
  p1->setMargin(6U);
  p1->setPadding(4U);
  p1f1 = man->addField(p1, "p1f1", 1U, COLOR_WHITE, COLOR_NAVY, 6U, COLOR_NAVY, COLOR_WHITE);
  p1f2 = man->addField(p1, "p1f2", 1U, COLOR_NAVY, COLOR_ORANGE, 6U, COLOR_ORANGE, COLOR_NAVY);

  p1f1->setTouchBegin(p1f1_begin);
  p1f1->setTouchEnd(p1f1_end);
  p1f1->setTouchPress(p1f1_press);

  p2 = man->addPanel(
      0U,        // layer
     160U,  20U, // origin, top-left (x,y) point
      80U,  40U, // size, width and height
      8U,        // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_YELLOW, // panel color, touched color
      8U,        // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_GREEN, COLOR_BLUE  // border color, touched color
   );
  // set some callbacks
  p2->setTouchPress(p2_press);
}

void p1_press(Frame const &f, Touch const &t)
{
  info(InfoLevel::Info, "p1_press {%u,%u}", t.x(), t.y());
}

void p2_press(Frame const &f, Touch const &t)
{
  info(InfoLevel::Info, "p2_press {%u,%u}", t.x(), t.y());
}

void p1f1_begin(Frame const &f, Touch const &t)
{
  info(InfoLevel::Info, "p1f1_begin: {%u,%u}", t.x(), t.y());
}

void p1f1_end(Frame const &f, Touch const &t)
{
  info(InfoLevel::Info, "p1f1_end: {%u,%u}", t.x(), t.y());
}

void p1f1_press(Frame const &f, Touch const &t)
{
  info(InfoLevel::Info, "p1f1_press: {%u,%u}", t.x(), t.y());
}

void screenTouchBegin(Screen const &s, Touch const &t)
{
  info(InfoLevel::Info, "BEG({%u,%u}, %u)", t.x(), t.y(), t.pressure());
}

void screenTouchEnd(Screen const &s, Touch const &t)
{
  info(InfoLevel::Info, "END({%u,%u}, %u)", t.x(), t.y(), t.pressure());

  if (t.x() > 280) {
    uint8_t index = man->layerIndexTop() + 1U;
    // add a panel to a new layer
    man->addPanel(
        index,
        20U + index * 20,
        20U + index * 10,  // origin, top-left (x,y) point
        75U, 20U,  // size, width and height
        0U,        // radius of rounded corners of panel, 0 for none (square)
        COLOR_WHITE, COLOR_PURPLE, // panel color, touched color
        0U,        // rounded corner radius of border, as above
        0,         // border margin, <0 outside panel, >0 inside panel
        COLOR_PURPLE, COLOR_WHITE  // border color, touched color
    );
  }
  else {
    // remove the top-most layer
    man->layerRemoveTop();
  }
}
