#include "Fleet.hpp"
#include "Things.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

namespace {
std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream input(line);
    std::string token;
    while (input >> token) tokens.push_back(token);
    return tokens;
}
void requireSize(const std::vector<std::string>& args, std::size_t expected) {
    if (args.size() != expected) throw InvalidArgument("wrong number of arguments");
}
template<typename T>
T number(const std::string& token) {
    std::istringstream input(token);
    T value{};
    if (!(input >> value) || !input.eof()) {
        throw InvalidArgument("invalid number: " + token);
    }
    return value;
}

std::unique_ptr<InventoryItem> createItem(const std::vector<std::string>& args) {
    if (args.size() < 2) throw InvalidArgument("missing item type");
    const auto& kind = args[1];
    if (kind == "scooter" || kind == "ebike") {
        requireSize(args, 6);
        const double energy = number<double>(args[4]);
        const int score = number<int>(args[5]);
        if (kind == "scooter") {
            return std::make_unique<ElectricScooter>(args[2], args[3], energy, score);
        }
        return std::make_unique<ElectricBike>(args[2], args[3], energy, score);
    }
    if (kind == "bike") {
        requireSize(args, 5);
        return std::make_unique<Bike>(args[2], args[3], number<int>(args[4]));
    }
    if (kind == "helmet") {
        requireSize(args, 4);
        return std::make_unique<Helmet>(args[2], args[3]);
    }
    if (kind == "dock") {
        requireSize(args, 5);
        return std::make_unique<DockStation>(args[2], args[3], number<double>(args[4]));
    }
    if (kind == "cargo") {
        requireSize(args, 6);
        return std::make_unique<CargoBike>(args[2], args[3],
                                         number<int>(args[4]), number<int>(args[5]));
    }
    throw InvalidArgument("unknown item type: " + kind);
}

bool execute(Fleet& fleet, const std::vector<std::string>& args, std::ostream& out) {
    if (args.empty()) return true;
    const auto& command = args[0];
    if (command == "add") {
        fleet.add(createItem(args));
    } else if (command == "focus" || command == "remove" || command == "novice_threshold") {
        requireSize(args, 2);
        if (command == "focus") fleet.focus(args[1]);
        else if (command == "remove") fleet.remove(args[1]);
        else fleet.setNoviceThreshold(number<int>(args[1]));
    } else {
        requireSize(args, 1);
        if (command == "quit") return false;
        if (command == "list") fleet.list(out);
        else if (command == "energy") out << fleet.energy() << '\n';
        else if (command == "novice") fleet.novice(out);
        else if (command == "show_focus") fleet.showFocus(out);
        else if (command == "count_novice") out << fleet.countNovice() << '\n';
        else if (command == "report") {
            const double energy = fleet.energy();
            out << "items: " << fleet.size() << ", energy: " << energy << '\n';
        } else throw InvalidArgument("unknown command: " + command);
    }
    return true;
}
}

int main() {
    std::cout << std::fixed << std::setprecision(1);
    Fleet fleet;
    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            if (!execute(fleet, tokenize(line), std::cout)) break;
        } catch (const FleetError& error) {
            std::cout << "error: " << error.what() << '\n';
        } catch (const std::exception& error) {
            std::cout << "error: " << error.what() << '\n';
        }
    }
}
