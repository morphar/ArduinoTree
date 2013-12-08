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
The result is pretty satisfying as the following is a simple "starry night"-ish theme (see [YouTube video](http://youtu.be/AxqoiiopAbw)), that is the second really successful pattern (from SimpleDefinition sketch):

```C
int frames[FRAMES] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 100 };
```
Just 1 line of defining 30 frames for all 30 LEDs.
For each LED the program will make a copy of this sequence, but offset it randomly to generate new patterns each time.

The above sequence is a sequence of brightness in percent, each lasting 1 frame (1/25th of a second).