#ifndef IDT_H
#define IDT_H

// http://wiki.osdev.org/Interrupt_Descriptor_Table

#include "types.h"

// Starts packing the data. Pragma directive makes the struct occupy only 16
// bytes.
#pragma pack(push)
// Pack size.
#pragma pack(1)

/* Interrupt Descriptor */
typedef struct{
  word    offset_l,
          selector;
  byte    zero_byte,
          descriptor;
  word    offset_m;
  dword   offset_h,
          zero_dword;
}INT_DESCRIPTOR;
// Stops packing data.
#pragma pack(pop)

/* Pointer to the beggining of the Interrupt Descriptor Table. */
static INT_DESCRIPTOR * idt = (INT_DESCRIPTOR *) 0x0;
/* Pointer to the end of the Interrupt Descriptor Table. */
static INT_DESCRIPTOR * idt_end = (INT_DESCRIPTOR *) 0xfff;
/* Interrupt request first index */
static int IRQ_INDEX = 0x20;

/*
 *  Adds an interrupt descriptor to the Interrupt Descriptor Table.
 *  Parametres:
 *    -index:     index of the table.
 *    -selector:  code segment selector. (0x08 is an usual value)
 *    -offset:    memory address of the function associated to the interrupt.
 *    -type_attr: descriptor of the entry.
 *  Return:
 *    True if the entry is set.
 */
boolean
setup_idt_entry(int index, byte selector, qword offset, byte type_attr);

/*
 *	Executes the Interrupt Requested.
 *	Parametres:
 *	  -irq_number: number of the interrupt.
 */
void
irq_handler(int irq_number);

/*
 *	Loads the custom Interrupt Descriptors on the Interrupt Descriptor Table.
 */
void
set_idt();

#endif
