#include "notifications.h"
#include "rtcMem.h"

#if NOTIFICATIONS
#define MAX_NOTIF 10

Notification *notificationsList[10];
static int listHead = 0;
static int listTail = -1;
static int listSize = 0;

Notification *getLatest()
{
    return notificationsList[listTail];
}
bool isEmpty()
{
    return listSize == 0;
}
bool isFull()
{
    return listSize == MAX_NOTIF;
}
int size()
{
    return listSize;
}
Notification *pop()
{
    Notification *n = notificationsList[listHead++];
    if (listHead == MAX_NOTIF)
    {
        listHead = 0;
    }
    listSize--;
    return n;
}
void push(Notification *data)
{
    if (isFull())
    {
        pop();
        debugLog("NOTIFICATIONS: Too long, had to pop");
    }
    if (listTail == MAX_NOTIF - 1)
    {
        listTail = -1;
        debugLog("NOTIFICATIONS: listTail -1");
    }
    notificationsList[++listTail] = data;
    listSize++;
    debugLog("NOTIFICATIONS: added.");
    debugLog("NOTIFICATIONS: List Size: "+String(listSize));
    debugLog("NOTIFICATIONS: List Head/Tail: "+String(listHead)+"/"+String(listTail));
}

void addNotification(Notification *n, bool addToFs)
{
    debugLog("NOTIFICATIONS: addNotification entered");
    int ts = simplifyUnix(getUnixTime(timeRTCLocal));
    if (n->timestamp == 0)
        n->timestamp = ts;
    if (n->id == 0)
        n->id = ts; // sketchy, but should be unique enough for our purposes
    debugLog("NOTIFICATIONS: updated timestamp/id");
    // if (addToFs)
    // {
    //     if (fsSetBlob(String(n->id), (uint8_t *)n, sizeof(Notification), String(NOTIFICATIONS_DIR) + "/") == false)
    //     {
    //         debugLog("NOTIFICATIONS: Saving notification failed");
    //     }
    // }
    push(n);
}
void initNotifications()
{
    removeDir(NOTIFICATIONS_DIR);
    fsCreateDir(NOTIFICATIONS_DIR);
    for (int i = 0; i < 10; i++)
    {
        notificationsList[i] = nullptr;
    }

    // Load notifications from fs
    if (fsSetup() == false)
    {
        return;
    }

    File root = LittleFS.open(NOTIFICATIONS_DIR);
    if (root)
    {
        File file = root.openNextFile();
        int fileCount = 0;
        while (file)
        {
            debugLog("NOTIFICATIONS: opening file #" + String(fileCount));
            if (file.isDirectory() == false)
            {
                String id = String(file.name());
                bufSize nBuf = fsGetBlob(id, String(NOTIFICATIONS_DIR) + "/");
                if (nBuf.size != sizeof(Notification))
                {
                    debugLog("Bad notification data: " + id);
                    free(nBuf.buf);
                }
                Notification *nData = {0};
                memcpy(&nData, nBuf.buf, nBuf.size);
                addNotification(nData, false);
                debugLog("NOTIFICATIONS: returned from addNotification");
            }
            file.close();
            debugLog("NOTIFICATIONS: file.close");
            file = root.openNextFile();
            debugLog("NOTIFICATIONS: root.openNextFile " + String(file.name()));
            fileCount++;
        }
    }
}

// void updateNotification(Notification notification);
// void deleteNotification(uint64_t id);

#endif