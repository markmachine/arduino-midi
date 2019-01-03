#include <MIDI.h>

byte clockPin = 25;
int clockCount = 0;
int clockDiv = 4;
int clockMult = 0;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  pinMode(clockPin, OUTPUT);
  if(clockCount==0){
    digitalWrite(clockPin, HIGH);
    clockCount = 1;
  }else {
    digitalWrite(clockPin, LOW);
  }
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleClock(handleClockPulse);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  Serial.println("My program is starting");

}

void loop() {
  MIDI.read();
}

bool clockMode = false;
void handleClockPulse(){
  clockMult++;
  if (clockMult % clockDiv == 0) {
    if (clockMode) {
      Serial.println("-- clock pulse");
    }

    clockMult = 0;
    if(clockCount==0){
      digitalWrite(clockPin, HIGH);
      clockCount = 1;
    }else {
      digitalWrite(clockPin, LOW);
    }
  }
}

void handleControlChange(byte channel, byte number, byte value) {
  printCCData(channel, number, value, "------------------- CC Controller Change");
}

void handlePitchBend(byte channel, int bend) {

}

void printCCData(byte channel, byte number, byte value, char msg[]) {
  Serial.print(msg);
  Serial.print(", ch:");
  Serial.print(channel);
  Serial.print(", number:");
  Serial.print(number);
  Serial.print(", value:");
  Serial.println(value);
}

void printNoteData(byte channel, byte note, byte velocity, char msg[]) {
  Serial.print(msg);
  Serial.print(", ch:");
  Serial.print(channel);
  Serial.print(", note:");
  Serial.print(note);
  Serial.print(", velocity:");
  Serial.println(velocity);
}

void handleNoteOn(byte channel, byte note, byte velocity){
  printNoteData(channel, note, velocity, "------------------- note on");
}

void handleNoteOff(byte channel, byte note, byte velocity){
  printNoteData(channel, note, velocity, "------------------- note off");
}