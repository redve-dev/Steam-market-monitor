#pragma once
#include <string>

class Item {
	public:
		const std::string name;
	private:
		double average_price;
		std::string request;
		int curr;
	public:
		explicit Item( const std::string&, int);
		explicit Item( const std::string&);
		Item() = default;
		void Update( int delay );
		double GetPrice() const;
		void SetCurrency(int);
};
