#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace osal {

/**
 * @brief User context passed to thread entry points.
 */
class ThreadUserCtx
{};

/**
 * @brief Abstract base class representing a thread.
 *
 * This class encapsulates the basic properties and interface for a thread,
 * including its entry point, user context, stack size, priority, and name.
 */
class Thread
{
public:
  /**
   * @brief Type alias for the thread entry point function.
   * @param ThreadUserCtx* Pointer to user-defined context.
   */
  using EntryPoint = std::function<void(ThreadUserCtx*)>;

  /**
   * @brief Construct a new Thread object.
   * @param entry_point Function to execute in the thread.
   * @param p_ctx Pointer to user context.
   * @param stack_size Stack size for the thread.
   * @param priority Thread priority.
   * @param task_name Name of the thread/task.
   */
  Thread(const EntryPoint& entry_point,
         ThreadUserCtx* p_ctx,
         const uint16_t stack_size,
         const uint8_t priority,
         const std::string task_name);

  /**
   * @brief Destroy the Thread object.
   */
  virtual ~Thread() = default;

protected:
  const EntryPoint& m_entry_point; ///< Thread entry point function.
  ThreadUserCtx* m_p_ctx;          ///< Pointer to user context.
  uint16_t m_stack_size;           ///< Stack size.
  uint8_t m_priority;              ///< Thread priority.
  std::string m_name;              ///< Thread/task name.
};

/**
 * @brief Thread implementation for FreeRTOS.
 *
 * This class provides a concrete implementation of Thread for the FreeRTOS
 * platform.
 */
class FreeRTOSThread : public Thread
{
public:
  /**
   * @brief Construct a new FreeRTOSThread object.
   * @param entry_point Function to execute in the thread.
   * @param p_ctx Pointer to user context.
   * @param stack_size Stack size for the thread.
   * @param priority Thread priority.
   * @param task_name Name of the thread/task.
   */
  FreeRTOSThread(const EntryPoint& entry_point,
                 ThreadUserCtx* p_ctx,
                 const uint16_t stack_size,
                 const uint8_t priority,
                 const std::string task_name);

  /**
   * @brief Destroy the FreeRTOSThread object.
   */
  ~FreeRTOSThread() override;

private:
  struct Impl;                  ///< Opaque implementation details.
  std::unique_ptr<Impl> m_impl; ///< Pointer to implementation.
  /**
   * @brief Static entry point adapter for FreeRTOS.
   * @param user_ctx Pointer to user context.
   */
  static void entry_point(void* user_ctx);
};

} // namespace osal
