Hi, thank you for your interest in this project!

## Tasks

If you want to help, two important tasks are:
1. Port the plugins to JUCE.
1. Build the plugins for your platform and share them here*;
2. Modernize the C++ code with a focus on performance.

*Distributing vst2 plugins is illegal unless you have a contract with Steinberg.

todo(Gaétan) Musicians might want to build the plugins themselves, so write or redirect to a clear guide to build on all platforms.
todo(Gaétan) Explain how to port vst2 to JUCE vst3.

## Objectives

The main goal here is to (re-)distribute quality free plugins that run fast even on cheap hardware.
The end users are anyone working with audio: musicians, podcasters, ASMRtists, editors, etc.

Optimally, your code should produce the same result as the original and fill the buffer more quickly.
CPU speed is the priority.

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
