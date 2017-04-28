
Things related to Digital Signal Processing (DSP).

# Audio

Perception

* Loudness is non-linear, both amplitude-, frequency- and time-dependent.
[Instantaneous, Short-Term, and Long-Term](https://ccrma.stanford.edu/~jos/sasp/Instantaneous_Short_Term_Long_Term_Loudness.html)
* [The Bark Frequency Scale](https://ccrma.stanford.edu/~jos/bbt/Bark_Frequency_Scale.html),
corresponding to the first 24 critical (frequency) bands of hearing.

Distortion

* Inherently non-linear process. Creates new non-harmonically related overtones.
Causes expansion signal bandwidth, possibly over the Nyquist/2 - causing aliasing into audible range.

Resampling/oversampling

* [flyingSand: Audio Resampling: Part 2](https://christianfloisand.wordpress.com/2013/01/28/audio-resampling-part-2/).
Good explanation of polyphase filters for efficient oversampling. Includes C++ example code.
* [Sample rate conversion: up](http://www.earlevel.com/main/2010/12/05/sample-rate-conversion-up)
Hands-on description of 2x oversampling, using a polyphase filter. C example code.
* [Polynomial Interpolators for High-Quality Resampling of Oversampled Audio](http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf)
* Basic upsampling: zero-pad with N-1 samples [stretch operator](https://ccrma.stanford.edu/~jos/sasp/Upsampling_Stretch_Operator.html)
* Basic downsampling: pick every N sample [decimation operator](https://ccrma.stanford.edu/~jos/sasp/Downsampling_Decimation_Operator.html)
* Polyphase filter [for downsampling](https://ccrma.stanford.edu/~jos/sasp/Filtering_Downsampling.html).
* [resamp2 from liquid-dsp](http://liquidsdr.org/doc/resamp2/), C implementation that looks good.

Wavelets

* [Wavelet filter banks](https://ccrma.stanford.edu/~jos/sasp/Wavelet_Filter_Banks.html)

Cross-synthesis

* [Cross-synthesis](https://ccrma.stanford.edu/~jos/sasp/Cross_Synthesis.html)
"is the technique of impressing the spectral envelope of one sound on the flattened spectrum of another"
* Used for instance by vocoders
* [sines+noise modeling](https://ccrma.stanford.edu/~jos/sasp/Sines_Noise_Summary.html)

DSP libraries

* [liquid-dsp](https://github.com/jgaeddert/liquid-dsp). Plain C, no external dependencies, MIT/X11 licensed.
Designed for Software-Defined-Radio, but has tons of generally useful filters, incl good documentation.
