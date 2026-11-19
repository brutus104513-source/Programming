#pragma once
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include <algorithm>

class Fleet {
    Registry<InventoryItem> items_;
    ServiceCenter service_;
    std::weak_ptr<const ItemIdentity> focus_;
    int noviceThreshold_ = 6;

    std::size_t indexOf(const std::string& id) const {
        for (std::size_t i = 0; i < items_.size(); ++i) {
            if (items_[i].inventoryId() == id) return i;
        }
        throw ItemNotFound(id);
    }
    std::vector<const InventoryItem*> sortedItems() const {
        std::vector<const InventoryItem*> sorted;
        for (const auto& item : items_) sorted.push_back(item.get());
        std::sort(sorted.begin(), sorted.end(), [](const auto* a, const auto* b) {
            return *a < *b;
        });
        return sorted;
    }
public:
    void add(std::unique_ptr<InventoryItem> item) {
        if (!item) throw InvalidArgument("cannot add null item");
        for (const auto& current : items_) {
            if (*current == *item) {
                throw InvalidArgument("duplicate id: " + item->inventoryId());
            }
        }
        if (const auto* transport = dynamic_cast<const Transport*>(item.get())) {
            service_.inspect(*transport);
        }
        items_.add(std::move(item));
    }
    std::size_t size() const { return items_.size(); }
    double energy() const { return sumEnergy(items_); }
    void list(std::ostream& out) const {
        for (const auto* item : sortedItems()) out << *item << '\n';
    }
    void novice(std::ostream& out) const {
        for (const auto* item : sortedItems()) {
            if (item->suitableForNovice(noviceThreshold_)) out << *item << '\n';
        }
    }
    std::size_t countNovice() const {
        std::size_t count = 0;
        for (const auto& item : items_) {
            if (item->suitableForNovice(noviceThreshold_)) ++count;
        }
        return count;
    }
    void setNoviceThreshold(int threshold) { noviceThreshold_ = checkedScore(threshold); }
    void focus(const std::string& id) { focus_ = items_[indexOf(id)].weakIdentity(); }
    void showFocus(std::ostream& out) const {
        if (const auto card = focus_.lock()) out << card->id << ' ' << card->title << '\n';
        else out << "removed / expired\n";
    }
    void remove(const std::string& id) { items_.erase(indexOf(id)); }
};
