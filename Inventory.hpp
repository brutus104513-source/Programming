#pragma once
#include "Errors.hpp"
#include <cmath>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

inline double checkedEnergy(double value) {
    if (!std::isfinite(value) || value < 0) {
        throw InvalidArgument("energy must be finite and non-negative");
    }
    return value;
}
inline int checkedScore(int value) {
    if (value < 1 || value > 10) {
        throw InvalidArgument("score must be in 1..10");
    }
    return value;
}

struct ItemIdentity {
    std::string id;
    std::string title;
};

class InventoryItem {
public:
    virtual ~InventoryItem() = default;
    virtual const std::string& inventoryId() const = 0;
    virtual const std::string& name() const = 0;
    virtual void describe(std::ostream& out) const = 0;
    virtual std::weak_ptr<const ItemIdentity> weakIdentity() const = 0;
    virtual double dailyEnergy() const { return 0.0; }
    virtual bool suitableForNovice(int) const { return false; }
};

inline std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
    item.describe(out);
    return out;
}
inline bool operator<(const InventoryItem& a, const InventoryItem& b) {
    return a.inventoryId() < b.inventoryId();
}
inline bool operator==(const InventoryItem& a, const InventoryItem& b) {
    return a.inventoryId() == b.inventoryId();
}

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;
    virtual double dailyEnergy() const = 0;
};

class StoredItem : public InventoryItem {
    std::shared_ptr<const ItemIdentity> identity_;
public:
    StoredItem(std::string id, std::string title) {
        if (id.empty() || id.find_first_of(" \t\r\n") != std::string::npos) {
            throw InvalidArgument("id must be non-empty and contain no whitespace");
        }
        if (title.find_first_not_of(" \t\r\n") == std::string::npos) {
            throw InvalidArgument("name must be non-empty");
        }
        identity_ = std::make_shared<const ItemIdentity>(
            ItemIdentity{std::move(id), std::move(title)});
    }
    StoredItem(const StoredItem&) = delete;
    StoredItem& operator=(const StoredItem&) = delete;
    const std::string& inventoryId() const override { return identity_->id; }
    const std::string& name() const override { return identity_->title; }
    void describe(std::ostream& out) const override {
        out << inventoryId() << ' ' << name();
    }
    std::weak_ptr<const ItemIdentity> weakIdentity() const override {
        return identity_;
    }
};
