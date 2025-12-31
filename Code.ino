#include <LiquidCrystal.h>

// LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int buzzer = 8;

// DIP switch pins
int swMon  = 9;
int swTue  = 10;
int swWed  = 11;
int swThu  = 12;
int swFri  = 13;
int swStop = A0;

// Timing (simulation)
const unsigned long CLASS_TIME = 10000;
const unsigned long BREAK_TIME = 5000;
const unsigned long LUNCH_TIME = 15000;

unsigned long lastTime = 0;
unsigned long interval = 0;

int stage = 0;      // period tracker
int day   = -1;     // current day
int lastDay = -1;   // for latching day selection

// ------------------ Bell ------------------
void ringBell() {
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer, LOW);
}

// ------------------ Display Day ------------------
void showDay() {
  lcd.setCursor(0, 0);
  switch (day) {
    case 0: lcd.print("MONDAY     "); break;
    case 1: lcd.print("TUESDAY    "); break;
    case 2: lcd.print("WEDNESDAY  "); break;
    case 3: lcd.print("THURSDAY   "); break;
    case 4: lcd.print("FRIDAY     "); break;
  }
}

// ------------------ Display Subject ------------------
void showSubject() {
  lcd.setCursor(0, 1);

  // ===== MONDAY =====
  if (day == 0) {
    switch (stage) {
      case 0: lcd.print("01 - ADBMS "); interval = CLASS_TIME; break;
      case 1: lcd.print("02 - CSS   "); interval = CLASS_TIME; break;
      case 2: lcd.print("BREAK      "); interval = BREAK_TIME; break;
      case 3: lcd.print("03 - BIC   "); interval = CLASS_TIME; break;
      case 4: lcd.print("04 - IoT   "); interval = CLASS_TIME; break;
      case 5: lcd.print("LUNCH      "); interval = LUNCH_TIME; break;
      case 6: lcd.print("05 - DLCV  "); interval = CLASS_TIME; break;
      case 7: lcd.print("06 - MC 1  "); interval = CLASS_TIME; break;
      default: stage = 0; break;
    }
  }

  // ===== TUESDAY =====
  else if (day == 1) {
    switch (stage) {
      case 0: lcd.print("01 - ADBMS LAB"); interval = CLASS_TIME; break;
      case 1: lcd.print("02 - ADBMS LAB"); interval = CLASS_TIME; break;
      case 2: lcd.print("BREAK         "); interval = BREAK_TIME; break;
      case 3: lcd.print("03 - ACN      "); interval = CLASS_TIME; break;
      case 4: lcd.print("04 - BIC      "); interval = CLASS_TIME; break;
      case 5: lcd.print("LUNCH         "); interval = LUNCH_TIME; break;
      case 6: lcd.print("05 - ADBMS    "); interval = CLASS_TIME; break;
      case 7: lcd.print("06 - IoT LAB  "); interval = CLASS_TIME; break;
      default: stage = 0; break;
    }
  }

  // ===== WEDNESDAY =====
  else if (day == 2) {
    switch (stage) {
      case 0: lcd.print("01 - IoT LAB"); interval = CLASS_TIME; break;
      case 1: lcd.print("02 - IoT LAB"); interval = CLASS_TIME; break;
      case 2: lcd.print("BREAK       "); interval = BREAK_TIME; break;
      case 3: lcd.print("03 - IoT    "); interval = CLASS_TIME; break;
      case 4: lcd.print("04 - DLCV   "); interval = CLASS_TIME; break;
      case 5: lcd.print("LUNCH       "); interval = LUNCH_TIME; break;
      case 6: lcd.print("05 - ADBMS  "); interval = CLASS_TIME; break;
      case 7: lcd.print("06 - ACN    "); interval = CLASS_TIME; break;
      default: stage = 0; break;
    }
  }

  // ===== THURSDAY =====
  else if (day == 3) {
    switch (stage) {
      case 0: lcd.print("01 - ADBMS LAB"); interval = CLASS_TIME; break;
      case 1: lcd.print("02 - BIC      "); interval = CLASS_TIME; break;
      case 2: lcd.print("BREAK         "); interval = BREAK_TIME; break;
      case 3: lcd.print("03 - ACN      "); interval = CLASS_TIME; break;
      case 4: lcd.print("04 - IoT      "); interval = CLASS_TIME; break;
      case 5: lcd.print("LUNCH         "); interval = LUNCH_TIME; break;
      case 6: lcd.print("05 - CSS      "); interval = CLASS_TIME; break;
      case 7: lcd.print("06 - DLCV     "); interval = CLASS_TIME; break;
      default: stage = 0; break;
    }
  }

  // ===== FRIDAY =====
  else if (day == 4) {
    switch (stage) {
      case 0: lcd.print("01 - IoT     "); interval = CLASS_TIME; break;
      case 1: lcd.print("02 - DLCV    "); interval = CLASS_TIME; break;
      case 2: lcd.print("BREAK        "); interval = BREAK_TIME; break;
      case 3: lcd.print("03 - MC 1    "); interval = CLASS_TIME; break;
      case 4: lcd.print("04 - ADBMS   "); interval = CLASS_TIME; break;
      case 5: lcd.print("LUNCH        "); interval = LUNCH_TIME; break;
      case 6: lcd.print("05 - ACN     "); interval = CLASS_TIME; break;
      case 7: lcd.print("06 - GURUKULA"); interval = CLASS_TIME; break;
      default: stage = 0; break;
    }
  }
}

// ------------------ SETUP ------------------
void setup() {
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);

  pinMode(swMon,  INPUT_PULLUP);
  pinMode(swTue,  INPUT_PULLUP);
  pinMode(swWed,  INPUT_PULLUP);
  pinMode(swThu,  INPUT_PULLUP);
  pinMode(swFri,  INPUT_PULLUP);
  pinMode(swStop, INPUT_PULLUP);

  lcd.print("Select Day");
}

// ------------------ LOOP ------------------
void loop() {

  // -------- STOP SYSTEM --------
  if (!digitalRead(swStop)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM STOP");
    lcd.setCursor(0, 1);
    lcd.print("BELL OFF");
    digitalWrite(buzzer, LOW);
    return;
  }

  // -------- DAY SELECTION (LATCHED) --------
  if (!digitalRead(swMon)) day = 0;
  else if (!digitalRead(swTue)) day = 1;
  else if (!digitalRead(swWed)) day = 2;
  else if (!digitalRead(swThu)) day = 3;
  else if (!digitalRead(swFri)) day = 4;
  else return;

  // Reset stage only if day changes
  if (day != lastDay) {
    stage = 0;
    interval = 0;
    lastDay = day;
  }

  unsigned long currentTime = millis();

  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;

    ringBell();
    lcd.clear();
    showDay();
    showSubject();

    stage++;
    if (stage > 7) stage = 0;
  }
}
