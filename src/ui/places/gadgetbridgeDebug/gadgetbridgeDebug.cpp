#include "rtcMem.h"
#include "gadgetbridgeDebug.h"

int bleStatusLine;
int bleBondLine;
int blePasskeyLine;
int bleMacAddressLine;
int bleConnectedLine;

String blePreviousConnected;
int blePreviousBond;
int blePreviousPasskey;

void gbOnBtn()
{
    enableBonding();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

void gbRemoveBond()
{
    removeBondedDevices();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

void initGBDebugDisplay()
{
    init_general_page(6);
    general_page_set_title("Debug Menu: Gadgetbridge");
    genpage_set_center();

    GeneralPageButton button[] = {GeneralPageButton{"Enable Bonding", gbOnBtn}, GeneralPageButton{"Remove Bonded Devices", removeBondedDevices}};
    general_page_set_buttons(button, 2);

    genpage_add("MAC Address:");

    bleMacAddressLine = genpage_add(BLEDevice::getAddress().toString().c_str());

    genpage_add("Bonded Device Count: ");
    blePreviousBond = esp_ble_get_bond_device_num();
    bleBondLine = genpage_add(String(blePreviousBond).c_str());

    blePreviousConnected = BOOL_STR(bleClientConnected);
    genpage_add("Client Connected: ");
    bleConnectedLine - genpage_add(blePreviousConnected.c_str());

    genpage_add("PASS KEY: ");
    blePreviousPasskey = rM.ble_passkey;
    blePasskeyLine = genpage_add(String(blePreviousPasskey).c_str());

    general_page_set_main();
}

void loopGBDebugDisplay()
{
    if (genpage_is_menu() == false)
    {
        int bondNow = esp_ble_get_bond_device_num();
        if(blePreviousBond != bondNow) {
            blePreviousBond = bondNow;
            genpage_change(String(bondNow).c_str(), bleBondLine);
        }

        String bleConnNow = BOOL_STR(bleClientConnected);
        if(blePreviousConnected != bleConnNow) {
            blePreviousConnected = bleConnNow;
            genpage_change(bleConnNow.c_str(), bleConnectedLine);
        }

        int passkeyNow = rM.ble_passkey;
        if(blePreviousPasskey != passkeyNow) {
            blePreviousPasskey = passkeyNow;
            genpage_change(String(passkeyNow).c_str(), blePasskeyLine);
        }
    }

    // Never exit this if waiting on pairing
    if (rM.ble_passkey != 0)    {
        resetSleepDelay();
    }

    general_page_set_main();
    slint_loop();
}
