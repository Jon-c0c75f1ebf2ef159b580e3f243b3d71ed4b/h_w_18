#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

class User {
    std::string _name;
    std::string _login;
    std::string _pass;
public:
	User(std::string name, std::string login, std::string pass)
	:_name(name), _login(login), _pass(pass) {}
	
	friend std::fstream& operator >>(std::fstream& is, User& obj) {
	    is >> obj._name;
	    is >> obj._login;
	    is >> obj._pass;
	    return is;
    }
    
	friend std::ostream& operator <<(std::ostream& os, const User& obj) {
	    os << obj._name;
	    os << ' ';
	    os << obj._login;
	    os << ' ';
	    os << obj._pass;
	    return os;
    }
};

class Message {
    std::string _text;
    std::string _sender;
    std::string _receiver;
public:
	Message(std::string text, std::string sender, std::string receiver)
	:_text(text), _sender(sender), _receiver(receiver) {}
	
	friend std::fstream& operator >>(std::fstream& is, Message& obj) {
	    is >> obj._text;
	    is >> obj._sender;
	    is >> obj._receiver;
	    return is;
    }
    
	friend std::ostream& operator <<(std::ostream& os, const Message& obj) {
	    os << obj._text;
	    os << ' ';
	    os << obj._sender;
	    os << ' ';
	    os << obj._receiver;
	    return os;
    }
};

void _perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "-" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "-" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "-" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "-" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "-" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "-" : "-")
        << '\n';
}

void test_content() {
    User test_user_01("Dr.Jekyll", "JeKyll", "w;{@_fd?5!B'kHQz");
    User test_user_02("Mr.Hyde", "Hyd_e", "w;{@_fd?5!B'kHQz");
    Message message_001("Dr.Jekyll", "Mr.Hyde", "He_Edward,_what's_up?");
    Message message_002("Mr.Hyde", "Dr.Jekyll", "Fine,_I'm_watching_a_comedy_-_Night_of_the_Living_Dead.");
    
    //Save data chat
    std::fstream users_file = std::fstream("users.dat", std::ios::in | std::ios::out);
	if (!users_file) 
		// Для создания файла используем параметр ios::trunc
           users_file = std::fstream("users.dat", std::ios::in | std::ios::out | std::ios::trunc);
           
    if (users_file) { 
        users_file << test_user_01 << std::endl;
        users_file << test_user_02 << std::endl;
    }
    
    std::fstream messages_file = std::fstream("messages.dat", std::ios::in | std::ios::out);
	if (!messages_file) 
		// Для создания файла используем параметр ios::trunc
           messages_file = std::fstream("messages.dat", std::ios::in | std::ios::out | std::ios::trunc);
           
    if (messages_file) { 
        messages_file << message_001 << std::endl;
        messages_file << message_002 << std::endl;
    }
    
    //Load data chat
    users_file.seekg(0, std::ios_base::beg);
    users_file >> test_user_01;
    users_file >> test_user_02;
    std::cout << test_user_01 << "\n";
    std::cout << test_user_02 << "\n";
    
    messages_file.seekg(0, std::ios_base::beg);
    messages_file >> message_001;
    messages_file >> message_002;
    std::cout << message_001 << "\n"; 
    std::cout << message_002 << "\n";
    
    std::cout << "file users.dat with permissions: ";
    _perms(fs::status("users.dat").permissions());
    
    std::cout << "file messages.dat with permissions: ";
    _perms(fs::status("messages.dat").permissions());   
};
