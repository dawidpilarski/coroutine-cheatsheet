struct promise_type{
  // creating coroutine object -mandatory
  auto get_return_object();

  // returns awaitable object - mandatory
  auto initial_suspend();
  auto final_suspend();

  void unhandled_exception(); // mandatory

  // one of below is mandatory 
  // and only one must be present
  void return_value(/*type*/);
  void return_void();

  // support for yielding values - returns awaitable
  auto yield_value(/*co_yield operand*/);

  // modification of the awaitable
  auto await_transform(/*co_await operand*/);
};