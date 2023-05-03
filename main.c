#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define PIN_TRIG 8
#define PIN_ECHO 9

// Make custom characters:
byte monster1[8] = {
    0b01010,
    0b11111,
    0b10101,
    0b11111,
    0b10001,
    0b11111,
    0b01010,
    0b11011
};
byte monster2[8] = {
    0b11111,
    0b10101,
    0b11111,
    0b10001,
    0b10001,
    0b11111,
    0b01010,
    0b11011
};
byte monster3[8] = {
    0b11111,
    0b10101,
    0b11111,
    0b10001,
    0b11110,
    0b01010,
    0b01010,
    0b11011
};
byte monster4[8] = {
    0b11111,
    0b10101,
    0b11111,
    0b10001,
    0b11110,
    0b01010,
    0b11011,
    0b00000
};

byte rock[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

const int x_size = 16;
const int y_size = 2;


void setup() {
  lcd.begin(16, 2);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  lcd.createChar(0, monster1);
  lcd.createChar(1, monster2);
  lcd.createChar(2, monster3);
  lcd.createChar(3, monster4);
  lcd.createChar(4, rock);
}

void loop() {
  static int anim = 0;
  static bool write_blocks = true;
  static int rocks[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  // measurement
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  int duration = pulseIn(PIN_ECHO, HIGH);
  float distans = duration/ 2.0 / 29.1;

  // printing
  lcd.clear();
  lcd.setCursor(0, 0);
  int y = 0;
  if (distans > 10.00) {
    y = 1;
  }
  lcd.setCursor(0, y);
  lcd.write(byte(anim));
  anim = ++anim %4;
  
  for (int i = 0; i < sizeof(rocks)/sizeof(int); i++) {
    if (rocks[i] != -1) {
      lcd.setCursor(i, rocks[i]);
      lcd.write(byte(4));
    }
  }
  
  if (rocks[0] == y) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Game over");
    delay(5000);
  }
  
  if (write_blocks) {
    for (int i = 1; i < sizeof(rocks)/sizeof(int); i++) {
      rocks[i-1] = rocks[i];
    }
    rocks[sizeof(rocks)/sizeof(int)-1] = rand()%3-1;
  } else {
    rocks[0] = -1;
  }
  write_blocks = !write_blocks;

  delay(400);
}