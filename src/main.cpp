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
const double C_ZERO = 16.35;
const double LOG_TWO = log(2);

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

Note hash(double freq); 
int findOctave(double freq);
int calculateOffset(double freq, int octave, Note note);
void display(Note note, int octave, int offset);


void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  voltage = analogRead(piezoPin);
  if (voltage > 0)
  {
    currentTime = millis();
    double period = currentTime - prevTime;
    double freq = 1.0/period;
    prevTime = currentTime;

    //send frequency to hashmap where if it falls within a certain range, it returns a note
    Note outputNote = hash(freq);
    int outputNoteOctave = findOctave(freq);
    int offset = calculateOffset(freq, outputNoteOctave, outputNote);
    display(outputNote, outputNoteOctave, offset);//send note to screen
  }
} 

Note hash(double freq) 
{
  //calculates closest Note letter to given frequency
  int octaveNum = findOctave(freq);
  int noteIndex = 12*(log(freq)/LOG_TWO - log(C_ZERO)/LOG_TWO - octaveNum);

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

int findOctave(double freq)
{
  return (int) ((log(freq)/log(2)) - 4.0);
}

int calculateOffset(double freq, int octave, Note note)
{
  int correctFreq = C_ZERO * pow(RATIO, note) * (octave + 1);

  if (correctFreq > freq)
  {
    return correctFreq - freq;
  }
  else 
  {
    return freq - correctFreq;
  }
}


