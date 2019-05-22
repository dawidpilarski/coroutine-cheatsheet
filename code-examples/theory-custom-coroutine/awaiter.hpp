struct awaiter{
  bool await_ready();
  auto await_suspend(coro_handle_t);
  auto await_resume();
}