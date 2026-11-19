#pragma once
#include "Inventory.hpp"
#include <cstddef>
#include <memory>
#include <vector>

template<typename T>
class Registry {
    std::vector<std::unique_ptr<T>> items_;
public:
    void add(std::unique_ptr<T> item) {
        if (!item) throw InvalidArgument("cannot add null item");
        items_.push_back(std::move(item));
    }
    std::size_t size() const { return items_.size(); }
    const T& operator[](std::size_t index) const { return *items_.at(index); }
    void erase(std::size_t index) {
        if (index >= size()) throw InvalidArgument("registry index out of range");
        items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(index));
    }
    auto begin() const { return items_.cbegin(); }
    auto end() const { return items_.cend(); }
    friend std::ostream& operator<<(std::ostream& out, const Registry& registry) {
        for (const auto& item : registry) out << *item << '\n';
        return out;
    }
};

template<typename Container>
double sumEnergy(const Container& items) {
    double total = 0.0;
    for (const auto& item : items) total += item->dailyEnergy();
    if (!std::isfinite(total)) throw InvalidArgument("total energy overflow");
    return total;
}
