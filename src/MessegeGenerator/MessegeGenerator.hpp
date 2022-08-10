#include "../Item/Item.hpp"
#include <unordered_map>

class MessegeGenerator {
	private:
		std::unordered_map<Item::ERROR_CODES, std::string> errors;
		std::unordered_map<Item::SPECIAL, std::string> specials;
		std::unordered_map<Item::QUALITY, std::string> condition;
		std::unordered_map<int, std::string> currency;
		void LoadDictionaryErrors(const std::string&);
		void LoadDictionarySpecials(const std::string&);
		void LoadDictionaryConditions(const std::string&);
		void LoadDictionaryCurrency(const std::string&);
	public:
		MessegeGenerator();
		~MessegeGenerator();
		void LoadDictionaries(const std::string&);
		std::string GetError(Item::ERROR_CODES);
		std::string GetSpecial(Item::SPECIAL);
		std::string GetCondition(Item::QUALITY);
		std::string GetCurrency(int);
};
