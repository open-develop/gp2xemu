# Introduction #

I was looking up and down for a fixed address offset where the ARM940 exception vectors live, but then I got help from roxfan on #edev @ FreeNode to understand how the Memory Banking works. And it all comes to place.

# The DUAL CPU I/F interface #
See the MMSP2 docs, page 79 for more information.
Register DUALCTRL940 address 0xC0003B48 controls both the _running state_ of the ARM940, and its _starting address_ where its **exception vectors** live.
Bit 7 toggles between running and reset state.
Bits [6:0] defines the 940BANK, which works like a memory offset which affects the upper eight bits of the 940T's memory address.
The formula is as follows:
940 physical address = 940 address + (940BANK<<24)
Where _940 address_ is the address the from the 940T's perspective, while _physical address_ is the actual memory accessed.

Example: With 940BANK set to 0x1, before starting the 940T, it would find its RESET vector at address 0x01000000, but _see_ that address as address zero.

The ARM940T can also access peripherals via the hardware registers just like the ARM920T, but in order to compensate for the banking, you have to subtract 940BANK<<24 from the address you want to access.