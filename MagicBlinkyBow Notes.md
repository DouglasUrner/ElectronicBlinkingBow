# ElectronicBlinkyBow Notes

## Overview

Violin bow with a microphone and LEDs hooked to an Arduino (actually a Trinket) so that something fun can happen with the lights in response to playing the violin.

The code design tries to expose some fun options so that the owner of the bow (our niece/cousin) might have some motivation to learn about about programming (or hacking hardware).

The tonal range of the violin is about four octaves, the low string is a G at 196 Hz, the open strings go up by fifths to E – G3 (196.0 Hz), D4 (293.7 Hz), A4 (440.0 Hz), E5 (659.3 Hz). The highest note on the E string is about 10 KHz. From http://hyperphysics.phy-astr.gsu.edu/hbase/music/violin.html

## Ideas for the display

* LED for each step on the scale, color by octave (sharps & flats?)
* LED for each string (how to distinguish alternative notes?)

Tweakable parameters

* LED color
* Map color to pitch
* Map color to volume
* Vary decay (time till LED extinguishes)

This sounds like the bow is basically a variation on a guitar tuner. Here are some links to similar (tuner) projects:

http://www.instructables.com/id/Arduino-Guitar-Tuner
http://www.jameco.com/Jameco/workshop/challenge/arduino-guitar.html
http://www.instructables.com/id/Automatic-Guitar-Tuner
http://www.tonychai.com/guitar.html
http://deambulatorymatrix.blogspot.com/2010/11/digital-chromatic-guitar-tuner-2008.html

Work by Amanda Ghassaei on Arudino based signal processing:

http://www.instructables.com/id/Arduino-Audio-Input
http://www.instructables.com/id/Arduino-Frequency-Detection

## Tasks

### Microphone

Planning to use an electret ([Adafruit 1935](https://www.adafruit.com/products/1935)) which means either building or buying a preamp. The links below discuss some possible circuits using either transistors or an op amp.

https://en.wikipedia.org/wiki/Electret_microphone
http://electronics.stackexchange.com/questions/36795/using-a-microphone-with-an-arduino
http://electronics.stackexchange.com/questions/53698/how-to-connect-mic-on-arduino-with-opamp
http://wiring.org.co/learning/basics/microphone.html
http://lucidtronix.com/tutorials/22

#### Op Amps

Ron Mancini's _Op Amps for Everyone_

### LED control

The LEDs will probably be arranged in a line on the back of the bow. The current plan is to use Adafruit NeoPixels or a DotStar strip. Individual NeoPixels seem like they would mount nicely on the bow. A DotStar strip sounds like it would be easier to code as the timing requirements are less stringent.

### Power supply / management

### Component placement

### Coding
