# ElectronicBlinkyBow Notes

## Overview

Violin bow with a microphone and LEDs hooked to an Arduino (actually a Trinket) so that something fun can happen with the lights in response to playing the violin.

The code design tries to expose some fun options so that a user of the bow might have some motivation to learn about about programming (or hacking hardware).

The tonal range of the violin is about four octaves, the low string is a G at 196 Hz, the open strings go up by fifths to E – G3 (196.0 Hz), D4 (293.7 Hz), A4 (440.0 Hz), E5 (659.3 Hz). According to [Wikipedia](https://en.wikipedia.org/wiki/Violin) the highest practical note on the E string is E7 (2637 Hz), although http://hyperphysics.phy-astr.gsu.edu/hbase/music/violin.html claims a high note of around 10 KHz. For our purposes E7 seems like a reasonable target on the high end. This means that we need a sampling frequency of around 5275 Hz.

[List of notes and their frequencies](http://www.liutaiomottola.com/formulae/freqtab.htm).

[Another list of notes](http://www.phy.mtu.edu/~suits/notefreqs.html).

[Light wavelengths and colors](http://hyperphysics.phy-astr.gsu.edu/hbase/vision/specol.html).

[HSL, HSB and HSV color: differences and conversion](http://codeitdown.com/hsl-hsb-hsv-color/)

## Ideas for the display

One way to map notes onto colors is to start with the audible frequency range and keep moving up by octaves until you reach visible frequencies. This mapping, from [A mapping between musical notes and colors](http://www.endolith.com/wordpress/2010/09/15/a-mapping-between-musical-notes-and-colors/), is in the table below. Note that the entire visible spectrum is about one octave. The violin, by comparison, has a range of about five octaves.

The author of the referenced article adds:

>I used [this Python code]() to generate the RGB values for each wavelength, and Wolfram Alpha to find the nearest named HTML color.  Should find the nearest color names from the [XKCD color survey](https://xkcd.com/color/rgb/) instead (and “nearest” should be defined as distance in L*a*b* space, not in RGB space).

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

Since there is only one "octave" of visible light, and many octaves of notes on the violin, we need a way to encode octaves. Saturation seems like a possible way to do this.

Here is [another approach to the problem](http://www.gootar.com/theory.htm) – the author claims that major chords are primary colors, but s/he is talking about subtractive primaries rather than additive, so I'm not so sure about this…

### Other display ideas

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

Adafruit has a project they call [Piccolo Music Visualizer](https://learn.adafruit.com/piccolo) which also seems like a possible source of ideas / inspiration. They describe it as a "spectrum analyzer, "but not a "precision scientific instrument" – hence the term "visualizer."

Work by Amanda Ghassaei on Arudino based signal processing:

* http://www.instructables.com/id/Arduino-Audio-Input
* http://www.instructables.com/id/Arduino-Frequency-Detection

## Tasks

### Microphone

Planning to use an electret ([Adafruit 1935](https://www.adafruit.com/products/1935)) which means either building or buying a preamp. The links below discuss some possible circuits using either transistors or an op amp.

* https://en.wikipedia.org/wiki/Electret_microphone
* [LM386 microphone amplifier](https://lowvoltage.wordpress.com/2011/05/15/lm386-mic-amp/)
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
