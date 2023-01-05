This utility for AIX 4.3 (and possibly 5.1) allows reading out and printing the POS (Programmable Option Select) registers of IBM MicroChannel compatible adapters on POWER, POWER2 and PowerPC based UNIX systems.

It will drive the dedicated CD_SETUP# signals of each card and read out the MicroChannel AdapterID, followed by the 4 bytes of option select data pos[0-3] and the two registers of the POS subaddress extension:

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
