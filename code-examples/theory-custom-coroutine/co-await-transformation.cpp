{
  std::exception_ptr exception = nullptr;
  if (not a.await_ready()) {
    suspend_coroutine();
    
    <await_suspend>
  }
  
  resume_point:
  if(exception)
    std::rethrow_exception(exception);
  /*return*/ a.await_resume();
}