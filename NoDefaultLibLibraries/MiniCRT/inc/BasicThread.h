#pragma once

namespace MiniCRT
{
  class BasicThread
  {
  public:
    using Function = void(*)(void*);

    BasicThread();
    explicit BasicThread(Function&& func, void* arg = nullptr);
    BasicThread(const BasicThread&) = delete;
    BasicThread(BasicThread&& other) noexcept;
    BasicThread& operator=(const BasicThread&) = delete;
    BasicThread& operator=(BasicThread&&) noexcept;
   ~BasicThread();

    void Swap(BasicThread& other);

    /// <summary>
    /// Returns true if the thread is joinable
    /// </summary>
    /// <returns></returns>
    bool IsJoinable() const;

    /// <summary>
    /// Joins the this thread to the main thread
    /// </summary>
    void Join();

    /// <summary>
    /// Detachs this thread
    /// </summary>
    void Detach();

    /// <summary>
    /// Returns the native handle to this thread
    /// </summary>
    /// <returns></returns>
    void* NativeHandle() const;

  protected:
    static unsigned long StartRoutine(BasicThread*);

  private:
    void* m_thread;
    unsigned long m_id;
    Function m_function;
    void* m_arg;
  };
}
