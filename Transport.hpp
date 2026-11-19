#pragma once
#include "Inventory.hpp"

struct ModelSpec {
    std::string category;
    int wheels;
};

class Transport : public StoredItem {
    int score_;
    std::shared_ptr<const ModelSpec> spec_;
public:
    Transport(std::string id, std::string name, int score,
              std::shared_ptr<const ModelSpec> spec)
        : StoredItem(std::move(id), std::move(name)),
          score_(checkedScore(score)), spec_(std::move(spec)) {
        if (!spec_) throw InvalidArgument("missing model specification");
    }
    bool suitableForNovice(int threshold) const override { return score_ >= threshold; }
    const std::shared_ptr<const ModelSpec>& modelSpec() const { return spec_; }
};

class ElectricScooter final : public Transport, public EnergyConsumer {
    double energy_;
public:
    ElectricScooter(std::string id, std::string name, double energy, int score);
    double dailyEnergy() const override { return energy_; }
};
class Bike final : public Transport {
public:
    Bike(std::string id, std::string name, int score);
    double dailyEnergy() const override { return 0.0; }
};
class ElectricBike final : public Transport, public EnergyConsumer {
    double energy_;
public:
    ElectricBike(std::string id, std::string name, double energy, int score);
    double dailyEnergy() const override { return energy_; }
};
class CargoBike final : public Transport {
    int capacityKg_;
public:
    CargoBike(std::string id, std::string name, int score, int capacityKg);
    int capacityKg() const { return capacityKg_; }
    double dailyEnergy() const override { return 0.0; }
};
