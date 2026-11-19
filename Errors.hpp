#pragma once
#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class InspectionRejected : public FleetError {
public:
    InspectionRejected() : FleetError("inspection rejected") {}
};
class InvalidArgument : public FleetError {
public:
    using FleetError::FleetError;
};
class ItemNotFound : public FleetError {
public:
    explicit ItemNotFound(const std::string& id) : FleetError("item not found: " + id) {}
};
