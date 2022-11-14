#ifndef OUCONTAINER_H
#define OUCONTAINER_H

#include <memory>
#include <vector>

/*
 * Ownable Updateable Container (non-copyable)
 *
This container keeps two lists of objects.
One is the owning list (items) and the other is the non-owning list (items_no).
Users of the container have access to the non-owning list. So when the owning
list is updated by a managing class, the users have the updated list of
raw pointers.
*/
namespace irsf {
template <typename T>
class OUContainer {
 public:
  template <typename... Ts>
  T* AddItem(Ts... args) {
    std::unique_ptr<T> newItem = std::make_unique<T>(args...);

    T* ret = newItem.get();

    items_no.push_back(ret);
    items.emplace_back(std::move(newItem));

    return ret;
  }

  T* AddItem(T& other) {
    std::unique_ptr<T> newItem = std::make_unique<T>(other);

    T* ret = newItem.get();

    items_no.push_back(ret);
    items.emplace_back(std::move(newItem));

    return ret;
  }

  void Clear() {
    items.clear();
    items_no.clear();
  }

  std::vector<T*>& GetItemList() noexcept { return items_no; }

  void EraseAtIndex(std::streamsize index) noexcept {
    decltype(auto) cSize = items.size();

    decltype(auto) cIndex = static_cast<decltype(cSize)>(index);

    if (cIndex <= cSize - 1) {
      items.erase(items.begin() + index);
      items_no.erase(items_no.begin() + index);
    }
  }

 private:
  std::vector<T*> items_no;  // non-owning, available to users

  std::vector<std::unique_ptr<T>> items;  // owning, not available to users
};
}  // namespace irsf
#endif
