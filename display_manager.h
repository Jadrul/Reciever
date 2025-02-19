#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H



void initDisplay();
void displayMessage(String msg, int delayTime = 1000);
void displayError(String errorMsg);
void updateTankData(int tankID, float level);
void updateDisplay(TankTab currentTab, unsigned long lastLoRaUpdate);

const char* tabs[] = {"MAIN TANK", "DEEPWELL", "RAIN COLLECTOR TANK", "LIVESTOCK TANK"};

void initDisplay() {
  display.init();
  display.setContrast(255);
  display.flipScreenVertically();
}

void displayMessage(String msg, int delayTime) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 24, msg);
  display.display();
  delay(delayTime);
}

void displayError(String errorMsg) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 16, "ERROR");
  display.drawString(64, 32, errorMsg);
  display.display();
}

void updateTankData(int tankID, float level) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 10, "Tank " + String(tankID));
  display.drawString(64, 30, "Level: " + String(level, 1) + "%");
  display.display();
}

void updateDisplay(TankTab currentTab, unsigned long lastLoRaUpdate) {
  display.clear();
  display.drawHorizontalLine(0, 12, 128);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, tabs[currentTab]);
  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 20, "Last Update:");
  display.drawString(0, 40, String((millis() - lastLoRaUpdate) / 1000) + "s ago");

  display.display();
}

#endif