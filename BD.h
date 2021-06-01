//
// Created by Daniil Kolesnik on 14/05/2021.
//all rights and lefts reserved


#ifndef HOMEWORK1_BD_H
#define HOMEWORK1_BD_H

#pragma once

#include <vector>
#include <string>

#include "clothes.h"
#include "shoes.h"

using namespace std;

/// <summary>
/// единица БД
/// </summary>
class BD {
    string name;//Имя БД
    vector<Clothes> clothesScaldVect;//вектор складов одежды
    vector<Shoes> shoesScladVect;//вектор складов обуви

public:
// Возврат всех имен складов

    /// <summary>
    /// Получть название всех складов
    /// </summary>
    /// <returns>Вектор названий складов</returns>
    vector<string> GetScladName() {
        vector<string> scladName;
        for (auto &item : clothesScaldVect)
            scladName.push_back(item.GetName() + " - склад одежды");
        for (auto &item : shoesScladVect)
            scladName.push_back(item.GetName() + " - склад обуви");
        return scladName;
    }



// Возврат всех значений оъемов

    /// <summary>
/// Получть вместимость всех складов
/// </summary>
/// <returns>Вектор вместимости складов</returns>
    vector<string> GetScladVolume() {
        vector<string> scladVolume;
        for (auto &item : clothesScaldVect)
            scladVolume.push_back(to_string(item.GetMaxVolume()) + " - " + item.GetName() + " - склад одежды");
        for (auto &item : shoesScladVect)
            scladVolume.push_back(to_string(item.GetMaxVolume()) + " - " + item.GetName() + " - склад обуви");
        return scladVolume;
    }



// Вывод информации склада

    /// <summary>
    /// Поиск склада по названию
    /// </summary>
    /// <param name="_str"></param>
    /// <returns></returns>
    string GetInfoSclad(string _str) {
        for (auto &item: clothesScaldVect)
            if (item.GetName() == _str)
                return item.Print();

        for (auto &item : shoesScladVect)
            if (item.GetName() == _str)
                return item.Print();
        return "Такого склада нет\n";
    }



//Вывод вектора складов одежды с нестанд. размерами

    /// <summary>
    /// Склады обуви нестандартных размеров
    /// </summary>
    /// <param name="_big">-большие или маленькие размеры</param>
    /// <returns>вектор складов одежды нестандартных размеров</returns>
    vector<Clothes> &GetMadSizeVectCloth(bool _big) {
        vector<Clothes> *vect = new vector<Clothes>();
        for (auto &item : clothesScaldVect)
            if (item.MadSize(_big))
                vect->push_back(item);
        return *vect;
    }



// Вывод вектора складов одежды с нестанд. размерами


// Склады обуви нестандартных размеров


    vector<Shoes> &GetMadSizeVectShoes(bool _big) {
        vector<Shoes> *vect = new vector<Shoes>();
        for (auto &item : shoesScladVect)
            if (item.MadSize(_big))
                vect->push_back(item);
        return *vect;
    }



// Вывод вектора складов одежды объема меньше чем

    vector<Clothes> &GetSetMinSizeVectCloth(int _maxVolum) {
        vector<Clothes> *vect = new vector<Clothes>();
        for (auto &item : clothesScaldVect)
            if (item.GetMaxVolume() < _maxVolum)
                vect->push_back(item);
        return *vect;
    }



// Вывод вектора складов обуви объема меньше чем

    vector<Shoes> &GetSetMinSizeVectShoes(int _maxVolum) {
        vector<Shoes> *vect = new vector<Shoes>();
        for (auto &item : shoesScladVect)
            if (item.GetMaxVolume() < _maxVolum)
                vect->push_back(item);
        return *vect;
    }



// Функции доступа

    string GetName() { return name; }//функции доступа
    void SetName(string _name) { name = _name; }

    void PushClSclad(Clothes _cl) { clothesScaldVect.push_back(_cl); }

    void PushShSclad(Shoes _sh) { shoesScladVect.push_back(_sh); }

    const vector<Clothes> &GetVectClothes() { return clothesScaldVect; };

    const vector<Shoes> &GetVectShoes() { return shoesScladVect; };

    void SetVectClothes(vector<Clothes> &_vect) { clothesScaldVect = _vect; }

    void SetVectShoes(vector<Shoes> &_vect) { shoesScladVect = _vect; }



    // Получть склад по имени

    const Clothes &GetClothes(string _str) {
        for (auto &item : clothesScaldVect)
            if (item.GetName() == _str)
                return item;
        Clothes *cl = new Clothes();
        return *cl;
    }




    const Shoes &GetShoes(string _str) {
        for (auto &item : shoesScladVect)
            if (item.GetName() == _str)
                return item;
        Shoes *sh = new Shoes();
        return *sh;
    }

    //int GetVectClSize() { return clothesScaldVect.size(); }
    //int GetVectShSize() { return shoesScladVect.size(); }
    //Clothes GetVectCl(int _i) { return clothesScaldVect[_i]; }
    //Shoes GetVectSh(int _i) { return shoesScladVect[_i]; }


};


#endif //HOMEWORK1_BD_H
