#include <PCA9557.h>
#include <lvgl.h>
#include <Crowbits_DHT20.h>

#include <SPI.h>
#include "ui/ui.h"
#include "lgfx/lgfx.h"
#include <esp_now.h>
#include <WiFi.h>
#include "message.h"

// Setup the panel.
void setup()
{
  Serial.begin(115200);
  Serial.println("Running setup...");

  // Setup the panel
  lcd.setup();

  // Initialize the Square Line UI
  ui_init();

  // Run the LVGL timer handler once to get things started
  lv_timer_handler();
  // Generate SSID
  String ssid = generateSSID();
  Serial.print("Generated SSID: ");
  Serial.println(ssid);

  // Set device as a Wi-Fi Station and SoftAP
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid.c_str(), NULL, 1); // Start SoftAP with generated SSID on channel 1

  // Give some time for the AP to start
  delay(100);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callbacks
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Scan and add peers
  scanAndAddPeers();
}

int clickCount = 0;

// // Handle Click event
// void clickedClickMe(lv_event_t *e)
// {
//   clickCount++;
//   char ClickBuffer[20];
//   snprintf(ClickBuffer, sizeof(ClickBuffer), "%d", clickCount);
//   lv_label_set_text(ui_LabelCount, ClickBuffer);
// }

// Run Ardunio event loop
void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(10);
  // Periodically scan for new peers
  static unsigned long lastScanTime = 0;
  unsigned long scanInterval = 30000; // Scan every 30 seconds
  if (millis() - lastScanTime >= scanInterval)
  {
    lastScanTime = millis();
    if(peerCount == 0)
    scanAndAddPeers();
  }
}
