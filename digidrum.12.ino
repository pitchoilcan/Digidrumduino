/*
Componets & Pins: 
      Multiplexing 2,3,4,5, +, -,
      MCP2317 I2C Port Expander 20,21 +, -, (For driving LEDS INDICAROTORS)
      Speaker or Piezo BUZZER OUT (Tone) 14
      Midi_Out: TX, +, -, MIDI_IN: RX,
      Audio vs1053 I/O 6,7 (8.2),(9, 10), 50,51,52, +, -,
      LCD 32.33.34.35.36.37,(38) +, -, 
      LEDS and Buttons 24.25.26.27.28.29.30.31.39,40,41,42,43,44,,45,46,47,48,
      Excptions, VS1053's DREQ has been modfied in library from pin 2 to pin 9 as 2 is being used by mux
      -------------------------------------------
      VS1053:         ARDUINO_MEGA:
      SCK  - 13<==========>52
      MISO - 12<==========>50
      MOSI - 11<==========>51
      DREQ -  2<==========>8
      ==================Midi Range==============
      (>0, <127,)
      Bass=    0-31
      Tenor=   32-63
      Alto=    64-95
      Sprano=  96-127
      =======================INTERVALS=====================
      I   = ROOT                                       |INVERSION
      0   = Tonic //    I                              |________________
      0-1 = (Semitone)  m2   //+1                      | 1-0=  M7th  
      0-2 = (WholeTone) M2  //SuperTonic               | 2-0=  m7th  
      0-3 = m3             // Mediant                  | 3-0=  M6th  
      0-4 = M3 (DiTone)   //  Mediant                  | 4-0=  m6th  
      0-5 = Perfect_4th, // Subdominant (Diatessaron)  | 5-0=  5th //Dominant
      0-6 = (Tritone)        #4th,  b5th               | 6-0=  Tri //+6
      0-7 = Perfect_5th //   Dominant (Diapente)       | 7-0=  4th  //SubDominant
      0-8 = m6         //    SubMediant                | 8-0=  M3
      0-9 = M6        //     SubMediant  #5 //(?b4?)   | 9-0=  m3
      0-10= m7th     //                                | 10-0= M2
      0-11= M7th    //       Leading Tone              | 11-0= semitone, m2
      0-12= Octave //----------------------------------| 12-0= Oct
      0-13= m9th  =minor2nd
      0-14= M9th  =Major2nd
      ===========================SIGNS==========================
      #, //Sharp  _b, //Flat   M, //Major  m, //minor
      Dim,  //  Aug,  //  7th, // Seventh (DominantSeventh), 5th, // 4th, // 
      (2nd), (3rd),  (6th), (7th),  (9th),  (10th), (11th), (12th),  (13th),
      I, // II, //  III,  //  IV,  // V, //  VI,  //   VII,  //
      added = append note to chord in upper register  // i.e. Interval number
      Bass_On/ = add note to chord in lowest register //In_the_bass, i.e. Note name
      suspended = ;
      omited = ;
      ============================HARMONIC_STACK==============
      Octaves = 0,12,34,36,48, // +12
                1,13,25,37,    // +12
      ===========================Chords & Triads==============          
      Minor_chords = 0,3,7,12
                     1,4,8,13
      Major_chords = 0,4,7,12
                     1,5,8,13
      Augmented_chords = 0,4,8,12  //+4
               // 1,x,x,x
               // 2,x,x,x
               // 3.x.x.x
      Diminished_chords = 0,3,6,9  //+3
               // 1.x.x.x
               // 2.x.x.x
      =======================Seconds==========
      42,44,46,48,50,52,54,56,58; // WHOLE-TONE CYCLE 1    //+2
      43,45,47,49,51,53,55,57,59; // WHOLE-TONE CYCLE 2   //+2
      =======================Thirds===========
      0,3,6,9,12,15,18,21,24,27,30,33,36,39;  // m3RDS =====DIMINISHED OR MINOR 3RD CYCLES
      1,4,7,10,13,16,19,23,25,28,31,34,37,40; //m3RDS   //+3
      2,5,8,11,14,17,20,23,26,29,32,35,38,41; //m3RDS  //+3
                           //-------//
      0,4,8,12,16,20,24,28,32,36,40; //   ===AUGMENTED OR MAJOR 3RD CYCLES
      1,5,9,13,17,21,25,29,33,37,41; //      //+4
      2,6,10,14,18,22,26,30,34,38; //      //+4
      3,7,11,15,19,23,27,31,35,39; //     //+4
      =======================Fouths===========
      0,5,10,3,8,1,6,11,4,9,2,7,0;   //<<==LEFT  //+5
      =======================Fifths===========
      0,7,2,9,4,11,6,1,8,3,10,5,0;   //==>>RIGHT //+7
      =======================Sixths=========== 
      INVERSION 0F: //+8,+9
      =======================Sevenths========= 
      M7= 0,4,7,11   //+10,+11
      Mm7= 0,4,7,10 // dominant_7th
      m7= 0,3,7,10
      nM7= 0,3,7,11
      ======================Ninths============
      INVERSION OF:
      ======================Elevenths=========
      INVERSION OF:
      ======================Thirteenths=======
      INVERSION OF:
      ========================================
      TONIC          DOMINANT     SUBDOMINAT
      ========================================
      IM7/IM6          V7
                     VIIdim7          IIm7
      IIIm7            bII7
                     #IVdim7       IVM7/IVM6
      VIm7           #IIdim7
      ========================================
      
 */
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <EEPROM.h>
#include "pitches.h"
#include <SD.h> //VS1053
#include <SPI.h> //VS1053
#include <MusicPlayer.h>  //VS1053
#include <LiquidCrystal.h>
#include <MIDI.h> //MiDI-IN Setup 
MIDI_CREATE_DEFAULT_INSTANCE();//MiDI-IN Setup
//*******************************************************************************
// User settable variables			
//*******************************************************************************
//
/*
CAESAR'S NOTES ON NOTES
Full range: 0-127; , (<0, &&, >127,); //
0,7,2,9,4,11,6,1,8,3,10,5; //BASS RANGE -Perfect 5ths 
0,4,8,12,16,20,24,28,32,36,40; // #5  ===AUGMENTED OR MAJOR 3RD CYCLES
1,5,9,13,17,21,25,29,33,37,41; //  #5
2,6,10,14,18,22,26,30,34,38; //     #5
3,7,11,15,19,23,27,31,35,39; //      #5
0,3,6,9,12,15,18,21,24,27,30,33,36,39;  // m3RDS =====DIMINISHED OR MINOR 3RD CYCLES
1,4,7,10,13,16,19,23,25,28,31,34,37,40; //     m3RDS
2,5,8,11,14,17,20,23,26,29,32,35,38,41;  //    m3RDS
42,44,46,48,50,52,54,56,58; // WHOLE-TONE CYCLE 1
43,45,47,49,51,53,55,57,59; // WHOLE-TONE CYCLE 2
*/
unsigned char PadNote[48] = {
  64,69,62,67,60,65,84,86,71,66,61,68,63,70,85,87, //Tunable  //CHANGE TO WHOLE-TONE CYCLES
  64,69,62,67,60,65,84,86,71,66,61,68,63,70,85,87, //Tunable  //4/5
  76,81,74,79,72,77,84,88,83,78,73,80,75,82,85,87};        // MIDI notes from 0 to 127 (Mid C = 60) for drums

int PadCutOff[48] = {
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, //Tunable
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, //Tunable
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7};           // Minimum Analog value to cause a drum hit, default=600

int MaxPlayTime[48] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  //Tunable
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //Tunable
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};               // Cycles before a 2nd hit is allowed, default=90

#define  midichannel	0;                              // MIDI (OUT) channel from 0 to 15 (+1 in "real world")
boolean VelocityFlag  = true;                           // Velocity ON (true) or OFF (false)
#define LED 13   //MiDI-IN // LED pin on Arduino Uno
//**************************************************************************************
// Internal Use Variables			
//**************************************************************************************
// Defines
// Constants
#define MODSWITCH1UP 24
#define MODSWITCH1DOWN 25
#define MODSWITCH2UP 26
#define MODSWITCH2DOWN 27
//#define SWITCH5 43 
#define MODLED1 28
#define MODLED2 29
#define MODLED3 30
#define MODLED4 31
// Constants
#define SWITCH1 39
#define SWITCH2 40
#define SWITCH3 41
#define SWITCH4 42
#define SWITCH5 43 
#define LED1 44
#define LED2 45
#define LED3 46
#define LED4 47
#define LED5 48
// Variables: 
int MODswitches[4] = { 
  MODSWITCH1UP, MODSWITCH1DOWN, MODSWITCH2UP, MODSWITCH2DOWN };
int MODswitchState[4] = { 
  HIGH, HIGH, HIGH, HIGH }; 
// Initial state of switch is high due to internal pullup
int MODleds[4] = { 
  MODLED1, MODLED2, MODLED3, MODLED4 };
int currentMODSwitch = 0;
int USERSETTING = 22;   // current program - sent to the output
int bypassIIState = LOW;     // state of bypass pedal
int pedalActiveFlashII = 50; // Delay for flash when pedal is pressed
// Variables: 
int switches[5] = { 
  SWITCH1, SWITCH2, SWITCH3, SWITCH4, SWITCH5 };
int switchState[5] = { 
  HIGH, HIGH, HIGH, HIGH, HIGH }; 
// Initial state of switch is high due to internal pullup
int leds[5] = { 
  LED1, LED2, LED3, LED4, LED5 };
int currentSwitch = 0;
int currentProgram = 0xC;   // current program - sent to the output
int bypassState = LOW;     // state of bypass pedal
int pedalActiveFlash = 50; // Delay for flash when pedal is pressed

int ModACounter;
int ModBCounter;
int ModCCounter;

// MuxShield:
// Give convenient names to the control pins of the muxshield
#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2
// Create arrays for data from the the MUXs
// See the Arduino Array Reference: http://www.arduino.cc/en/Reference/Array
//int mux0array[16]; //************
int mux1array[16];
int mux2array[16]; //************
int analogPin=0;
int pad=0;

//Adafruit_MCP23017 mcp0; //first MCP23017  //******************
Adafruit_MCP23017 mcp1; //second MCP23017
Adafruit_MCP23017 mcp2; //third MCP23017  //******************

boolean activePad[48] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                   // Array of flags of pad currently playing
int PinPlayTime[48] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                     // Counter since pad started to play
unsigned char status;
int pin =0;     
int hitavg = 0;

//midi through
byte byte1;
byte byte2;
byte byte3;
//  Making analog readings faster (for drumrolls) works with this code
// read http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1208715493/11 for more info
#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// notes to play, corresponding to the 48+ sensors:
int notes[48] = {
  NOTE_E5,  NOTE_A5,  NOTE_D5,  NOTE_G5,  NOTE_C5,  NOTE_F5,  NOTE_C7,  NOTE_D7,
  NOTE_B5 , NOTE_FS5,  NOTE_CS5,  NOTE_GS5,  NOTE_DS5,  NOTE_AS5,  NOTE_CS7,  NOTE_DS7,//********************* 
  NOTE_E5,  NOTE_A5,  NOTE_D5,  NOTE_G5,  NOTE_C5,  NOTE_F5,  NOTE_C7,  NOTE_D7,
  NOTE_B5 , NOTE_FS5,  NOTE_CS5,  NOTE_GS5,  NOTE_DS5,  NOTE_AS5,  NOTE_CS7,  NOTE_DS7,//***************************
  NOTE_E6,  NOTE_A6,  NOTE_D6,  NOTE_G6,  NOTE_C6,  NOTE_F6,  NOTE_C7,  NOTE_E7,
  NOTE_B6 , NOTE_FS6,  NOTE_CS6,  NOTE_GS6,  NOTE_DS6,  NOTE_AS6,  NOTE_CS7,  NOTE_DS7 };//*****************************

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(32,33,34,35,36,37);
///////
//////
// Start of code
//***********************************************************************************************
// Setup			
//************************************************************************************************
void setup() {
  
  MIDI.begin(0); //MiDI-IN Setup  // Launch MIDI and listen to channel 0
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); // Print a message to the LCD.
  lcd.print("DigiDrumDuino!");
  
  //Set I2C/GPIO Port Expander  
  //Initallize i2C bus
  //	mcp0.begin(0);			//initialize MCP23017 0  //***********
  mcp1.begin(1);			//initialize MCP23017 1
  mcp2.begin(2);			//initialize MCP23017 2   //***********
  // make all pins outputs
  for(int i=0; i<16; i++){
    //		mcp0.pinMode(i, OUTPUT); //******************
    mcp1.pinMode(i, OUTPUT);
    mcp2.pinMode(i, OUTPUT); //******************
  }
  //Set MUX control pins to output
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  
  //Serial.begin(9600);                                   // connect to the serial port 9600 (for debug)
  //Serial.begin(57600);                                  // connect to the serial port 57600
  Serial.begin(31250);                                 // connect to the serial port (31250) //midi standard
  //Serial.begin(115200);                                   // connect to the serial port 115200

    midiInit(); //VS1053
     //player.setVolume(20.20);
     
  // Setup Switches and activation LEDs
  for( currentMODSwitch = 0; currentMODSwitch < 4; currentMODSwitch++ ) {
    pinMode( MODswitches[currentMODSwitch], INPUT );          // Set pin for switch
    digitalWrite( MODswitches[currentMODSwitch], HIGH );      // Turn on internal pullup
    pinMode( MODleds[currentMODSwitch], OUTPUT );             // Set pin for LED
    flashIIPin( MODleds[currentMODSwitch], 100 ); // Flash LED
  }

  // Setup Switches and activation LEDs
  for( currentSwitch = 0; currentSwitch < 5; currentSwitch++ ) {
    pinMode( switches[currentSwitch], INPUT );          // Set pin for switch
    digitalWrite( switches[currentSwitch], HIGH );      // Turn on internal pullup
    pinMode( leds[currentSwitch], OUTPUT );             // Set pin for LED
    flashPin( leds[currentSwitch], 100 ); // Flash LED  
  }

#if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
#endif
}
//*************************************************************************************************
// Main Program			
//*************************************************************************************************
void loop(){
   if (MIDI.read())   //MiDI-IN Setup  // If we have received a message
    {
        digitalWrite(LED,HIGH);	//MiDI-IN Setup	
//        MIDI.sendNoteOn(42,127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
//        delay(1000);	// Wait for a second  //MiDI-IN Setup
//        MIDI.sendNoteOff(42,0,1);   // Stop the note  //MiDI-IN Setup
        digitalWrite(LED,LOW);//MiDI-IN Setup
    }
    
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
  
  //loopback all incoming midi events
  midiLoopback();
  //  readSensors(0); //  ***********
  readSensors(1);
  readSensors(2); //************
  //  checkSensors(0); //  ***********
  checkSensors(1);
  checkSensors(2);//************

}

void readSensors(int analogPin){
  for( currentSwitch = 0; currentSwitch < 5; currentSwitch++ ) {
    if((digitalRead(switches[currentSwitch]) != switchState[currentSwitch] )&&(switchState[currentSwitch] == HIGH)){
      switch( currentSwitch ) {
      case 0:
        //Bypass
        if( bypassState == LOW ) {
          bypassState = HIGH;
          //midiSend( 0xB0, 0x5B, 0x00 ); // bypass off
          player.midiWriteData( 0xB0, 0x5B, 0x00 ); // bypass off
          digitalWrite( leds[currentSwitch], LOW );
        }
        else {
          bypassState = LOW;
          //midiSend( 0xB0, 0x5B, 0x7F ); // bypass on
          player.midiWriteData( 0xB0, 0x5B, 0x7F ); // bypass on
          digitalWrite( leds[currentSwitch], HIGH );
        }
        break;
      case 1:
        //Prev Program
        currentProgram = currentProgram--;
        if( currentProgram < 1 )
          currentProgram = 0; // Don't go lower than 0
        //midiProg( 0xC0, currentProgram );
        player.midiWriteData( 0xC0, currentProgram, 0 );
        flashPin( leds[currentSwitch], pedalActiveFlash );
        break;
      case 2:
        // Next Program
        currentProgram = currentProgram++;
        if( currentProgram > 96 )
          currentProgram = 97; // Don't go lower than 97
        //midiProg( 0xC0, currentProgram );
        player.midiWriteData( 0xC0, currentProgram, 0 );
        flashPin( leds[currentSwitch], pedalActiveFlash );
        break;
      case 3:
        // Favourite 1
        currentProgram = 0xC; //14
        //midiProg( 0xC0, currentProgram );
        player.midiWriteData( 0xC0, currentProgram, 0 );
        flashPin( leds[currentSwitch], pedalActiveFlash );
        break;
      case 4:
        // Favourite 2
        currentProgram = 0x1B; //27
        //midiProg( 0xC0, currentProgram );
        player.midiWriteData( 0xC0, currentProgram, 0 );
        flashPin( leds[currentSwitch], pedalActiveFlash );
        break;
      }
      //      delay( BOUNCEDELAY );
    }
    switchState[currentSwitch] = digitalRead( switches[currentSwitch] );
  }  
  //////////
  //////////   
  for( currentMODSwitch = 0; currentMODSwitch < 4; currentMODSwitch++ ) {
    if((digitalRead(MODswitches[currentMODSwitch]) != MODswitchState[currentMODSwitch] )&&(MODswitchState[currentMODSwitch] == HIGH)){
      switch( currentMODSwitch ) {
      case 0:
        //Bypass
        if( bypassIIState == LOW ) {
          bypassIIState = HIGH;
          //            player.midiWriteData( 0xB0, 0x5B, 0x00 ); // bypass off
          digitalWrite( MODleds[currentMODSwitch], LOW );
          ModACounter++;
        }
        else {
          bypassIIState = LOW;
          //            player.midiWriteData( 0xB0, 0x5B, 0x7F ); // bypass on
          digitalWrite( MODleds[currentMODSwitch], HIGH );
          --ModACounter;
        }
        break;
      case 1:
        //Prev Program
        USERSETTING = USERSETTING--;
        if( USERSETTING < 1 )
          USERSETTING = 0; // Don't go lower than 0
        //           player.midiWriteData( 0xC0, currentProgram, 0 );
        flashIIPin( MODleds[currentMODSwitch], pedalActiveFlashII );
        ++ModBCounter;
        break;
      case 2:
        // Next Program
        USERSETTING = USERSETTING++;
        if( USERSETTING > 96 )
          USERSETTING = 97; // Don't go lower than 97
        //           player.midiWriteData( 0xC0, currentProgram, 0 );
        flashIIPin( MODleds[currentMODSwitch], pedalActiveFlashII );
        --ModBCounter;
        break;
      case 3:
        // Favourite 1
        USERSETTING = 22;
        //           player.midiWriteData( 0xC0, currentProgram, 0 );
        flashIIPin( MODleds[currentMODSwitch], pedalActiveFlashII );
        ++ModCCounter;
        break;
        //        case 4:
        //          // Favourite 2
        //          currentProgram = 27;
        ////           player.midiWriteData( 0xC0, currentProgram, 0 );
        //          flashPin( leds[currentSwitch], pedalActiveFlash );
        //          break;
      }
      ////      delay( BOUNCEDELAY );
    }
    MODswitchState[currentMODSwitch] = digitalRead( MODswitches[currentMODSwitch] );
  }  
  ///////////////
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i=0; i<16; i++){
    digitalWrite(CONTROL0, (i&15)>>3); 
    digitalWrite(CONTROL1, (i&7)>>2);  
    digitalWrite(CONTROL2, (i&3)>>1);  
    digitalWrite(CONTROL3, (i&1));     
    //Read and store the input value at a location in the array
    //    if(analogPin==0){  //  ***********
    //    mux0array[i] = analogRead(analogPin);  //**************
    //    } //  *************
    if(analogPin==1){
      mux1array[i] = analogRead(analogPin);
    }
    if(analogPin==2){ //**********
      mux2array[i] = analogRead(analogPin); //************
    } //**********
  }
}

void checkSensors(int analogPin)
{
  ///////////  
  for(int pin=0; pin <16; pin++)
  {   

    //      if(analogPin==0) // ***********
    //      { //**************
    //         hitavg = mux0array[pin]; //**********
    //         pad=pin; //**************
    //      } //****************
    if(analogPin==1)
    {
      hitavg = mux1array[pin];
      pad=pin+16;
    }
    if(analogPin==2) //**************
    { //*******************
      hitavg = mux2array[pin];//*************
      pad=pin+32;//******************
    } //**************

    if((hitavg > PadCutOff[pin]))
    {
      //Serial.writeln("hitavg > PadCutOff[pin])");
      if((activePad[pad] == false))
      {
        if(VelocityFlag == true)
        {
          //hitavg = 127 / ((1023 - PadCutOff[pin]) / (hitavg - PadCutOff[pin]));    // With full range (Too sensitive ?)
          hitavg = (hitavg / 8) -1 ;                      // 1023/8=128, -1=127  //                  // Upper range  // 
        }
        else
        {
          hitavg = 127;
        }

        MIDI_TX(144,PadNote[pad],hitavg);
        player.midiNoteOn(0, PadNote[pad], hitavg); //VS1053
        PinPlayTime[pad] = 0;
        activePad[pad] = true;
        tone(14, notes[pad]); //Pin 14
      }
      else
      {
        PinPlayTime[pad] = PinPlayTime[pad] + 1;
      }         
    }
    else 
    {
      if((activePad[pad] == true))
      {
        PinPlayTime[pad] = PinPlayTime[pad] + 1;

        if(PinPlayTime[pad] > MaxPlayTime[pad])
        {
          activePad[pad] = false;
          MIDI_TX(128,PadNote[pad],127);
          player.midiNoteOff(0, PadNote[pad], hitavg);//VS1053
          noTone(14); //Pin 14 
        }
      }
    }

    if(analogPin==1)
    {
      if (activePad[pad])
        mcp1.digitalWrite(pad-16, HIGH);
      else
        mcp1.digitalWrite(pad-16, LOW);
    }
    if(analogPin==2) //*************
    { //******************
      if (activePad[pad]) //**************
        mcp2.digitalWrite(pad-32, HIGH);//***************
      else //***************
      mcp2.digitalWrite(pad-32, LOW);//*************************
    }//**********************
  }
}

//*******************************************************************************************
// Transmit MIDI Message			
//*******************************************************************************************
void MIDI_TX(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) 
{
  status = MESSAGE + midichannel;
  Serial.write(status);
  Serial.write(PITCH);
  Serial.write(VELOCITY);
}

//*************** MIDI LOOPBACK ******************//
void midiLoopback(){
  if(Serial.available() > 0){
    byte1 = Serial.read();
    byte2 = Serial.read();
    byte3 = Serial.read();

    MIDI_TX(byte1, byte2, byte3);
  }
}
//*******************************************************************************
// VS1053			
//*******************************************************************************  
// Initializes MIDI
void midiInit(){
  player.beginInMidiFmt();
  player.midiWriteData(0xB0, 0x07, 127); // Set MIDI channel volume
  player.midiWriteData(0xC0, currentProgram, 0); // Select instrument
  player.setVolume(0X00); //20 04 2016
}

// Sets MIDI bank to GM1 or GM2. Takes values 1 or 2
void setMIDIBank(byte bank) {
  if (bank==1) player.midiWriteData(0xB0, 0, 0x00);  // Select bank GM1
  else player.midiWriteData(0xB0, 0, 0x78);  // Select bank GM2
}

//  Send a three byte midi message  
void midiSend(char status, char data1, char data2) {
  Serial.print(status);
  Serial.print(data1);
  Serial.print(data2);
}

//  Send a two byte midi message  
void midiProg(char status, int data ) {
  Serial.print(status);
  Serial.print(data);
}
void flashPin( int ledPin, int flashDelay ) {
  digitalWrite( ledPin, HIGH );
  //delay( flashDelay ); //No hecups PLEASE
  digitalWrite( ledPin, LOW );
}

void flashIIPin( int ledPinII, int flashDelay ) {
  digitalWrite( ledPinII, HIGH );
  //delay( flashDelay ); //Don't hesitate 
  digitalWrite( ledPinII, LOW );
}

