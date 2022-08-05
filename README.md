# Steam market monitor

A simple tool to automatically print prices of choosen items in 1 window.<br>
To build, type 'make' in build directory (lib curl required).<br>

to use it, type<br>
<b> ./steam-market-monitor \<path-to-file></b></br>
for example:<br>
./steam-market-monitor cases <br>

If the path to file will be not provided, then program will look for file named items<br>

To create your own items list, create a file with those arguments:<br>
<b>currency</b> (1 - USD, 2 - GBP, 3 - EUR, 6 - PLN).<br>
You can add any currency according to steam [documentation](https://partner.steamgames.com/doc/store/pricing/currencies) in file src/Item/Item.cpp.<br>
Add it to hashmap in function Item::PrintItemData)<br>

<b>delay</b> between each request in ms (recommended value: 5000. Steam will block you for a short period of time if you exceed 20 requests per minute)<br>

and then in new lines name of items you wanna track (each word starts with capital letter).
example input:

<b>
1 4000<br>
Chroma Case<br>
Operation Vanguard Weapon Case<br>
StatTrak AK-47 | Fire Serpent (Battle-Scarred)<br>
M4A4 | Global Offensive (Minimal Wear)<br>
</b><br>

those lines will print median price of chroma case in USD, then wait 4 seconds (4000ms)<br>
then print price of vanguard case in USD, then wait 4 seconds and so on.<br>

If you don't know the name of item you look for, open it's site on steam market<br>
For example:<br><br>
<b>[https://steamcommunity.com/market/listings/730/Clutch Case](https://steamcommunity.com/market/listings/730/Clutch%20Case)<br></b>

The name of item, is everything after last slash ('/'). In this example it's: <br>
<b>Clutch Case</b><br>
In case the item name looks like: <br>
<b>Clutch%20Case</b><br>
The program might brake. In this case, use any free URL Decoder, and try again.

If the item you inserted prints with <b>FAIL</b> communicate, in first step look for a typo<br>
If you don't see any typo, look on steam market if the item actually exist <br>
(for example if you cannot get price of <b>StatTrak M4A4 | Global Offensive</b>)<br>
If the problem still occures, then feel free to open github issues, or try debugging on your own.<br>
