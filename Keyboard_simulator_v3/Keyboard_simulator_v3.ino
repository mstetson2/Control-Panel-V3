//  Control Panel Keyboard Emulator Version 3 (3.0.1)
//  Last Updated: 2/5/2015
//  Matt Stetson

const int keyboardEstop = 38;
const int keyboardDispatch = 41;
const int keyboardOpenGates = 42;
const int keyboardCloseGates = 43;
const int keyboardOpenRestraints = 45;
const int keyboardCloseRestraints = 44;
const int keyboardRaiseFloor = 49;
const int keyboardLowerFloor = 48;
const int keyboardLockFlyer = 51;
const int keyboardUnlockFlyer = 50;
const int keyboardOpenPanel = 52;
const int checkConnectionInput = 36;
//const int checkConnectionOutput = ;



void setup() {
  Serial.begin(9600);
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  pinMode(2, INPUT_PULLUP);

  pinMode(keyboardEstop, INPUT);
  pinMode(keyboardDispatch, INPUT);
  pinMode(keyboardOpenGates, INPUT);
  pinMode(keyboardCloseGates, INPUT);
  pinMode(keyboardOpenRestraints, INPUT);
  pinMode(keyboardCloseRestraints, INPUT);
  pinMode(keyboardRaiseFloor, INPUT);
  pinMode(keyboardLowerFloor, INPUT);
  pinMode(keyboardLockFlyer, INPUT);
  pinMode(keyboardUnlockFlyer, INPUT);
  pinMode(keyboardOpenPanel, INPUT);
  pinMode(checkConnectionInput, INPUT_PULLUP);

  digitalWrite(keyboardEstop, LOW);
  digitalWrite(keyboardDispatch, LOW);
  digitalWrite(keyboardOpenRestraints, LOW);
  digitalWrite(keyboardCloseRestraints, LOW);
  digitalWrite(keyboardRaiseFloor, LOW);
  digitalWrite(keyboardLowerFloor, LOW);
  digitalWrite(keyboardLockFlyer, LOW);
  digitalWrite(keyboardUnlockFlyer, LOW);
  digitalWrite(keyboardOpenPanel, LOW);
  digitalWrite(checkConnectionInput, LOW);

  Serial.println("active");
  Keyboard.begin();

}

void loop() {
  if (digitalRead(checkConnectionInput) == HIGH) {

    if (digitalRead(keyboardEstop) == HIGH ) {
      Keyboard.write(48);
      Serial.println("48 estop");
      delay(50);
    }

    if (digitalRead(keyboardDispatch) == HIGH) {
      Keyboard.write(49);
      Serial.println("49 dispatch");
    }

    if (digitalRead(keyboardOpenGates) == HIGH) {
      Keyboard.write(52);
      Serial.println("52 open gates");
      delay(50);
    }

    if (digitalRead(keyboardCloseGates) == HIGH) {
      Keyboard.write(53);
      Serial.println("53 Close gates");
      delay(50);
    }

    if (digitalRead(keyboardOpenRestraints) == HIGH) {
      Keyboard.write(50);
      Serial.println("50 open restraitns");
      delay(50);
    }

    if (digitalRead(keyboardCloseRestraints) == HIGH) {
      Keyboard.write(51);
      Serial.println("51 close restraints");
      delay(50);
    }

    if (digitalRead(keyboardRaiseFloor) == HIGH) {
      Keyboard.write(55);
      Serial.println("55 raise floor");
      delay(50);
    }

    if (digitalRead(keyboardLowerFloor) == HIGH) {
      Keyboard.write(54);
      Serial.println("54 lower floor");
    }

    if (digitalRead(keyboardLockFlyer) == HIGH) {
      Keyboard.write(57);
      Serial.println("56 lockFlyer");
    }
    if (digitalRead(keyboardUnlockFlyer) == HIGH) {
      Keyboard.write(56);
      Serial.println("57 unlock flyer");
    }

    if (digitalRead(keyboardOpenPanel) == HIGH) {
      Keyboard.write(71);
      Serial.println("71 keyboardOpenPanel");
    }

    checkConnection();

  }
}

void checkConnection() {

}


