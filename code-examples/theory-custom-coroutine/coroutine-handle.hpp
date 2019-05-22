namespace std {
  template<>
  struct coroutine_handle<void>
  {
    // [coroutine.handle.con], construct/reset
    constexpr coroutine_handle() noexcept;
    constexpr coroutine_handle(nullptr_t) noexcept;
    coroutine_handle& operator=(nullptr_t) noexcept;

    // [coroutine.handle.export.import], export/import
    constexpr void* address() const noexcept;
    constexpr static coroutine_handle from_address(void* addr);

    // [coroutine.handle.observers], observers
    constexpr explicit operator bool() const noexcept;
    bool done() const;

    // [coroutine.handle.resumption], resumption
    void operator()() const;
    void resume() const;
    void destroy() const;

  private:
    void* ptr;  // exposition only
  };

  template<class Promise>
  struct coroutine_handle : coroutine_handle<>
  {
    // [coroutine.handle.con], construct/reset
    using coroutine_handle<>::coroutine_handle;
    static coroutine_handle from_promise(Promise&);
    coroutine_handle& operator=(nullptr_t) noexcept;

    // [coroutine.handle.export.import], export/import
    constexpr static coroutine_handle from_address(void* addr);

    // [coroutine.handle.promise], promise access
    Promise& promise() const;
  };
}