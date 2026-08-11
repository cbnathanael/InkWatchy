#pragma once

#include "defines.h"

#if NOTIFICATIONS

struct Notification
{
    uint64_t id;
    uint64_t timestamp;
    String src;
    String title;
    String body;
};
// struct NotifNode {
//     Notification* data = NULL;
//     struct NotifNode* next = NULL;
// };

// struct NotifList {
//     NotifNode* head;
//     size_t size;
// };

struct NotificationMem 
{
    char src[16];
    char title[32];
};
extern Notification* notificationsList[10];
Notification* getLatest();
void addNotification(Notification *n, bool addToFs);
void initNotifications();

void initNotificationDisplay();
void loopNotificationDisplay();
void exitNotificationDisplay();
// void updateNotification(Notification notification);
// void deleteNotification(uint64_t id);

#endif