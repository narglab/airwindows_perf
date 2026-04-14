# Public TODO-list

## juce
Make a JUCE template; prototype with DitherBox for now.
Port each plugin to JUCE as is.

## versioning
People might want to change formats, e.g. vst2 -> vst3.
As I'm porting I might as well distribute individual .vst3 (I can only build for Win).
Test if Consolidated can retrieve settings of .vst2, and if not, etc.
    If I go this route: separate the branches between I. identical / II. my own twist
    Then versioning is easy: same metadata for I (compatibility), my own names for II.

## standardize airwindows GUI.
Resizeable GUI like later Consoles X and H.
Optional Meter/DarkMeter where relevant (for example, saturation & slew plugins).
Copy/paste state on plugin.
Basic preset manager for complex plugins.
I/O and polarity flip control in the top bar.
Integrated theme customization with Airwindows_globals (syncs across all AW plugins).
Option: 32/64 bit buss. Each plugin remembers.
Option: dithering.
Option: oversampling with offline rendering.
Self-documenting: text in bottom bar that explains the knobs, "?" icon that displays airwindowpedia entry.

## GUI generator
Write meta code generator that outputs a GUI template as a starting point.
Easier to begin with: copy/paste a template with N knobs to start a plugin with N knobs.

## possible performance gains
Horner's method for polynomial
Range reduction
Vectorization (see how to detect architecture; can assume SSE for now)
Optional 32bit/64bit processing (sync all instances).
Optional dithering.

## profiling + graphs
I should make a program that measures CPU_time%. (for DAW-like buffers: up to 2048)
Use it for profiling and to post bar graphs on here. 

## contribute.md
Write a document for people who want to contribute.
Write my method for current plugins (should be a changelog to explain reasoning behind mods, not just commit messages).

## installation manager
Not anytime soon (overlap with Consolidated), but there are a lot of AW plugins and they're categorized; idea makes sense to me.
