//  Control Panel Generation 3 Version 8 Revision 0 (3.8.0)
//  Last Updated: 7/2/2015
//  Matt Stetson

char* creditMessage[] = {"Control Panel Version 3.8.0", "Last Updated: 7/2/2015"};

#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,39);

const int manualLed = 27;
const int autoKeyswitch = 22;
const int bypassKeyswitch = 23;
const int powerKeyswitch = 24;
const int eStopLed = 42;
const int eStopButton = 44;
const int acknowledgeButton = 37;
const int startLed = 33;
const int gateSwitch = 51;
const int restraintsButton = 50;
const int startButton = 32;
const int dispatchRightButton = 48;
const int powerLed = 28;
const int restraintsLed = 30;
const int acknowledgeLed = 29;
const int dispatchRightLed = 49;
const int dispatchLeftLed = 25;
const int dispatchLeftButton = 26;
const int functionEnable = 43;
const int troubleLed = 40;
const int troubleButton = 41;
const int speakerPin = 12;
const int rideStopButton = 47;
const int rideStopLed = 46;
const int typeOneSwitch = 38;
const int typeThreeSwitch = 21;

const int keyboardEstop = 35;
const int keyboardDispatch = 20;
const int keyboardOpenGates = 2;
const int keyboardCloseGates = 3;
const int keyboardOpenRestraints = 4;
const int keyboardCloseRestraints = 5;
const int keyboardRaiseFloor = 6;
const int keyboardLowerFloor = 7;
const int keyboardLockFlyer = 8;
const int keyboardUnlockFlyer = 9;
const int keyboardOpenPanel = 10;
const int checkConnectionOut = 14;
//const int checkConnectionIn = ;

int dispatchLeftButtonState = 0;
int dispatchRightButtonState = 0;
int eStopButtonState = 0;
int startButtonState = 0;
int gateSwitchState = 0;
int restraintsButtonState = 0;
int powerKeyswitchState = 0;
int autoKeyswitchState = 0;
int bypassKeyswitchState = 0;
int acknowledgeButtonState = 0;
int functionEnableState = 0;
int troubleButtonState = 0;
int rideStopButtonState = 0;
int typeOneSwitchState = 0;
int typeThreeSwitchState = 0;

int speakerTest = 0;
int dispatchingTime = 0;
int flyerLockedTime = 0;
int floorLoweredTime = 0;

int errorCode = 0;
int startupButton = 0;
int resetTroubleButton = 0;
int timeOut = 0;
int esrResetButton = 0;
int troubleResetButton = 0;

int acknowledgePress = 0;
int typeSelected = 1;


//Blinking led setup:
//stores last time LED was updated
long previousMillis = 0;
long previousRestartMillis = 0;
long dispatchMillis = 0;
long resetMillis = 0;
long previousAckMillis = 0;
long previousManualMillis = 0;
long previousRideStopMillis = 0;
long previousDispatchMillis = 0;
long previousPreDispatchMillis = 0;

//intervals
long longInterval = 1000;
long shortInterval = 500;
long shorterInterval = 250;
long shortestInverval = 100;

//boolean noLimitsStarted = false;

boolean gateOpen = false;
boolean restraintsOpen = false;
boolean floorToggle = false;
boolean flyerToggle = false;

boolean dispatchPressed = false;
boolean resetPressed = false;
boolean eStopPressed = false;
boolean powerOn = false;
boolean errorOcc = false;
boolean functionBypassSerial = false;
boolean extraFunctionBypassSerial = false;
boolean extraFunctionContinueSerial = false;
boolean extraOpFunctionSerial = true;
boolean registeredSerial = false;
boolean powerOnSerial = false;
boolean longWarningSerial = false;
boolean timeOutAck = false;


boolean booted = false;


boolean lampTested = false;
boolean eStopTested = false;
boolean extraFunctionsChoose = false;
boolean extraFunctionsDone = false;
boolean started = false;
boolean startupLongTone = false;
boolean startupSerial = false;
boolean eStopSerialMessage = false;
boolean eStopTestSerialMessage = false;
boolean longToneSerialMessage = false;
boolean lampTestSerialMessage = false;
boolean eStopTestSerialTwo = false;
boolean bootupMessage = false;
boolean errorSerialMessage1 = false;
boolean poweredOffMessage = false;
boolean bootupEstopMessage = false;
boolean dispatchUnlock = true;
boolean warningSerial = false;
boolean lampFunctionMessage = false;

boolean eStopDown = false;
boolean eStopReset = false;
boolean ledOff = false;
boolean eStopAcked = false;
boolean error = false;
boolean ackPressed = false;
boolean restraintsPressed = false;
boolean gatePressed = false;
boolean eStopped = false;
boolean rideStopped = false;
boolean eStopTestedPressed = false;
boolean postDispatch = false;
boolean bypassed = false;
boolean rideStopPressed = false;
boolean rideStopLedOn = false;
boolean bypassMessage = false;
boolean bootKeyoff = false;
boolean bootKeyoffMessage1 = false;
boolean bootKeyoffMessage2 = true;
boolean bootKeyoffMessage3 = true;
boolean functionsListed = false;

boolean startupHorn = false;
boolean troubleAlarm = true;
boolean troubleSilenced = false;
boolean singleDispatch = false;
boolean bypassDispatchMessage = false;
boolean autoRestraints = true;
boolean supervisorMode = false;
boolean functionsMessage2 = false;

boolean powerMessage = false;
boolean dispatching = false;
boolean restraintsLocked = true;
boolean errorAck = true;
boolean errorMessage = false;
boolean acknowledgeCount = false;
boolean rideStartBypass = false;
boolean badDispatch = false;
boolean flyerLocked = false;
boolean floorLowered = false;

//FOR KEYBOARD OUTPUTS
boolean keyboardDispatchSent = false;
boolean keyboardEstopSent = false;
boolean keyboardOpenGatesSent = false;
boolean keyboardCloseGatesSent = false;
boolean keyboardRaiseFloorSent = false;
boolean keyboardLowerFloorSent = false;
boolean keyboardLockFlyerSent = false;
boolean keyboardUnlockFlyerSent = false;
boolean keyboardOpenPanelSent =  false;

int powerLedFlashes = 58;

void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(dispatchLeftLed, OUTPUT);
  pinMode(dispatchRightLed, OUTPUT);
  pinMode(eStopLed, OUTPUT);
  pinMode(startLed, OUTPUT);
  pinMode(powerLed, OUTPUT);
  pinMode(troubleLed, OUTPUT);
  pinMode(restraintsLed, OUTPUT);
  pinMode(acknowledgeLed, OUTPUT);
  pinMode(manualLed, OUTPUT);
  pinMode(rideStopLed, OUTPUT);

  pinMode(keyboardEstop, OUTPUT);
  pinMode(keyboardDispatch, OUTPUT);
  pinMode(keyboardOpenGates, OUTPUT);
  pinMode(keyboardCloseGates, OUTPUT);
  pinMode(keyboardOpenRestraints, OUTPUT);
  pinMode(keyboardCloseRestraints, OUTPUT);
  pinMode(keyboardRaiseFloor, OUTPUT);
  pinMode(keyboardLowerFloor, OUTPUT);
  pinMode(keyboardLockFlyer, OUTPUT);
  pinMode(keyboardUnlockFlyer, OUTPUT);
  pinMode(keyboardOpenPanel, OUTPUT);
  pinMode(checkConnectionOut, OUTPUT);

  pinMode(dispatchLeftButton, INPUT);
  pinMode(dispatchRightButton, INPUT);
  pinMode(eStopButton, INPUT);
  pinMode(startButton, INPUT);
  pinMode(gateSwitch, INPUT);
  pinMode(powerKeyswitch, INPUT);
  pinMode(autoKeyswitch, INPUT);
  pinMode(bypassKeyswitch, INPUT);
  pinMode(restraintsButton , INPUT);
  pinMode(acknowledgeButton, INPUT);
  pinMode(functionEnable, INPUT);
  pinMode(troubleButton, INPUT);
  pinMode(rideStopButton, INPUT);
  pinMode(typeOneSwitch, INPUT);
  pinMode(typeThreeSwitch, INPUT);

  digitalWrite(dispatchLeftButton, HIGH);
  digitalWrite(dispatchRightButton, HIGH);
  digitalWrite(eStopButton, HIGH);
  digitalWrite(startButton, HIGH);
  digitalWrite(gateSwitch, HIGH);
  digitalWrite(restraintsButton, HIGH);
  digitalWrite(powerKeyswitch, HIGH);
  digitalWrite(autoKeyswitch, HIGH);
  digitalWrite(bypassKeyswitch, HIGH);
  digitalWrite(acknowledgeButton, HIGH);
  digitalWrite(functionEnable, HIGH);
  digitalWrite(troubleButton, HIGH);
  digitalWrite(rideStopButton, HIGH);
  digitalWrite(typeOneSwitch, HIGH);
  digitalWrite(typeThreeSwitch, HIGH);

  digitalWrite(keyboardEstop, LOW);
  digitalWrite(keyboardDispatch, LOW);
  digitalWrite(keyboardOpenRestraints, LOW);
  digitalWrite(keyboardCloseRestraints, LOW);
  digitalWrite(keyboardRaiseFloor, LOW);
  digitalWrite(keyboardLowerFloor, LOW);
  digitalWrite(keyboardLockFlyer, LOW);
  digitalWrite(keyboardUnlockFlyer, LOW);
  digitalWrite(keyboardOpenPanel, LOW);

  digitalWrite(checkConnectionOut, HIGH);
}

void loop() {

  dispatchLeftButtonState = digitalRead(dispatchLeftButton);
  dispatchRightButtonState = digitalRead(dispatchRightButton);
  eStopButtonState = digitalRead(eStopButton);
  startButtonState = digitalRead(startButton);
  gateSwitchState = digitalRead(gateSwitch);
  restraintsButtonState = digitalRead(restraintsButton);
  powerKeyswitchState = digitalRead(powerKeyswitch);
  acknowledgeButtonState = digitalRead(acknowledgeButton);
  autoKeyswitchState = digitalRead(autoKeyswitch);
  bypassKeyswitchState = digitalRead(bypassKeyswitch);
  functionEnableState = digitalRead(functionEnable);
  troubleButtonState = digitalRead(troubleButton);
  rideStopButtonState = digitalRead(rideStopButton);
  typeOneSwitchState = digitalRead(typeOneSwitch);
  typeThreeSwitchState = digitalRead(typeThreeSwitch);

  unsigned long currentMillis = millis();
  int countDown = timeOut * 2;

  if (eStopButtonState == LOW) {
    noTone(speakerPin);
    digitalWrite(eStopLed, HIGH);
  }

  if (booted == false) {
    if (powerOnSerial == false) {
      
      Serial.println(F(" "));
      Serial.println(F("//////////////////////////////////////////////////////////////"));
      Serial.println(F(" "));
      Serial.println(creditMessage[0]);
      Serial.println(F(" "));
      Serial.println(creditMessage[1]);
      Serial.println(F(" "));
      Serial.println(F("Matt Stetson"));
      Serial.println(F(" "));
      Serial.println(F("//////////////////////////////////////////////////////////////"));
      Serial.println(F(" "));
      delay(500);
      Serial.println(F(" "));
      Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
      Serial.println(F("READ OPERATING INSTRUCTIONS BEFORE USE!"));
      Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
      Serial.println(F(" "));
      
      mySerial.write(254); 
      mySerial.write(128);
      mySerial.write("                "); 
      mySerial.write("                ");
      mySerial.write(254); 
      mySerial.write(128);
      mySerial.write("PANEL V:3.8.0   ");
      mySerial.write("MATT STETSON");
      mySerial.write(254); 
      mySerial.write(128);
      
      powerOnSerial = true;
      delay(1000);
      if (powerKeyswitchState != 0) {
        Serial.println(F("STATUS OO1: Panel is off. Turn CONTROL PANEL POWER on to begin."));
        
      mySerial.write("                "); 
      mySerial.write("                ");
      mySerial.write(254); 
      mySerial.write(128);
      mySerial.write("PANEL is off.   ");
      mySerial.write("TURN PANEL ON");
      mySerial.write(254); 
      mySerial.write(128);
      
      }
    }
    bootSeq();
  }
  else {
    if (powerKeyswitchState == 0) {
      digitalWrite(powerLed, HIGH);
      poweredOn();
      rideStop();
      manualIndicator();
    }
    else {
      ledsOff();
      eStopPressed = true;
      error = true;
      started = false;
      eStopReset = false;
      errorAck = false;
      errorMessage = false;
      errorCode = 010;
      startupButton = 0;
      esrResetButton = 0;
      troubleResetButton = 0;
      eStopReset = false;
      if (poweredOffMessage == false) {
        Serial.println(F("STATUS 002: MAIN OP PANEL: POWER KEY switched to OFF."));
      mySerial.write("                "); 
      mySerial.write("                ");
      mySerial.write(254); 
      mySerial.write(128);
      mySerial.write("MAIN OP KEY OFF");
      mySerial.write("TURN PANEL ON");
      mySerial.write(254); 
      mySerial.write(128);
        poweredOffMessage = true;
      }
      noTone(speakerPin);

      if (currentMillis - previousMillis > longInterval) {
        previousMillis = currentMillis;
        if (digitalRead(powerLed) == LOW) {
          digitalWrite(powerLed, HIGH);
        }
        else {
          digitalWrite(powerLed, LOW);
        }
      }

      if (keyboardEstopSent == false) {
        digitalWrite(keyboardEstop, HIGH);
        delay(10);
        //Serial.println("keyboardEstop = High (error)");
        digitalWrite(keyboardEstop, LOW);
        //Serial.println("keyboardEstop = low (error)");
        keyboardEstopSent = true;
      }

    }

    if (started == false) {
      if (eStopped == false) {
        //  Serial.println("keyboardEstop from started == false");
        //  digitalWrite(keyboardEstop, LOW);
        eStopped = true;
        //  delay(500);
      }
      else {
        //  digitalWrite(keyboardEstop, HIGH);
      }

      /*if (powerKeyswitchState == 0) {
        digitalWrite(rideStopLed, HIGH);
      }
      else {
        digitalWrite(rideStopLed, LOW);
      }
      */
    }
  }
  /*
  if (timeOut == 100) {
    //error = true;
    started = false;
    //ledsOff();
    //errorCode = 021;
    digitalWrite(dispatchLeftLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    timeOut = 0;

  }
  */

}

void poweredOn() {
  if (eStopButtonState == LOW) {
    if (eStopPressed == false) {
      eStopPressed = true;
      error = true;
      started = false;
      eStopReset = false;
      errorAck = false;
      errorMessage = false;
      errorCode = 27;
      noTone(speakerPin);

      if (keyboardEstopSent == false) {
        digitalWrite(keyboardEstop, HIGH);
        delay(10);
        //Serial.println("keyboardEstop = High (error)");
        digitalWrite(keyboardEstop, LOW);
        //Serial.println("keyboardEstop = low (error)");
        keyboardEstopSent = true;
      }

      digitalWrite(dispatchLeftLed, LOW);
      digitalWrite(dispatchRightLed, LOW);
      digitalWrite(startLed, LOW);
      digitalWrite(restraintsLed, LOW);
      digitalWrite(troubleLed, LOW);
      digitalWrite(manualLed, LOW);

      Serial.println(F("STATUS 031: MAIN OP PANEL E-STOP PUSHBUTTON PRESSED"));
      if (supervisorMode == true) {
        Serial.println(F("[SUPERVISOR MODE]Switch to BYPASS MODE to allow ESR RESET"));
      }
      else {
        Serial.println(F("Switch to BYPASS MODE and enable FUNCTION ENABLE to allow ESR RESET"));
      }
    }
  }

  if (error == true || eStopPressed == true || started == false) {
    if (eStopPressed == true) {
      eStopPress();
    }
    else {
      if (error == true) {
        errorReset();
      }
      else {
        if (started == false) {
          firstStartup();
        }



      }
    }

  }
  else {
    dispatchButtons();
    restraints();
    autoAcknowledge();
    gate();


    if (startButtonState == LOW) {
    }
    else {
      noTone(speakerPin);
    }

  }

}

void restraints() {

  if (restraintsButtonState == LOW) {
    if ((floorLowered == false && flyerLocked == false && autoKeyswitchState == 0) || (bypassKeyswitchState != 0 && autoKeyswitchState != 0) || (bypassKeyswitchState == 0)) {
      if (functionEnableState != 0) {
        if (restraintsPressed == false) {
          restraintsPressed = true;
          postDispatch = false;

          if (restraintsLocked == false) {
            restraintsLocked = true;
            digitalWrite(restraintsLed, HIGH);
            Serial.println("STATUS 013: RESTRAINTS LOCKED.");
            digitalWrite(keyboardCloseRestraints, HIGH);
            delay(10);
            // Serial.println("close restraints keyboard");
            digitalWrite(keyboardCloseRestraints, LOW);
            timeOut = 0;
            digitalWrite(startLed, HIGH);
          }
          else {
            restraintsLocked = false;
            digitalWrite(restraintsLed, LOW);
            digitalWrite(dispatchLeftLed, LOW);
            Serial.println("STATUS 014: RESTRAINTS UNLOCKED.");
            digitalWrite(keyboardOpenRestraints, HIGH);
            delay(10);
            // Serial.println("open restraints keyboard");
            digitalWrite(keyboardOpenRestraints, LOW);
            timeOut = 0;
            digitalWrite(startLed, HIGH);
          }
        }
      }
      else {
        error = true;
        started = false;
        errorAck = false;
        ledsOff();
        errorCode = 061;
        Serial.println(F("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error."));
      }
    }
    else {
      if (floorLowered == true) {
        error = true;
        started = false;
        errorAck = false;
        ledsOff();
        errorCode = 063;
        Serial.println(F("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error"));
      }
      else {
        if (flyerLocked == true) {
          error = true;
          started = false;
          errorAck = false;
          ledsOff();
          errorCode = 064;
          Serial.println(F("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error"));
        }
      }
    }
  }
  else {
    restraintsPressed = false;
  }


}

void gate() {
  unsigned long restartMillis = millis();

  if (gateSwitchState != 0) {
    if ((floorLowered == false && flyerLocked == false && autoKeyswitchState == 0) || (bypassKeyswitchState != 0 && autoKeyswitchState != 0) || (bypassKeyswitchState == 0)) {

      if (gatePressed == false) {
        gatePressed = true;

        if (gateOpen == false) {
          gateOpen = true;
          digitalWrite(dispatchLeftLed, LOW);
          Serial.println(F("STATUS 016: AIR GATES OPEN. CLOSE GATES TO DISPATCH TRAIN."));
           mySerial.write("                "); 
          mySerial.write("                ");
          mySerial.write(254); 
          mySerial.write(128);
          mySerial.write("AIR GATES OPEN");
          mySerial.write("CLOSE TO DISPATCH");
          mySerial.write(254); 
          mySerial.write(128);
          digitalWrite(keyboardOpenGates, HIGH);
          delay(10);
          // Serial.println("open gates keyboard");
          digitalWrite(keyboardOpenGates, LOW);
          timeOut = 0;
          digitalWrite(startLed, HIGH);
        }
        else {
          gateOpen = false;
          Serial.println(F("STATUS 017: AIR GATES CLOSING."));
           mySerial.write("                "); 
      mySerial.write("                ");
      mySerial.write(254); 
      mySerial.write(128);
      mySerial.write("AIR GATES CLOSED");
      //mySerial.write("TURN PANEL ON");
      mySerial.write(254); 
      mySerial.write(128);
          digitalWrite(keyboardCloseGates, HIGH);
          delay(10);
          //  Serial.println("close gates keyboard");
          digitalWrite(keyboardCloseGates, LOW);
          timeOut = 0;
          digitalWrite(startLed, HIGH);
        }
      }
    }
    else {
      if (floorLowered == true) {
        error = true;
        started = false;
        errorAck = false;
        ledsOff();
        errorCode = 066;
        Serial.println(F("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error"));
      }
      else {
        if (flyerLocked == true) {
          error = true;
          started = false;
          errorAck = false;
          ledsOff();
          errorCode = 067;
          Serial.println(F("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error"));
        }
      }
    }
  }
  else {
    if (restartMillis - previousRestartMillis > shortInterval) {
      gatePressed = false;
      previousRestartMillis = restartMillis;
    }
  }

}





void autoAcknowledge() {
  unsigned long currentRideStopMillis = millis();
  unsigned long ackMillis = millis();
  int countDown = timeOut;

  if (startButtonState == LOW) {
    timeOut = 0;
    digitalWrite(startLed, HIGH);
  }


  if (acknowledgeButtonState == LOW) {
    timeOut = 0;
    digitalWrite(startLed, HIGH);
    if (autoKeyswitchState == 0) {
      digitalWrite(acknowledgeLed, HIGH);
      if (acknowledgeCount == false) {
        acknowledgePress++;
        Serial.println(F("STATUS 306: ACKNOWLEDGE PRESSED: No error in automatic mode."));
        //Serial.println(acknowledgePress);
        acknowledgeCount = true;
        previousAckMillis = ackMillis;
      }
    }
  }
  else {
    if (timeOut < 250) {
      digitalWrite(acknowledgeLed, LOW);

    }
    acknowledgeCount = false;
  }

  if (timeOut > 250) {
    if (currentRideStopMillis - previousRideStopMillis > 500) {
      previousRideStopMillis = currentRideStopMillis;
      if (digitalRead(acknowledgeLed) == LOW) {
        digitalWrite(acknowledgeLed, HIGH);
        digitalWrite(startLed, LOW);
      }
      else {
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(startLed, HIGH);
        timeOutAck = false;
      }

      if (timeOutAck == false) {
        Serial.print(F("STATUS 314: Ride will timeout in: "));
        Serial.print(300 - countDown);
        Serial.print(F(" seconds."));
        Serial.println(F(" "));
        timeOutAck = true;
      }
    }
  }



  if (ackMillis - previousAckMillis < 5000) {
    if (acknowledgePress >= 10) {

      error = true;
      errorCode = 036;
      ledsOff();
      started = false;
      errorAck = false;
      errorMessage = false;
      digitalWrite(acknowledgeLed, LOW);
    }
  }
  else {
    acknowledgePress = 0;
  }
}

void rideStop() {
  unsigned long currentRideStopMillis = millis();
  if (rideStopButtonState == LOW) {
    if (rideStopped == false) {
      //digitalWrite(rideStopLed, HIGH);
      digitalWrite(dispatchLeftLed, LOW);
      digitalWrite(dispatchRightLed, LOW);
      digitalWrite(restraintsLed, LOW);
      digitalWrite(startLed, LOW);
      restraintsLocked = false;
      started = false;
      rideStopPressed = true;
      Serial.println(F("STATUS 324: MAIN OP RIDE STOP PRESSED."));
      Serial.println(F("PRESS AND HOLD RIDE START TO START RIDE."));

      if (keyboardEstopSent == false) {
        keyboardEstopSent = true;
        digitalWrite(keyboardEstop, HIGH);
        delay(10);
        //Serial.println("keyboardEstop = High (ride stop)");
        digitalWrite(keyboardEstop, LOW);
        //Serial.println("keyboardEstop = low (ride stop) ");

      }

      if (bypassKeyswitchState == 0) {
        if (bypassMessage == false) {
          Serial.println(F("STATUS 325: RIDE STOP pressed while in BYPASS MODE. Press RIDE START to restart ride without WARNING HORN."));
          Serial.println(F("Press E-STOP if this was a mistake."));
          bypassMessage = true;
        }
        rideStartBypass = true;
      }
      rideStopped = true;
    }
  }

  if (rideStopPressed == true) {
    if (currentRideStopMillis - previousRideStopMillis > 250) {
      previousRideStopMillis = currentRideStopMillis;
      if (digitalRead(rideStopLed) == LOW) {
        digitalWrite(rideStopLed, HIGH);
      }
      else {
        digitalWrite(rideStopLed, LOW);
      }
    }
  }



}


void dispatchButtons() {
  unsigned long currentMillis = millis();
  unsigned long dispatchMillis = millis();
  int countDown = timeOut * 2;

  if (timeOut == 300) {
    timeOut = 0;
    error = true;
    started = false;
    errorAck = false;
    ledsOff();
    errorCode = 100;

  }

  if (autoKeyswitchState == 0 && functionEnableState != 0) {
    if (typeSelected == 1) {
      if (gateOpen == false && restraintsLocked == true) {
        if (currentMillis - previousMillis > longInterval) {
          previousMillis = currentMillis;
          if (digitalRead(dispatchRightLed) == LOW) {
            if (singleDispatch == false) {
              digitalWrite(dispatchLeftLed, HIGH);
            }
            digitalWrite(dispatchRightLed, HIGH);
          }
          else {
            digitalWrite(dispatchLeftLed, LOW);
            digitalWrite(dispatchRightLed, LOW);
          }
          timeOut++;
        }

        if (singleDispatch == false) {
          if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
            digitalWrite(dispatchLeftLed, HIGH);
            digitalWrite(dispatchRightLed, HIGH);
            digitalWrite(restraintsLed, LOW);
            timeOut = 0;
            digitalWrite(startLed, HIGH);
            dispatchUnlock = false;
            dispatch();


          }
          else {
            dispatching = false;

            if (autoRestraints) {
              if (dispatchUnlock == false) {
                Serial.println(F("STATUS 018: Train has parked. RESTRAINTS UNLOCKED."));
                digitalWrite(restraintsLed, LOW);
                digitalWrite(keyboardOpenRestraints, HIGH);
                delay(10);
                digitalWrite(keyboardOpenRestraints, LOW);
                restraintsLocked = false;
                dispatchUnlock = true;

              }
              else {
                if (restraintsLocked == true) {
                  digitalWrite(restraintsLed, HIGH);
                }
              }
            }
            if (restraintsLocked == true) {
              digitalWrite(restraintsLed, HIGH);
            }
          }
        }
        else {
          if (dispatchRightButtonState == LOW) {
            digitalWrite(dispatchLeftLed, HIGH);
            digitalWrite(dispatchRightLed, HIGH);
            digitalWrite(restraintsLed, LOW);
            timeOut = 0;
            digitalWrite(startLed, HIGH);
            dispatchUnlock = false;
            dispatch();


          }
          else {
            dispatching = false;
            if (autoRestraints) {
              if (dispatchUnlock == false) {

                Serial.println(F("STATUS 018: Train has parked. RESTRAINTS UNLOCKED."));
                digitalWrite(restraintsLed, LOW);
                digitalWrite(keyboardOpenRestraints, HIGH);
                delay(10);
                digitalWrite(keyboardOpenRestraints, LOW);
                restraintsLocked = false;
                dispatchUnlock = true;

              }
              else {
                if (restraintsLocked == true) {
                  digitalWrite(restraintsLed, HIGH);
                }
              }
            }
            if (restraintsLocked == true) {
              digitalWrite(restraintsLed, HIGH);
            }
          }





        }
      }
      else {
        digitalWrite(dispatchLeftLed, LOW);
        digitalWrite(dispatchRightLed, LOW);
      }

    }
    else {
      if (typeSelected == 2) {
        //INVERTED COASTER
        if (gateOpen == false && restraintsLocked == true) {
          if (floorLowered == false) {
            if (currentMillis - previousMillis > longInterval) {
              previousMillis = currentMillis;
              if (digitalRead(dispatchLeftLed) == LOW) {
                digitalWrite(dispatchLeftLed, HIGH);
              }
              else {
                digitalWrite(dispatchLeftLed, LOW);
              }
              timeOut++;
            }

          }
          else {
            if (currentMillis - previousMillis > longInterval) {
              previousMillis = currentMillis;
              if (digitalRead(dispatchRightLed) == LOW) {
                digitalWrite(dispatchRightLed, HIGH);
                digitalWrite(dispatchLeftLed, LOW);
              }
              else {
                digitalWrite(dispatchRightLed, LOW);
                digitalWrite(dispatchLeftLed, HIGH);
              }
              timeOut++;
            }
          }


          if (dispatchLeftButtonState == LOW ) {
            digitalWrite(dispatchRightLed, LOW);
            timeOut = 0;
            digitalWrite(startLed, HIGH);
            if (floorToggle == false) {
              if (floorLowered == false) {
                floorToggle = true;
                digitalWrite(dispatchLeftLed, HIGH);
                previousDispatchMillis = dispatchMillis;
                digitalWrite(keyboardLowerFloor, HIGH);
                Serial.println(F("STATUS 022: FLOOR LOWERING"));
                digitalWrite(restraintsLed, LOW);
                delay(10);
                digitalWrite(keyboardLowerFloor, LOW);
                floorLowered = true;
                digitalWrite(dispatchLeftLed, LOW);
              }
              else {
                floorToggle = true;
                digitalWrite(dispatchLeftLed, HIGH);
                digitalWrite(keyboardRaiseFloor, HIGH);
                Serial.println(F("STATUS 023: FLOOR RAISING"));
                digitalWrite(restraintsLed, HIGH);
                delay(10);
                digitalWrite(keyboardRaiseFloor, LOW);
                floorLowered = false;
                digitalWrite(dispatchLeftLed, LOW);

              }
            }
          }
          else {
            floorToggle = false;
          }

          if (dispatchRightButtonState == LOW && floorLowered == true) {
            timeOut = 0;
            digitalWrite(startLed, HIGH);
            digitalWrite(dispatchRightLed, HIGH);
            digitalWrite(dispatchLeftLed, LOW);
            dispatch();
          }
          else {
            dispatching = false;
          }
        }
      }
      else {
        if (typeSelected == 3) {
          //FLYING COASTER
          if (gateOpen == false && restraintsLocked == true) {
            if (flyerLocked == false) {
              if (currentMillis - previousMillis > longInterval) {
                previousMillis = currentMillis;
                if (digitalRead(dispatchLeftLed) == LOW) {
                  digitalWrite(dispatchLeftLed, HIGH);
                }
                else {
                  digitalWrite(dispatchLeftLed, LOW);
                }
                timeOut++;
              }

            }
            else {
              if (currentMillis - previousMillis > longInterval) {
                previousMillis = currentMillis;
                if (digitalRead(dispatchRightLed) == LOW) {
                  digitalWrite(dispatchRightLed, HIGH);
                  digitalWrite(dispatchLeftLed, LOW);
                }
                else {
                  digitalWrite(dispatchRightLed, LOW);
                  digitalWrite(dispatchLeftLed, HIGH);
                }
                timeOut++;
              }
            }


            if (dispatchLeftButtonState == LOW ) {
              timeOut = 0;
              digitalWrite(startLed, HIGH);
              digitalWrite(dispatchRightLed, LOW);
              digitalWrite(dispatchLeftLed, HIGH);
              if (flyerToggle == false) {
                if (flyerLocked == false) {
                  flyerToggle = true;
                  digitalWrite(dispatchLeftLed, HIGH);
                  previousDispatchMillis = dispatchMillis;
                  digitalWrite(keyboardLockFlyer, HIGH);
                  Serial.println(F("STATUS 025: CHAISIE UP"));
                  digitalWrite(restraintsLed, LOW);
                  delay(10);
                  digitalWrite(keyboardLockFlyer, LOW);
                  flyerLocked = true;
                  digitalWrite(dispatchLeftLed, LOW);
                }
                else {
                  flyerToggle = true;
                  digitalWrite(dispatchLeftLed, HIGH);
                  digitalWrite(keyboardUnlockFlyer, HIGH);
                  Serial.println(F("STATUS 026: CHAISE DOWN"));
                  digitalWrite(restraintsLed, HIGH);
                  delay(10);
                  digitalWrite(keyboardUnlockFlyer, LOW);
                  flyerLocked = false;
                  digitalWrite(dispatchLeftLed, LOW);

                }
              }
            }
            else {
              flyerToggle = false;
            }

            if (dispatchRightButtonState == LOW && flyerLocked == true) {
              digitalWrite(dispatchRightLed, HIGH);
              digitalWrite(dispatchLeftLed, LOW);
              timeOut = 0;
              digitalWrite(startLed, HIGH);
              dispatch();
            }
            else {
              dispatching = false;
            }
          }
        }
      }
    }
  }
  else {
    //WHAT TO DO WHEN BYPASSED
    if (functionEnableState != 0) {
      if (bypassKeyswitchState != 0 && autoKeyswitchState != 0) {
        //MANUAL MODE
        if (typeSelected == 1) {
          if (currentMillis - previousMillis > longInterval) {
            previousMillis = currentMillis;
            if (digitalRead(dispatchLeftLed) == LOW) {
              digitalWrite(dispatchLeftLed, HIGH);
              digitalWrite(dispatchRightLed, HIGH);
            }
            else {
              digitalWrite(dispatchLeftLed, LOW);
              digitalWrite(dispatchRightLed, LOW);
            }
          }


          if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
            digitalWrite(dispatchLeftLed, HIGH);
            digitalWrite(dispatchRightLed, HIGH);
            dispatch();


          }
          else {
            dispatching = false;
          }
        }
        else {
          if (typeSelected == 2) {
            //INVERTED COASTER
            if (dispatching == false) {
              if (currentMillis - previousMillis > longInterval) {
                previousMillis = currentMillis;
                if (digitalRead(dispatchLeftLed) == LOW) {
                  digitalWrite(dispatchLeftLed, HIGH);
                  digitalWrite(dispatchRightLed, LOW);
                }
                else {
                  digitalWrite(dispatchLeftLed, LOW);
                  digitalWrite(dispatchRightLed, HIGH);
                }
              }
            }



            if (dispatchLeftButtonState == LOW ) {
              digitalWrite(dispatchRightLed, LOW);
              if (floorToggle == false) {
                if (floorLowered == false) {
                  floorToggle = true;
                  digitalWrite(dispatchLeftLed, HIGH);
                  previousDispatchMillis = dispatchMillis;
                  digitalWrite(keyboardLowerFloor, HIGH);
                  Serial.println(F("STATUS 022: FLOOR LOWERING"));
                  delay(10);
                  digitalWrite(keyboardLowerFloor, LOW);
                  floorLowered = true;
                  digitalWrite(dispatchLeftLed, LOW);
                }
                else {
                  floorToggle = true;
                  digitalWrite(dispatchLeftLed, HIGH);
                  digitalWrite(keyboardRaiseFloor, HIGH);
                  Serial.println(F("STATUS 023: FLOOR RAISING"));
                  delay(10);
                  digitalWrite(keyboardRaiseFloor, LOW);
                  floorLowered = false;
                  digitalWrite(dispatchLeftLed, LOW);

                }
              }
            }
            else {
              floorToggle = false;
            }

            if (dispatchRightButtonState == LOW) {
              digitalWrite(dispatchRightLed, HIGH);
              digitalWrite(dispatchLeftLed, LOW);
              if (floorLowered == false && registeredSerial == false) {
                Serial.println(F("STATUS 024: FLOOR NOT REGISTERED AS LOWERED. Will attempt dispatch anyway."));
                registeredSerial = true;
              }
              dispatch();
            }
            else {
              dispatching = false;
              registeredSerial = false;
            }

          }
          else {
            if (typeSelected == 3) {
              //FLYING COASTER
              if (dispatching == false) {
                if (currentMillis - previousMillis > longInterval) {
                  previousMillis = currentMillis;
                  if (digitalRead(dispatchLeftLed) == LOW) {
                    digitalWrite(dispatchLeftLed, HIGH);
                    digitalWrite(dispatchRightLed, LOW);
                  }
                  else {
                    digitalWrite(dispatchLeftLed, LOW);
                    digitalWrite(dispatchRightLed, HIGH);
                  }
                }
              }



              if (dispatchLeftButtonState == LOW ) {
                digitalWrite(dispatchRightLed, LOW);
                if (flyerToggle == false) {
                  if (flyerLocked == false) {
                    flyerToggle = true;
                    digitalWrite(dispatchLeftLed, HIGH);
                    previousDispatchMillis = dispatchMillis;
                    digitalWrite(keyboardLockFlyer, HIGH);
                    Serial.println(F("STATUS 025: CHAISIE UP"));
                    delay(10);
                    digitalWrite(keyboardLockFlyer, LOW);
                    flyerLocked = true;
                    digitalWrite(dispatchLeftLed, LOW);
                  }
                  else {
                    flyerToggle = true;
                    digitalWrite(dispatchLeftLed, HIGH);
                    digitalWrite(keyboardUnlockFlyer, HIGH);
                    Serial.println(F("STATUS 026: CHAISE DOWN"));
                    delay(10);
                    digitalWrite(keyboardUnlockFlyer, LOW);
                    flyerLocked = false;
                    digitalWrite(dispatchLeftLed, LOW);

                  }
                }
              }
              else {
                flyerToggle = false;
              }

              if (dispatchRightButtonState == LOW) {
                digitalWrite(dispatchRightLed, HIGH);
                digitalWrite(dispatchLeftLed, LOW);
                if (flyerLocked == false && registeredSerial == false) {
                  Serial.println(F("STATUS 027: CHASSIS NOT REGISTERED AS LOCKED. Will attempt dispatch anyway."));
                  registeredSerial = true;
                }
                dispatch();
              }
              else {
                dispatching = false;
                registeredSerial = false;
              }

            }
          }
        }



      }
      else {
        if (bypassKeyswitchState == 0) {
          if (typeSelected == 1) {
            if (currentMillis - previousMillis > longInterval) {
              previousMillis = currentMillis;
              if (digitalRead(dispatchRightLed) == LOW) {
                digitalWrite(dispatchRightLed, HIGH);
              }
              else {
                digitalWrite(dispatchRightLed, LOW);
                digitalWrite(dispatchLeftLed, LOW);
              }
            }


            if (dispatchRightButtonState == LOW) {
              digitalWrite(dispatchLeftLed, HIGH);
              digitalWrite(dispatchRightLed, HIGH);
              digitalWrite(restraintsLed, LOW);
              dispatch();
            }
            else {
              digitalWrite(dispatchLeftLed, LOW);
              if (restraintsLocked == true) {
                digitalWrite(restraintsLed, HIGH);
              }
              dispatching = false;
            }

          }
          else {
            if (bypassDispatchMessage == false) {
              Serial.println(F("STATUS 087: Bypass mode only affects operation while in type 1. Switch to manual mode for desired function with types 2 and 3."));
              bypassDispatchMessage = true;
            }
          }
        }
        else {
          bypassDispatchMessage = false;
        }
      }
    }
  }
}


void dispatch() {
  if (dispatching == false) {
    digitalWrite(keyboardDispatch, HIGH);
    Serial.println(F("STATUS 010: TRAIN IS LEAVING STATION AREA"));
    delay(10);
    digitalWrite(keyboardDispatch, LOW);
    dispatching = true;
  }

}




//////////////////////////////////////












void eStopPress() {
  unsigned long currentMillis = millis();

  if (keyboardEstopSent == false) {
    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    // Serial.println("keyboardEstop = High (error)");
    digitalWrite(keyboardEstop, LOW);
    // Serial.println("keyboardEstop = low (error)");
    keyboardEstopSent = true;
  }

  if (rideStopPressed == false && rideStopLedOn == false) {
    rideStopLedOn = true;
    digitalWrite(rideStopLed, HIGH);
  }

  // if (digitalRead(eStopButton) == HIGH) {
  if (eStopReset == false) {
    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;
      if (digitalRead(troubleLed) == LOW) {
        digitalWrite(eStopLed, HIGH);
        digitalWrite(troubleLed, HIGH);
      }
      else {
        if (digitalRead(eStopButton) == HIGH) {
          digitalWrite(eStopLed, LOW);
        }
        digitalWrite(troubleLed, LOW);
        //  noTone(speakerPin);
      }
    }
    esrReset();
  }
  else {
    if (error == true) {
      errorReset();
    }
    else {
      if (started == false) {
        if (autoKeyswitchState == 0 || bypassed == true) {
          firstStartup();
        }
      }
    }
  }




  //}
  /* else {
     digitalWrite(eStopLed, HIGH);
     digitalWrite(troubleLed, LOW);
     digitalWrite(startLed, LOW);
     //noTone(speakerPin);
   }
   */

  if (startupLongTone == true && bypassed == false) {
    if (bypassKeyswitchState == 0) {
      bypassed = true;
    }
  }
}

void esrReset() {
  unsigned long restartMillis = millis();

  if (restartMillis - previousRestartMillis > shorterInterval) {
    previousRestartMillis = restartMillis;

    if ((eStopButtonState == HIGH) && ((functionEnableState == 0 || supervisorMode == true) && bypassKeyswitchState == 0) || (bypassKeyswitchState == 0 && booted == false)) {
      if (startButtonState == LOW) {
        if (startupHorn == true) {
          tone(speakerPin, 750);
        }
        esrResetButton++;
        // Serial.println(esrResetButton);
      }
      else {
        esrResetButton = 0;
      }

      if (digitalRead(startLed) == LOW) {
        digitalWrite(startLed, HIGH);

      }
      else {
        digitalWrite(startLed, LOW);
        if (startButtonState == LOW) {
          if (startupHorn == true) {
            tone(speakerPin, 350);
          }


        }
        else {
          noTone(speakerPin);
        }
      }
    }
    else {
      digitalWrite(startLed, LOW);
      noTone(speakerPin);
    }

  }
  if (esrResetButton == 15) {
    if (startupSerial == false && booted == false) {
      Serial.println(F("E-Stop Reset complete. Switch to AUTOMATIC MODE to continue Phase II startup."));
      Serial.println(F("Phase II startup: Extra Functions."));
    }
    else {
      if (supervisorMode == true) {
        Serial.println(F("[SUPERVISOR MODE]ESR Reset complete. Switch to MANUAL MODE to continue startup."));
      }
      else {
        Serial.println(F("ESR Reset complete. Enable FUNCTION ENABLE and switch to MANUAL MODE to continue startup"));
      }
    }
    digitalWrite(eStopLed, LOW);
    digitalWrite(startLed, LOW);
    digitalWrite(restraintsLed, LOW);
    digitalWrite(acknowledgeLed, LOW);
    eStopReset = true;
    esrResetButton = 0;
    noTone(speakerPin);
  }
}

void errorReset() {

  if (errorSerialMessage1 == false) {
    Serial.println(F("Error Reset: Press ACKNOWLEDGE button to display error code & message."));
    errorSerialMessage1 = true;
  }

  unsigned long currentMillis = millis();
  unsigned long restartMillis = millis();

  if (troubleButtonState == LOW && troubleSilenced == false) {
    troubleSilenced = true;
    noTone(speakerPin);
    Serial.println(F("Trouble alarm has been silenced."));
  }

  if (keyboardEstopSent == false) {
    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    //Serial.println("keyboardEstop = High (error)");
    digitalWrite(keyboardEstop, LOW);
    //Serial.println("keyboardEstop = low (error)");
    keyboardEstopSent = true;
  }

  if (rideStopPressed == false && rideStopLedOn == false) {
    rideStopLedOn = true;
    digitalWrite(rideStopLed, HIGH);
  }

  if (bypassKeyswitchState != 0 && autoKeyswitchState != 0 && (functionEnableState == 0 || supervisorMode == true) && eStopButtonState == HIGH) {
    if (errorAck == false) {
      acknowledgeError();
    }
    else {

      if (troubleResetButton == 3) {
        Serial.println(F("Error cleared & reset."));
        Serial.println(F("Switch to desired operations mode then press and hold RIDE START to complete startup."));
        error = false;
        errorMessage = false;
        errorAck = false;
        troubleSilenced = false;
        errorOcc = true;
        noTone(speakerPin);
        digitalWrite(troubleLed, LOW);
        errorCode = 0;
      }

      if (currentMillis - previousMillis > shortInterval) {
        previousMillis = currentMillis;

        if (troubleButtonState == LOW) {
          digitalWrite(troubleLed, LOW);
          if (startupHorn == true) {
            tone(speakerPin, 800);
          }
          troubleResetButton++;
          //0 Serial.println(troubleResetButton);

        }
        else {
          troubleResetButton = 0;
        }

        if (digitalRead(troubleLed) == LOW) {
          digitalWrite(troubleLed, HIGH);
          if (troubleAlarm == true && troubleSilenced == false) {
            tone(speakerPin, 800);
          }
        }
        else {
          digitalWrite(troubleLed, LOW);
          noTone(speakerPin);
        }
      }
    }
  }
  else {

    troubleResetButton = 0;
    digitalWrite(acknowledgeLed, LOW);

    if (restartMillis - previousRestartMillis > longInterval) {
      previousRestartMillis = restartMillis;
      if (digitalRead(troubleLed) == LOW) {
        digitalWrite(troubleLed, HIGH);
        if (troubleAlarm == true && troubleSilenced == false) {
          tone(speakerPin, 800);
        }
        //   tone(speakerPin, 800);
      }
      else {
        digitalWrite(troubleLed, LOW);
        noTone(speakerPin);
      }
    }
  }
}







void acknowledgeError() {
  unsigned long currentMillis = millis();

  if (acknowledgeButtonState == 0) {
    Serial.println(F("Error acknowledged."));
    Serial.println(F("Press and hold TROUBLE button to clear error."));
    digitalWrite(acknowledgeLed, LOW);
    errorMessage = false;
    errorAck = true;
    errorOcc = true;
  }
  else {

    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;
      if (digitalRead(troubleLed) == LOW) {
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(troubleLed, HIGH);
        if (troubleAlarm == true && troubleSilenced == false) {
          tone(speakerPin, 800);
        }
      }
      else {
        digitalWrite(acknowledgeLed, HIGH);
        digitalWrite(troubleLed, LOW);
        noTone(speakerPin);
      }
    }
  }
  if (errorMessage == false) {
    switch (errorCode) {

      case 0:
        Serial.println(F("No Error"));
        break;

      case 010:
        Serial.println(F("ERROR 010: PANEL KEYED OFF"));
        Serial.println(F("PANEL POWER KEYSWITCH turned to OFF."));
        errorMessage = true;
        break;

      case 021:
        Serial.println(F("ERROR 021: RIDE TIMEOUT"));
        Serial.println(F("No input from panel for 100 seconds while in auto mode."));
        errorMessage = true;
        break;

      case 27:
        Serial.println(F("ERROR 099: E-STOP PRESSED"));
        Serial.println(F("MAIN OP PANEL E-STOP was pressed"));
        errorMessage = true;
        break;

      case 036:
        Serial.println(F("ERROR 036: TREVOR ERROR"));
        Serial.println(F("ACKNOWLEDGE BUTTON PUSHED WHILE IN AUTO MODE"));
        Serial.println(F("Acknowledge button was pressed too many times while in auto mode"));
        errorMessage = true;
        break;

      case 061:
        Serial.println(F("ERROR 061: FUNCTION NOT FOUND"));
        Serial.println(F("FUNCTION ENABLE was ENABLED and restraint button was pressed. No function on RESTRAINT PUSHBUTTON found!"));
        errorMessage = true;
        break;

      case 063:
        Serial.println(F("ERROR 063: RESTRAINTS TOGGLED WHILE FLOOR LOWERED"));
        Serial.println(F("Restraints button was pressed while floor was lowered. Cannot change restraint state."));
        errorMessage = true;
        break;

      case 064:
        Serial.println(F("ERROR 064: RESTRAINTS TOGGLED WHILE CHASSIS UP"));
        Serial.println(F("Restraints button was pressed while chassis was up. Cannot change restraint state."));
        errorMessage = true;
        break;

      case 066:
        Serial.println(F("ERROR 066: GATES OPENED WHILE FLOOR LOWERED"));
        Serial.println(F("GATES switch was switched to OPEN while floor lowered. Cannot open air gates."));
        errorMessage = true;
        break;

      case 067:
        Serial.println(F("ERROR 067: GATES OPENED WHILE CHASSIS UP"));
        Serial.println(F("GATES switch was switched to OPEN while floor lowered. Cannot open air gates."));
        errorMessage = true;
        break;

      case 072:
        Serial.println(F("ERROR 072: AIRGATE ERROR"));
        Serial.println("Gates switch was in on position when trying to dispatch while in AUTO mode OR gate switch was changed to ON while train was dispatching.");
        errorMessage = true;
        break;

      case 073:
        Serial.println(F("ERROR 073: FUNCTION NOT FOUND"));
        Serial.println(F("Function enable was ENABLED and dispatch buttons were pressed.  No function on DISPATCH PUSHBUTTON LEFT or DISPATCH PUSHBUTTON RIGHT found!"));
        errorMessage = true;
        break;

      case 100:
        Serial.println(F("ERROR 100: RIDE TIMEOUT"));
        Serial.println(F("Panel was not used for 7 minutes. Ride stopped for safety."));
        errorMessage = true;
        break;

      case 600:
        Serial.println(F("ERROR 600: Communication with Due Lost."));
        Serial.println(F("This error cannot be cleared normally. Please reset main board and recconnect boards."));
        errorMessage = true;
        break;

    }
  }




}

void manualIndicator() {
  unsigned long manualMillis = millis();

  if (functionEnableState != 0) {
    if (autoKeyswitchState != 0) {
      digitalWrite(manualLed, HIGH);
    }
    else {
      digitalWrite(manualLed, LOW);
    }
  }
  else {
    if (autoKeyswitchState == 0) {
      if (manualMillis - previousManualMillis > 500) {
        previousManualMillis = manualMillis;
        if (digitalRead(manualLed) == LOW) {
          digitalWrite(manualLed, HIGH);
        }
        else {
          digitalWrite(manualLed, LOW);
        }
      }
    }
    else {
      if (manualMillis - previousManualMillis > 250) {
        previousManualMillis = manualMillis;
        if (digitalRead(manualLed) == LOW) {
          digitalWrite(manualLed, HIGH);
        }
        else {
          digitalWrite(manualLed, LOW);
        }
      }
    }
  }
}



//FOLLOWING IS FOR BOOTUP:
void bootSeq() {
  if (eStopButtonState == LOW && bootupEstopMessage == false && eStopTested == true) {
    eStopTested = false;
    digitalWrite(eStopLed, HIGH);
    Serial.println(F("E-STOP Pressed during Phase II or Phase III startup."));
    if (functionEnableState != 0) {
      Serial.println(F("Startup sequence was interupted by an E-STOP. Must restart starting sequence."));
      Serial.println(F("Pullup FUNCTION ENABLE while in MANUAL MODE if this was a mistake."));
      lampTested = false;
      eStopReset = false;
      extraFunctionsChoose = false;
      extraFunctionsDone = false;
      startupLongTone = false;
      started = false;
    }
    else {
      Serial.println(F("Switch to BYPASS MODE and press ACKNOWLEDGE to resume startup."));
    }
    digitalWrite(eStopLed, HIGH);
    bootupEstopMessage = true;
  }
  if (powerKeyswitchState == 0) {

    digitalWrite(powerLed, HIGH);
    bootKeyoffMessage1 = false;
    bootKeyoff = false;
    if (bootupMessage == false) {
      delay(500);
      //  Matt Stetson

      Serial.println(F("Switch to MANUAL MODE to begin Phase I startup."));
      bootupMessage = true;
    }
    if (lampTested == false) {
      if (autoKeyswitchState != 0 && bypassKeyswitchState != 0) {
        lampTest();
      }
      else {
        ledsOff();
        bootupEstopMessage = false;
        digitalWrite(acknowledgeLed, LOW);
        noTone(speakerPin);
        speakerTest = 0;
      }
    }
    else {
      if (eStopTested == false) {
        if (bootKeyoffMessage2 == false) {
          Serial.println(F("Switch to BYPASS MODE to reset ESR."));
          bootKeyoffMessage2 = true;
        }
        if (bypassKeyswitchState == 0) {
          eStopTest();
        }
        else {
          digitalWrite(eStopLed, LOW);
          digitalWrite(acknowledgeLed, LOW);
        }
      }
      else {
        if (eStopReset == false) {
          if (eStopButtonState == HIGH) {
            esrReset();
          }
          else {
            digitalWrite(startLed, LOW);
          }
        }
        else {
          if (extraFunctionsChoose == false) {
            extraFunctionsBypass();
          }
          else {
            if (extraFunctionsDone == false) {
              extraFunctions();
            }
            else {
              if (startupLongTone == false) {
                if (autoKeyswitchState != 0 && bypassKeyswitchState != 0 && eStopButtonState == HIGH) {
                  firstStartupLongTone();
                }
                else {
                  digitalWrite(startLed, LOW);
                }
              }
              else {
                if (started == false) {
                  if (bypassed == true) {
                    firstStartup();
                  }
                  else {
                    digitalWrite(startLed, LOW);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    digitalWrite(powerLed, LOW);
    ledsOff();
    digitalWrite(acknowledgeLed, LOW);
    startupButton = 0;
    noTone(speakerPin);
    speakerTest = 0;
    eStopTested = false;
    eStopReset = false;
    bootKeyoff = true;
    bootKeyoffMessage2 = false;
    bootKeyoffMessage3 = false;
    if (bootKeyoffMessage1 == false && lampTested == true) {
      Serial.println(F("CONTROL PANEL was turned OFF during startup. Turn CONTROL PANEL ON to resume startup."));
      bootKeyoffMessage1 = true;
    }
  }
  if (startupLongTone == true && bypassed == false) {
    if (bypassKeyswitchState == 0) {
      bypassed = true;
    }
  }
}

void lampTest() {
  if (lampTestSerialMessage == false) {
    Serial.println(F("Phase I startup: LAMP TEST: Ensure all lamps function correctly."));
    Serial.println(F("Press ACKNOWLEDGE to confirm all lamps function properly and continue startup."));
    lampTestSerialMessage = true;
  }

  if (functionEnableState == LOW && rideStopButtonState == LOW) {
    Serial.println(F("ATTENTION: E-STOP TEST, E-STOP RESET, & WARNING HORN have been skipped. Please restart if this was a mistake."));
    booted == true;
    lampTested = true;
    eStopTested = true;
    eStopReset = true;
    startupLongTone = true;
    rideStartBypass = true;
    startupSerial = true;
    extraFunctionsChoose = true;
    ledsOff();
  }

  if (functionEnableState == LOW && lampFunctionMessage == false) {
    Serial.println(F("EXTRA FUNCTIONS: "));
    Serial.println(F("Switch ENTRANCE GATES to OPEN to turn all lamps solid."));
    Serial.println(F("Press and hold TROUBLE for STARTUP HORN test."));
    Serial.println(F("Press RIDE STOP to bypass startup => MAINTAINENCE ONLY!"));
    lampFunctionMessage = true;
  }

  if (acknowledgeButtonState == LOW && gateSwitchState == 0) {
    ledsOff();
    noTone(speakerPin);
    digitalWrite(acknowledgeLed, LOW);
    lampTested = true;
    Serial.println(F("LAMP TEST completed. Switch to BYPASS MODE to continue Phase I startup."));
    speakerTest = 100;
  }



  unsigned long currentMillis = millis();
  unsigned long currentRestartMillis = millis();

  if (currentRestartMillis - previousRestartMillis > 50) {
    previousRestartMillis = currentRestartMillis;

    speakerTest = 1 + speakerTest;

    if (speakerTest > 1000) {
      speakerTest = 0;
    }

    if (functionEnableState == LOW && eStopButtonState == HIGH && powerKeyswitchState == 0 && autoKeyswitchState != 0 && bypassKeyswitchState != 0 && troubleButtonState == LOW) {
      tone(speakerPin, speakerTest);
      digitalWrite(troubleLed, HIGH);
    }
    else {
      noTone(speakerPin);
      speakerTest = 0;
      noTone(speakerPin);
    }

  }
  if (gateSwitchState != 0 && functionEnableState == LOW) {
    digitalWrite(dispatchRightLed, HIGH);
    digitalWrite(eStopLed, HIGH);
    digitalWrite(startLed, HIGH);
    digitalWrite(restraintsLed, HIGH);
    digitalWrite(troubleLed, HIGH);
    digitalWrite(manualLed, HIGH);
    digitalWrite(dispatchLeftLed, HIGH);
    digitalWrite(rideStopLed, HIGH);
    digitalWrite(acknowledgeLed, HIGH);

  }
  else {
    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;

      if (digitalRead(dispatchRightLed) == LOW) {
        digitalWrite(dispatchRightLed, HIGH);
        digitalWrite(eStopLed, HIGH);
        digitalWrite(startLed, HIGH);
        digitalWrite(restraintsLed, HIGH);
        digitalWrite(manualLed, HIGH);
        digitalWrite(dispatchLeftLed, HIGH);
        if (functionEnableState == 0) {
          digitalWrite(rideStopLed, LOW);
          if (troubleButtonState != LOW) {
            digitalWrite(troubleLed, LOW);
          }
        }
        else {
          digitalWrite(rideStopLed, HIGH);
          digitalWrite(troubleLed, HIGH);
        }
        digitalWrite(acknowledgeLed, LOW);

      }
      else {
        digitalWrite(dispatchRightLed, LOW);
        digitalWrite(eStopLed, LOW);
        digitalWrite(startLed, LOW);
        digitalWrite(restraintsLed, LOW);
        digitalWrite(manualLed, LOW);
        digitalWrite(dispatchLeftLed, LOW);
        if (functionEnableState == 0) {
          digitalWrite(rideStopLed, HIGH);
          digitalWrite(troubleLed, HIGH);
        }
        else {
          digitalWrite(rideStopLed, LOW);
          if (troubleButtonState != LOW || functionEnableState == 0) {
            digitalWrite(troubleLed, LOW);
          }
        }
        digitalWrite(acknowledgeLed, HIGH);

      }
    }
  }
}

void eStopTest() {
  if (eStopTestSerialMessage == false) {
    Serial.println(F("Phase I Startup: E-STOP Test"));
    Serial.println(F("Press E-STOP to continue."));
    eStopTestSerialMessage = true;
  }
  if (bootKeyoff == true) {
    if (bootKeyoffMessage3 == false) {
      Serial.println(F("Press ACKNOWLEDGE; CONTROL PANEL was turned OFF during startup."));
      bootKeyoffMessage3 = true;
    }
  }
  unsigned long currentMillis = millis();

  if (eStopTestedPressed == true && digitalRead(eStopButton) == HIGH) {
    if (eStopTestSerialTwo == false) {
      Serial.println(F("E-Stop test successful. Press ACKNOWLEDGE button to continue."));
      eStopTestSerialTwo = true;
    }
    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;

      if (digitalRead(eStopLed) == LOW) {
        digitalWrite(eStopLed, HIGH);
        digitalWrite(acknowledgeLed, LOW);

      }
      else {
        digitalWrite(eStopLed, LOW);
        digitalWrite(acknowledgeLed, HIGH);
      }
    }

    if (acknowledgeButtonState == LOW) {
      Serial.println(F("E-STOP TEST completed."));
      Serial.println(F("Phase I startup complete."));
      Serial.println(F("Phase II Startup: E-Stop Reset."));
      Serial.println(F("Press and hold RIDE START to reset ESR loop."));
      digitalWrite(eStopLed, HIGH);
      digitalWrite(acknowledgeLed, LOW);
      bootupEstopMessage = false;
      eStopTested = true;
    }
  }


  if (digitalRead(eStopButton) == HIGH) {
    if (eStopTestedPressed == false) {
      if (currentMillis - previousMillis > shortInterval) {
        previousMillis = currentMillis;

        if (digitalRead(eStopLed) == LOW) {
          digitalWrite(eStopLed, HIGH);
          //digitalWrite(acknowledgeLed, LOW);

        }
        else {
          digitalWrite(eStopLed, LOW);
          //digitalWrite(acknowledgeLed, HIGH);
        }
      }
    }

  }
  else {
    if (eStopSerialMessage == false) {
      Serial.println(F("Pull up E-STOP to continue."));
      eStopSerialMessage = true;
    }
    eStopTestedPressed = true;
    digitalWrite(eStopLed, HIGH);
    digitalWrite(acknowledgeLed, LOW);
  }
}

void firstStartup() {
  if (startupSerial == false) {
    Serial.println(F("////////////////////////////////////////"));
    Serial.println(F("Phase III Startup: LIFT & RIDE START."));
    Serial.println(F("Press and hold RIDE START to complete Phase III startup and start ride."));
    Serial.println(F("WARNING: RIDE UNITS MAY BEGIN MOVING. ALL COMPONENTS WILL BECOME POWERED."));
    Serial.println(F("////////////////////////////////////////"));
    startupSerial = true;
  }
  unsigned long currentMillis = millis();

  if (acknowledgeButtonState == LOW) {
    digitalWrite(acknowledgeLed, HIGH);
  }
  else {
    if (functionEnableState != 0 || extraFunctionsDone == true) {
      digitalWrite(acknowledgeLed, LOW);
    }
  }
  // ||1



  if (eStopButtonState == HIGH) {
    if (functionEnableState == 0 && extraFunctionsDone == false && errorOcc == false) {
      extraFunctions();
    }
    else {
      digitalWrite(troubleLed, LOW);
      digitalWrite(restraintsLed, LOW);
      digitalWrite(dispatchLeftLed, LOW);
      digitalWrite(dispatchRightLed, LOW);
      if (currentMillis - previousMillis > longInterval) {
        previousMillis = currentMillis;

        if (startButtonState == LOW) {
          if (rideStartBypass == true || (bypassKeyswitchState == 0 && acknowledgeButtonState == LOW)) {
            startupButton = 10;
          }
          startupButton++;
          if (startupHorn == true) {
            tone(speakerPin, 400);
          }
          if (warningSerial == false) {
            Serial.println(F("WARNING: THE RIDE IS NOW STARTING."));
            warningSerial = true;
          }
        }
        else {
          startupButton = 0;
          warningSerial = false;
          noTone(speakerPin);
        }


        if (digitalRead(startLed) == LOW) {
          digitalWrite(startLed, HIGH);
        }

        else {
          digitalWrite(startLed, LOW);
          //digitalWrite(acknowledgeLed, LOW);
          digitalWrite(dispatchRightLed, LOW);
          if (startButtonState == LOW) {
            noTone(speakerPin);
            //tone(speakerPin, 600);
          }
          else {
            noTone(speakerPin);
          }
        }
      }
    }
  }
  else {
    digitalWrite(startLed, LOW);
    startupButton = 0;
    warningSerial = false;
  }

  if (startupButton >= 10)
  {
    digitalWrite(eStopLed, LOW);
    digitalWrite(startLed, HIGH);
    digitalWrite(restraintsLed, HIGH);
    digitalWrite(rideStopLed, LOW);
    digitalWrite(acknowledgeLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    digitalWrite(dispatchLeftLed, LOW);
    started = true;
    booted = true;
    eStopPressed = false;
    restraintsLocked = true;
    eStopped = false;
    rideStopped = false;
    bypassed = false;
    rideStartBypass = false;
    rideStopPressed = false;
    rideStopLedOn = false;
    startupSerial = false;
    extraFunctionsDone = false;
    errorOcc = false;
    warningSerial = false;
    bypassMessage = false;
    extraOpFunctionSerial = false;
    timeOut = 0;

    //if(keyboardEstopSent == false) {

    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    // Serial.println("keyboardEstop = High");
    digitalWrite(keyboardEstop, LOW);
    // Serial.println("keyboardEstop = low");

    keyboardEstopSent = false;
    // }

    startupButton = 0;
    Serial.println(F("RIDE START has been completed. Startup sequence complete. Switch to desired operations mode or enable FUNCTION ENABLE for further options."));
    /*   if (noLimitsStarted == false) {
         Serial.println("#S|STARTNL2|[]#");
         noLimitsStarted = true;
       }
       */

  }
}

void firstStartupLongTone() {
  if (longToneSerialMessage == false) {
    Serial.println(F("Phase II Startup: RIDE AREA ALERT."));
    Serial.println(F("All gates must be secured and ride areas free of personnel to continue!"));
    Serial.println(F("Press and hold RIDE START to initiate WARNING ALERT."));
    longToneSerialMessage = true;
  }
  unsigned long currentMillis = millis();
  unsigned long restartMillis = millis();

  //formerly 50
  if (startupButton == 70) {
    Serial.println(F("Phase II Startup Complete. Switch to BYPASS MODE then to desired operations mode to complete startup."));
    noTone(speakerPin);
    digitalWrite(startLed, LOW);
    digitalWrite(acknowledgeLed, LOW);
    digitalWrite(manualLed, LOW);
    startupButton = 0;
    startupLongTone = true;
  }

  if (currentMillis - previousMillis > 100) {
    previousMillis = currentMillis;

    if (startButtonState == LOW) {
      digitalWrite(startLed, LOW);
      if (longWarningSerial == false) {
        Serial.println(F("ENSURE ALL RIDE AREAS ARE CLEAR OF PERSONNEL AND LOW POINT GATES ARE SECURED!"));
        longWarningSerial = true;
      }
      if (startupHorn == true) {
        tone(speakerPin, 500);
      }

      startupButton++;
    }
    else {
      startupButton = 0;
      longWarningSerial = false;
      digitalWrite(acknowledgeLed, LOW);
      digitalWrite(manualLed, LOW);
    }

    if (digitalRead(startLed) == LOW) {
      digitalWrite(startLed, HIGH);
    }
    else {
      digitalWrite(startLed, LOW);
      noTone(speakerPin);
    }
  }
}



void ledsOff() {
  digitalWrite(dispatchLeftLed, LOW);
  digitalWrite(dispatchRightLed, LOW);
  digitalWrite(eStopLed, LOW);
  digitalWrite(rideStopLed, LOW);
  digitalWrite(startLed, LOW);
  digitalWrite(restraintsLed, LOW);
  digitalWrite(troubleLed, LOW);
  digitalWrite(manualLed, LOW);
}

void extraFunctionsBypass() {
  unsigned long currentMillis = millis();
  if (autoKeyswitchState == 0) {
    if (functionEnableState == 0) {
      if (functionBypassSerial == false) {
        Serial.println(F("Press ACKNOWLEDGE to continue startup or RIDE STOP for extra functions."));
        functionBypassSerial = true;
      }
      if (acknowledgeButtonState == LOW) {
        extraFunctionsChoose = true;
        extraFunctionsDone = true;
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(restraintsLed, LOW);
        Serial.println(F("Extra Functions selected and complete. Switch to MANUAL MODE to continue Phase II startup."));
      }
      else {

        if (rideStopButtonState == LOW) {
          extraFunctionsChoose = true;
          digitalWrite(acknowledgeLed, LOW);
          digitalWrite(rideStopLed, LOW);
          Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
          Serial.println(F("EXTRA FUNCTIONS: [PAGE 1 of 2]"));
          Serial.println(F("Press LOCK RESTRAINTS to toggle AUTO MODE RESTRAINT UNLOCK"));
          Serial.println(F("Press TROUBLE RESET for TROUBLE ALARM TOGGLE"));
          Serial.println(F("Press RIDE START for STARTUP HORN TOGGLE"));
          Serial.println(F("Press DISPATCH RIGHT to toggle BUTTON DISPATCH"));
          Serial.println(F("Press DISPATCH LEFT for TYPE SELECT"));
          Serial.println(F("Press ACKNOWLEDGE to EXIT and continue startup."));
          Serial.println(F("Press FUNCTION ENABLE for list of current settings."));
          Serial.println(F("Switch ENTRANCE GATES to OPEN for PAGE TWO of extra functions."));
          Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
        }
      }
      if (currentMillis - previousMillis > longInterval) {
        previousMillis = currentMillis;
        if (digitalRead(rideStopLed) == LOW) {
          digitalWrite(acknowledgeLed, LOW);
          digitalWrite(rideStopLed, HIGH);
        }
        else {
          digitalWrite(acknowledgeLed, HIGH);
          digitalWrite(rideStopLed, LOW);
        }
      }

    }
    else {
      if (extraFunctionBypassSerial == false) {
        Serial.println(F("Press ACKNOWLEDGE to continue startup or pullup FUNCTION ENABLE for extra functions."));
        extraFunctionBypassSerial = true;
      }
      digitalWrite(rideStopLed, LOW);
      if (acknowledgeButtonState == LOW) {
        extraFunctionsChoose = true;
        extraFunctionsDone = true;
        digitalWrite(acknowledgeLed, LOW);
        Serial.println(F("Extra Functions selected and complete. Switch to MANUAL MODE to continue Phase II startup."));
      }

      if (currentMillis - previousMillis > longInterval) {
        previousMillis = currentMillis;
        if (digitalRead(acknowledgeLed) == LOW) {
          digitalWrite(acknowledgeLed, HIGH);
        }
        else {
          digitalWrite(acknowledgeLed, LOW);
        }
      }
    }
  }
}

void extraFunctions() {
  unsigned long currentMillis = millis();



  if (gateSwitchState == 0) {

    if (extraOpFunctionSerial == false) {
      Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
      Serial.println(F("EXTRA FUNCTIONS: [PAGE 1 of 2]"));
      Serial.println(F("Press LOCK RESTRAINTS to toggle AUTO MODE RESTRAINT UNLOCK"));
      Serial.println(F("Press TROUBLE RESET for TROUBLE ALARM TOGGLE"));
      Serial.println(F("Press RIDE START for STARTUP HORN TOGGLE"));
      Serial.println(F("Press DISPATCH RIGHT to toggle BUTTON DISPATCH"));
      Serial.println(F("Press DISPATCH LEFT for TYPE SELECT"));
      Serial.println(F("Press ACKNOWLEDGE to EXIT and continue startup."));
      Serial.println(F("Press FUNCTION ENABLE for list of current settings."));
      Serial.println(F("Switch ENTRANCE GATES to OPEN for PAGE TWO of extra functions."));
      Serial.println(F("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"));
      extraOpFunctionSerial = true;
      functionsMessage2 = false;
    }

    if (troubleAlarm == true) {
      digitalWrite(troubleLed, HIGH);
    }
    if (startupHorn == true) {
      digitalWrite(startLed, HIGH);
    }
    if (singleDispatch == true) {
      digitalWrite(dispatchRightLed, HIGH);
    }
    if (autoRestraints == true) {
      digitalWrite(restraintsLed, HIGH);
    }

    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;



      if (digitalRead(dispatchLeftLed) == LOW) {
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(dispatchLeftLed, HIGH);

        if (troubleAlarm == false) {
          digitalWrite(troubleLed, HIGH);
        }
        if (startupHorn == false) {
          digitalWrite(startLed, HIGH);
        }
        if (singleDispatch == false) {
          digitalWrite(dispatchRightLed, HIGH);
        }
        if (autoRestraints == false) {
          digitalWrite(restraintsLed, HIGH);
        }
      }
      else {
        if (troubleAlarm == false) {
          digitalWrite(troubleLed, LOW);
        }
        if (startupHorn == false) {
          digitalWrite(startLed, LOW);
        }
        if (singleDispatch == false) {
          digitalWrite(dispatchRightLed, LOW);
        }
        if (autoRestraints == false) {
          digitalWrite(restraintsLed, LOW);
        }
        digitalWrite(acknowledgeLed, HIGH);
        digitalWrite(dispatchLeftLed, LOW);
      }
    }


    if (troubleButtonState == LOW) {
      if (troubleAlarm == false) {
        troubleAlarm = true;
        Serial.println(F("Trouble alarm is now ON"));
        tone(speakerPin, 800);
      }
      else {
        if (troubleAlarm == true) {
          troubleAlarm = false;
          Serial.println(F("Trouble alarm is now OFF"));
        }
      }
      delay(500);
      noTone(speakerPin);
    }

    if (startButtonState == LOW) {
      if (startupHorn == false) {
        startupHorn = true;
        Serial.println(F("Startup horn is now ON"));
        tone(speakerPin, 500);

      }
      else {
        if (startupHorn == true) {
          startupHorn = false;
          Serial.println(F("Startup horn is now OFF"));
        }
      }
      delay(500);
      noTone(speakerPin);
    }

    if (dispatchRightButtonState == LOW) {
      if (singleDispatch == false) {
        singleDispatch = true;
        Serial.println(F("While in type 1, only DISPATCH RIGHT needed to send train."));
      }
      else {
        if (singleDispatch == true) {
          singleDispatch = false;
          Serial.println(F("While in type 1, both DISPATCH buttons needed for dispatch."));
        }
      }
      delay(500);
    }

    if (dispatchLeftButtonState == LOW) {
      if (typeOneSwitchState != 0 && typeThreeSwitchState != 0) {
        typeSelected = 2;
        flyerLocked = false;
      }
      else {
        if (typeOneSwitchState == 0) {
          typeSelected = 1;
          floorLowered = false;
          flyerLocked = false;
        }
        else {
          if (typeThreeSwitchState == 0) {
            typeSelected = 3;
            floorLowered = false;
          }
        }
      }
      Serial.print(F("TYPE  "));
      Serial.print(typeSelected);
      Serial.print(F("  SELECTED: "));

      switch (typeSelected) {
        case 0:
          Serial.println(F("ERROR: UNKNOWN TYPE."));
          break;

        case 1:
          Serial.print(F(" Normal coaster"));
          break;

        case 2:
          Serial.print(F(" Inverted, floorless, or dive coaster"));
          break;

        case 3:
          Serial.print(F(" Flying coaster"));
          break;
      }
      Serial.println(F(" "));
      delay(500);
    }

    if (restraintsButtonState == LOW) {
      if (autoRestraints == false) {
        autoRestraints = true;
        Serial.println(F("Restraints will open automatically while in AUTO MODE"));
      }
      else {
        if (autoRestraints == true) {
          autoRestraints = false;
          Serial.println(F("Restraints will not open automatically while in AUTO MODE"));
        }
      }
      delay(500);
    }
  }
  else {
    digitalWrite(restraintsLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    digitalWrite(dispatchLeftLed, LOW);
    digitalWrite(troubleLed, LOW);

    if (functionsMessage2 == false) {
      Serial.println(F("EXTRA FUNCTIONS: [PAGE 2 of 2]"));
      Serial.println(F("Press RIDE START to toggle SUPERVISOR MODE"));
      Serial.println(F("Press LOCK RESTRAINTS for a list of current settings"));
      Serial.println(F("Switch ENTRANCE GATES to CLOSE for PAGE 1 of functions."));
      functionsMessage2 = true;
      extraOpFunctionSerial = false;
    }

    if (supervisorMode == true) {
      digitalWrite(startLed, HIGH);
    }

    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;



      if (digitalRead(acknowledgeLed) == LOW) {
        digitalWrite(acknowledgeLed, HIGH);
        if (supervisorMode == false) {
          digitalWrite(startLed, LOW);
        }

      }
      else {
        digitalWrite(acknowledgeLed, LOW);
        if (supervisorMode == false) {
          digitalWrite(startLed, HIGH);
        }
      }
    }

    if (startButtonState == LOW) {
      if (supervisorMode == false) {
        supervisorMode = true;
        Serial.println(F("SUPERVISOR MODE is now ENABLED!"));
        Serial.println(F("E-STOPS & ERRORS MAY BE RESET WITHOUT FUNCTION ENABLE/MAINT."));
      }
      else {
        if (supervisorMode == true) {
          supervisorMode = false;
          Serial.println(F("SUPERVISOR MODE is now DISABLED!"));
          Serial.println(F("E-STOPS & ERRORS REQUIRE FUNCTION ENABLE/MAINT. TO BE RESET."));
        }
      }
      delay(500);
    }




  }






  /*
    if(functionEnableState != 0) {
      if(functionsListed == false) {
        if(autoRestraints == true) {
          Serial.println("Restraints will open automatically while in AUTO MODE");
        }
        else{
          Serial.println("Restraints will not open automatically while in AUTO MODE");
        }
         Serial.print("TYPE  ");
   Serial.print(typeSelected);
   Serial.print("  SELECTED: ");

   switch (typeSelected) {
     case 0:
       Serial.println("ERROR: UNKNOWN TYPE.");
       break;

     case 1:
       Serial.print(" Normal coaster");
       break;

     case 2:
       Serial.print(" Inverted, floorless, or dive coaster");
       break;

     case 3:
       Serial.print(" Flying coaster");
       break;
   }
   if(singleDispatch == true) {
    Serial.println("While in type 1, only DISPATCH RIGHT needed to send train.");
   }
   else {
     Serial.println("While in type 1, both DISPATCH buttons needed to send train.");
   }





    functionsListed = true;
    }
   }
  else {
  functionsListed = false;
  }
  */


  if (acknowledgeButtonState == LOW) {
    digitalWrite(restraintsLed, LOW);
    digitalWrite(troubleLed, LOW);
    digitalWrite(startLed, LOW);
    digitalWrite(acknowledgeLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    digitalWrite(dispatchLeftLed, LOW);
    extraOpFunctionSerial = false;

    Serial.println(F("CURRENT SETTINGS: "));
    if (troubleAlarm == true) {
      Serial.println(F("Trouble Alarm: ENABLED"));
    } else {
      Serial.println(F("Trouble Alarm: DISABLED"));
    }
    if (startupHorn == true) {
      Serial.println(F("Startup Horn: ENABLED"));
    } else {
      Serial.println(F("Startup Horn: DISABLED"));
    }
    if (singleDispatch == true) {
      Serial.println(F("Single Button Dispatch: ENABLED"));
    } else {
      Serial.println(F("Single Button Dispatch: DISABLED"));
    }
    if (autoRestraints == true) {
      Serial.println(F("Restraints will open automatically when train parks."));
    } else {
      Serial.println(F("Restraints will NOT open automatically when train parks."));
    }
    Serial.print(F("TYPE SELECTED: "));
    Serial.print(typeSelected);
    if (supervisorMode == true) {
      Serial.println(F("SUPERVISOR MODE: ENABLED"));
    } else {
      Serial.println(F("SUPERVISOR MODE: DISABLED"));
    }







    if (extraFunctionContinueSerial == false) {
      Serial.println(F("Extra Functions selected and complete. Switch to MANUAL MODE to continue Phase II startup."));
      extraFunctionContinueSerial = true;
    }
    extraFunctionsDone = true;

  }








}
