



#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3= "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7= "The selected password cannot contain a dictionary word.";

int run(string leaked_password_file, string english_word_file)
{
    ifstream leaked_password(leaked_password_file);
    ifstream english_word(english_word_file);

    string password;
    vector<string> password_list;
    vector<string> word_list;

    //read leaked password file
    while(getline(leaked_password, password))
    {
        password_list.push_back(password);
    }

    leaked_password.close();

    //read dictionary file
    while(getline(english_word, password))
    {
        word_list.push_back(password);
    }

    english_word.close();

    //prompt user for password and check rules
    cout << "Enter a password: ";
    cin >> password;

    if(password.length() < 8)
    {
        cout << rule_msg_1;
        return 1;
    }

    if(find(password_list.begin(), password_list.end(), password) != password_list.end())
    {
        cout << rule_msg_6;
        return 1;
    }

    if(find(word_list.begin(), word_list.end(), password) != word_list.end())
    {
        cout << rule_msg_7;
        return 1;
    }

    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special_char = false;

    for(int i=0; i<password.length(); i++)
    {
        if(isupper(password.at(i)))
        {
            has_uppercase = true;
        }
        else if(islower(password.at(i)))
        {
            has_lowercase = true;
        }
        else if(isdigit(password.at(i)))
        {
            has_digit = true;
        }
        else if(password.at(i) == '@' || password.at(i) == '!' || password.at(i) == '#' || password.at(i) == '^' || password.at(i) == '&' || password.at(i) == '*' || password.at(i) == '$')
        {
            has_special_char = true;
        }
    }

    if(!has_uppercase)
    {
        cout << rule_msg_2;
        return 0;
    }

    if(!has_lowercase)
    {
        cout << rule_msg_3;
        return 0;
    }

    if(!has_digit)
    {
        cout << rule_msg_4;
        return 0;
    }

    if(!has_special_char)
    {
        cout << rule_msg_5;
        return 0;
    }

    cout << "The selected password is valid.";

    return 0;
}

int main()
{
    string leaked_password_file = "alleged-gmail-passwords.txt";
    string english_word_file = "words_5.txt";

    run(leaked_password_file, english_word_file);

    return 0;
}