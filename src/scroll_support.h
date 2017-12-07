#ifndef __SCROLL_SUPPORT__
#define __SCROLL_SUPPORT__

#include <Arduino.h>


typedef enum {
  TopToBottom,
  BottomToTop,
  LeftToRight,
  RightToLeft
} readingDirection_t;


class ScrollSupport
{
 public:
  static ScrollSupport *makeFor(readingDirection_t dir, String message);
  ScrollSupport(String aMessage);
  virtual int16_t initialX() = 0;
  virtual int16_t initialY(int8_t h) = 0;
  virtual boolean isFinished(int16_t x, int16_t y) = 0;
  virtual int16_t nextX(int16_t x) = 0;
  virtual int16_t nextY(int16_t y) = 0;
  virtual int16_t nextCharacterX(int16_t x, int8_t advance) = 0;
  virtual int16_t nextCharacterY(int16_t y, int8_t advance) = 0;
  virtual int8_t selectAdvance(int8_t horizontal, int8_t vertical) = 0;

 protected:
	
  String message;
};

class ScrollLeft : public ScrollSupport
{
 public:
  ScrollLeft(String message);
  int16_t initialX() { return 12; }
  int16_t initialY(int8_t h) { return 6 + (h / 2); }
  boolean isFinished(int16_t x, int16_t y) { return x <= (((int)message.length() - 1) * -12); }
  int16_t nextX(int16_t x) { return x - 1; }
  int16_t nextY(int16_t y) { return y; }
  int16_t nextCharacterX(int16_t x, int8_t advance) { return x + (int16_t)advance; }
  int16_t nextCharacterY(int16_t y, int8_t advance) { return y; }
  int8_t selectAdvance(int8_t horizontal, int8_t vertical) { return horizontal; }
};

/* class ScrollRight : public ScrollSupport */

/* }; */

class ScrollUp : public ScrollSupport
{
 public:
  ScrollUp(String message);
  int16_t initialX() { return 0; }
  int16_t initialY(int8_t h) { return 12 + h; }
  boolean isFinished(int16_t x, int16_t y) { return y <= (((int)message.length() - 1) * -12); }
  int16_t nextX(int16_t x) { return x; }
  int16_t nextY(int16_t y) { return y - 1; }
  int16_t nextCharacterX(int16_t x, int8_t advance) { return x; }
  int16_t nextCharacterY(int16_t y, int8_t advance) { return y + (int16_t)advance; }
  int8_t selectAdvance(int8_t horizontal, int8_t vertical) { return vertical; }
};

/* class ScrollDown : public ScrollSupport */
/* { */
/* }; */

#endif
