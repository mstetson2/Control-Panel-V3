// constants used here to set pin numbers:
const int dispatchButton = 2;
const int eStopButton = 3;
const int resetButton = 4;
const int gateSwitch = 5;
const int restraintSwitch = 6;
const int keySwitch = 7;
const int dispatchLed = 8;
const int eStopLed = 9;
const int resetLed = 10;
const int powerLed = 11;
const int troubleLed = 12;
// PIN 13

// variables will change:
int dispatchButtonState = 0;
int eStopButtonState = 0;
int resetButtonState = 0;
int gateSwitchState = 0;
int restraintSwitchState = 0;
int keySwitchState = 0;

int lastGateSwitchState = 1;
int lastRestraintSwitchState = 1;

//Blinking led setup:
//stores last time LED was updated
long previousMillis = 0;
//intervals
long longInterval = 1000;
long shortInterval = 500;


boolean noLimitsStarted = false;

boolean gatesOpen = false;
boolean restraintsOpen = false;

boolean dispatchPressed = false;
boolean resetPressed = false;
boolean eStopPressed = false;
boolean eStopSent = false;
boolean gateSwitchTurned = false;
boolean restraintSwitchTurned = false;
boolean powerOn = false;

void setup() {
  //initialize the serial port
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(dispatchLed, OUTPUT);
  pinMode(eStopLed, OUTPUT);
  pinMode(resetLed, OUTPUT);
  pinMode(powerLed, OUTPUT);
  pinMode(troubleLed, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(dispatchButton, INPUT);  
  pinMode(eStopButton, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(gateSwitch, INPUT);
  pinMode(restraintSwitch, INPUT);
  pinMode(keySwitch, INPUT);

  //initialize the buttonPin as output
  digitalWrite(dispatchButton, HIGH);
  digitalWrite(eStopButton, HIGH);
  digitalWrite(resetButton, HIGH);
  digitalWrite(gateSwitch, HIGH);
  digitalWrite(restraintSwitch, HIGH);
  digitalWrite(keySwitch, HIGH);
}

void loop(){
  // read the state of the pushbutton value:
  dispatchButtonState = digitalRead(dispatchButton);
  eStopButtonState = digitalRead(eStopButton);
  resetButtonState = digitalRead(resetButton);
  gateSwitchState = digitalRead(gateSwitch);
  restraintSwitchState = digitalRead(restraintSwitch);
  keySwitchState = digitalRead(keySwitch);

  unsigned long currentMillis = millis(); 
  ////////////////////////////////////////////////////// 
  //             Lighting Effects                     // 
  ////////////////////////////////////////////////////// 



  //dispatch button blink
  if(restraintsOpen != false && eStopPressed == false && gatesOpen != false && powerOn == true) {
    if(currentMillis - previousMillis > longInterval) { 
      previousMillis = currentMillis;

      if (digitalRead(dispatchLed) == LOW){ 
        digitalWrite(dispatchLed, HIGH); 
      } 
      else { 
        digitalWrite(dispatchLed, LOW);    
      }     
    }  
  }
  else {
    if(digitalRead(dispatchLed) == HIGH) {
      digitalWrite(dispatchLed, LOW);   
    }
  }

  //key switch
  if(keySwitchState == 0){
    digitalWrite(powerLed, HIGH);
    powerOn = true;
    if(noLimitsStarted == false && resetButtonState == HIGH && dispatchButtonState == LOW) {
      Serial.println("#S|STARTNOLIM|[]#");
      noLimitsStarted = true;
      for(int i=0;i<=3;i++){ 
        // Blink all lights 
        delay(shortInterval); 
        digitalWrite(powerLed, LOW); 
        delay(shortInterval); 
        digitalWrite(powerLed, HIGH);
      }
    }

  }
  else {
    powerOn = false;
    noLimitsStarted = false;
    //eStopPressed = true;

    if(currentMillis - previousMillis > longInterval) { 
      // save the last time you blinked the LED  
      previousMillis = currentMillis;    

      // if the LED is off turn it on and vice-versa: 
      if (digitalRead(powerLed) == LOW){ 
        digitalWrite(powerLed, HIGH); 
      } 
      else { 
        digitalWrite(powerLed, LOW);    
      } 
    }
  }
  
  //E-STOP
  
  
  
  
  
  
  
  
  
//normal operation buttons
  if(powerOn == true) {

    //dispatch button
    if(dispatchButtonState == LOW) {
      digitalWrite(dispatchLed, HIGH);
      if(dispatchPressed == false) {
        Serial.println("dispatchPressed");
        Serial.println("#S|SENDK|[0&{ENTER}]#");
        dispatchPressed = true;
      }
    }
    else {
      dispatchPressed = false;
    }

    //gate switch
    if(gateSwitchState == 0){
      gatesOpen = false;
    }
    else if(gateSwitchState == 1 && gatesOpen == false) {
      gatesOpen = true;
      Serial.println("gate change");
      Serial.println("#S|SENDK|[0&{F10}]#");
      delay(100);
    }

    //restraint switch
    if(restraintSwitchState == 0){
      restraintsOpen = false;
    }
    else if(restraintSwitchState == 1 && restraintsOpen == false) {
      restraintsOpen = true;
      Serial.println("restraints change");
      Serial.println("#S|SENDK|[0&{F9}]#");
      delay(100);
    }
  }





















}

