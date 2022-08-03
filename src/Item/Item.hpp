#include <string>

class Item {
	private:
		double average_price;
		const std::string name;
		const std::string request;

	public:
		explicit Item( const std::string&);
		void Update( int delay );
		double GetPrice() const;
};
