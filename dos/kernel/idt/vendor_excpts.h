#ifndef __VENDOR_EXCPTS_H__
#define __VENDOR_EXCPTS_H__

void vendor_excpt_divide_error(void);
void vendor_excpt_debug_exception(void);
void vendor_excpt_nmi(void);
void vendor_excpt_breakpoint(void);
void vendor_excpt_overflow(void);
void vendor_excpt_bound_range_exceeded(void);
void vendor_excpt_invalid_opcode(void);
void vendor_excpt_device_not_available(void);
void vendor_excpt_double_fault(void);
void vendor_excpt_coprocessor_segment_overrun(void);
void vendor_excpt_invalid_tss(void);
void vendor_excpt_segment_not_present(void);
void vendor_excpt_stack_segment_fault(void);
void vendor_excpt_general_protection(void);
void vendor_excpt_page_fault(void);
void vendor_excpt_fpu_floating_point_error(void);
void vendor_excpt_alignment_check(void);
void vendor_excpt_machine_check(void);
void vendor_excpt_simd_floating_point_exception(void);
void vendor_excpt_virtualization_exception(void);

#endif