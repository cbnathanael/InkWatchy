#pragma once

#include "defines.h"

#if GADGETBRIDGE_ENABLED


void gadgetbridgeInit();
void notify(JsonDocument doc);
bool gadgetbridgeNoSleep();
void initGBNotificationDisp();
void loopGBNotificationDisp();
void exitGBNotificationDisp();
#endif