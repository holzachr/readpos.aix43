

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mdio.h>
#include <errno.h>


main(int argc, char * argv[], char * envp[])
{
	int	slot;	    /* slot of adapters */
	int	id;			/* card id */

    for (slot = 1; slot <= 8; slot++)
	{
        id = readCardId("/dev/bus0", slot);

        printf("CDID of slot %d: 0x%4.4X\n", slot, id);
        
        if (id != 0xFFFF)
        {
            readCardPos("/dev/bus0", slot);
        }
    }

	exit(0);
}


/*
 *  NAME: readCardId
 * 
 *  INPUTS:
 *      bus     - The name of the bus device, for example, bus0.
 *      slot    - The slot number from the parent connection descriptor.
 *                It should be a value of 1 through 8, with 0 being used
 *                for the Standard I/O Planar.
 *
 * RETURNS: Returns 0xFFFF for an empty slot or the card's ID.
 */
int readCardId(char * bus, int slot)
{
	MACH_DD_IO mddRecord;
	uchar pos[2];
	int fd;

	pos[0] = 0xff;
	pos[1] = 0xff;

	/* Decrement slot number found in database */
	slot == (slot--) & 0x0F;

	if (0 > (fd = open(bus, O_RDWR)))
    {
        fprintf(stderr, "Error opening bus.\n");
		return 0xFFFF;
    }

	mddRecord.md_size = 2; 
	mddRecord.md_incr = MV_BYTE;
	mddRecord.md_data = (char *)pos;      
	mddRecord.md_addr = POSREG(0, slot);

	if (0 > ioctl(fd, MIOCCGET, &mddRecord))
    {
        fprintf(stderr, "Error in ioctl: %s\n", strerror(errno));
        close(fd);
		return 0xFFFF;
    }

	close(fd);

    return ((pos[1] << 8) | pos[0]);
}

/*
 *  NAME: readCardPos
 * 
 *  INPUTS:
 *      bus     - The name of the bus device, for example, bus0.
 *      slot    - The slot number from the parent connection descriptor.
 *                It should be a value of 1 through 8, with 0 being used
 *                for the Standard I/O Planar.
 *
 * RETURNS: Returns 0 in case of success.
 */
int readCardPos(char * bus, int slot)
{
	MACH_DD_IO mddRecord;
	uchar pos[8];
	int fd, i, rc;

	memset(pos, 0xFF, sizeof(pos));

	/* Decrement slot number found in database */
	slot == (slot--) & 0x0F;

	if (0 > (fd = open(bus, O_RDWR)))
    {
        fprintf(stderr, "Error opening bus.\n");
		return -1;
    }

	mddRecord.md_size = 8; 
	mddRecord.md_incr = MV_BYTE;
	mddRecord.md_data = (char *)pos;      
	mddRecord.md_addr = POSREG(0, slot);

	if ((rc = ioctl(fd, MIOCCGET, &mddRecord)) < 0)
    {
        fprintf(stderr, "Error in MIOCCGET ioctl: %s\n", strerror(errno));
        close(fd);
		return -1; 
    }
    
    for (i = 0; i < 8; i++)
    {
        printf("  POS[%d] register = 0x%2.2X\n", i, pos[i]);
    }
    printf("\n");
    
    if (pos[2] & (1 << 0))
    {
        printf("  The card is enabled.\n");
    }
    else
    {
        printf("  The card is disabled.\n");
    }    
   
    if (!(pos[5] & (1 << 6)))
    {
        printf("  'Channel check' exceptions are supported.\n");
        
        if (!(pos[5] & (1 << 7)))
        {
            printf("  A 'channel check' exception is active.\n");
        }
        else
        {
            printf("  No exceptions are active.\n");
        }        
    }
    else
    {
        printf("  'Channel check' exceptions are not supported.\n");
    }
    
    printf("\n");

	close(fd);   

    return 0;
}


