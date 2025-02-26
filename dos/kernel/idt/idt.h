#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>

#define IDT_SIZE 512

#define IDT_TYPE_INTR_R3 0xEE

struct idt_desc
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_2;
} __attribute__((packed));

struct idtr_desc
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init(void);
void idt_set(int index, uint32_t offset, uint16_t selector, uint8_t type_attr);

#endif