//  Control Panel Generation 3 Version 2 Revision 1 (3.2.1)
//  Last Updated: 11/21/2014
//  Matt Stetson

const int manualLed = 27;
const int autoKeyswitch = 22;
const int bypassKeyswitch = 23;
const int powerKeyswitch = 24;
const int eStopLed = 42;
const int eStopButton = 44;
const int acknowledgeButton = 26;
const int startLed = 33;
const int gateSwitch = 30;
const int restraintsButton = 37;
const int startButton = 32;
const int dispatchRightButton = 48;
const int powerLed = 28;
const int restraintsLed = 29;
const int acknowledgeLed = 25;
const int dispatchRightLed = 49;
const int dispatchLeftLed = 51;
const int dispatchLeftButton = 50;
const int functionEnable = 43;
const int troubleLed = 40;
const int troubleButton = 41;
const int speakerPin = 12;
const int rideStopButton = 47;
const int rideStopLed = 46;
const int typeOneSwitch = 38;
const int typeThreeSwitch = 39;

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

boolean noLimitsStarted = false;

boolean gateOpen = false;
boolean restraintsOpen = false;

boolean dispatchPressed = false;
boolean resetPressed = false;
boolean eStopPressed = false;
boolean powerOn = false;

boolean booted = false;
boolean lampTested = false;
boolean eStopTested = false;
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
  //initialize the serial port
  Serial.begin(9600);
  // initialize the LED pin as an output:
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
  // put your main code here, to run repeatedly:

  // read the state of the pushbutton value:
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
    bootSeq();
  }
  else {
    if (powerKeyswitchState == 0) {
      digitalWrite(powerLed, HIGH);
      poweredOn();
      rideStop();
      manualIndicator();
      /*
            if (autoKeyswitchState != 0 && bypassKeyswitchState != 0) {
              digitalWrite(manualLed, HIGH);
            }
            else {
              digitalWrite(manualLed, LOW);
            }
            */
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
        Serial.println("MAIN OP PANEL: POWER KEY switched to OFF.");
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
        Serial.println("keyboardEstop = High (error)");
        digitalWrite(keyboardEstop, LOW);
        Serial.println("keyboardEstop = low (error)");
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
  if (timeOut == 100) {
    //error = true;
    started = false;
    //ledsOff();
    //errorCode = 021;
    digitalWrite(dispatchLeftLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    timeOut = 0;

  }

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

      if (keyboardEstopSent == false) {
        digitalWrite(keyboardEstop, HIGH);
        delay(10);
        Serial.println("keyboardEstop = High (error)");
        digitalWrite(keyboardEstop, LOW);
       Serial.println("keyboardEstop = low (error)");
        keyboardEstopSent = true;
      }

      digitalWrite(dispatchLeftLed, LOW);
      digitalWrite(dispatchRightLed, LOW);
      digitalWrite(startLed, LOW);
      digitalWrite(restraintsLed, LOW);
      digitalWrite(troubleLed, LOW);
      digitalWrite(manualLed, LOW);

      Serial.println("MAIN OP PANEL E-STOP PUSHBUTTON PRESSED");
      Serial.println("Switch to BYPASS MODE and enable FUNCTION ENABLE to allow ESR RESET");
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
    if (functionEnableState != 0 || (bypassKeyswitchState != 0 && autoKeyswitchState != 0)) {
      if (restraintsPressed == false) {
        restraintsPressed = true;
        postDispatch = false;

        if (restraintsLocked == false) {
          restraintsLocked = true;
          digitalWrite(restraintsLed, HIGH);
          Serial.println("Restraints Locked.");
          digitalWrite(keyboardCloseRestraints, HIGH);
          // Serial.println("close restraints keyboard");
          digitalWrite(keyboardCloseRestraints, LOW);
        }
        else {
          restraintsLocked = false;
          digitalWrite(restraintsLed, LOW);
          Serial.println("Restraints Unlocked.");
          digitalWrite(keyboardOpenRestraints, HIGH);
          // Serial.println("open restraints keyboard");
          digitalWrite(keyboardOpenRestraints, LOW);
        }
      }
    }
    else {
      error = true;
      started = false;
      errorAck = false;
      ledsOff();
      errorCode = 061;
      Serial.println("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error");
    }
  }
  else {
    restraintsPressed = false;
  }


}

void gate() {
  unsigned long restartMillis = millis();

  if (gateSwitchState != 0) {

    if (gatePressed == false) {
      gatePressed = true;

      if (gateOpen == false) {
        gateOpen = true;
        Serial.println("Air gates open. Close gates to dispatch train.");
        digitalWrite(keyboardOpenGates, HIGH);
        //  Serial.println("open gates keyboard");
        digitalWrite(keyboardOpenGates, LOW);
      }
      else {
        gateOpen = false;
        Serial.println("Air gates closing.");
        digitalWrite(keyboardCloseGates, HIGH);
        //  Serial.println("close gates keyboard");
        digitalWrite(keyboardCloseGates, LOW);
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
  unsigned long ackMillis = millis();
  
if (acknowledgeButtonState == LOW) {
  timeOut = 0;
  if (autoKeyswitchState == 0) { 
      digitalWrite(acknowledgeLed, HIGH);
      if (acknowledgeCount == false) {
        acknowledgePress++;
        //Serial.println(acknowledgePress);
        acknowledgeCount = true;
        previousAckMillis = ackMillis;
      }
    }
}
    else {
      digitalWrite(acknowledgeLed, LOW);
      acknowledgeCount = false;
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
      Serial.println("MAIN OP RIDE STOP PRESSED.");
      Serial.println("PRESS AND HOLD RIDE START TO START RIDE.");

      if (keyboardEstopSent == false) {
        keyboardEstopSent = true;
        digitalWrite(keyboardEstop, HIGH);
        delay(10);
        Serial.println("keyboardEstop = High (ride stop)");
        digitalWrite(keyboardEstop, LOW);
        Serial.println("keyboardEstop = low (ride stop) ");

      }

      if (bypassKeyswitchState == 0) {
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
  if ((gateSwitchState == 0 && functionEnableState != 0) || (autoKeyswitchState != 0 && bypassKeyswitchState != 0) || (bypassKeyswitchState == 0)) {

    preDispatchMethod();

    if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
      digitalWrite(dispatchLeftLed, HIGH);
      digitalWrite(dispatchRightLed, HIGH);
      digitalWrite(restraintsLed, LOW);
      dispatchingTime++;
      // Serial.println(dispatchingTime);
      restraintsLocked = false;
      timeOut = 0;

    }
    else {
      dispatching = false;
      //previousDispatchMillis = dispatchMillis;
      //digitalWrite(keyboardDispatch, LOW);


    }
    if (restraintsLocked == true || (autoKeyswitchState != 0 && bypassKeyswitchState != 0)) {
      if (currentMillis - previousMillis > longInterval) {
        previousMillis = currentMillis;
        if (digitalRead(dispatchLeftLed) == LOW) {
          digitalWrite(dispatchLeftLed, HIGH);
          digitalWrite(dispatchRightLed, HIGH);
          if (autoKeyswitchState == 0) {
            timeOut++;
            if (timeOut > 80) {
              digitalWrite(acknowledgeLed, HIGH);
              Serial.print("The Ride will timeout in: ");
              Serial.print(200 - countDown);
              Serial.print(" seconds.");
              Serial.println(" ");
            }
          }
        }
        else {
          digitalWrite(dispatchLeftLed, LOW);
          digitalWrite(dispatchRightLed, LOW);
          if(timeOut > 80) {
           digitalWrite(acknowledgeLed, LOW); 
          }
        }
      }
    }
    else {
      if (dispatching == false) {
        digitalWrite(dispatchLeftLed, LOW);
        digitalWrite(dispatchRightLed, LOW);
      }
    }



  }
  else {
    if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
      if (gateSwitchState != 0) {
        error = true;
        started = false;
        errorAck = false;
        ledsOff();
        errorCode = 072;
        Serial.println("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error");
      }
      else {
        if (functionEnableState == 0) {
          error = true;
          started = false;
          errorAck = false;
          ledsOff();
          errorCode = 073;
          Serial.println("Switch to MANUAL MODE and enable FUNCTION ENABLE to clear error");
        }
      }
    }
    digitalWrite(dispatchLeftLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
    timeOut = 0;
  }

  if (dispatching == false && (dispatchingTime > 10) && autoKeyswitchState == 0) {

    dispatchingTime = 0;
    Serial.println("POST DISPATCH");
    postDispatchMethod();

  }

}


void postDispatchMethod() {
  //TYPE 1: Regular Coasters
  //TYPE 2: Inverted Coasters/Dive Machines/Floorless
  //TYPE 3: Flying Coaster
  if (badDispatch == false && dispatching == false) {

    if (typeOneSwitchState == 0) {
      Serial.println("type 1");
      restraintsLocked = false;
      digitalWrite(restraintsLed, LOW);
      Serial.println("restraints unlocked post dispatch");
      digitalWrite(keyboardOpenRestraints, HIGH);
      Serial.println("open restraints keyboard post dispatch");
      digitalWrite(keyboardOpenRestraints, LOW);

    }
    else if (typeOneSwitchState != 0 && typeThreeSwitchState != 0) {
      //floor
      Serial.println("type 2");
      //restraints:
      restraintsLocked = false;
      digitalWrite(restraintsLed, LOW);
      Serial.println("restraints unlocked post dispatch");
      digitalWrite(keyboardOpenRestraints, HIGH);
      Serial.println("open restraints keyboard post dispatch");
      digitalWrite(keyboardOpenRestraints, LOW);
    }
    else if (typeThreeSwitchState == 0) {
      //flyer lock/unlock
      Serial.println("type 3");
      if (flyerLocked == false) {
        Serial.println("type 3");
        digitalWrite(keyboardUnlockFlyer, HIGH);
        Serial.println("unlock flyer - post");
        digitalWrite(keyboardUnlockFlyer, LOW);
        flyerLocked = true;
      }
      else {
        flyerLockedTime++;
        Serial.println(flyerLockedTime);
      }

      if (flyerLockedTime > 1100) {
        restraintsLocked = false;
        digitalWrite(restraintsLed, LOW);
        Serial.println("restraints unlocked post dispatch");
        digitalWrite(keyboardOpenRestraints, HIGH);
        Serial.println("open restraints keyboard post dispatch");
        digitalWrite(keyboardOpenRestraints, LOW);
        flyerLocked = false;
        flyerLockedTime = 0;
      }




      //restraints:
      restraintsLocked = false;
      digitalWrite(restraintsLed, LOW);
      Serial.println("restraints unlocked post dispatch");
      digitalWrite(keyboardOpenRestraints, HIGH);
      Serial.println("open restraints keyboard post dispatch");
      digitalWrite(keyboardOpenRestraints, LOW);

    }
    else {
      Serial.println("type switch not found");
    }

  }
  else {
    Serial.println("badDispatch!");
  }







}

void preDispatchMethod() {
  unsigned long currentPreDispatchMillis = millis();

  if (typeOneSwitchState == 0) {
    if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
      //type one
      // dispatch
      if (dispatching == false) {
        Serial.println("type 1");
        Serial.println("dispatching pre");
        dispatching = true;
        digitalWrite(keyboardDispatch, HIGH);
        Serial.println("dispatch keyboard pre");
        digitalWrite(keyboardDispatch, LOW);
      }
    }

  }
  else if (typeOneSwitchState != 0 && typeThreeSwitchState != 0) {
    //lower floor
    //dispatch

    if (dispatching == false) {
      if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
        Serial.println("type 2");
        Serial.println("dispatching pre");
        dispatching = true;
        digitalWrite(keyboardDispatch, HIGH);
        Serial.println("dispatch keyboard pre dsipach");
        digitalWrite(keyboardDispatch, LOW);
      }
      else {
        //raise floor
        Serial.println("raise floor");
      }
    }

  }
  else if (typeThreeSwitchState == 0) {
    //lock flyer
    //dispatch

    if (dispatching == false) {
      if (dispatchLeftButtonState == LOW && dispatchRightButtonState == LOW) {
        if (flyerLocked == false) {
          Serial.println("type 3");
          digitalWrite(keyboardLockFlyer, HIGH);
          Serial.println("lock flyer - pre");
          Serial.println("lock flyer - pre");
          digitalWrite(keyboardLockFlyer, LOW);
          flyerLocked = true;
          badDispatch = true;
        }
        else {
          flyerLockedTime++;
          Serial.println(flyerLockedTime);
        }

        if (flyerLockedTime > 1200) {
          Serial.println("dispatching pre");
          badDispatch = false;
          dispatching = true;
          digitalWrite(keyboardDispatch, HIGH);
          Serial.println("dispatch keyboard pre");
          digitalWrite(keyboardDispatch, LOW);
          flyerLocked = false;
          flyerLockedTime = 0;
        }
      }
      else {
        //unlock flyer
        if (badDispatch == true) {
          Serial.println("unlock flyer - bad dispatch");
          digitalWrite(keyboardUnlockFlyer, HIGH);
          Serial.println("Unlock flyer - pre");
          digitalWrite(keyboardUnlockFlyer, LOW);
          badDispatch = false;
          flyerLocked = false;
          flyerLockedTime = 0;
        }
      }
    }
  }
}











//////////////////////////////////////












void eStopPress() {
  unsigned long currentMillis = millis();

  if (keyboardEstopSent == false) {
    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    Serial.println("keyboardEstop = High (error)");
    digitalWrite(keyboardEstop, LOW);
    Serial.println("keyboardEstop = low (error)");
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

        // tone(speakerPin, 800);
      }
      else {
        if (digitalRead(eStopButton) == HIGH) {
          digitalWrite(eStopLed, LOW);
        }


        digitalWrite(troubleLed, LOW);
        // noTone(speakerPin);
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

    if ((eStopButtonState == HIGH) && (functionEnableState == 0 && bypassKeyswitchState == 0) || (bypassKeyswitchState == 0 && booted == false)) {
      if (startButtonState == LOW) {
        if (functionEnableState == LOW && gateSwitchState == HIGH) {
          noTone(speakerPin);
          digitalWrite(acknowledgeLed, LOW);
          digitalWrite(restraintsLed, LOW);
        }
        else {
          tone(speakerPin, 750);
        }
        esrResetButton++;
        // Serial.println(esrResetButton);

      }
      else {
        esrResetButton = 0;
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(restraintsLed, LOW);
      }

      if (digitalRead(startLed) == LOW) {
        digitalWrite(startLed, HIGH);

      }
      else {
        digitalWrite(startLed, LOW);
        if (startButtonState == LOW) {
          if (functionEnableState == LOW && gateSwitchState == HIGH) {
            noTone(speakerPin);
            digitalWrite(acknowledgeLed, HIGH);
            digitalWrite(restraintsLed, HIGH);
          }
          else {
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
    if (startupSerial == false) {
      Serial.println("E-Stop Reset complete. Switch to MANUAL MODE to continue Phase II Startup.");
    }
    else {
      Serial.println("ESR Reset complete. Enable FUNCTION ENABLE and switch to MANUAL MODE to continue E-STOP RESET");
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
    Serial.println("Error Reset: Press ACKNOWLEDGE button to display error code & message.");
    errorSerialMessage1 = true;
  }

  unsigned long currentMillis = millis();
  unsigned long restartMillis = millis();

  if (keyboardEstopSent == false) {
    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    Serial.println("keyboardEstop = High (error)");
    digitalWrite(keyboardEstop, LOW);
    Serial.println("keyboardEstop = low (error)");
    keyboardEstopSent = true;
  }

  if (rideStopPressed == false && rideStopLedOn == false) {
    rideStopLedOn = true;
    digitalWrite(rideStopLed, HIGH);
  }

  if (bypassKeyswitchState != 0 && autoKeyswitchState != 0 && functionEnableState == 0 && eStopButtonState == HIGH) {
    if (errorAck == false) {
      acknowledgeError();
    }
    else {

      if (troubleResetButton == 3) {
        Serial.println("Error cleared & reset. Press and hold RIDE START to complete startup.");
        error = false;
        errorMessage = false;
        errorAck = false;
        noTone(speakerPin);
        digitalWrite(troubleLed, LOW);
        errorCode = 0;
      }

      if (currentMillis - previousMillis > shortInterval) {
        previousMillis = currentMillis;

        if (troubleButtonState == LOW) {
          digitalWrite(troubleLed, LOW);
          tone(speakerPin, 800);
          troubleResetButton++;
          //0 Serial.println(troubleResetButton);

        }
        else {
          troubleResetButton = 0;
        }

        if (digitalRead(troubleLed) == LOW) {
          digitalWrite(troubleLed, HIGH);
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

    if (restartMillis - previousRestartMillis > longInterval) {
      previousRestartMillis = restartMillis;
      if (digitalRead(troubleLed) == LOW) {
        digitalWrite(troubleLed, HIGH);
        //   tone(speakerPin, 800);
      }
      else {
        digitalWrite(troubleLed, LOW);
        //  noTone(speakerPin);
      }
    }
  }
}







void acknowledgeError() {
  unsigned long currentMillis = millis();

  if (acknowledgeButtonState == 0) {
    Serial.println("Error acknowledged.");
    Serial.println("Press and hold TROUBLE button to clear error.");
    digitalWrite(acknowledgeLed, LOW);
    errorMessage = false;
    errorAck = true;
  }
  else {

    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;
      if (digitalRead(troubleLed) == LOW) {
        digitalWrite(acknowledgeLed, LOW);
        digitalWrite(troubleLed, HIGH);
      }
      else {
        digitalWrite(acknowledgeLed, HIGH);
        digitalWrite(troubleLed, LOW);
      }
    }
  }
  if (errorMessage == false) {
    switch (errorCode) {

      case 0:
        Serial.println("No Error");
        break;

      case 010:
        Serial.println("ERROR 010: PANEL KEYED OFF");
        Serial.println("PANEL POWER KEYSWITCH turned to OFF.");
        errorMessage = true;
        break;

      case 021:
        Serial.println("ERROR 021: RIDE TIMEOUT");
        Serial.println("No input from panel for 100 seconds while in auto mode.");
        errorMessage = true;
        break;

      case 27:
        Serial.println("ERROR 099: E-STOP PRESSED");
        Serial.println("MAIN OP PANEL E-STOP was pressed");
        errorMessage = true;
        break;

      case 036:
        Serial.println("ERROR 036: TREVOR ERROR");
        Serial.println("ACKNOWLEDGE BUTTON PUSHED WHILE IN AUTO MODE");
        Serial.println("Acknowledge button was pressed too many times while in auto mode");
        errorMessage = true;
        break;

      case 061:
        Serial.println("ERROR 061: FUNCTION NOT FOUND");
        Serial.println("FUNCTION ENABLE was ENABLED and restraint button was pressed. No function on RESTRAINT PUSHBUTTON found!");
        errorMessage = true;
        break;

      case 072:
        Serial.println("ERROR 072: AIRGATE ERROR");
        Serial.println("Gates switch was in on position when trying to dispatch while in AUTO mode OR gate switch was changed to ON while train was dispatching.");
        errorMessage = true;
        break;

      case 073:
        Serial.println("ERROR 073: FUNCTION NOT FOUND");
        Serial.println("Function enable was ENABLED and dispatch buttons were pressed.  No function on DISPATCH PUSHBUTTON LEFT or DISPATCH PUSHBUTTON RIGHT found!");
        errorMessage = true;
        break;

      case 600:
        Serial.println("ERROR 600: Communication with Due Lost.");
        Serial.println("This error cannot be cleared normally. Please reset main board and recconnect boards.");
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
}













//FOLLOWING IS FOR BOOTUP:
void bootSeq() {
  if (eStopButtonState == LOW && bootupEstopMessage == false && eStopReset == true) {
    eStopTested = false;
    Serial.println("E-STOP Pressed during Phase II or Phase III startup.");
    Serial.println("Switch to BYPASS MODE and press ACKNOWLEDGE to resume startup.");
    digitalWrite(eStopLed, HIGH);
    bootupEstopMessage = true;
  }
  if (powerKeyswitchState == 0) {
    digitalWrite(powerLed, HIGH);
    if (bootupMessage == false) {
      Serial.println("Switch to MANUAL MODE to begin Phase I startup.");
      bootupMessage = true;
    }
    if (lampTested == false) {
      if (autoKeyswitchState != 0 && bypassKeyswitchState != 0) {
        lampTest();
      }
      else {
        ledsOff();
        digitalWrite(acknowledgeLed, LOW);
        noTone(speakerPin);
        speakerTest = 0;
      }
    }
    else {
      if (eStopTested == false) {
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
  else {
    digitalWrite(powerLed, LOW);
    ledsOff();
    digitalWrite(acknowledgeLed, LOW);
    startupButton = 0;
    noTone(speakerPin);
    speakerTest = 0;
    eStopTested = false;
  }
  if (startupLongTone == true && bypassed == false) {
    if (bypassKeyswitchState == 0) {
      bypassed = true;
    }
  }
}

void lampTest() {
  if (lampTestSerialMessage == false) {
    Serial.println("Phase I startup: LAMP TEST: Press ACKNOWLEDGE button to continue.");
    lampTestSerialMessage = true;
  }

  if (functionEnableState == LOW && dispatchLeftButtonState == LOW) {
    Serial.println(functionEnableState);
    Serial.println("boot bypass");
    booted == true;
    lampTested = true;
    eStopTested = true;
    eStopReset = true;
    startupLongTone = true;
    rideStartBypass = true;
    startupSerial = true;
    ledsOff();
  }

  if (acknowledgeButtonState == LOW) {
    ledsOff();
    noTone(speakerPin);
    digitalWrite(acknowledgeLed, LOW);
    lampTested = true;
    Serial.println("LAMP TEST completed. Switch to BYPASS MODE to continue Phase I startup.");
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
    }
    else {
      noTone(speakerPin);
      speakerTest = 0;
      noTone(speakerPin);
    }

  }

  if (currentMillis - previousMillis > longInterval) {
    previousMillis = currentMillis;

    if (digitalRead(troubleLed) == LOW) {
      digitalWrite(dispatchLeftLed, HIGH);
      digitalWrite(dispatchRightLed, HIGH);
      digitalWrite(eStopLed, HIGH);
      digitalWrite(startLed, HIGH);
      digitalWrite(restraintsLed, HIGH);
      digitalWrite(troubleLed, HIGH);
      digitalWrite(manualLed, HIGH);
      digitalWrite(rideStopLed, HIGH);
      digitalWrite(acknowledgeLed, LOW);

    }
    else {
      digitalWrite(dispatchLeftLed, LOW);
      digitalWrite(dispatchRightLed, LOW);
      digitalWrite(eStopLed, LOW);
      digitalWrite(startLed, LOW);
      digitalWrite(restraintsLed, LOW);
      digitalWrite(troubleLed, LOW);
      digitalWrite(manualLed, LOW);
      digitalWrite(rideStopLed, LOW);
      digitalWrite(acknowledgeLed, HIGH);

    }
  }

}

void eStopTest() {
  if (eStopTestSerialMessage == false) {
    Serial.println("Phase I Startup: E-STOP Test");
    Serial.println("Press E-STOP to continue.");
    eStopTestSerialMessage = true;
  }
  unsigned long currentMillis = millis();

  if (eStopTestedPressed == true && digitalRead(eStopButton) == HIGH) {
    if (eStopTestSerialTwo == false) {
      Serial.println("E-Stop test successful. Press ACKNOWLEDGE button to continue.");
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
      Serial.println("E-STOP TEST completed.");
      Serial.println("Phase I startup complete.");
      Serial.println("Phase II Startup: E-Stop Reset.");
      Serial.println("Press and hold RIDE START to reset ESR.");
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
      Serial.println("Pull up E-STOP to continue.");
      eStopSerialMessage = true;
    }
    eStopTestedPressed = true;
    digitalWrite(eStopLed, HIGH);
    digitalWrite(acknowledgeLed, LOW);
  }
}

void firstStartup() {
  if (startupSerial == false) {
    Serial.println("////////////////////////////////////////");
    Serial.println("Phase III Startup: LIFT & RIDE START.");
    Serial.println("Press and hold RIDE START to complete Phase III startup and start ride.");
    Serial.println("WARNING: RIDE UNITS MAY BEGIN MOVING. ALL COMPONENTS WILL BECOME POWERED.");
    Serial.println("////////////////////////////////////////");
    startupSerial = true;
  }
  unsigned long currentMillis = millis();

  if (acknowledgeButtonState == LOW) {
    digitalWrite(acknowledgeLed, HIGH);
  }
  else {
    digitalWrite(acknowledgeLed, LOW);
  }
  // ||



  if (eStopButtonState == HIGH) {
    if (currentMillis - previousMillis > longInterval) {
      previousMillis = currentMillis;

      if (startButtonState == LOW) {
        if (rideStartBypass == true || (bypassKeyswitchState == 0 && acknowledgeButtonState == LOW)) {
          startupButton = 10;
        }
        startupButton++;
        tone(speakerPin, 400);
        Serial.print("WARNING: THE RIDE IS NOW STARTING. ");
        Serial.print(startupButton);
        Serial.println(" ");
      }
      else {
        startupButton = 0;
        noTone(speakerPin);
      }


      if (digitalRead(startLed) == LOW) {
        digitalWrite(startLed, HIGH);
      }

      else {
        digitalWrite(startLed, LOW);
        digitalWrite(acknowledgeLed, LOW);
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
  else {
    digitalWrite(startLed, LOW);
    startupButton = 0;
  }

  if (startupButton >= 10)
  {
    digitalWrite(eStopLed, LOW);
    digitalWrite(startLed, HIGH);
    digitalWrite(restraintsLed, HIGH);
    digitalWrite(rideStopLed, LOW);
    digitalWrite(acknowledgeLed, LOW);
    digitalWrite(dispatchRightLed, LOW);
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
    startupSerial = true;

    //if(keyboardEstopSent == false) {

    digitalWrite(keyboardEstop, HIGH);
    delay(10);
    Serial.println("keyboardEstop = High");
    digitalWrite(keyboardEstop, LOW);
     Serial.println("keyboardEstop = low");

    keyboardEstopSent = false;
    // }

    startupButton = 0;
    Serial.println("RIDE START has been completed. Startup sequence complete. Switch to desired operations mode or enable FUNCTION ENABLE for further options.");
    /*   if (noLimitsStarted == false) {
         Serial.println("#S|STARTNL2|[]#");
         noLimitsStarted = true;
       }
       */

  }
}

void firstStartupLongTone() {
  if (longToneSerialMessage == false) {
    Serial.println("Phase II Startup: RIDE AREA ALERT.");
    Serial.println("Press and hold RIDE START to initiate WARNING ALERT.");
    longToneSerialMessage = true;
  }
  unsigned long currentMillis = millis();
  unsigned long restartMillis = millis();

  //formerly 50
  if (startupButton == 40) {
    Serial.println("Phase II Startup Complete. Switch to BYPASS MODE then to desired operations mode to complete startup.");
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
      if (functionEnableState == LOW && gateSwitchState == HIGH) {
        noTone(speakerPin);
        digitalWrite(acknowledgeLed, HIGH);
        digitalWrite(manualLed, HIGH);
      }
      else {
        tone(speakerPin, 500);
      }
      startupButton++;
    }
    else {
      startupButton = 0;
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

void checkConnectionMega() {

}









