#pragma once

#include <string>
#include <vector>
#include <world/Object.hpp>

namespace space::parser {

    class OBJParser {
    private:
        static std::string loadFile(const std::string& path);
        static std::vector<std::string> split(const std::string& full, char separator);
        static float toF(const std::string& arg);
        static int toI(const std::string& arg);

    public:
        static world::Object parse(const std::string& path);
    };

} // namespace space::parser