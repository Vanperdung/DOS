#ifndef __IO_H__    
#define __IO_H__

unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);

void outb(unsigned short port, unsigned char data);
void outw(unsigned short port, unsigned short data);

#endif  // __IO_H__