## Arduino Tree

This is a personal "art" project utilizing small Arduino clones.

Currently the code is done for [PICnDuino](http://www.bradsprojects.com/the-picnduino/) which is a ATmega328 based Arduino clone.

The technique used is called [Charlieplexing](http://en.wikipedia.org/wiki/Charlieplexing).
It is NOT the best/easiest way to drive a lot of LEDs - there are components that will make that easier for you.

BUT... I wanted to see what I could do with a single MCU, a tree that my wife painted on the wall and as little wires as possible.

I ended up using 6 pins, a lot of wire (not as much as having 2 wires/LED though), very much masking tape and some acrylic paint.

### The goal
My main goal, was to create a tree with 30 LEDs, that could be controlled "individually" and be able to create patterns based on frames or "movement".

Basically the goal was to create some code, that could take an array of LED frames and run through them, turning on and off the LEDs one by one.
The result is pretty satisfying as the following is a simple "starry night"-ish theme, that is the first really successful pattern (from StarryNight sketch):

```C
int frames[FRAMES][LED_COUNT] = {
  {   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100 },
  {   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0 },
  {   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2 },
  {  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4 },
  {  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10 },
  { 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20, 100,   0,   2,   4,  10,  20 }
};
```
Just 6 lines of defining 6 frames for all 30 LEDs.