#include <kernel/Memory/VirtualAddress.h>

uint16_t VirtualAddress::get_page_table_offset()
{
    return (m_vaddr & (0x3ff << PT_OFFSET_BITS)) >> PT_OFFSET_BITS;
}

uint16_t VirtualAddress::get_page_directory_offset()
{
    return (m_vaddr & (0x3ff << PD_OFFSET_BITS)) >> PD_OFFSET_BITS;
}
