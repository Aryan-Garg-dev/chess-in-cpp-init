#include <map>
#include <string>
#include <iostream>
using namespace std;

enum class Color  {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Purple,
    Cyan,
    White,
};

const string $reset = "\e[0m";

const map<Color, string> Regular = {
    { Color::Black,  "\e[0;30m" },
    { Color::Red,    "\e[0;31m" },
    { Color::Green,  "\e[0;32m" },
    { Color::Yellow, "\e[0;33m" },
    { Color::Blue,   "\e[0;34m" },
    { Color::Purple, "\e[0;35m" },
    { Color::Cyan,   "\e[0;36m" },
    { Color::White,  "\e[0;37m" },
};

const map<Color, string> Bold = {
    { Color::Black,  "\e[1;30m" },
    { Color::Red,    "\e[1;31m" },
    { Color::Green,  "\e[1;32m" },
    { Color::Yellow, "\e[1;33m" },
    { Color::Blue,   "\e[1;34m" },
    { Color::Purple, "\e[1;35m" },
    { Color::Cyan,   "\e[1;36m" },
    { Color::White,  "\e[1;37m" },
};

const map<Color, string> Underline = {
    { Color::Black,  "\e[4;30m" },
    { Color::Red,    "\e[4;31m" },
    { Color::Green,  "\e[4;32m" },
    { Color::Yellow, "\e[4;33m" },
    { Color::Blue,   "\e[4;34m" },
    { Color::Purple, "\e[4;35m" },
    { Color::Cyan,   "\e[4;36m" },
    { Color::White,  "\e[4;37m" },
};

const map<Color, string> Background = {
    { Color::Black,  "\e[40m" },
    { Color::Red,    "\e[41m" },
    { Color::Green,  "\e[42m" },
    { Color::Yellow, "\e[43m" },
    { Color::Blue,   "\e[44m" },
    { Color::Purple, "\e[45m" },
    { Color::Cyan,   "\e[46m" },
    { Color::White,  "\e[47m" },
};

const map<Color, string> HighIntensity = {
    { Color::Black,  "\e[0;90m" },
    { Color::Red,    "\e[0;91m" },
    { Color::Green,  "\e[0;92m" },
    { Color::Yellow, "\e[0;93m" },
    { Color::Blue,   "\e[0;94m" },
    { Color::Purple, "\e[0;95m" },
    { Color::Cyan,   "\e[0;96m" },
    { Color::White,  "\e[0;97m" },
};

const map<Color, string> BoldHighIntensity = {
    { Color::Black,  "\e[1;90m" },
    { Color::Red,    "\e[1;91m" },
    { Color::Green,  "\e[1;92m" },
    { Color::Yellow, "\e[1;93m" },
    { Color::Blue,   "\e[1;94m" },
    { Color::Purple, "\e[1;95m" },
    { Color::Cyan,   "\e[1;96m" },
    { Color::White,  "\e[1;97m" },
};

const map<Color, string> HighIntensityBackground = {
    { Color::Black,  "\e[0;100m" },
    { Color::Red,    "\e[0;101m" },
    { Color::Green,  "\e[0;102m" },
    { Color::Yellow, "\e[0;103m" },
    { Color::Blue,   "\e[0;104m" },
    { Color::Purple, "\e[0;105m" },
    { Color::Cyan,   "\e[0;106m" },
    { Color::White,  "\e[0;107m" },
};

enum class Type {
    Background,
    Bold,
    Underline,
    BoldHighIntensity,
    HighIntensity,
    HighIntensityBackground,
    Regular
};

const map<Type, map<Color, string>> colorMaps = {
    { Type::Regular, Regular },
    { Type::Bold, Bold },
    { Type::Underline , Underline},
    { Type::BoldHighIntensity, BoldHighIntensity },
    { Type::HighIntensity, HighIntensity },
    { Type::HighIntensityBackground, HighIntensityBackground },
    { Type::Background, Background }
};


string $color(Type type, Color color){
    return colorMaps.at(type).at(color);
}

// int main(){
//     cout<<$color(Type::Regular, Color::Red)<<"I am aryan"<<$reset<<endl;
//     cout<<$color(Type::Background, Color::Blue)<<"I am aryan"<<$reset<<endl;
//     cout<<$color(Type::Underline, Color::Blue)<<"I am aryan"<<$reset<<endl;
//     cout<<$color(Type::Bold, Color::Blue)<<"Hello world"<<$reset<<endl;
// }

