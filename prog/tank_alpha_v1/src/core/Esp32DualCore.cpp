// Author: John-William Lebel, 2021-04-10, creation

#include "Esp32DualCore.h"

void Esp32DualCore::init()
{
    // Disable whatchdogs on core 0. 
    // This prevents the kernel from rebooting
    // for some faults related to whatchdogs. 
    disableCore0WDT();

    // Create a task handler
    static TaskHandle_t secondCoreTaskHandler;

    // Create a task
    xTaskCreatePinnedToCore(
        Esp32DualCore::_secondCoreRootTask, // Task function
        "secondCore",                       // Name of task
        SECOND_CORE_USABLE_STACK_SIZE,      // Stack size
        NULL,                               // Parameters
        1,                                  // Priority
        &secondCoreTaskHandler,             // Task handler
        0                                   // Task pinned to core 0
    );
}

void Esp32DualCore::_secondCoreRootTask(void* params)
{
    Esp32DualCore::main();
}