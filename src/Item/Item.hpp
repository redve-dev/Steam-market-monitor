#include <string>

class Item {
	private:
		double average_price;
		const std::string name;
		std::string request;
		int curr;

	public:
		explicit Item( const std::string&, int);
		explicit Item( const std::string&);
		void Update( int delay );
		double GetPrice() const;
		void SetCurrency(int);
};
