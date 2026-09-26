#include <Arduino.h>
#include <math.h>

/*
COMPONENTS NEEDED:
Piezoelectric disk (for sensing)
ADC (to convert analog to digital data)
Screen (for output)
CPU (for adding and communication)
*/


/*
loop code goes like:
continuously read from analog pin
increment frequency int every time voltage is detected
get the frequency after a timespan of 30 milliseconds then reset for the next
put into hashmap associated with notes
output to screen 

*/
#define piezoPin A0

unsigned long currentTime;
unsigned long prevTime;
uint8_t voltage;
int increment;
const double RATIO = pow(2, 0.083333);

enum Note  
{//the ratio between each adjacent semitone is the same every time in equal temperament
  A,
  A_SHARP,
  B,
  C,
  C_SHARP,
  D,
  D_SHARP,
  E,
  F,
  F_SHARP,
  G,
  G_SHARP,
  NONE,
};

Note hash(int freq); 
int calculateOffset(int freq, Note note);
void display(Note note, int offset);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  if(currentTime - prevTime >= 30UL)
  {
    prevTime = currentTime;
    //send increment to hashmap where if it falls within a certain range, it returns a note
    Note outputNote = hash(increment);
    int offset = calculateOffset(increment, outputNote);
    display(outputNote, offset);
    //send note to screen
    increment = 0;
  }
  
  voltage = analogRead(piezoPin);
  if (voltage > 0)
  {
    increment++;
  }


}

Note hash(int freq) 
{
  //calculates closest Note letter to given frequency
  int freqRatio = round(freq / RATIO);
  int noteIndex = freqRatio % 12;

  switch (noteIndex) {
    case 0:
      return A;
    case 1:
      return A_SHARP;
    case 2:
      return B;
    case 3:
      return C;
    case 4:
      return C_SHARP;
    case 5:
      return D;
    case 6:
      return D_SHARP;
    case 7:
      return E;
    case 8:
      return F;
    case 9:
      return F_SHARP;
    case 10:
      return G;
    case 11:
      return G_SHARP;
    default:
      return NONE;
  }
}

int calculateOffset(int freq, Note note)
{
  int correctFreq = A*(note*RATIO);
   
}

