#pragma once

#include <map>
#include <string>

namespace snake3d::config
{

    class Value
    {
    public:
        explicit Value(std::string value = "");

        template <typename T>
        T as() const;

    private:
        std::string _value;
    };

    class ConfigParser;

    class Section
    {
    public:
        explicit Section(const std::string& name);
        friend class ConfigParser;
        // TODO add friend
        void add(const std::string& key, const std::string& value);

        [[nodiscard]] const Value& field(const std::string& key) const;

        const static std::string GLOBAL_SECTION;
        [[nodiscard]] std::string name() const;

    private:
        std::string _name;
        std::map<std::string, Value> _elements;
        Value _empty_value;
    };

    class ConfigParser
    {
    public:
        ConfigParser();
        bool parse(const char* filename);
        [[nodiscard]] const Section& section(const std::string& key) const;

    private:
        std::map<std::string, Section> _config;
    };

} // namespace snake3d::config
