#include <iostream>
#include <string>
#include <stringx.hpp>

using namespace std;
using namespace strx;

enum class FG
{
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    light_gray = 37,
    default_foreground_color = 39,
    dark_gray = 90,
    light_red = 91,
    light_green = 92,
    light_yellow = 93,
    light_blue = 94,
    light_magenta = 95,
    light_cyan = 96,
    white = 97
};

enum class BG
{
    black = 40,
    red = 41,
    green = 42,
    yellow = 43,
    blue = 44,
    magenta = 45,
    cyan = 46,
    light_gray = 47,
    default_background_color = 49,
    dark_gray = 100,
    light_red = 101,
    light_green = 102,
    light_yellow = 103,
    light_blue = 104,
    light_magenta = 105,
    light_cyan = 106,
    white = 107
};

string color(FG fg, BG bg, bool fgh)
{
    return "\033[{0};{1};{2}m"_f % fgh % (int)fg % (int)bg % endf;
}

const char *CLR_RES = "\033[0m";

int main(int argc, const char *argv[])
{
    for (int f = 0; f < 8; f++)
    {
        for (int b = 0; b < 8; b++)
        {
            cout << color((FG)(30 + f), (BG)(40 + b), false) << "####";
        }
        cout << endl;
        for (int b = 0; b < 8; b++)
        {
            cout << color((FG)(30 + f), (BG)(40 + b), true) << "####";
        }
        cout << endl;
    }
    return 0;
}
