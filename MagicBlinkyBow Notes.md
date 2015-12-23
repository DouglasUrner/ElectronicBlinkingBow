# ElectronicBlinkyBow Notes

## Overview

Violin bow with a microphone and LEDs hooked to an Arduino (actually a Trinket) so that something fun can happen with the lights in response to playing the violin.

The code design tries to expose some fun options so that a user of the bow might have some motivation to learn about about programming (or hacking hardware).

The tonal range of the violin is about four octaves, the low string is a G at 196 Hz, the open strings go up by fifths to E – G3 (196.0 Hz), D4 (293.7 Hz), A4 (440.0 Hz), E5 (659.3 Hz). The highest note on the E string is about 10 KHz. From http://hyperphysics.phy-astr.gsu.edu/hbase/music/violin.html

According to [Wikipedia](https://en.wikipedia.org/wiki/Violin#Pitch_range):

>The lowest note of a violin, tuned normally, is G3, or G below middle C. (On rare occasions, the lowest string may be tuned down by as much as a fourth, to D3.) The highest note is less well defined: E7, the E two octaves above the open string (which is tuned to E5) may be considered a practical limit for orchestral violin parts, but it is often possible to play higher, depending on the length of the fingerboard and the skill of the violinist. Yet higher notes (up to C8) can be sounded using harmonics, either natural or artificial.

E7 is 2637 Hz.

http://www.phy.mtu.edu/~suits/notefreqs.html

http://www.liutaiomottola.com/formulae/freqtab.htm

## Signal processing

Filter out signals we don't want to, can't handle. Otherwise we will still them as spurious (aliased) input.

Nyquist says 2x desired frequency. Filter comes in slowly so need to sample higher than the actual frequency of interest. Instruments have lots of harmonics.

### Zero Crossing Detection

Work by Amanda Ghassaei on Arudino based signal processing:

* http://www.instructables.com/id/Arduino-Audio-Input
* http://www.instructables.com/id/Arduino-Frequency-Detection

### FFT

Bins limit resolution (and memory limits bins)

* [FFT Library](http://forum.arduino.cc/index.php?topic=299461.0) - discussion about similar project trying to use the [fix_FFT library](http://forum.arduino.cc/index.php?topic=38153.0) – 8-bit, fixed point in-place FFT.

* [Open Music Labs Arduino FFT Library](http://wiki.openmusiclabs.com/wiki/ArduinoFFT), not sure if it will work with 1.6.

Lots of good looking stuff here: http://www.arduinoos.com/projects/

### FHT

Alternative to FFT, Open Music Labs has an implementation.

### Auto Correlation

* [Reliable Frequency Measurment Using Autocorrelation](http://forum.arduino.cc/index.php?topic=195085.0)
* http://www.instructables.com/id/Reliable-Frequency-Detection-Using-DSP-Techniques/

## Ideas for the display

Use HSV for color. Then map as:

* Hue: Note (A, B, C, etc.).
* Saturation: Octave
* Value/Brightness: Volume?

A number of people have tried to find [_A Mapping Between Musical Notes and Colors_](http://www.endolith.com/wordpress/2010/09/15/a-mapping-between-musical-notes-and-colors) – in this one, the mapping is achieved by moving up from sound frequencies by octaves until you get into the range of light. Note that people hear several octaves of sound, but ony see about one "octave" of light. This means that we need another method of encoding octaves visually.

<table border="1" cellspacing="0">
<tbody>
<tr>
<th>Note</th>
<th>Freq (Hz)</th>
<th>+40 oct. (THz)</th>
<th>Wavelength (nm)</th>
<th>R</th>
<th>G</th>
<th>B</th>
<th>Color</th>
<th>HTML name</th>
</tr>
<tr>
<td>F♯<sub>4</sub></td>
<td>370</td>
<td>407</td>
<td>737</td>
<td>174</td>
<td>0</td>
<td>0</td>
<td style="background-color: #ae0000;"></td>
<td>dark red</td>
</tr>
<tr>
<td>G<sub>4</sub></td>
<td>392</td>
<td>431</td>
<td>696</td>
<td>255</td>
<td>0</td>
<td>0</td>
<td style="background-color: #ff0000;"></td>
<td>red</td>
</tr>
<tr>
<td>G♯<sub>4</sub></td>
<td>415</td>
<td>457</td>
<td>657</td>
<td>255</td>
<td>0</td>
<td>0</td>
<td style="background-color: #ff0000;"></td>
<td>red</td>
</tr>
<tr>
<td><a href="http://en.wikipedia.org/wiki/A440_%28Concert_A%29">A<sub>4</sub></a></td>
<td>440</td>
<td>484</td>
<td>620</td>
<td>255</td>
<td>102</td>
<td>0</td>
<td style="background-color: #ff6600;"></td>
<td>orange-red</td>
</tr>
<tr>
<td>B♭<sub>4</sub></td>
<td>466</td>
<td>513</td>
<td>585</td>
<td>255</td>
<td>239</td>
<td>0</td>
<td style="background-color: #ffef00;"></td>
<td>yellow</td>
</tr>
<tr>
<td>B<sub>4</sub></td>
<td>494</td>
<td>543</td>
<td>552</td>
<td>153</td>
<td>255</td>
<td>0</td>
<td style="background-color: #99ff00;"></td>
<td>chartreuse</td>
</tr>
<tr>
<td>C<sub>5</sub></td>
<td>523</td>
<td>575</td>
<td>521</td>
<td>40</td>
<td>255</td>
<td>0</td>
<td style="background-color: #28ff00;"></td>
<td>lime</td>
</tr>
<tr>
<td>C♯<sub>5</sub></td>
<td>554</td>
<td>610</td>
<td>492</td>
<td>0</td>
<td>255</td>
<td>242</td>
<td style="background-color: #00fff2;"></td>
<td>aqua</td>
</tr>
<tr>
<td>D<sub>5</sub></td>
<td>587</td>
<td>646</td>
<td>464</td>
<td>0</td>
<td>122</td>
<td>255</td>
<td style="background-color: #007aff;"></td>
<td>sky blue</td>
</tr>
<tr>
<td>D♯<sub>5</sub></td>
<td>622</td>
<td>684</td>
<td>438</td>
<td>5</td>
<td>0</td>
<td>255</td>
<td style="background-color: #0500ff;"></td>
<td>blue</td>
</tr>
<tr>
<td>E<sub>5</sub></td>
<td>659</td>
<td>725</td>
<td>414</td>
<td>71</td>
<td>0</td>
<td>237</td>
<td style="background-color: #4700ed;"></td>
<td>blue</td>
</tr>
<tr>
<td>F<sub>5</sub></td>
<td>698</td>
<td>768</td>
<td>390</td>
<td>99</td>
<td>0</td>
<td>178</td>
<td style="background-color: #6300b2;"></td>
<td>indigo</td>
</tr>
</tbody>
</table>

### Other Ideas

* LED for each step on the scale, color by octave (sharps & flats?)
* LED for each string (how to distinguish alternative notes?)

Tweakable parameters

* LED color
* Map color to pitch
* Map color to volume
* Vary decay (time till LED extinguishes)

This sounds like the bow is basically a variation on a guitar tuner. Here are some links to similar (tuner) projects:

* http://www.instructables.com/id/Arduino-Guitar-Tuner
* http://www.jameco.com/Jameco/workshop/challenge/arduino-guitar.html
* http://www.instructables.com/id/Automatic-Guitar-Tuner
* http://www.tonychai.com/guitar.html
* http://deambulatorymatrix.blogspot.com/2010/11/digital-chromatic-guitar-tuner-2008.html

Adafruit has a project they call [Piccolo Music Visualizer](https://learn.adafruit.com/piccolo) which also seems like a possible source of ideas / inspiration. They describe it as a "spectrum analyzer, "but not a "precision scientific instrument" – hence the term "visualizer." This uses an Arduino Teensy which is a much bigger machine than the "standard" Arduino or the Trinket.

## Libraries

### [FastLCD](http://fastled.io)

Use for HSV support with NeoPixels.

Code is on GitHub at [FastLED/FastLED](https://github.com/FastLED/FastLED).

## Tasks

### Microphone

Planning to use an electret ([Adafruit 1935](https://www.adafruit.com/products/1935)) which means either building or buying a preamp. The links below discuss some possible circuits using either transistors or an op amp.

* https://en.wikipedia.org/wiki/Electret_microphone
* [LM386 microphone amplifier](https://lowvoltage.wordpress.com/2011/05/15/lm386-mic-amp/) – this is currently the circuit being used for the input.
* http://electronics.stackexchange.com/questions/36795/using-a-microphone-with-an-arduino
* http://electronics.stackexchange.com/questions/53698/how-to-connect-mic-on-arduino-with-opamp
* http://wiring.org.co/learning/basics/microphone.html
* http://lucidtronix.com/tutorials/22

#### Op Amps

Ron Mancini's _Op Amps for Everyone_

### LED control

The LEDs will probably be arranged in a line on the back of the bow. The current plan is to use Adafruit NeoPixels or a DotStar strip. Individual NeoPixels seem like they would mount nicely on the bow. A DotStar strip sounds like it would be easier to code as the timing requirements are less stringent.

### Power supply / management

### Component placement

### Coding
