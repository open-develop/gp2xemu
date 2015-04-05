# Introduction #

---

**Gp2xemu** is an emulator which emulates the [gp2x](http://www.gp2x.co.uk) handheld device.
The goal is to be able to boot a working bootloader and OS. By emulating an RS-232 port via the EXT port, one can get visual feedback without audio and graphics. Audio and graphics will be added at the end of the development cycle, if **at all**. This emulator isn't made with gaming in mind, but to aid developers in debugging firmware.

## Documentation ##
  * Helpful documentation can be found [here](http://www.mechcore.net/files/docs/)
  * GNU ARM as reference for macros, directives and psuedo-instructions can be found [here](http://www.mechcore.net/files/docs/GasARMRef.pdf)
  * A nice ARM opcode reference made by Re-Eject can be found [here](http://www.mechcore.net/files/docs/armref.pdf)
  * A nice ARM Thumb opcode reference made by Re-Eject can be found [here](http://www.mechcore.net/files/docs/ThumbRefV2-beta.pdf)
  * The specifications for the MMSP2 System-On-A-Chip can be found [here](http://www.mechcore.net/files/docs/MP2520F_Manual_Eng_V1.0.pdf)

The GP2X uses some extra peripherals which is not a part of the MMSP2. I'll add them later when the time comes.
### Suggested books ###
The _ARM System Developer's Guide_ (Morgan Kaufmann series) can be bought from [Amazon](http://www.amazon.com/ARM-System-Developers-Guide-Architecture/dp/1558608745)

## TODO ##
  1. Implement the full ARMv4 instruction set and the _M_ extension (xMLAL, xMULL). This also includes defining structures for the PSRs, the 16 general-purpose registers and the banked registers.
  1. Come up with a code design for reading the NAND image located under /trunk/gp2x-emu/nand, fetch the instructions and dispatching them.
  1. Implement structures to hold states related to the MMU and MPU ( cp15).
  1. Implement structures to hold states related to SD memory (cache regions and access regions?)
  1. Abstract away the difference between absolute memory and hardware registers, and allow relocation.
  1. Implement the different peripherals, starting with the _memory controller_, _interrupt controller_, _timer_/_watchdog timer_ and the _RS-232 port_.
  1. Implement emulation of EmbeddedIce and JTAG?