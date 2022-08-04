# Steam market monitor

A simple tool to automatically print prices of choosen items in 1 window.<br>
To build, type 'make' in build directory (lib curl required).<br>

then in file 'items' insert currency (1 - USD, 2 - GBP, 3 - EUR, 6 - PLN. You can add any currency according to steam documentation https://partner.steamgames.com/doc/store/pricing/currencies in file Item.cpp)<br>

delay between each request in ms (recommended value: 5000. Steam will block you for a short period of time if you exceed 20 requests per minute)<br>

and then in new lines name of items you wanna track (each word starts with capital letter).
example input:

1 4000<br>
Chroma Case<br>
Vanguard Case<br>


those lines will print median price of chroma keys in USD, then wait 4 seconds (4000ms), and print price of vanguard case.<br>
