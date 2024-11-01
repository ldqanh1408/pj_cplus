#include<iostream>
#include "Menu.h"
#include "Account.h"
#include "gotp.h"
#include "Console.h"
using namespace std;

void Console::print(int x, int y, string s) {
    Menu::gotoxy(x, y);
    cout << s;
}

string Console::input(int x, int y, bool isPlus, bool ispassword, int mn) {
    string res = "";
    char ch;
    bool clearedPrompt = false;

    Menu::gotoxy(x, y);
    while (true) {
        ch = _getch();
            
        if(ch == 9) {	//tab
            return "";
        }
        if(isPlus && ch == 43) {	// neu dang nhap thi co tao tai khoan moi
            return "+";
        }
        if (res.length() >= 38 && ch != 8 && ch != 13) {
            continue; 
        }

        if (ch == 13) { // Enter
            if(res.length() >= mn) break; //toi thieu ki tu
            else continue;
                
        } else if (ch == 8) { // Backspace
            if (!res.empty()) {
                res.pop_back();
                Menu::gotoxy(x + res.length(), y);
                cout << ' ';
                Menu::gotoxy(x + res.length(), y);
            }
        } else {
            if (!clearedPrompt) {
                cout << "                              "; // Xóa nhãn "Enter username:"
                Menu::gotoxy(x, y);
                clearedPrompt = true;
            }
            res.push_back(ch);
            
            if(ispassword) {
                cout << "*";	
            }
            else {
                cout << ch;
            }
        }
    }
    return res;
}

string Console::change(string& title, string& enter_new, string& old_ans, string& old_password, bool age, bool gender, bool phone_number) {
    Menu::print_otp();
    Menu::gotoxy(53,3);
    cout << title;
    Menu::gotoxy(51,9);
    cout << enter_new << ":";
    Menu::gotoxy(41,6); //password
            
    char ch;
    bool clearedPrompt = false;
    string password = "";
    int mn;

    if(age) mn = 10;
    else if(gender) mn = 1;
    else if(phone_number) mn = 10;
    else mn = 5;

    while (true) {
        ch = _getch();
        
        if(ch == 9) return "";	// tab: back
        
        if (password.length() >= 38 && ch != 8 && ch != 13) {
            continue; 
        }
        
        if (ch == 13) { // Enter
            if(password.length() >= 8) {
                break;
            }
        } else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                Menu::gotoxy(41 + password.length(), 6);
                cout << ' ';
                Menu::gotoxy(41 + password.length(), 6);
            }
        } else {
            if (!clearedPrompt) {
                cout << "               ";
                Menu::gotoxy(41, 6);
                clearedPrompt = true;
            }
            password.push_back(ch);
            cout << "*";
        }
    }
        
    Menu::gotoxy(41,9); //ans
    clearedPrompt = false;
    string ans = "";
    
    while (true) {
        ch = _getch();
        
        if(ch == 9) return "";	// tab: back
        
        if (ans.length() >= 38 && ch != 8 && ch != 13) {
            continue; 
        }
    
        if (ch == 13) { // Enter
            if(ans.length() >= mn) break;
            else continue;
        } else if (ch == 8) { // Backspace
            if (!ans.empty()) {
                ans.pop_back();
                Menu::gotoxy(41 + ans.length(), 9);
                cout << ' ';
                Menu::gotoxy(41 + ans.length(), 9);
            }
        } else {
            if (!clearedPrompt) {
                cout << "                                    ";
                Menu::gotoxy(41, 9);
                clearedPrompt = true;
            }
            ans.push_back(ch);
            cout << ch;
        }
    }
    
    Menu::gotoxy(56,12); //otp
    string OTP = gotp::generate_otp();
    cout << OTP;
    
    Menu::gotoxy(47,15);
    char c;
    string check_otp = "";
    
    while(true) {
        c = _getch();
        
        if(c == 9) return ""; //tab
        
        else if(check_otp.size() == 6 && c != 8) {
            if(c == 13) break;
            continue;
        }
        else if(c == 13) continue;
        else if(c == 8) {
            if(!check_otp.empty()) {
                check_otp.pop_back();
                Menu::gotoxy(48 + check_otp.size()*5 - 1,15);
                cout << " ";
                Menu::gotoxy(48 + check_otp.size()*5 - 1,15);
            }
        }
        else {
            check_otp.push_back(c);
            cout << c;
            if(check_otp.size() == 6)
                Menu::gotoxy(48 + check_otp.size()*5 + 1 -5, 15);
            else
                Menu::gotoxy(48 + check_otp.size()*5 - 1, 15);
        }
    }
    
    if(password != old_password || OTP != check_otp) {
        Menu::notification("Incorrect Password or OTP!", 47, 5);
        ans = change(title, enter_new, old_ans, old_password, 0, 0, 0);
    }

    if(age) {
        //if(ans khong hop le (dd/mm/yyyy)) {   ===========================================================================
        //   Menu::notification("Invalid information!", 47, 5);
        //   ans = change(title, enter_new, old_ans, old_password, age, gender, phone_number);
        //}
    }
    else if(gender) {
        if(ans != "1" && ans != "0") {
            Menu::notification("Invalid information!", 48, 5);
            ans = change(title, enter_new, old_ans, old_password, age, gender, phone_number);
        }
    }
    else if(phone_number) {
        //if(SDT khong hop le) { ===========================================================================
        //   Menu::notification("Invalid information!", 48, 5);
        //   ans = change(title, enter_new, old_ans, old_password, age, gender, phone_number);
        //}
    }
    else if(ans == old_ans) {
        Menu::notification("Duplicate Old Information!", 47, 5);
        ans = change(title, enter_new, old_ans, old_password, 0, 0, 0);
    }

    if(ans != "") {
        Menu::notification("----Successful Operation----", 45, 5);
    }
    return ans;
}


bool Console::create_account() {
    Menu::create_account_screen();
    
    string username = input(21, 6, false, false, 8);
    if(username == "") return 1; //tab
    // if(username =================================================== tồn tại===============================) {
    //     Menu::notification("Username already exist !", 44, 5);
    //     return 0;
    // }
    
    string password = input(21, 9, false, true, 8);
    if(password == "") return 1;
    
    string password_again = input(21, 12, false, true, 8);
    if(password_again == "") return 1;
    
    if(password != password_again) {
        Menu:: notification("Password is incorrect !", 49, 5);
        return 0;
    }

    string phone;
    while(true) {
        phone = input(21, 15, false, false, 10);
        if(phone == "") return 1;

        // if(phong khong hop le ===================================================================) continue;
        else break;
    }

    string fullname = input(62, 6, false, false, 5);
    
    string age;
    while(true) {
        age = input(62, 9, false, false, 10);

        if(age == "") return 1; // tab
        // if(kiem tra age khong hop le========================================================================) {
        //     print(41, 19, "Age is incorrect !!!                   ");
            
        // } else break;
        else break;
    }

    char ch;
    char gender;

    while(true) {
        Menu::gotoxy(62, 12);
        ch = _getch();
        cout << "                                       ";
        Menu::gotoxy(62, 12);

        if(ch == 9) return 1; // tab
        if(ch == '0' || ch == '1') {
            gender = ch;
            cout << ch;
            break;
        }
    }

    string address = input(62, 15, false, false, 8);
    string country = input(62, 18, false, false, 5);
    Menu::gotoxy(5, 33);
    // luu 9 thong tin lại =======================================================================================;
    Menu::notification("Account created successfully", 45, 5);
    
    return 1; // tro ve đăng nhập
}




void Console::change_information() {
    char c; 
    while (true) {
        Menu::print_change_information();
        Menu::gotoxy(4, 27);
        cout << "--> Enter your choice: ";

        c = _getch(); 
        cout << c;
        Sleep(200);
        
        if(c == 9) return;
        
        if (c < '1' || c > '8') {
            Menu::notification("Invalid result !!!", 50, 5);
        }
    
        string old_password = "00000000" /* PASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWORDDDDDDDDD?*/;
        
        switch (c) {
            
            case '1': {//full name
                string old_name = "aa" /* NAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMMMMMMMMMMMMMMMMMMMMMMMMMMMMeeeeeeeeeeeeeeeeeeee*/;
                string title = "FULL NAME";
                string enter_new = "fullname";
                string name = change(title, enter_new, old_name, old_password, 0, 0, 0);
                // if !name.emmtpy() thi luu lai, lam voi tat ca cac truong hop o ben duoi ===============================================
                break;
            }
            
            case '2': {// password
                string title = "PASSWORD";
                string enter_new = "password";
                string password_current = change(title, enter_new, old_password, old_password, 0, 0, 0);
                break;
            }	
            
            case '3': {//address
                string old_address = "a" /*ADDRESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS*/;
                string title = "ADDRESS";
                string enter_new = "address";
                string address = change(title, enter_new, old_address, old_password, 0, 0, 0);
                break;
            }

            case '4': {
                string old_age = "a";
                string title = "AGE";
                string enter_new = "age (dd/mm/yyyy)";
                string age = change(title, enter_new, old_age, old_password, 1, 0, 0);
                break;
            }

            case '5': {
                string old_gender = "a";
                string title = "GENDER";
                string enter_new = "gender (Male: 1, Female: 0)";
                string gender = change(title, enter_new, old_gender, old_password, 0, 1, 0);
                break;
            }

            case '6': {
                string old_phone_number = "a";
                string title = "PHONE NUMBER";
                string enter_new = "phone number";
                string phone_number = change(title, enter_new, old_phone_number, old_password, 0, 0, 1);
                break;
            }

            case '7': {
                string old_country = "aaaaaa"; //Country ========================================================
                string title = "COUNTRY";
                string enter_new = "country";
                string country = change(title, enter_new, old_country, old_password, 0, 0, 0);
                break;
            }
        }
    }
}


void Console::print_information(){
    system("cls");
    string str = R"(
    IDENTIFICATION INFORMATION
    --------------------------------------------------------------------------------------

    Full Name:                                 
    Date of Birth:
    Gender:

    ACCOUNT INFORMATION
    --------------------------------------------------------------------------------------
    Account Balance:
    Phone Number:
    Country:
    
    --------------------------------------------------------------------------------------
                              Note that pressing the 'Tab' will back	
    )";
    cout << str;
    
    
    Menu::gotoxy(52,4);
    string fullname = "a"; //==============================================================
    cout << fullname;
    Menu::gotoxy(52,5);
    string age = "a"; //=================================================;
    Menu::gotoxy(52,6);
    string ge;
    char ch;
    while(1) {
        ch = _getch();
        if(ch != 9)
            continue;
        else break;
    }
}	