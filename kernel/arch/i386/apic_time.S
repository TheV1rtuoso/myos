
.set APIC_DISABLE,  0x10000
.set APIC_TMRINITCNT,  0x380
.set APIC_TMRCURRCNT,  0x390
.set APIC_TMRDIV,  0x3E0
#define APIC_LVT_TMR 0x320


.global calibrate_apic_timer
.section .text
# takes apic pointer as argument
calibrate_apic_timer:
        pushl		%ebp
        movl		%esp, %ebp
        pushl           %ebx
        pushl           %edx
        # TODO save register
        mov       16(%esp), %edi
	movl      $32, APIC_LVT_TMR(%edi)
	#set up divide value to 16
	movl     $0x03,  APIC_TMRDIV(%edi)
        # ebx=0xFFFFFFFF;
        xorl        %ebx, %ebx
        decl        %ebx

        # initialize PIT Ch 2 in one-shot mode
        # waiting 1 sec could slow down boot time considerably,
        # so we'll wait 1/100 sec, and multiply the counted ticks
        mov        $0x61, %dx
        inb         %dx, %al
        andb        $0xfd, %al
        orb         $0x1, %al
        outb        %al, %dx
        movb        $0xb2, %al
        outb        %al, $0x43
        # 1193180/100 Hz = 11931 = 0x2e9b
        movb        $0x9b, %al     # LSB
        outb        %al, $0x42
        inb         $0x60, %al     # short delay
        movb        $0x2e, %al     # MSB
        outb        %al, $0x42
        # reset PIT one-shot counter (start counting)
        inb         %dx, %al
        andb        $0xfe, %al
        outb        %al, %dx      # gate low
        orb         $0x1, %al
        outb        %al, %dx      # gate high
        # reset APIC timer (set counter to -1)
        movl        %ebx, APIC_TMRINITCNT(%edi)
        # now wait until PIT counter reaches zero
wait:   inb         %dx, %al
        andb        $0x20, %al
        jz          wait
        # stop APIC timer
        movl        $APIC_DISABLE, APIC_LVT_TMR(%edi)
        movl	    APIC_TMRCURRCNT(%edi), %eax
        popl           %edx
        popl           %ebx
        leave
        ret
