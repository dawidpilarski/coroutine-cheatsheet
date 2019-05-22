#include <cppcoro/read_only_file.hpp>
#include <cppcoro/task.hpp>

cppcoro::task<int> count_lines(std::string path)
{
  auto file = co_await cppcoro::read_only_file::open(path);

  int lineCount = 0;
  char buffer[1024];
  size_t bytesRead;
  std::uint64_t offset = 0;
  do
  {
    bytesRead = co_await file.read(offset, buffer, sizeof(buffer));
    lineCount += std::count(buffer, buffer + bytesRead, '\n');
    offset += bytesRead;
  } while (bytesRead > 0);

  co_return lineCount;
}
