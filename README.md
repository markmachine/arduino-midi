# Arduino MIDI & CV Controller Library

This library enables MIDI I/O communications on the Arduino serial ports.

### Features
* Compatible with all Arduino boards (and clones with an AVR processor).
* Simple and fast way to send and receive every kind of MIDI message (including all System messages, SysEx, Clock, etc..).
* OMNI input reading (read all channels).
* Software Thru, with message filtering.

### Getting Started

1. Start coding:
 
   ```c++
    #include <MIDI.h>

    // Created and binds the MIDI interface to the default hardware Serial port
    MIDI_CREATE_DEFAULT_INSTANCE();

    void setup()
    {
        MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
    }

    void loop()
    {
        // Send note 42 with velocity 127 on channel 1
        MIDI.sendNoteOn(42, 127, 1);

        // Read incoming messages
        MIDI.read();
    }
    ```