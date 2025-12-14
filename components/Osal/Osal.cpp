#include "Osal.hpp"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/Osal.hpp"

  namespace osal {

  Thread::Thread(const EntryPoint& entry_point,
                 ThreadUserCtx* p_ctx,
                 const uint16_t stack_size,
                 const uint8_t priority,
                 const std::string name)
    : m_entry_point(entry_point)
    , m_p_ctx(p_ctx)
    , m_stack_size(stack_size)
    , m_priority(priority)
    , m_name(name)
  {
  }

  struct FreeRTOSThread::Impl
  {
    TaskHandle_t task_handle = nullptr;
  };

  FreeRTOSThread::FreeRTOSThread(const EntryPoint& entry_point,
                                 ThreadUserCtx* p_ctx,
                                 const uint16_t stack_size,
                                 const uint8_t priority,
                                 const std::string task_name)
    : Thread(entry_point, p_ctx, stack_size, priority, task_name)
    , m_impl(std::make_unique<Impl>())
  {
    xTaskCreate(&FreeRTOSThread::entry_point,
                task_name.c_str(),
                m_stack_size,
                this,
                m_priority,
                &m_impl->task_handle);
  }

  FreeRTOSThread::~FreeRTOSThread() {}

  void FreeRTOSThread::entry_point(void* user_ctx)
  {
    auto* self = static_cast<FreeRTOSThread*>(user_ctx);
    if (self->m_entry_point) {
      self->m_entry_point(self->m_p_ctx);
    }
    vTaskDelete(nullptr);
  }

  } // namespace osal

} // End of extern "C"
