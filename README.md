# irsf

Vrsion: 0.0.1  	(June 2020)

This is code I worked on in 2019-2020 and uploaded to GitHub just so I would have some of my work online. It has potential for future development, but I am currently not working on it.

IRSF is a QT desktop app for Windows which runs along the iRacing simulator. It captures live telemetry from your car, and converts the forces into sounds to give you a better feel for the car dynamics.
Just like motion rigs can move around due to forces of the car, we try to make this movement into low latency sound to give the user some kind of sense of forces in the car.

It is coded in C++ and features:
- Follows the isocpp.org best practices for C++
- SOLID principles (95%)
- Template specialization for iRacing SDK data types
- Custom templated container (OUContainer)
- QT signals and multithreading
- Binary file serialization
- Follows some of google style guide
- Factory design pattern

Some classes are a little bit larger, and do too many things, since this isn't a project intended to be extremely modular (ie work with other simumlators and telemetry sources), but is rather a small project focused on a specific need that I wanted to code in a short time.

I also haven't included any of the Google Tests.

Libraries used:
- libsnd 
- portaudio (I copied the whole C project here)
- iracing sdk (aka: irsdk)

