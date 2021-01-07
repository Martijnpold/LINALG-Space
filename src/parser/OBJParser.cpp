#include "OBJParser.hpp"

#include <fstream>
#include <sstream>

using namespace space::world;

namespace space::parser {

    std::string OBJParser::loadFile(const std::string& path) {
        std::ifstream input {path};
        std::stringstream sstr;
        while (input >> sstr.rdbuf())
            ;
        return sstr.str();
    }

    std::vector<std::string> OBJParser::split(const std::string& full, char separator) {
        std::vector<std::string> args {};
        std::istringstream lineStream {full};
        std::string arg;
        while (std::getline(lineStream, arg, separator)) {
            args.push_back(arg);
        }
        return args;
    }

    float OBJParser::toF(const std::string& arg) {
        return std::stof(arg);
    }

    int OBJParser::toI(const std::string& arg) {
        return std::stoi(arg);
    }

    world::Object OBJParser::parse(const std::string& path) {
        Object object {};
        std::vector<Vector> points {};

        std::string fullFile = loadFile(path);
        std::vector<std::string> lines = split(fullFile, '\n');
        for (const std::string& line : lines) {
            std::vector<std::string> args = split(line, ' ');
            if (args.empty())
                continue;
            if (args[0] == "v") {
                points.emplace_back(toF(args[1]), toF(args[2]), toF(args[3]));
            }
            if (args[0] == "f") {
                Polygon p {};
                for (int i = 1; i < args.size(); i++) {
                    p.add(points[toI(split(args[i], '/')[0]) - 1]);
                }
                object.add(p);
            }
        }
        return object;
    }
} // namespace space::parser