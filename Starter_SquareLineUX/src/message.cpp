#include "message.h"
#include "ui/ui.h"
// Create a struct_message instance for outgoing and incoming messages
struct_message outgoingMessage;
struct_message incomingMessage;

// List to hold peer information
esp_now_peer_info_t peers[20]; // Adjust size as needed
int peerCount = 0;

// Function to generate SSID
String generateSSID()
{
    uint8_t mac[6];
    WiFi.macAddress(mac);
    char ssid[20];
    sprintf(ssid, "CFMK_%02X%02X%02X", mac[3], mac[4], mac[5]);
    return String(ssid);
}

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    Serial.print("Received message from: ");
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2],
             mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.println(macStr);

    Serial.print("Data length received: ");
    Serial.println(data_len);

    Serial.print("Expected struct size: ");
    Serial.println(sizeof(incomingMessage));

    if (data_len != sizeof(incomingMessage))
    {
        Serial.println("Received data length does not match expected struct size");
        return;
    }

    memcpy(&incomingMessage, data, sizeof(incomingMessage));

    Serial.print("Message Type: ");
    Serial.println(incomingMessage.type);

    Serial.print("Target: ");
    Serial.println(incomingMessage.target);

    // Depending on message type or target, decide whether to use value_int or value_float
    if (incomingMessage.type == MSG_DATA && incomingMessage.target == TARGET_SENSOR1)
    {
        Serial.print("Value (float): ");
        Serial.println(incomingMessage.value.value_float);
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "SENSOR A\n%.0f*C", incomingMessage.value.value_float);
        lv_label_set_text(ui_Label1, buffer);
        lv_chart_set_next_value(ui_Chart2, ui_Chart2_series_1, incomingMessage.value.value_float);
    }
    else
    {
        Serial.print("Value (int): ");
        Serial.println(incomingMessage.value.value_int);
    }
}

// Function to scan for other devices and add them as peers
void scanAndAddPeers()
{
    Serial.println("Scanning for peers...");

    int8_t numNetworks = WiFi.scanNetworks();
    if (numNetworks == -1)
    {
        Serial.println("No WiFi networks found");
        return;
    }

    for (int i = 0; i < numNetworks; ++i)
    {
        String ssid = WiFi.SSID(i);
        if (ssid.startsWith("CFMK_"))
        {
            // Get BSSID (MAC address of the AP)
            uint8_t *bssid = WiFi.BSSID(i);
            char macStr[18];
            snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                     bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
            Serial.print("Found peer with SSID: ");
            Serial.print(ssid);
            Serial.print(", MAC: ");
            Serial.println(macStr);

            // Check if peer is already added
            bool alreadyAdded = false;
            for (int j = 0; j < peerCount; ++j)
            {
                if (memcmp(peers[j].peer_addr, bssid, 6) == 0)
                {
                    alreadyAdded = true;
                    break;
                }
            }

            if (!alreadyAdded)
            {
                esp_now_peer_info_t peerInfo = {};
                memcpy(peerInfo.peer_addr, bssid, 6);
                peerInfo.channel = 1; // Ensure all devices are on the same channel
                peerInfo.encrypt = false;

                if (esp_now_add_peer(&peerInfo) == ESP_OK)
                {
                    Serial.println("Peer added successfully");
                    // Add to peers array
                    memcpy(&peers[peerCount], &peerInfo, sizeof(peerInfo));
                    peerCount++;
                }
                else
                {
                    Serial.println("Failed to add peer");
                }
            }
        }
    }
    if(peerCount>0){
        lv_label_set_text(ui_Label2, "Connection: Connected");
    }
}
