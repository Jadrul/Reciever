#include "config.h"  // Include the config file
#include "heltec_edited.h"
#include "display_manager.h"

#define OK_btn 19
#define LEFT_btn 20
#define RIGHT_btn 21
#define UP_btn 22
#define DOWN_btn 23
#define BUZZER_PIN 36

#define LEFT_THRESHOLD 300
#define RIGHT_THRESHOLD 700
#define DEBOUNCE_DELAY 200
#define LORA_TIMEOUT 1000

TankTab currentTab = MAIN;
unsigned long lastTabChange = 0;
String receivedMessage = "";
unsigned long lastLoRaUpdate = 0;
void setup() {
  heltec_ve(true);
  initDisplay();  // Call the display setup

  // Initialize buttons
  pinMode(LEFT_btn, INPUT_PULLUP);
  pinMode(RIGHT_btn, INPUT_PULLUP);
  pinMode(UP_btn, INPUT_PULLUP);
  pinMode(DOWN_btn, INPUT_PULLUP);
  pinMode(OK_btn, INPUT_PULLUP);

  // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize LoRa
  heltec_setup();
  int state = radio.begin(915.0);
  if (state != RADIOLIB_ERR_NONE) {
    displayError("LoRa error: " + String(state));
    while (1);
  }

  displayMessage("System Ready", 1000);
}

void handleButton() {
   if (digitalRead(LEFT_btn) == LOW && (millis() - lastTabChange) > DEBOUNCE_DELAY) {
    currentTab = (TankTab)((currentTab + 1) % 4);
    beep(50);
   lastTabChange = millis(); // Update here

} else if (digitalRead(RIGHT_btn) == LOW && (millis() - lastTabChange) > DEBOUNCE_DELAY) {
    currentTab = (TankTab)((currentTab - 1 + 4) % 4);
     beep(50);
    lastTabChange = millis(); // Update here

}

// Do not update lastTabChange here

}

void beep(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);  // Turn the buzzer on
  delay(duration);                 // Wait for the specified duration
  digitalWrite(BUZZER_PIN, LOW);   // Turn the buzzer off
}


void handleLoRa() {
  int state = radio.receive(receivedMessage, LORA_TIMEOUT);
  if (state == RADIOLIB_ERR_NONE) {
    lastLoRaUpdate = millis();
    int commaPos = receivedMessage.indexOf(',');
    if (commaPos != -1) {
      int tankID = receivedMessage.substring(0, commaPos).toInt();
      float level = receivedMessage.substring(commaPos + 1).toFloat();
      updateTankData(tankID, level);
    }
    radio.transmit("ACK");
  }
}

void loop() {
  heltec_loop();
  handleButton();  // Handle button inputs
  handleLoRa();     // Handle LoRa communication
  updateDisplay(currentTab, lastLoRaUpdate);  // Update the display
  delay(100);  // Small delay to reduce CPU usage
}