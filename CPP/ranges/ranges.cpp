#include <ranges>
#include <cstdio>

auto main(int argc, char *argv[]) -> int
{
  for(auto&& num : std::views::iota(1, 5)){
    printf("%d", num);
  }
  puts("\n");
  return 0;
}
