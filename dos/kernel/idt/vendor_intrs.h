#ifndef __VENDOR_INTRS_H__
#define __VENDOR_INTRS_H__

void vendor_intr_divide_error(void);
void vendor_intr_debug_exception(void);
void vendor_intr_nmi(void);
void vendor_intr_breakpoint(void);
void vendor_intr_overflow(void);
void vendor_intr_bound_range_exceeded(void);
void vendor_intr_invalid_opcode(void);
void vendor_intr_device_not_available(void);
void vendor_intr_double_fault(void);
void vendor_intr_coprocessor_segment_overrun(void);
void vendor_intr_invalid_tss(void);
void vendor_intr_segment_not_present(void);
void vendor_intr_stack_segment_fault(void);
void vendor_intr_general_protection(void);
void vendor_intr_page_fault(void);
void vendor_intr_fpu_floating_point_error(void);
void vendor_intr_alignment_check(void);
void vendor_intr_machine_check(void);
void vendor_intr_simd_floating_point_exception(void);
void vendor_intr_virtualization_exception(void);

#endif