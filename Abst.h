//
// Created by Daniil Kolesnik on 14/05/2021.
//all rights and lefts reserved

#ifndef HOMEWORK1_ABST_H
#define HOMEWORK1_ABST_H




#include <string>


using namespace std;

class Abst {

    string name;//название склада
    string city;//город склада
    int maxVolume;//макс. кол-во ед товара для склада
    int volume;//кол-во ед товара на склада


    virtual int Score() = 0;//чистые функции
    virtual string Print() = 0;

    virtual bool MadSize(bool) = 0;

//    virtual string DeleteKey(string&) = 0;
//    virtual string DeleteMeaning(string _str, int _h) = 0;
//    virtual string AddNewMeaning(string& _str) = 0;
//    virtual string AddNewKey(string& _str) = 0;
//    virtual string AddNewKey(string _str) = 0;
//    virtual string AddNewMeaning(string _str) = 0;
//    virtual void SearchSclad() = 0;
public:
    Abst(string _name, string _city, int _volume) {
//        SetConsoleCP(1251);
//        SetConsoleOutputCP(1251);
        name = _name;
        city = _city;
        maxVolume = _volume;
    }

    Abst() {
        name = "";
        city = "";
        maxVolume = 0;
        int volume = 0;
    }

// функции доступа

    string GetName() { return name; }//функции доступа
    string GetCity() { return city; }

    int GetMaxVolume() { return maxVolume; }

    int GetVolume() { return volume; }

    void SetName(string _name) { name = _name; }

    void SetCity(string _city) { city = _city; }

    void SetMaxVolume(int _volume) { maxVolume = _volume; }

    void SetVolume(int _volume) { volume = _volume; }


};


#endif //HOMEWORK1_ABST_H
