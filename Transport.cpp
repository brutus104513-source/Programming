#include "Transport.hpp"

namespace {
std::shared_ptr<const ModelSpec> scooterSpec() {
    static const auto spec = std::make_shared<const ModelSpec>(ModelSpec{"scooter", 2});
    return spec;
}
std::shared_ptr<const ModelSpec> bikeSpec() {
    static const auto spec = std::make_shared<const ModelSpec>(ModelSpec{"bike", 2});
    return spec;
}
std::shared_ptr<const ModelSpec> ebikeSpec() {
    static const auto spec = std::make_shared<const ModelSpec>(ModelSpec{"ebike", 2});
    return spec;
}
std::shared_ptr<const ModelSpec> cargoSpec() {
    static const auto spec = std::make_shared<const ModelSpec>(ModelSpec{"cargo", 3});
    return spec;
}
}

ElectricScooter::ElectricScooter(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score, scooterSpec()),
      energy_(checkedEnergy(energy)) {}
Bike::Bike(std::string id, std::string name, int score)
    : Transport(std::move(id), std::move(name), score, bikeSpec()) {}
ElectricBike::ElectricBike(std::string id, std::string name, double energy, int score)
    : Transport(std::move(id), std::move(name), score, ebikeSpec()),
      energy_(checkedEnergy(energy)) {}
CargoBike::CargoBike(std::string id, std::string name, int score, int capacityKg)
    : Transport(std::move(id), std::move(name), score, cargoSpec()),
      capacityKg_(capacityKg) {
    if (capacityKg_ <= 0) throw InvalidArgument("cargo capacity must be positive");
}
