#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct VIDEO
{
	unsigned char symb;
	unsigned char attr;
};

#define COLOR_COUNT 7

unsigned char colors[7]={0x0B,0x4A,0x6C,0xA4, 0xAA, 0x74, 0xf1}; //array of colors for videobuffer
char color=0x5E;                                                 //default color;

void print()                                                     //Print all 6 registers
{
	char temp;
	int i,val;
	VIDEO far* screen = (VIDEO far *)MK_FP(0xB800, 0);           
    
	val=inp(0x21);
    for(i=7;i>=0;i--)             //find bits
	{
		temp=val%2;
		val/=2;                   //fill the screen
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
}
	screen++;
	val=inp(0xA1);
	for (i=7;i>=0;i--)
	{
		temp=val%2;
		val/=2;
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
	}
	screen+=63;
	outp(0x20,0x0A);
	val=inp(0x20);
	for (i=7;i>=0;i--)
	{
		temp=val%2;
		val/=2;
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
	}
	screen++;
	outp(0xA0,0x0A);
	val=inp(0xA0);
	for (i=7;i>=0;i--)
	{
		temp=val%2;
		val/=2;
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
	}
	screen+=63;
	outp(0x20,0x0B);
	val=inp(0x20);
	for (i=7;i>=0;i--)
	{
		temp=val%2;
		val/=2;
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
	}
	screen++;
	outp(0xA0,0x0b);
	val=inp(0xA0);
	for (i=7;i>=0;i--)
	{
		temp=val%2;
		val/=2;
		screen->symb=temp+'0';
		screen->attr=color;
		screen++;
	}
}
//IRQ0-7
void interrupt (*int8) (...);
void interrupt (*int9) (...);
void interrupt (*int10) (...);
void interrupt (*int11) (...);
void interrupt (*int12) (...);
void interrupt (*int13) (...);
void interrupt (*int14) (...);
void interrupt (*int15) (...);

void interrupt (*int16) (...);
void interrupt (*int17) (...);
void interrupt (*int18) (...);
void interrupt (*int19) (...);
void interrupt (*int20) (...);
void interrupt (*int21) (...);
void interrupt (*int22) (...);
void interrupt (*int23) (...);

// new interrupt handlers
void interrupt  int60(...) { print(); int8(); }
void interrupt  int61(...) { 
    color=colors[rand() % COLOR_COUNT]; 
    print(); 
    int9(); 
}
void interrupt  int62(...) { print(); int10(); }
void interrupt  int63(...) { print(); int11(); }
void interrupt  int64(...) { print(); int12(); }
void interrupt  int65(...) { print(); int13(); }
void interrupt  int66(...) { print(); int14(); }
void interrupt  int67(...) { print(); int15(); }

void interrupt  int68(...) { print(); int16(); }
void interrupt  int69(...) { print(); int17(); }
void interrupt  int70(...) { print(); int18(); }
void interrupt  int71(...) { print(); int19(); }
void interrupt  int72(...) { print(); int20(); }
void interrupt  int73(...) { print(); int21(); }
void interrupt  int74(...) { print(); int22(); }
void interrupt  int75(...) { print(); int23(); }

void init()
{
	//IRQ0-7
	int8 = getvect(0x08);  // IRQ0 - system timer
	int9 = getvect(0x09);  // IRQ1 - keyboard controller
	int10 = getvect(0x0A); // IRQ2 - cascaded signals from IRQs 8-15 (any devices configured to use IRQ2 will actually be using IRQ9)
	int11 = getvect(0x0B); // IRQ3 - serial port controller for serial port 2 (shared with  serial port 4, if present)
	int12 = getvect(0x0C); // IRQ4 - serial port controller for serial port 1 (shared with serial port 3, if present)
	int13 = getvect(0x0D); // IRQ5 - parallel port 2 and 3 or sound card
	int14 = getvect(0x0E); // IRQ6 - floppy disk controller
	int15 = getvect(0x0F); // IRQ7 - parallel port 1. It is used for printers or for any parallel port if a printer is not present
    
	//IRQ8-15
	int16 = getvect(0x70); // IRQ8 - real-time clock (RTC)
	int17 = getvect(0x71); // IRQ9 - Advanced Configuration and Power Interface (ACPI) system control interrupt
	int18 = getvect(0x72); // IRQ10 - the interrupt is left open for the use of peripherals (open interrupt/available, SCSI or NIC)
	int19 = getvect(0x73); // IRQ11 - the interrupt is left open for the use of peripherals (open interrupt/available, SCSI or NIC)
	int20 = getvect(0x74); // IRQ12 - mouse on PS/2 connector
	int21 = getvect(0x75); // IRQ13 - CPU co-processor or integrated floating point unit or inter-processor interrupt (use depends on OS)
	int22 = getvect(0x76); // IRQ14 - primary ATA channel (ATA interface usually serves hard disk drives and CD drives)
	int23 = getvect(0x77); // IRQ15 - secondary ATA channel

	//set new handlers for IRQ0-7
	setvect(0x08, int60); //08h
	setvect(0x09, int61); 
	setvect(0x0A, int62); 
	setvect(0x0B, int63); 
	setvect(0x0C, int64); 
	setvect(0x0D, int65); 
	setvect(0x0E, int66); 
	setvect(0x0F, int67);
    
	//set new handlers for IRQ8-15
	setvect(0x90, int68); //90h
	setvect(0x91, int69); 
	setvect(0x92, int70); 
	setvect(0x93, int71); 
	setvect(0x94, int72); 
	setvect(0x95, int73); 
	setvect(0x96, int74); 
	setvect(0x97, int75); 
    
	_disable(); // disable interrupts handling (cli)

	// master 
	outp(0x20, 0x11);	//ICW1
	outp(0x21, 0x08);   //ICW2 - base vector for maser
	outp(0x21, 0x04);	//ICW3
	outp(0x21, 0x01);	//ICW4

	// slave
	outp(0xA0,0x11);    //ICW1
	outp(0xA1,0x90);	//ICW2 - base vector for slave
	outp(0xA1,0x04);    //ICW3
	outp(0xA1,0x01);    //ICW4

	_enable(); // enable interrupt handling (sti)
}

int main()
{
	unsigned far *fp;      // declare pointer
	init();                // execute initialization

	FP_SEG (fp) = _psp; // get segment
	FP_OFF (fp) = 0x2c; // get data segment offset with environment variables
	_dos_freemem(*fp);  // free

	_dos_keep(0,(_DS -_CS)+(_SP/16)+1); // left program resident, 1st param - ending code,
                                        // 2nd param - volume of memory, that must be reserved for program after ending
	return 0;
}
