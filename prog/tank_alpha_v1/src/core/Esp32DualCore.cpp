// Author: John-William Lebel, 2021-04-10, creation

#include "Esp32DualCore.h"

void Esp32DualCore::init()
{
    // disable the kernel panic. 
    // this prevents the kernel from rebooting for some of the
    // faults it detects. 
    disableCore0WDT();

    // create a task handler
    static TaskHandle_t secondCoreTaskHandler;

    // create a task
    xTaskCreatePinnedToCore(
        Esp32DualCore::_secondCoreRootTask, // task function
        "secondCore",                       // name of task
        SECOND_CORE_USABLE_STACK_SIZE,      // stack size
        NULL,                               // parameters
        1,                                  // priority
        &secondCoreTaskHandler,             // task handler
        0                                   // task pinned to core 0
    );
}

void Esp32DualCore::_secondCoreRootTask(void* params)
{
    Esp32DualCore::main();
}