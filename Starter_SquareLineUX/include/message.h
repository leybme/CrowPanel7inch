#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Message Type Constants
#define MSG_DATA     0   // Data command
#define MSG_SET      1   // Set command
#define MSG_CONTROL  2   // Control command

// Target Type Constants
#define TARGET_SENSOR1   0  // Sensor 1
#define TARGET_STEPPER1  1  // Stepper 1
#define TARGET_STEPPER2  2  // Stepper 2
#define TARGET_SERVO1    3  // Servo 1
#define TARGET_SERVO2    4  // Servo 2

// Structure to send/receive data via ESP-NOW
typedef struct __attribute__((packed))
{
    uint8_t type;   // 1 byte
    uint8_t target; // 1 byte
    union
    {
        float value_float; // 4 bytes
        int value_int;     // 4 bytes
    } value;
} struct_message;

// Function prototypes
String generateSSID();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);
void scanAndAddPeers();

// External variables
extern struct_message outgoingMessage;
extern struct_message incomingMessage;
extern esp_now_peer_info_t peers[];
extern int peerCount;

#endif // MESSAGE_H
