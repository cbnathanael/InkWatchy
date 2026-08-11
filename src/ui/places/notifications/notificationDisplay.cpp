#include "notifications.h"
#include "rtcMem.h"

#if NOTIFICATIONS
uint32_t notDisplayMilStart = 0;
uint32_t notDisplayMotorLast = 0;
uint8_t notDisplayVibeCount = 0;
Notification *n;

void initNotificationDisplay()
{
  n = getLatest();
  checkIfButtonIsRunning();
  notDisplayMilStart = millisBetter();
  notDisplayMotorLast = 0;
  notDisplayVibeCount = 0;
  dis->fillRect(0, 0, 200, 200, SCWhite);
  //dis->fillRect(3, 3, 194, 194, SCWhite);
  setFont(getFont("UbuntuMono10"));
  dis->setTextWrap(true);
  String message = String(n->src)+"\r\n"+String(n->title)+"\r\n"+String(n->body);
  dis->setCursor(8, 20);
  dis->print(message);
  // dis->setCursor(8, 34);
  // dis->print("From: " + String(n->title));
  // dis->setTextWrap(true);
  // dis->setCursor(8, 48);
  // dis->print(String(n->body));
  dUChange = true;
}

void loopNotificationDisplay()
{
  if ((millisBetter() - notDisplayMotorLast) > GADGETBRIDGE_VIBRATE_DELAY && notDisplayVibeCount < GADGETBRIDGE_VIBRATE_COUNT)
  {
    notDisplayMotorLast = millisBetter();
    vibrateMotor(GADGETBRIDGE_VIBRATE_TIME);
    notDisplayVibeCount++;
  }
  buttonState btn = useButton();
  int timeDisplayed = (millisBetter() - notDisplayMilStart) / 1000;
  debugLog("timeDisplayed: " + String(timeDisplayed));
 
  if (timeDisplayed > 15 || btn != None)
  {
    debugLog("NOTIFICATION canceled!");
    switchBack();
  }
  disUp();
  resetSleepDelay();
}

void exitNotificationDisplay()
{
    useButtonBlank();                             // Cancel any buttons
    sleepDelayMs = sleepDelayMs - SLEEP_EVERY_MS; // Requesting sleep
}
#endif