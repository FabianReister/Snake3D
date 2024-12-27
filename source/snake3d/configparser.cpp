#include "configparser.h"

#include <snake3d/nunchuck.h>

#include <cctype>
#include <fstream>
#include <iostream>

namespace snake3d
{

    namespace config
    {

        const std::string Section::GLOBAL_SECTION = "";

        ConfigParser::ConfigParser() = default;

        bool
        ConfigParser::parse(const char* filename)
        {
            std::ifstream file(filename);
            std::string line;

            Section section(Section::GLOBAL_SECTION);
            while (std::getline(file, line))
            {
                // remove whitespaces
                std::erase_if(line, isspace);

                // skip empty lines
                if (line.empty())
                {
                    continue;
                }
                // check for section
                if (line.at(0) == '[' && line.at(line.size() - 1))
                {
                    // first, add last section to storage
                    _config[section.name()] = section;
                    // std::cout << section.name() << std::endl;
                    // now create new section
                    line = line.substr(1, line.size() - 2);
                    section = Section(line);
                }
                else
                {
                    size_t eq_pos = line.find_first_of('=');
                    if (eq_pos == std::string::npos)
                    {
                        continue;
                    }
                    std::string key = line.substr(0, eq_pos);
                    std::string val = line.substr(eq_pos + 1, line.size() - 1);
                    // std::cout << key << " , " << val << std::endl;
                    section.add(key, val);
                }
            }

            return true;
        }

        const Section&
        ConfigParser::section(const std::string& key) const
        {
            auto search = _config.find(key);
            if (search != _config.end())
            {
                return search->second;
            }
            // if no match, return global section
            return _config.find(Section::GLOBAL_SECTION)->second;
        }

        //---------------------------------------------
        Section::Section(const std::string& name = Section::GLOBAL_SECTION) : _name(name)
        {
            _elements.clear();
        }

        void
        Section::add(const std::string& key, const std::string& value)
        {
            _elements[key] = Value(value);
        }

        const Value&
        Section::field(const std::string& key) const
        {
            const auto search = _elements.find(key);
            if (search != _elements.end())
            {
                return search->second;
            }

            return _empty_value;
        }

        std::string
        Section::name() const
        {
            return _name;
        }

        /*
template <typename T>
const T& Value::as() const
{

}*/

        template <>
        std::string
        Value::as() const
        {
            return _value;
        }

        template <>
        const char*
        Value::as() const
        {
            return _value.c_str();
        }

        template <>
        int
        Value::as() const
        {
            std::cout << _value << std::endl;
            return std::stoi(_value);
        }

        template <>
        double
        Value::as() const
        {
            return std::stod(_value);
        }

        template <>
        float
        Value::as() const
        {
            return std::stof(_value);
        }

        template <>
        nunchuck::Variant
        Value::as() const
        {
            if (_value == "white")
            {
                return nunchuck::WHITE;
            }

            return nunchuck::BLACK;
        }

        Value::Value(std::string value) : _value(std::move(value))
        {
        }
    }; // namespace config

} // namespace snake3d
