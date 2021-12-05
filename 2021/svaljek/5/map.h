#include <cstdint>
#include <unordered_map>

template <int SIZE = 1000>
class Map {
  std::unordered_map<uint32_t, uint8_t> map;

public:

  void add(int x, int y) {
      map[SIZE*x + y]++;
  }

  int count() {
      int counter{0};
      for (const auto& point: map)
          if (point.second > 1) counter++;
      return counter;
  }
};
