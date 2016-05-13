# Digidrumduino
A MIDI (Digital) Steelpan (Steeldrum) (Synth),
built using an Arduino microcontroller.
By Caesar Passée
(pitchoilcan at gmail dot com)

Spring 2016

# Parts and components

 up to 48 INPUT (Piezo) sensors (1 per NOTE)
 
 up to 48 NOTE activity indicating LED's (1 per INPUT sensor)
 
 MayhewLabs Mux shield
 
 MCP23017 - i2c 16 INPUT/OUT port expander
 
 SparkFun MIDI Shield - MIDI-IN  . MIDI-OUT ports
 
 Arduino MP3 shield board with TF card - Headphones audio OUT , Microphone IN , micro-SD card
 
 HD44780 16*2 LCD
 
 8 ControlChange  pushbutton switches
 
 8 controlChange indicator LEDs (1 per CC pushbutton)
 
 Piezo buzzer/8ohm speaker OUTPUT
 
 3 foot pedals (SUS and CC )
 
 Volume control pot
 
 An Arduino Mega
 
# How it works
 Modern steeldrums have a maximum range of two OCTAVES, plus or minus a few NOTES (no more than five) 24+5. A pan (a.k.a steeldrum) with 48 notes? WTF! Oh the possibilties.
 
 A multiplexer or demultiplexer enables you to expand the in-and outputs on your Arduino board.
 
#                       MIDI :   Musical Instrument Digital Interface
  EPISODE: Start with Ardunio Knock code (how to use a Piezo element to detect vibration)
  
  
  A piezo is an electronic device that generates a voltage when it's physically deformed by a vibration, sound wave, or mechanical strain. Similarly, when you put a voltage across a piezo, it vibrates and creates a tone. Piezos can be used both to play tones and to detect tones. 
  
  
  READ up to 48 Analog pins for INPUT from PIEZO SENSORS and TRIGGER an EVENT (NOTE_ON NOTE_OFF) based on a SET CONDITIONS (STICK_ON,STICK_OFF).  Each NOTE of the instrument is assiggned a (PIEZO) TOUCH SENSOR, VELOCITY is determind by how hard or softly you TOUCH the SENSOR. 
  
  WRITE/Prints and auto analyse what you play (NOTES) (INPUT) to LCD and via serial port.
  
  WRITE/OUTPUT MIDI DATA to midi-module, midi-keybord or computer
  
  WRITE/OUTPUT AUDIO to onboard GM wavetable(vs1053b) via builtin and external speakers
  
  LED NOTE and activity sensor (one per NOTE)
  
  Pedal INPUT for SUSTAIN, REVERB, etc and for changing voice/instrument types
  
  --------------------------------------------------
  
  Tuning is key! This is where it gets interesting 
  
  --------------------------------------------------
#  Arrangement /Deveopment
  The steeldrum is the only musical instrument that I can think of on which the tones are not 
  arranged in linear oder. 
  TO BE CONTINUED....
  
  ---------------------------------------------------------------------------
  
  (1 NOTE at a time, = Melody, more than 1 NOTE a time = Harmony, Time = Rhythm;)   
  
  ----------------------------------------------------------------------------
  
  
  You've heard it said that music is all numbers. Midi notes are numbered 0-126, 60 being middle C.
  likewise volume is scaled from 0-127. Frequencies in Hertz..... 
  
  Different members of the steeldrum familly use diferent tone cycles.
  
  Cycles of fifths
  
  Cyces of fourths
  
  Cycles of thirds
  
  Cycles of seconds 
    
    Dividing an octave:
  One notable characteristic Cycles or cyclics is that they end where they began.
  
#   Requirments 
  Tone library // 
  
  A sound synthesizer (usually abbreviated as "synthesizer" or "synth", also spelled "synthesiser") is an electronic musical instrument that generates electric signals that are converted to sound through instrument amplifiers and loudspeakers or headphones. 

   pitches.h // https://github.com/arduino/Arduino/blob/master/build/shared/examples/02.Digital/toneMelody/pitches.h
   
   (other libraries)
   
   Adafruit_MCP23017 // Port expander //
   
   MusicPlayer.h  // VS1053 //
   
   LiquidCrystal.h // LCD //
   
   MIDI.h // MiDI-IN  //
   
   EEPROM.h  //  Memory // Electrically Erasable Programmable Read-Only Memory
   
   Wire.h // I2C // 
   
   SD.h> // VS1053's SD card
   
   SPI.h // VS1053 //
# Build your own
 DIY INPUT TRIGGERS
#  The sensors (scalability i.e. up to 48)

 Ingredients: (Per INPUT SENSOR) 1 PIEZO , 1 resistor, 1 capacitor 1 schottky diode;
 
  Tunability (various (editable)tone cycles)
  
  Adjustabe INPUT SENSIBILITY.
  
  -----------------------------
  
  Visual indicators
  
  ------------------------------
  ------------------------------
  
  Sampling capabiities 
  
  ---------------------------------
  
#  CONTRIB  | CORE-PRINCIPLES |  OTHER USE CASES | ADD-ONS

---------------------------------

Effects

---------------------------------
 
 Stay tuned!
