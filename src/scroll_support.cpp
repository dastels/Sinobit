#include "scroll_support.h"

ScrollSupport::ScrollSupport(String aMessage)
{
  message = aMessage;
}


ScrollLeft::ScrollLeft(String aMessage) : ScrollSupport(aMessage)
{
}


ScrollUp::ScrollUp(String aMessage) : ScrollSupport(aMessage)
{
}

