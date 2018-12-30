#include <MIDI.h>  // Add Midi Library

#define LED 13    // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder

 int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command

int ledState = LOW;

void setup() {
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
  MIDI.setHandleClock(MyClockHandler);
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}

void MyClockHandler(void) {
  if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LED, ledState);
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED,HIGH);  //Turn LED on
  MIDImessage(noteON, pitch, velocity);//turn note on
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED,LOW);  //Turn LED off
  MIDImessage(noteOFF, pitch, velocity);//turn note off
}
