Hi, thank you for your interest in this project!

## Tasks

1. Port a plugin to JUCE and build it for your platform*.
2. Translate a section of code to efficient modern C++.

* Distributing vst2 plugins is illegal unless you have a contract with Steinberg.

todo(Gaétan) Musicians might want to build the plugins themselves, so write or redirect to a clear guide to build on all platforms.

## Objectives

The main goal here is to (re-)distribute quality free plugins that run fast even on cheap hardware.
The end users are anyone working with audio: musicians, podcasters, ASMRtists, editors, etc.

Optimally, your code should produce the same result as the original and fill the buffer more quickly.

## Avoid

This project is not about inventing new plugins, and I will reject your PR if you:
• Add a GUI to a plugin
• Add functionality to a plugin as to make it unrecognizable

The reason is that airwindows plugins usually have one function.
The design philosophy can be summarized as:
"This does one thing really well. If you need something else, use something else."
This is efficient for both designers and end users.

## Coding conventions

Please use a linter and formatter.

## What are we measuring?

*For people new to audio programming*

In a computer, audio is typically represented as a stream of floating point numbers between -1.0 and 1.0.
These numbers approximate the continuous wave that hits your eardrums when speakers vibrate.
To represent a sinewave of frequency f, you need 2f points.
Human beings hear up to about 20 kHz; the lowest samplerate in most audio software is 44.1 kHz, safely above 2*20 = 40kHz.

Audio software chunk this data into buffers.
This is done to avoid recomputing expensive operations every sample and leverage vectorized operations.
Let buffer_size = 512.
Then instead of recomputing expensive_function() 44100 times per second per channel,
you recompute about 86 times.

That being said, what audio devs measure is the relative time that the CPU takes to fill the buffer.
In general, perf% = time_compute / time_available

For a buffer size of 512 at 44100 Hz, time_available = 512 / 44100 = 11.6 milliseconds.
What we measure is the fraction of these 11.6 ms that the computation takes to complete.

This fraction can be greater than 100%.
That means the CPU did not compute fast enough, and you get silence.
This is called an overload.
But the CPU returns its results quickly after, which means brief intermissions of silence,
and you get crackling noise.

Note that we're not measuring total CPU usage.
