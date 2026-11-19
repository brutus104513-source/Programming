#pragma once
#include "Transport.hpp"
#include <algorithm>
#include <cctype>

class ServiceCenter {
public:
    void inspect(const Transport& transport) const {
        std::string lower = transport.name();
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        if (lower.find("broken") != std::string::npos) throw InspectionRejected();
    }
};
