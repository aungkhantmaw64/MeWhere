#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace osal {

class ThreadUserCtx
{};

class Thread
{
public:
  using EntryPoint = std::function<void(ThreadUserCtx*)>;

  Thread(const EntryPoint& entry_point,
         ThreadUserCtx* p_ctx,
         const uint16_t stack_size,
         const uint8_t priority,
         const std::string task_name);

  virtual ~Thread() = default;

protected:
  const EntryPoint& m_entry_point;
  ThreadUserCtx* m_p_ctx;
  uint16_t m_stack_size;
  uint8_t m_priority;
  std::string m_name;
};

class FreeRTOSThread : public Thread
{
public:
  FreeRTOSThread(const EntryPoint& entry_point,
                 ThreadUserCtx* p_ctx,
                 const uint16_t stack_size,
                 const uint8_t priority,
                 const std::string task_name);
  ~FreeRTOSThread() override;

private:
  struct Impl;
  std::unique_ptr<Impl> m_impl;
  static void entry_point(void* user_ctx);
};

} // namespace osal
