#include <kernel/Devices/DeviceManager.h>
#include <kernel/Devices/Timer.h>
#include <kernel/Devices/Keyboard.h>
#include <kernel/Devices/TTY.h>
#include <kernel/Memory/Heap.h>
#include <stdio.h>

static DeviceManager dev_mgr;

static Singleton<DeviceManager, []() -> DeviceManager* {return &dev_mgr;}> _dev_mgr;

void DeviceManager::init_devices()
{
    //TODO Debug printf("Initializing devices\n");
    auto timer = new Timer;
    auto keyboard = new PS_2Keyboard;
    set_timer(timer);
    set_keyboard(keyboard);
}

DeviceManager& DeviceManager::the()
{
    return _dev_mgr;
}
