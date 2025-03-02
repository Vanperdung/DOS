#include <stdint.h>
#include <stddef.h>

#include "idt.h"
#include "vendor_excpts.h"
#include "dos.h"
#include "utils/mem_utils.h"

struct idt_desc idt[IDT_SIZE];
struct idtr_desc idtr;

extern void idt_load(struct idtr_desc *idtr);

void idt_init(void)
{
    memset(idt, 0, sizeof(idt));

    // Load the IDT descriptor
    idt_set(0, (uint32_t)vendor_excpt_divide_error, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(1, (uint32_t)vendor_excpt_debug_exception, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(2, (uint32_t)vendor_excpt_nmi, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(3, (uint32_t)vendor_excpt_breakpoint, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(4, (uint32_t)vendor_excpt_overflow, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(5, (uint32_t)vendor_excpt_bound_range_exceeded, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(6, (uint32_t)vendor_excpt_invalid_opcode, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(7, (uint32_t)vendor_excpt_device_not_available, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(8, (uint32_t)vendor_excpt_double_fault, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(9, (uint32_t)vendor_excpt_coprocessor_segment_overrun, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(10, (uint32_t)vendor_excpt_invalid_tss, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(11, (uint32_t)vendor_excpt_segment_not_present, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(12, (uint32_t)vendor_excpt_stack_segment_fault, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(13, (uint32_t)vendor_excpt_general_protection, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(14, (uint32_t)vendor_excpt_page_fault, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(16, (uint32_t)vendor_excpt_fpu_floating_point_error, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(17, (uint32_t)vendor_excpt_alignment_check, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(18, (uint32_t)vendor_excpt_machine_check, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);
    idt_set(19, (uint32_t)vendor_excpt_simd_floating_point_exception, GDT_CODE_SEG_ADDR, IDT_TYPE_INTR_R3);

    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint32_t)idt;

    // Load the IDT
    idt_load(&idtr);
}

void idt_set(int intr_no, uint32_t offset, uint16_t selector, uint8_t type_attr)
{
    if (intr_no < 0 || intr_no >= IDT_SIZE)
        return;

    idt[intr_no].offset_1 = (uint16_t)(offset & 0x0000FFFF);
    idt[intr_no].selector = selector;
    idt[intr_no].zero = 0;
    idt[intr_no].type_attr = type_attr;
    idt[intr_no].offset_2 = (uint16_t)((offset & 0xFFFF0000) >> 16);
}