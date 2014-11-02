Intervalometer
===========

Schematic, board file, and 3d printed case (.stl) for an intervalometer designed for use with Canon DSLR cameras (uses 2.5mm remote jack).

![Header Image](https://github.com/lhuff/electronics/blob/master/intervalometer/img/board_top.jpg)

This project was mostly done to make use of some spare parts and does not include all of the features that a proper intervalometer should have.

Current Version: V1

Other Features to Add:
- Operation with low frequency clock (realtime clock) [Pads for low frequency clock was included, but not wired to XTAL pins]
- Use of RTC module for exact timing [Timing is currently done with the (terrible) internal RC oscillator of the Attiny]
- Regulation of chip power supplies [Vcc is supplied directly from 3.7V LiPo]
- Better display [Either simpler to cut down components or more detailed to provide more info]

This work is licensed under a Creative Commons 
Attribution-NonCommercial-ShareAlike 4.0 International License.
