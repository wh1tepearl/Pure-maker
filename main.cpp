#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <unistd.h>

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

string cpp_path = "";
string icon_path = "";
string program_name = "";
bool launch_with_a_out = false;
string cont;

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

string select_file_zenity(string for_what) {
    string cmd;
    if (for_what == "cpp")
        cmd = "zenity --file-selection --title=\"Выберите .cpp файл\" --file-filter='*.cpp'";
    else if (for_what == "icon")
        cmd = "zenity --file-selection --title=\"Выберите .cpp файл\" --file-filter='*.png *.svg *.xpm *.jpg *.jpeg'";
    char buffer[256];
    string result = "";
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (pipe) {
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result = buffer;
            result.erase(result.find_last_not_of("\n") + 1);
        }
        pclose(pipe);
    }
    
    return result;
}

void chlang() {
    string lang_temp;
    string temp;
    cout << col_yellow << "Chose language (russian/english)\n" 
         << "Выбери язык (русский/английский)\n>>> " << col_;
    cin >> lang_temp;


    while(lang_temp != "RU" && lang_temp != "Ru" && lang_temp != "ru" && lang_temp != "r" && lang_temp != "R" && lang_temp != "Russian" && lang_temp != "RUSSIAN" && lang_temp != "russian" && lang_temp != "ENG" && lang_temp != "Eng" && lang_temp != "eng" && lang_temp != "E" && lang_temp != "e" && lang_temp != "ENGLISH" && lang_temp != "English" && lang_temp != "english") {
        cerr << col_red << "Chose a valid option\n>>> " << col_;
        cin >> lang_temp;
    }
    if (lang_temp == "ENG" || lang_temp == "Eng" || lang_temp == "eng" || lang_temp == "E" || lang_temp == "e" || lang_temp == "ENGLISH" || lang_temp == "English" || lang_temp == "english") {
        if(lang != 'e') {
            system("rm ~/pure_maker/.info/ru_lang");
        }
        cout << col_green << "Language changed succesfully\nTo see the changes, restart PureMaker\n" << col_;
        cin >> temp;
        
    }
    else if (lang_temp == "RU" || lang_temp == "Ru" || lang_temp == "ru" || lang_temp == "R" || lang_temp == "r" || lang_temp == "RUSSIAN" || lang_temp == "Russian" || lang_temp == "russian") {
        ru_lang();
        cout << col_green << "Язык успешно изменен\nЧтобы увидеть изменения, перезагрузите PureMaker\n" << col_;
        cin >> temp;
    }

}
void init() {
    fs::path path_obj(cpp_path);
    string cpp_dir_only = path_obj.parent_path().string();
    string cpp_file_name = path_obj.filename().string();

    const char* home = getenv("HOME");

    string desktop_path = string(home) + "/.local/share/applications/" + program_name + ".desktop";
    string script_path = string(home) + "/.scripts/";
    
    

    fs::create_directories(".scripts");
    ofstream scriptfile(".scripts/"+program_name+".sh");
    
    if(scriptfile.is_open()) {
        if(launch_with_a_out == false) {
            scriptfile << "#!/bin/bash\n"
                    << "cd " << cpp_dir_only << "\n"
                    << "g++ -o " << program_name << " " << cpp_file_name <<"\n"
                    << "./" << program_name << "\n";
        }
        else if(launch_with_a_out = true) {
            scriptfile << "#!/bin/bash\n"
                << "cd " << cpp_dir_only << "\n"
                << "g++ "<< cpp_file_name <<"\n"
                << "./" << "a.out\n"
                << "read";
        }
        

    
        ofstream desktopfile(desktop_path);
        if(desktopfile.is_open()) {
            if (icon_path == "") {
                desktopfile << "[Desktop Entry]\n"
                << "Type=Application\n"
                << "Name=" << program_name << "\n"
                << "Exec=" << "x-terminal-emulator -e " << script_path << program_name << ".sh" << "\n"
                << "Icon=utilities-terminal\n"
                << "Categories=Development;\n";
            }
            else if (icon_path != "") {
                desktopfile << "[Desktop Entry]\n"
                << "Type=Application\n"
                << "Name=" << program_name << "\n"
                << "Exec=" << "x-terminal-emulator -e " << script_path << program_name << ".sh" << "\n"
                << "Icon=" << icon_path << "\n"
                << "Categories=Development;\n";
            }
        system("update-desktop-database ~/.local/share/applications");
        system("clear");
        if(lang == 'e') cout << col_green << "Shortcut created\n" << col_;
        if (lang == 'r') cout << col_green << "Ярлык создан\n" << col_;
        
        }
    }
       

}
void ru_about() {
    system("clear");
    cout << col_green << "\nЯзык программы: Русский\n\n" << col_;
    cout << col_cyan << "Добро пожаловать в PureMaker! Это бета-версия, поэтому возможны ошибки..\nВам надоело вводить две команды в терминале, чтобы запустить C++ код?\nС PureMaker вы легко создадите ярлык для сборки и запуска программы.\nPureMaker добавит ярлык в меню приложений.\n\n" << col_;
    cout << col_purple << "Чтобы выбрать опцию, введите ее номер" << col_;
    cout << "\n\nНажмите любую букву + Enter, чтобы продолжить\n";
    cin >> cont;
}
void eng_about() {
    system("clear");
    cout << col_green << "\nProgram language: English\n\n" << col_;
    cout << col_cyan << "Welcome to PureMaker, this is a beta version so it can contain bugs..\nYou are tired of having to type 2 commands in terminal just to run your c++ code?\nWith PureMaker you can easily create shortcut to build and run your code.\nPureMaker will add shortcut to your app menu.\n\n" << col_;
    cout << col_purple << "To select an option, enter its number" << col_;
    cout << "\n\nPress any letter + enter to continue\n";
    cin >> cont;
    
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
void main_eng() {
    string temp;
    string mode;
    string mode_in_1;
    while(true) {
        system("clear");
        cout << col_red << "#######################\n"
                        << "##" << col_ <<" PureMaker Release "<< col_red << "##\n#######################" << col_ <<"\n\nSelect a mode\n1. Create a shorcut\n2. view all shorcuts\n3. Show \"About\"\n4. Change Language\n5. Quit\n" << col_red << ">>> " << col_;
        cin >> mode;

        while(mode != "1" && mode != "2" && mode != "3" && mode != "4" && mode != "5") {
            cerr << col_red  << "Chose a valid option\n>>> " << col_;
            cin >> mode;
        }

        if (mode == "1") {
            system("clear");
            while (true) {
                if (program_name == "") {
                    cout << col_red << "1. Program name: none\n" << col_;
                }
                else if (program_name != "") {
                    cout << col_green << "1. Program name: " << program_name << "\n" << col_;
                }



                if (cpp_path == "") {
                    cout << col_red << "2. main.cpp file directory: none\n" << col_;
                }
                else if (cpp_path != "") {
                    cout << col_green << "2. main.cpp file directory: " << cpp_path << "\n" << col_;
                }



                if (icon_path == "") {
                    cout << col_red << "3. icon path (optional): none\n" << col_;
                }
                else if (icon_path != "") {
                    cout << col_green << "3. icon path (optional): " << icon_path << "\n" << col_;
                }



                if (launch_with_a_out == false) {
                    cout << col_red << "4. Launch with a.out (optional): false\n" << col_;
                }
                else if (launch_with_a_out == true) {
                    cout << col_green << "4. Launch with a.out (optional): true\n" << col_;
                }



                cout << col_purple << "5. Create script\n6. Quit\n" << col_ << ">>> " << col_red;


                cin >> mode_in_1;
                while(mode_in_1 != "1" && mode_in_1 != "2" && mode_in_1 != "2" && mode_in_1 != "3" && mode_in_1 != "4" && mode_in_1 != "5" && mode_in_1 != "6") {
                    cerr << col_red  << "Chose a valid option\n>>> " << col_;
                    cin >> mode_in_1;
                }



                if(mode_in_1 == "1") {
                    system("clear");
                    cout << col_green << "Enter name for your program\n" << col_ << ">>> " << col_green;
                    cin >> program_name;
                    mode_in_1 = "null";
                    system("clear");
                }
                else if(mode_in_1 == "2") {
                    cpp_path = select_file_zenity("cpp");
                    system("clear");
                }
                else if(mode_in_1 == "3") {
                    icon_path = select_file_zenity("icon");
                    system("clear");
                }
                else if(mode_in_1 == "4") {
                    if(launch_with_a_out == false)
                        launch_with_a_out = true;
                    else
                        launch_with_a_out = false;
                    system("clear");
                }
                else if(mode_in_1 == "5") {
                    if(program_name != "" && cpp_path != "")
                        init();
                    else
                        if(program_name == "")
                            cerr << col_red << "Can't create, program name can't be none\n\n" << col_;
                            
                        if(cpp_path == "")
                            cerr << col_red << "Can't create, cpp file path can't be none\n\n" << col_;
                        cout << "Press any letter + enter to continue\n";
                        cin >> temp;
                    break;
                }
                else if(mode_in_1 == "6") {
                    break;
                }


            }
        }
        else if (mode == "2") {
            system("clear");
            system("cd ~/pure_maker/.scripts/ && ls -l");
            cout << col_purple <<"\nTo continue, press any key + Enter\n" << col_;
            cin >> temp;
        }
        else if (mode == "3") {
            eng_about();
        }
        else if (mode == "4") {
            system("clear");
            chlang();
        }
        else if(mode == "5") {
            break;
        }
    }
}
void main_ru() {
    string temp;
    string mode;
    string mode_in_1;
    while(true) {
        system("clear");
        cout << col_red << "#######################\n"
                        << "##" << col_ <<" PureMaker Release "<< col_red << "##\n#######################" << col_ <<"\n\nВыберите режим\n1. Создайте ярлык\n2. Просмотреть все ярлыки\n3. Показать \"О программе\"\n4. Изменить язык\n5. Прервать\n" << col_red << ">>> " << col_;
        cin >> mode;

        while(mode != "1" && mode != "2" && mode != "3" && mode != "4" && mode != "5") {
            cerr << col_red  << "Выберите допустимый вариант\n>>> " << col_;
            cin >> mode;
        }

        if (mode == "1") {
            system("clear");
            while (true) {
                if (program_name == "") {
                    cout << col_red << "1. Название программы: не задано\n" << col_;
                }
                else if (program_name != "") {
                    cout << col_green << "1. Название программы: " << program_name << "\n" << col_;
                }



                if (cpp_path == "") {
                    cout << col_red << "2. Каталог файла main.cpp: не задано\n" << col_;
                }
                else if (cpp_path != "") {
                    cout << col_green << "2. Каталог файла main.cpp: " << cpp_path << "\n" << col_;
                }



                if (icon_path == "") {
                    cout << col_red << "3. Путь к значку (необязательно): не задано\n" << col_;
                }
                else if (icon_path != "") {
                    cout << col_green << "3. Путь к значку (необязательно): " << icon_path << "\n" << col_;
                }



                if (launch_with_a_out == false) {
                    cout << col_red << "4. Запуск с помощью a.out (необязательно): нет\n" << col_;
                }
                else if (launch_with_a_out == true) {
                    cout << col_green << "4. Запуск с помощью a.out (необязательно): да\n" << col_;
                }



                cout << col_purple << "5. Создать скрипт\n6. Прервать\n" << col_ << ">>> " << col_red;


                cin >> mode_in_1;
                while(mode_in_1 != "1" && mode_in_1 != "2" && mode_in_1 != "2" && mode_in_1 != "3" && mode_in_1 != "4" && mode_in_1 != "5" && mode_in_1 != "6") {
                    cerr << col_red  << "Выберите допустимый вариант\n>>> " << col_;
                    cin >> mode_in_1;
                }



                if(mode_in_1 == "1") {
                    system("clear");
                    cout << col_green << "Введите название вашей программы\n" << col_ << ">>> " << col_green;
                    cin >> program_name;
                    mode_in_1 = "null";
                    system("clear");
                }
                else if(mode_in_1 == "2") {
                    cpp_path = select_file_zenity("cpp");
                    system("clear");
                }
                else if(mode_in_1 == "3") {
                    icon_path = select_file_zenity("icon");
                    system("clear");
                }
                else if(mode_in_1 == "4") {
                    if(launch_with_a_out == false)
                        launch_with_a_out = true;
                    else
                        launch_with_a_out = false;
                    system("clear");
                }
                else if(mode_in_1 == "5") {
                    if(program_name != "" && cpp_path != "")
                        init();
                    else
                        if(program_name == "")
                            cerr << col_red << "Невозможно создать, имя программы не может быть не заданным\n\n" << col_;
                            
                        if(cpp_path == "")
                            cerr << col_red << "Невозможно создать, путь к файлу cpp не может быть не заданным\n\n" << col_;
                        cout << "Нажмите любую букву + Enter, чтобы продолжить\n";
                        cin >> temp;
                    break;
                }
                else if(mode_in_1 == "6") {
                    break;
                }


            }
        }
        else if (mode == "2") {
            system("clear");
            system("cd ~/pure_maker/.scripts/ && ls -l");
            cout << col_purple <<"\nНажмите любую букву + Enter, чтобы продолжить\n" << col_;
            cin >> temp;

        }
        else if (mode == "3") {
            ru_about();
        }
        else if (mode == "4") {
            system("clear");
            chlang();
        }
        else if(mode == "5") {
            break;
        }
    
    }
}

int main() {
    

	greeting();
    if (lang == 'r') {
        main_ru();
    }
    else if(lang == 'e') {
        main_eng();
    }
}   