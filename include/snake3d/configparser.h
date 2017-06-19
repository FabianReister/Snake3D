#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "config.h"

namespace Config {

class Value {
 public:
  explicit Value(const std::string &value = "") : _value(value) {}

  template <typename T>
  T as() const;

 private:
  std::string _value;
};

class ConfigParser;

class Section {
 public:
  explicit Section(const std::string &name);
  friend class ConfigParser;
  // TODO add friend
  void add(const std::string &key, const std::string &value);

  const Value &field(const std::string &key) const;

  const static std::string GLOBAL_SECTION;
  std::string name() const;

 private:
  std::string _name;
  std::map<std::string, Value> _elements;
  Value _empty_value;
};

class ConfigParser {
 public:
  ConfigParser();
  bool parse(const char *filename);
  const Section &section(const std::string &key) const;

 private:
  std::map<std::string, Section> _config;
};

}  // namespace Config
#endif  // CONFIGPARSER_H
