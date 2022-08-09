#pragma once
#include <string>

class Item {
  public:
	explicit Item(const std::string &);
	Item() = delete;
	void Update(int delay);
  private:
	enum class QUALITY { FACTORY_NEW,
	MINIMAL_WEAR,
	FIELD_TESTED,
	WELL_WORN,
	BATTLE_SCARRED,
	NO_QUALITY};
	std::string name;
	enum class ERROR_CODES { FAILED_TO_GET_DATA, NO_UNITS, NO_ERROR };
	enum class SPECIAL {STATTRAK, SOUVENIR, NO_SPECIAL};
	double price;
	ERROR_CODES error_code;
	QUALITY condition;
	SPECIAL special;
	void GenerateItemRequest();
	std::string PerformRequest();
	friend Item ReadItem(const auto&);
	friend class Interface;
	inline static std::string request;
	static void GenerateRequest(int);
	std::string GetQuality();
	std::string GetSpecials();
	std::string GenerateName();
	void SetQuality(const std::string&);
	void SetSpecial(const std::string&);
};
