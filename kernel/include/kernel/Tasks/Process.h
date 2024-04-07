#include <kernel/Memory/PhysicalAddress.h>

using SegmentSelector = u16;

class Process {

private:
    PhysicalAddress m_cr3;

    SegmentSelector m_cs;
    SegmentSelector m_ds;
    SegmentSelector m_es;
    SegmentSelector m_fs;
    SegmentSelector m_gs;
    SegmentSelector m_ss;
};
