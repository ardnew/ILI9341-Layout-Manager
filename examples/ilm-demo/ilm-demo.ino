/*******************************************************************************
 *
 *  name: ilm-demo.ino
 *  date: Dec 13, 2019
 *  auth: andrew
 *  desc:
 *
 ******************************************************************************/

#include <LayoutManager.h>

// ------------------------------------------------------------ configuration --

//
// ** IMPORTANT ** README **
// 
// for the touchscreen calibration to work as best as possible, you need to
// either (a) use the LayoutManager constructor that accepts the additional 6
// Point objects required to construct a TS_Calibration object, or (b) update
// the 6 calibration parameters defined in obj/Screen.cpp. you can try sticking
// with the same values I have defined there, but you *may* have issues with
// touch coordinates being a little off.
//
// to obtain these 6 calibration parameters, see the example sketch named
// TouchCalibration.ino provided with the XPT2046_Calibrated library. it walks
// you through the simple steps necessary to calibrate your touch screen.
//

#define WAIT_FOR_SERIAL

//#define GRAND_CENTRAL_M4
#define ITSY_BITSY_M4

// TFT Touchscreen GPIO pin definitions
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
#define TFT_CS_PIN         10 // 16 // A2
#define TFT_RST_PIN    /* 3v3 */
#define TFT_DC_PIN         17 // A3
#define TFT_MOSI_PIN       25
#define TFT_SCK_PIN        24
#define TFT_LED_PIN    /* 3v3 */
#define TFT_MISO_PIN       23
#define TOUCH_CLK_PIN      24
#define TOUCH_CS_PIN        2
#define TOUCH_MOSI_PIN     25
#define TOUCH_MISO_PIN     23
#define TOUCH_IRQ_PIN       7
#endif

#define EXPAND(x) x ## 1
#define DEFINED_VAL(x) 1 != EXPAND(x)

// -------------------------------------------------------- screen components --

LayoutManager *man;

Panel *p1;
Field *p1f1;
Field *p1f2;

Panel *p2;
Field *p2f1;
Field *p2f2;
Field *p2f3;

Panel *p3;
Field *p3f1;
Field *p3f2;

Panel *popup;
Field *popupText;

Panel *popupSubpanel;
Field *popupButton;

void p1_press(Frame const &f, Touch const &t);
void p2_press(Frame const &f, Touch const &t);
void p1f1_begin(Frame const &f, Touch const &t);
void p1f1_end(Frame const &f, Touch const &t);
void p1f1_press(Frame const &f, Touch const &t);
void screenTouchEnd(Screen const &s, Touch const &t);
void popupButton_press(Frame const &f, Touch const &t);

// -------------------------------------------------------- arduino functions --

void initGPIO(void);
void initPeripherals(void);

void setup()
{
  initGPIO();
  initPeripherals();

  // initialize the screen with all currently defined components
  if (!man->begin()) {
    Serial.println("failed to start!");
  }
  else {
    Serial.println("all good");
  }
}

void loop()
{
  static uint32_t time = 0;
  static uint32_t curr;
  static char buf[32];

  curr = millis();
  if (curr - time > 500)  {
    uint16_t val1 = curr % 1000;
    uint16_t val2 = time % 500;
    if (val1 > 500) {
      sprintf(buf, "%u", val1);
    }
    else {
      sprintf(buf, "%u\n%u", val1, val2);
    }
    p1f2->setText(buf);
    time = curr;
  }

  // call once per iteration to effeciently update screen content and invoke
  // any user-defined callbacks for requested events
  man->draw();
}

// -------------------------------------------------------- private functions --

void initGPIO(void)
{
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

  // ---- MANAGER OBJECT ----

  // primary object containing and organizing all components
  man = new LayoutManager(
      // TFT
      TFT_CS_PIN, TFT_DC_PIN,
      // Touchscreen
      TOUCH_CS_PIN, TOUCH_IRQ_PIN,
      // Both
      320, 240, Orientation::Landscape, COLOR_BLACK);
  man->setTouchEnd(screenTouchEnd);

  Serial.printf("ILI9341-Layout-Manager v%s\r\n", man->version());

  // ---- PANEL 1 ----

  Serial.printf("creating panel (%u)\r\n", 1);

  // add one panel to the first layer
  p1 = man->addPanel(
      0,          // layer 0 (bottom-most)
      10,   20,   // origin, top-left (x,y) point
      120,  120,  // size, width and height
      6,          // radius of rounded corners of panel, 0 for none (square)
      COLOR_BLACK, COLOR_GREEN, // panel color, touched color
      6,          // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_GREEN, COLOR_GREEN  // border color, touched color
  );

  p1->setAxis(LayoutAxis::Vertical);
  p1->setMargin(8);
  p1->setPadding(8);

  // set some callbacks
  p1->setTouchPress(p1_press);

  // ---- PANEL 1 FIELDS ----

  p1f1 = man->addField(
      p1,     // parent panel
      "BIG", // field text
      3,      // text size
      COLOR_BLACK, COLOR_ORANGE, // text color, touched color
      3,      // radius of rounded corners of panel, 0 for none (square)
      COLOR_ORANGE, COLOR_BLACK, // panel color, touched color
      3,      // rounded corner radius of border, as above
      0,      // border margin, <0 outside panel, >0 inside panel
      COLOR_ORANGE, COLOR_ORANGE  // border color, touched color
  );
  p1f2 = man->addField(
      p1,     // parent panel
      "--",   // field text, changed dynamically in loop()
      2,      // text size
      COLOR_WHITE, COLOR_GREEN, // text color, touched color
      6,      // radius of rounded corners of panel, 0 for none (square)
      COLOR_BLACK, COLOR_BLACK  // panel color, touched color
  );

  p1f1->setTouchBegin(p1f1_begin);
  p1f1->setTouchEnd(p1f1_end);
  p1f1->setTouchPress(p1f1_press);

  // ---- PANEL 2 ----

  Serial.printf("creating panel (%u)\r\n", 2);

  p2 = man->addPanel(
      0,           // layer
      20,  160,    // origin, top-left (x,y) point
      220,  60,    // size, width and height
      0,           // radius of rounded corners of panel, 0 for none (square)
      COLOR_BLACK, // panel color
      0,           // rounded corner radius of border, as above
      0,           // border margin, <0 outside panel, >0 inside panel
      COLOR_RED    // border color
  );

  p2->setAxis(LayoutAxis::Horizontal);
  p2->setMargin(6) ;
  p2->setPadding(4) ;

  // set some callbacks
  p2->setTouchPress(p2_press);

  // ---- PANEL 2 FIELDS ----

  p2f1 = man->addField(
      p2,      // parent panel
      "small", // field text
      1,       // text size
      COLOR_BLACK, COLOR_RED, // text color, touched color
      8,       // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_BLACK  // panel color, touched color
  );
  p2f2 = man->addField(
      p2,     // parent panel
      "buttons", // field text
      1,      // text size
      COLOR_BLACK, COLOR_RED, // text color, touched color
      8,      // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_BLACK, // panel color, touched color
      8,      // rounded corner radius of border, as above
      -4,     // border margin, <0 outside panel, >0 inside panel
      COLOR_ORANGE, COLOR_ORANGE  // border color, touched color
  );
  p2f3 = man->addField(
      p2,     // parent panel
      "here", // field text
      2,      // text size
      COLOR_BLACK, COLOR_RED, // text color, touched color
      2,      // radius of rounded corners of panel, 0 for none (square)
      COLOR_RED, COLOR_BLACK,   // panel color, touched color
      2,      // rounded corner radius of border, as above
      4,      // border margin, <0 outside panel, >0 inside panel
      COLOR_RED, COLOR_RED  // border color, touched color
  );

  // ---- PANEL 3 ----

  Serial.printf("creating panel (%u)\r\n", 3);

  // add one panel to the first layer
  p3 = man->addPanel(
      0,          // layer 0 (bottom-most)
      140,  10,   // origin, top-left (x,y) point
      100,  140,  // size, width and height
      2,          // radius of rounded corners of panel, 0 for none (square)
      COLOR_NAVY, // panel color
      2,          // rounded corner radius of border, as above
      0,          // border margin, <0 outside panel, >0 inside panel
      COLOR_CYAN  // border color
  );

  p3->setAxis(LayoutAxis::Vertical);
  p3->setMargin(8);
  p3->setPadding(0);
  p3->setProportional(true);

  // set some callbacks
  p3->setTouchPress(p1_press);

  // ---- PANEL 3 FIELDS ----

  p3f1 = man->addField(
      p3,           // parent panel
      "Two\nLines", // field text
      2,            // text size
      COLOR_CYAN,   // text color, touched color
      6,            // radius of rounded corners of panel, 0 for none (square)
      COLOR_NAVY    // panel color, touched color
  );
  p3f2 = man->addField(
      p3,     // parent panel
      "Button", // field text
      2,      // text size
      COLOR_CYAN, COLOR_NAVY, // text color, touched color
      6,      // radius of rounded corners of panel, 0 for none (square)
      COLOR_NAVY, COLOR_CYAN, // panel color, touched color
      6,      // rounded corner radius of border, as above
      0,      // border margin, <0 outside panel, >0 inside panel
      COLOR_CYAN, COLOR_NAVY  // border color, touched color
  );
}

void p1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1_press {%u,%u}\r\n", t.x(), t.y());
}

void p2_press(Frame const &f, Touch const &t)
{
  Serial.printf("p2_press {%u,%u}\r\n", t.x(), t.y());
}

void p1f1_begin(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_begin: {%u,%u}\r\n", t.x(), t.y());
}

void p1f1_end(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_end: {%u,%u}\r\n", t.x(), t.y());
}

void p1f1_press(Frame const &f, Touch const &t)
{
  Serial.printf("p1f1_press: {%u,%u}\r\n", t.x(), t.y());

  Serial.printf("p1f1_press: {%u,%u}: adding new layer\r\n", t.x(), t.y());

  popup = man->addPanel(
      1,
      50, 40,
      220, 110,
      8,
      COLOR_WHITE,
      8,
      0,
      COLOR_WHITE
  );
  popup->setMargin(8);
  popup->setPadding(0);

  popupText = man->addField(
      popup,
      "Choose your fate\n \n \n \n",
      2,
      COLOR_PURPLE,
      0,
      COLOR_WHITE
  );

  popupSubpanel = man->addPanel(
      1,
      120, 100,
      80,  40,
      4,
      COLOR_WHITE,
      0,
      0,
      COLOR_WHITE
  );

  popupButton = man->addField(
      popupSubpanel,
      "OK!",
      2,
      COLOR_YELLOW, COLOR_PURPLE,
      8,
      COLOR_PURPLE, COLOR_YELLOW,
      8,
      0,
      COLOR_YELLOW, COLOR_PURPLE
  );

  popupButton->setTouchPress(popupButton_press);
}

void screenTouchEnd(Screen const &s, Touch const &t)
{
  Serial.printf("screen: ({%u,%u}, %u)\r\n", t.x(), t.y(), t.pressure());
}

void popupButton_press(Frame const &f, Touch const &t)
{
  Serial.printf("popupButton_press: {%u,%u}: removing top layer\r\n", t.x(), t.y());

  man->layerRemoveTop();
}
