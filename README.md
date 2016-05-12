# Digidrumduino
A midi Steelpan (Steeldrum) Synth,
built using an Arduino microcontroller.
By Caesar Passee
(pitchoilcan at gmail dot com)
2016

# Parts and components

 up to 48 Input (Piezo) sensors (1 per note)
 
 up to 48 Note activity indicating LED's (1 per input sensor)
 
 MayhewLabs Mux shield
 
 MCP23017 - i2c 16 input/output port expander
 
 SparkFun MIDI Shield - MIDI-IN  . MIDI-OUT ports
 
 Arduino MP3 shield board with TF card - Headphones audio out , Micophone ib , micro-SD card
 
 HD44780 16*2 LCD
 
 8 ControlChange  pushbutton switches
 
 8 controlChange indicator LEDs (1 per CC pushbutton)
 
 Piezo buzzer/8ohm speaker output
 
 3 foot pedals (SUS and CC
 
 Volume control pot
 
 An Arduino Mega
 
# How it works
 ......//(clarification needed)
 
#                       MIDI :   Musical Instrument Digital Interface
  EPISODE: Start with Ardunio Knock code
  
  Read up to 48 Analog pins for input from piezo sensors and trigger an event based on set conditions ......//(clarification needed) Each note of the instrument is assiggned a TOUCH sensor, volocity is determind by how hard or softly you touch the sensor. 
  
  Prints and auto analyse what you play to LCD and via serial port.
  
  Outputs to midi module or computer
  
  Outputs to onboard GM wavetable, builtin and external speakers
  
  LED note and activity sensor (one per note)
  
  Pedal inputs for sustain, reverb, etc and for changing voice/instrument types
  
  Tuning is key! This is where it gets intersting 
#  Arrangement /Deveopment
  The steeldrum is the only musical instrument that I can think of on which the tones are not 
  arranged in linear oder. 
  TO BE CONTINUED.....
  
  You've heard it said that music is all numbers. Midi notes are numbered 0-126, 60 being middle C.
  likewise volume is scaled from 0-127. Frequencies in Hertz. Different members of the steeldrum familly use diferent tone cycles..........More info here......
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
 DIY instructions coming soon!
#  The sensors (scalability i.e. up to 48)

 Ingredients: (Per input sensor) 1 piezo , 1 resistor, 1 capacitor 1 schottky diode;
 
  Tunability (various (editable)tone cycles)
  
  Adjustabe input sensitivity. 
 
 Stay tuned!
