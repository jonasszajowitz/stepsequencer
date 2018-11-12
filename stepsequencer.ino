
int ledPins [4] = {3, 5, 7, 9};
int buttonPins [4] = {25, 26, 27, 28};
int tempo = 0;
int currentStep = 0;
unsigned long lastStepTime = 0;
boolean lastButtonState [4] = {LOW, LOW, LOW, LOW};
boolean buttonState[4] = {LOW, LOW, LOW, LOW};
boolean on[4] = {false, false, false, false};


void setup() {

  for (int i = 0; i < 4; i++) {
  pinMode(buttonPins[i], INPUT);
  pinMode(ledPins[i], OUTPUT);
  
  }
}
  
 void loop () {

  tempo = map(analogRead(A12), 0, 1023, 50, 1000);
  sequence(); 
  checkButtons(); 
  setLeds();
 
 }


 void sequence() {

  if (millis() > lastStepTime + tempo) {

  if (on[currentStep] == true) {
    usbMIDI.sendNoteOff(56, 0, 0);
  }
    currentStep++;

  if (currentStep > 3) {
    currentStep = 0;
  }

  if (on[currentStep] == true) {
    usbMIDI.sendNoteOn(56, 127, 0);
  }
    lastStepTime = millis();
  
  }
}

 void checkButtons() {
   
  for (int i = 0; i < 4; i++) {

    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPins[i]);

  if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
    on[i] = !on[i];
  
     }
   }
 }

 void setLeds() {
  
  for (int i = 0; i < 4; i++) {

    analogWrite(ledPins[currentStep], 50);
    if (on[i] == true) {
      analogWrite(ledPins[i], 200);
    } else if (on[i] == false) {
      analogWrite(ledPins[i], 0);
    
     }
   }
 }
