# Digidrumduino
A midi Steelpan (Steeldrum) Synth,
built using an Arduino microcontroller.
By Caesar Passee
(pitchoilcan at gmail dot com)
2016

# Parts and components
 ......//(clarification needed)
# How it works
 ......//(clarification needed)
 
#                       MIDI :   Musical Instrument Digital Interface
  Start with Ardunio Knock code
  
  Read 48 Analog pins for input from piezo sensors and trigger an event based on set conditions 
  
  Prints and auto analyse what you play to LCD and via serial port.
  
  Outputs to midi module or computer
  
  Outputs to onboard GM wavetable, builtin and external speakers
  
  LED note and activity sensor (one per note)
  
  Pedal inputs for sustain, reverb, etc and for changing voice/instrument types
  
  Tuning is key! This is where it gets intersting 
  The steeldrum is the only musical instrument that I can think of on which the tones are not 
  arranged in linear oder. 
  TO BE CONTINUED.....
  
  You've heard it said that music is all numbers. Midi notes are numbered 0-126, 60 being middle C.
  likewise volume is scaled from 0-127. Frequencies in Hertz. Differnt members of the steeldrum familly uses tone cycles
  One notable characteristic Cycles or cyclics is that they end where they began.
  
#   Requirments 
   pitches.h // https://github.com/arduino/Arduino/blob/master/build/shared/examples/02.Digital/toneMelody/pitches.h
   
   (other libraries)
   
   Adafruit_MCP23017 // Port expander //
   
   MusicPlayer.h  // VS1053 //
   
   LiquidCrystal.h // LCD //
   
   MIDI.h // MiDI-IN  //
   
   EEPROM.h  //  Memory //
   
   Wire.h // I2C //
   
   SD.h> // VS1053's SD card
   
   SPI.h // VS1053 //
# Build your own
 ......//(clarification needed)
#  The sensors (scalability i.e. up to 48)
  
  Tunability (variable tone cycles)
  Adjustabe input sensitivity. 
 
 Stay tuned!
# Contribute 
