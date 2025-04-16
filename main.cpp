#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#define col_   "\033[0m"
#define col_purple  "\033[35m"
#define col_red     "\033[31m"
#define col_green   "\033[32m"
#define col_yellow  "\033[33m"
#define col_cyan    "\033[36m"

using namespace std;
namespace fs = filesystem;

const string MARKER_PATH = ".info/isfirstlaunch";
const string lang_path = ".info/ru_lang";
char lang;

bool ru_lang() {
    try {
        ofstream file(lang_path);
        return file.is_open();
    } catch (...) {
        return false;
    }
}
bool create_marker() {
    try {
        fs::create_directories(".info");
        ofstream file(MARKER_PATH);
        return file.is_open();
    } catch (...) {
        return false;
    }
}
void ru_about() {
    cout << col_green << "\nЯзык программы: Русский\n\n" << col_;
    cout << col_cyan << "Добро пожаловать в PureMaker! Это бета-версия, поэтому возможны ошибки..\nВам надоело вводить две команды в терминале, чтобы запустить C++ код?\nС PureMaker вы легко создадите ярлык для сборки и запуска программы.\nPureMaker добавит ярлык в меню приложений и на рабочий стол.\n\n" << col_;
    cout << col_purple << "Чтобы изменить язык, введите \"$chlang\"\nЧтобы снова показать информацию о программе, введите \"$About\"\n\n" << col_;
}
void eng_about() {
    cout << col_green << "\nProgram language: English\n\n" << col_;
    cout << col_cyan << "Welcome to PureMaker, this is a beta version so it can contain bugs..\nYou are tired of having to type 2 commands in terminal just to run your c++ code?\nWith PureMaker you can easily create shortcut to build and run your code.\nPureMaker will add shortcut to your app menu and desktop.\n\n" << col_;
    cout << col_purple << "To change language type \"$chlang\"\nTo show about program again type \"$About\"\n\n" << col_;
}
void greeting() {
    string lang_temp;
    if (!fs::exists(MARKER_PATH)) {
        cout << col_red
             << "##################\n"
             << "## First Launch ##\n"
             << "##################\n\n"<< col_;
        

        if (create_marker()) {
            cout << col_green << "Marker file created!\n\n" << col_;
        } else {
            cerr << col_red << "Error while creating file-marker\n" << col_;
        }
        

        cout << col_yellow << "Chose language (russian/english)\n" 
             << "Выбери язык (русский/английский)\n>>> " << col_;
        cin >> lang_temp;


        while(lang_temp != "RU" && lang_temp != "Ru" && lang_temp != "ru" && lang_temp != "r" && lang_temp != "R" && lang_temp != "Russian" && lang_temp != "RUSSIAN" && lang_temp != "russian" && lang_temp != "ENG" && lang_temp != "Eng" && lang_temp != "eng" && lang_temp != "E" && lang_temp != "e" && lang_temp != "ENGLISH" && lang_temp != "English" && lang_temp != "english") {
            cerr << col_red << "Chose a valid option\n>>> " << col_;
            cin >> lang_temp;
        }


        if (lang_temp == "ENG" || lang_temp == "Eng" || lang_temp == "eng" || lang_temp == "E" || lang_temp == "e" || lang_temp == "ENGLISH" || lang_temp == "English" || lang_temp == "english") {
            eng_about();
        }
        else if (lang_temp == "RU" || lang_temp == "Ru" || lang_temp == "ru" || lang_temp == "R" || lang_temp == "r" || lang_temp == "RUSSIAN" || lang_temp == "Russian" || lang_temp == "russian") {
            ru_lang();
            ru_about();
            
        }
        
        

    }
    if (!fs::exists(lang_path)) {
        lang = 'e';
    }
    else if (fs::exists(lang_path)){
        lang = 'r';
    }
}

int main() {

	greeting();
    if (lang == 'r') {
        cout << "Программа работает...\n";
    }
    else if(lang == 'e') {
        cout << "Program works...\n";
    }
}   