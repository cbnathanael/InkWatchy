#include "gadgetbridgeMod.h"
#include "rtcMem.h"
#if GADGETBRIDGE_MODULE

void wfGbridgeCheckShow(bool *showBool, bool *redrawBool)
{
    // force for now, need to find proper logic
    *showBool = true;
    *redrawBool = true;
    // wifiStatusSimple wss = wifiStatusWrap();
    // if (wss != previousWifiState)
    // {
    //     debugLog("Wifi module should be shown and redrawn");
    //     previousWifiState = wss;
    //     *showBool = true;
    //     *redrawBool = true;
    // }
}

void wfGbridgeRequestShow(buttonState button, bool *showBool)
{
    
    squareInfo modSq = getWatchModuleSquare();
    modSq.cord.x = modSq.cord.x + 1;
    modSq.cord.y = modSq.cord.y + 1;
    dis->setCursor(modSq.cord.x, modSq.cord.y + 5);
    setFont(getFont("dogicapixel4"));
    setTextSize(1);
    dis->print("gbNotifications");
    Notification* latest = getLatest();
    if(latest != nullptr){
        dis->setCursor(modSq.cord.x, modSq.cord.y + 10);
        dis->print(latest->src);
        dis->setCursor(modSq.cord.x, modSq.cord.y + 20);
        dis->print(latest->title);
    }
    // if(gbNotifications.size() > 0) {
    //     gadgetbridgeNotification* n = gbNotifications.get(0);
    //     dis->print(n->title);
    // } else {
    //     dis->print("No gbNotifications");
    // }
    // if (button == Menu)
    // {
    //     *showBool = false;
    //     return;
    // }
    // debugLog("Launched");
    // squareInfo modSq = getWatchModuleSquare();
    // modSq.cord.x = modSq.cord.x + 1;
    // modSq.cord.y = modSq.cord.y + 1;
    // if (previousWifiState == WifiOff)
    // {
    //     writeImageN(modSq.cord.x, modSq.cord.y, getImg("wifiOff"));
    // }
    // else if (previousWifiState == WifiOn)
    // {
    //     writeImageN(modSq.cord.x, modSq.cord.y, getImg("wifiOn"));
    // }
    // else if (previousWifiState == WifiConnected)
    // {
    //     writeImageN(modSq.cord.x, modSq.cord.y, getImg("wifiConnected"));
    //     dis->setCursor(modSq.cord.x, modSq.cord.y + 25);
    //     setFont(getFont("dogicapixel4"));
    //     setTextSize(1);
    //     dis->print(WiFi.SSID());
    // }
    dUChange = true;
}

#endif