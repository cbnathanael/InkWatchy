#pragma once

#include "defines.h"

#if GADGETBRIDGE_MODULE

void wfGbridgeCheckShow(bool *showBool, bool *redrawBool);
void wfGbridgeRequestShow(buttonState button, bool *showBool);

#endif
