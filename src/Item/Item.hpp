#pragma once
#include <string>

class Item {
public:
  const std::string name;
private:
  enum class ERROR_CODES { FAILED_TO_GET_DATA, NO_UNITS, NO_ERROR };
  double price;
  std::string request;
  int curr;
  ERROR_CODES error_code;
  void PrintItemData(ERROR_CODES);
public:
  explicit Item(const std::string &, int);
  Item() = delete;
  void Update(int delay);
  void GenerateItemRequest();
};
