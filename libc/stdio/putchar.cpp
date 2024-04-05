#include <stdio.h>

#if defined(__is_libk)
#include <kernel/Devices/DeviceManager.h>
#include <kernel/Devices/tty.h>
#endif

int putchar(int ic)
{
#if defined(__is_libk)
    char c = (char)ic;
    auto& dev_mgr = DeviceManager::the();
    dev_mgr.tty()->write(&c, sizeof(c));
#else
    // TODO: Implement stdio and the write system call.
#endif
    return ic;
}
