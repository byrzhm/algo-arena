#include <list>
#include <unordered_map>

namespace slow {

class LRUCache
{
public:
  explicit LRUCache(int capacity)
    : capacity(capacity)
  {
  }

  int get(int key)
  {
    if (map.count(key) > 0) {
      history.remove(key);
      history.emplace_front(key);
      return map[key];
    }
    return -1;
  }

  void put(int key, int value)
  {
    history.remove(key);
    history.emplace_front(key);
    map[key] = value;
    while (history.size() > capacity) {
      map.erase(history.back());
      history.pop_back();
    }
  }

private:
  std::list<int> history;
  std::unordered_map<int, int> map;
  int capacity;
};

}  // namespace slow

namespace fast {

class LRUCache
{
public:
  explicit LRUCache(int capacity)
    : capacity(capacity)
  {
  }

  int get(int key)
  {
    if (map.count(key) > 0) {
      auto iter = map[key];
      history.splice(history.begin(), history, iter);
      return iter->second;
    }
    return -1;
  }

  void put(int key, int value)
  {
    if (map.count(key) > 0) {
      auto iter = map[key];
      history.splice(history.begin(), history, iter);
      iter->second = value;
    } else {
      history.emplace_front(key, value);
      map[key] = history.begin();
      while (history.size() > capacity) {
        map.erase(history.back().first);
        history.pop_back();
      }
    }
  }

private:
  std::list<std::pair<int, int>> history;
  std::unordered_map<int, decltype(history)::iterator> map;
  int capacity;
};

}  // namespace fast
