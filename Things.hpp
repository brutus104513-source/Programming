#pragma once
#include "Inventory.hpp"

class Helmet final : public StoredItem {
public:
    using StoredItem::StoredItem;
};
class DockStation final : public StoredItem, public EnergyConsumer {
    double energy_;
public:
    DockStation(std::string id, std::string name, double energy)
        : StoredItem(std::move(id), std::move(name)), energy_(checkedEnergy(energy)) {}
    double dailyEnergy() const override { return energy_; }
};
