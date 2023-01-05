This utility for AIX 4.3 (and possibly 5.1) allows reading out and printing the POS (Programmable Option Select) registers of IBM MicroChannel compatible adapters on POWER, POWER2 and PowerPC based UNIX systems.

It will drive the dedicated CD_SETUP# signals of all 8 cards and read out each MicroChannel AdapterID, followed by the 4 bytes of option select data pos[0-3] and the two registers of the POS subaddress extension:

```
100h	POS register 0: Adapter ID low-order byte
101h	POS register 1: Adapter ID high-order byte
102h	POS register 2: Option select data pos[0]
103h	POS register 3: Option select data pos[1]
104h	POS register 4: Option select data pos[2]
105h	POS register 5: Option select data pos[3]
106h	POS register 6: Subaddress extension
107h	POS register 7: Subaddress extension
```

Example output:

```
CDID of slot 1: 0x8F96
  POS[0] register = 0x96
  POS[1] register = 0x8F
  POS[2] register = 0x53
  POS[3] register = 0x00
  POS[4] register = 0x01
  POS[5] register = 0xF2
  POS[6] register = 0x01
  POS[7] register = 0x01

  The card is enabled.
  'Channel check' exceptions are not supported.

CDID of slot 2: 0x8F62
  POS[0] register = 0x62
  POS[1] register = 0x8F
  POS[2] register = 0x1F
  POS[3] register = 0x40
  POS[4] register = 0x03
  POS[5] register = 0xFF
  POS[6] register = 0x00
  POS[7] register = 0x00

  The card is enabled.
  'Channel check' exceptions are not supported.

CDID of slot 3: 0xFFFF
CDID of slot 4: 0xDFE5
  POS[0] register = 0xE5
  POS[1] register = 0xDF
  POS[2] register = 0x35
  POS[3] register = 0x01
  POS[4] register = 0x02
  POS[5] register = 0x99
  POS[6] register = 0x00
  POS[7] register = 0xFF

  The card is enabled.
  'Channel check' exceptions are supported.
  No exceptions are active.

CDID of slot 5: 0xFFFF
CDID of slot 6: 0xFFFF
CDID of slot 7: 0xFFFF
CDID of slot 8: 0xFFFF
```