#ifndef CONFIG_H
#define CONFIG_H

// Button Configuration
#define LEFT_btn 20
#define RIGHT_btn 21
#define UP_btn 22
#define DOWN_btn 23
#define OK_btn 19
const int DEBOUNCE_DELAY = 200;  // ms

// Tank Display Management
enum TankTab {MAIN, DEEPWELL, RAINWATER, LIVESTOCK};
extern TankTab currentTab;
extern unsigned long lastTabChange;

// LoRa Configuration
#define LORA_TIMEOUT 3000  // 3 seconds
extern String receivedMessage;
extern unsigned long lastLoRaUpdate;

#endif