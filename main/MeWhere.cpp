#include "Osal.hpp"
#include "esp_log.h"

static const char* TAG = "main";

void
my_task(osal::ThreadUserCtx* p_ctx)
{
  ESP_LOGI(TAG, "Hello");
}

extern "C" void
app_main()
{
  osal::Thread::EntryPoint entry = my_task;
  uint16_t stack_size = 2048;
  uint8_t priority = 5;
  std::string name = "MyTask";
  osal::FreeRTOSThread thread(entry, nullptr, stack_size, priority, name);
}
