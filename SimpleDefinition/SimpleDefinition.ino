// Define the LEDs and how they should be set
// These are defined in a way that match the construction of my tree...

byte matrix[30][2] = {
  { 0b00001100, 0b00000100 }, // LED  1 - 01
  { 0b00001100, 0b00001000 }, // LED  2 - 10
  { 0b00010100, 0b00000100 }, // LED  3 - 02
  { 0b00010100, 0b00010000 }, // LED  4 - 20
  { 0b00011000, 0b00001000 }, // LED  5 - 12
  { 0b00011000, 0b00010000 }, // LED  6 - 21
  { 0b00100100, 0b00000100 }, // LED  7 - 03
  { 0b01000100, 0b00000100 }, // LED  8 - 04
  { 0b01000100, 0b01000000 }, // LED  9 - 40
  { 0b01100000, 0b00100000 }, // LED 10 - 34
  { 0b01100000, 0b01000000 }, // LED 11 - 43
  { 0b00100100, 0b00100000 }, // LED 12 - 30
  { 0b10001000, 0b10000000 }, // LED 13 - 51
  { 0b00101000, 0b00100000 }, // LED 14 - 33
  { 0b00101000, 0b00001000 }, // LED 15 - 13
  { 0b10001000, 0b00001000 }, // LED 16 - 15
  { 0b10100000, 0b00100000 }, // LED 17 - 35
  { 0b10100000, 0b10000000 }, // LED 18 - 53
  { 0b11000000, 0b10000000 }, // LED 19 - 54
  { 0b10000100, 0b10000000 }, // LED 20 - 50
  { 0b10000100, 0b00000100 }, // LED 21 - 05
  { 0b01001000, 0b00001000 }, // LED 22 - 14
  { 0b01001000, 0b01000000 }, // LED 23 - 41
  { 0b11000000, 0b01000000 }, // LED 24 - 45
  { 0b00110000, 0b00100000 }, // LED 25 - 32
  { 0b01010000, 0b00010000 }, // LED 26 - 24
  { 0b01010000, 0b01000000 }, // LED 27 - 42
  { 0b10010000, 0b10000000 }, // LED 28 - 52
  { 0b10010000, 0b00010000 }, // LED 29 - 25
  { 0b00110000, 0b00010000 }  // LED 30 - 23
};

// The default
byte DDRDOriginal = B00000000;
byte PORTDOriginal = B00000000;

// Set a couple of constants
#define LEDS 30
#define FRAMES 30

void shiftLeft(int *fromArr, int *toArr, int len, int shiftBy) {
  int newIndex = (shiftBy % len);
  for(int originalIndex=0 ; originalIndex < len; originalIndex++) {
    if(newIndex > len-1) {
      newIndex = 0;
    }
    toArr[newIndex] = fromArr[originalIndex];
    newIndex++;
  }
}


// Define the frames
int frames[FRAMES] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 100 };

// Ready the randomized array of LED frames
int ledFrames[FRAMES][LEDS];

void buildLEDFrames() {
  randomSeed(analogRead(2));

  for(int led=0 ; led < LEDS ; led++) {
    int randNumber = random(FRAMES);

    int tmpFrames[FRAMES];
    shiftLeft(frames, tmpFrames, FRAMES, randNumber);
    for(int i=0 ; i < FRAMES ; i++) {
      ledFrames[i][led] = tmpFrames[i];
    }
  }

//  for(int frame=0 ; frame < FRAMES ; frame++) {
//    for(int led=0 ; led < LEDS ; led++) {
//      Serial.print(ledFrames[frame][led]);
//      Serial.print(", ");
//    }
//    Serial.println("");
//  }

//  for(int led=0 ; led < LEDS ; led++) {
//    randomSeed(millis());
//    int randNumber = random(FRAMES);
//
//    shiftLeft(frames, ledFrames[led], FRAMES, randNumber);
//  }
}

// Run a frame til time is up
void runFrame(int frame) {
  // This is supposed to make sure, the frame is repeated, if it is under a frame long.
  // That will probably not happen, as the 16MHz is to slow to go through this more than 1 time.
  unsigned long start;
  start = millis();

  while((millis() - start) < 40) {
    // Use percentage as a "understandable" value to loop through each "percentage" of the range 
    for(int percent=1 ; percent <= 100 ; percent++) {

      // For each percent, go through each LED and calculate if it should be on or off
      for(int led=0 ; led < LEDS ; led++) {

        if(ledFrames[frame][led] == 0) {
          DDRD = DDRDOriginal;
          PORTD = PORTDOriginal;

        // This is an easy way to have it on for x% time
        // The backside is that it may seem dimmer in the lower percent and brighter in the higher percent,
        //   than if you actually turn on every 1.49 time @ 67%, but that is really hard to do ;)
        } else if(percent <= ledFrames[frame][led]) {
          DDRD = DDRDOriginal | matrix[led][0];
          PORTD = PORTDOriginal | matrix[led][1];

        } else {
          DDRD = DDRDOriginal;
          PORTD = PORTDOriginal;
        }
      }
    }
  }
}

void setup() {
  // Set the default to initial values
  DDRDOriginal = DDRD;
  PORTDOriginal = PORTD;
  buildLEDFrames();
}

// Loop over the frames
void loop() {
  for(int frame=0 ; frame < FRAMES ; frame++) {
    runFrame(frame);
  }
}

