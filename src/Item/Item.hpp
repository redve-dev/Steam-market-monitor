#pragma once
#include <string>

class Item {
  public:
	explicit Item(const std::string &, bool);
	Item() = delete;
	void Update(int delay);
  private:
	enum class QUALITY { FACTORY_NEW,
	MINIMAL_WEAR,
	FIELD_TESTED,
	WELL_WORN,
	BATTLE_SCARRED,
	NO_QUALITY,
	SOUVENR};
	std::string name;
	bool StatTrak;
	enum class ERROR_CODES { FAILED_TO_GET_DATA, NO_UNITS, NO_ERROR };
	double price;
	ERROR_CODES error_code;
	QUALITY state;
	void GenerateItemRequest();
	std::string PerformRequest();
	friend class Interface;
	inline static std::string request;
	static void GenerateRequest(int);
	std::string GetQuality();
	std::string GenerateName();
	void SetQuality(const std::string&);
};
