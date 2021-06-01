//
// Created by Daniil Kolesnik on 14/05/2021.
//all rights and lefts reserved


#ifndef HOMEWORK1_CLOTHES_H
#define HOMEWORK1_CLOTHES_H




#include "Abst.h"
#include <map>
#include <vector>
#include <utility>
#include <iterator>

using namespace std;


//Содержит размеры одежды и кол-во для них

struct SizeCl {
    SizeCl() {
        height = 0;
        size = 0;
        count = 0;
    };
    int height;
    int size;
    int count;

    bool Found(int _h, int _s) {
        if (_h == height && _s == size)
            return true;
        return false;
    }
};

/// <summary>
/// Класс для склада одежды
/// </summary>
class Clothes : public Abst {
    map<string, vector<SizeCl>> ClothItamMap;//словарь
public:
// Добавление ключа

    /// <summary>
/// Добавление типа товара
/// </summary>
/// <param name="_str-Тип одежды"></param>
/// <param name="_vect-Вектор структур размеров"></param>
    string AddNewKey(string &_str, vector<SizeCl> *_vect = new vector<SizeCl>()) {
        if (ClothItamMap.find(_str) == ClothItamMap.end())//если ключа _str нет, то добавляем
        {
            ClothItamMap.insert(make_pair(_str, *_vect));
            return "Добавление прошло успешно\n";
        } else//если ключ _str есть, выводим предупреждение
            return "Такой вид товара уже есть на складе\n";
    }



// Добаление значения

    /// <summary>
/// Добавление размера
/// </summary>
/// <param name="_str-Тип одежды"></param>
/// <param name="_mean-Структура размеров"></param>
    string AddNewMeaning(string &_str, SizeCl &_mean) {
        if (ClothItamMap.find(_str) == ClothItamMap.end())//если ключа _str нет, то говорим об ошибке
            return "Такого вида товара не существует\n";
        else//если ключ _str есть, добавляем новое значение в вектор
        {
            if (this->GetMaxVolume() - this->GetVolume() >= _mean.count)//если товар помещается
            {
                ClothItamMap.find(_str)->second.push_back(_mean);//в значение(в вектор) добавляем структуру
                return "Добавление прошло успешно\n";
            } else
                return "Для товара нет места\n";
        }
    }



// Смена ключа

    string ChangeKey(string &_strOld, string &_strNew) {
        if (ClothItamMap.find(_strOld) == ClothItamMap.end())//если ключа _strOld нет
        {
            return "Такого вида одежы нет\n";
        } else//если ключ _strOld есть
        {
            if (ClothItamMap.find(_strNew) == ClothItamMap.end())//если ключ _strNew есть
            {
                vector<SizeCl> vec = ClothItamMap.find(_strOld)->second;//сохраняем значение
                ClothItamMap.erase(_strOld);//удаляем старое значение
                ClothItamMap.insert(make_pair(_strNew, vec));//добавляем ключ
                return "Нзвание изменено\n";
            }
            return "Такой вид одежды уже есть\n";
        }
    }



// Смена значения

    string ChangeMeaning(string _str, int _h, int _s, SizeCl &_siNew) {
        if (ClothItamMap.find(_str) == ClothItamMap.end())//если ключа _str нет
        {
            return "Такого вида одежы нет\n";
        } else//если ключ _str есть
        {
            vector<SizeCl> svec;//создаем вектор
            svec = ClothItamMap.find(_str)->second;//копируем вектор
            for (int i = 0; i < svec.size(); i++) {
                if (svec[i].Found(_h, _s))//если есть ткое значение
                {
                    ClothItamMap.find(_str)->second.at(i) = _siNew;
                    return "Изменение прошло успешно\n";
                }
            }
        }
    }



// Удаление значения


    string DeleteMeaning(string _str, int _h, int _s) {
        if (ClothItamMap.find(_str) == ClothItamMap.end())//если ключа _str нет
        {
            return "Такого вида одежы нет\n";
        } else//если ключ _str есть
        {
            vector<SizeCl> svec;//создаем вектор
            svec = ClothItamMap.find(_str)->second;//копируем вектор
            for (int i = 0; i < svec.size(); i++) {
                if (svec[i].Found(_h, _s))//если есть ткое значение
                {
                    ClothItamMap.find(_str)->second.erase(ClothItamMap.find(_str)->second.begin() + i);
                    return "Удаление прошло успешно\n";
                }
            }
            return "Такого размера не существует\n";
        }
    }



// Удаление ключа

    /// <summary>
    /// Удаление значения
    /// </summary>
    /// <param name="_str-Тип одежды"></param>
    string DeleteKey(string &_str) {
        if (ClothItamMap.erase(_str))
            return "Удаление прошло успешно\n";
        else
            return "Такого вида товара не существует\n";
    }



// Подсчет ед. товара


    int Score() {
        int sum = 0;//сумма
        for (auto &itemVect : ClothItamMap)//перебираем все элементы
        {
            for (auto &itemStruct : itemVect.second)//перебираем сами значения
            {
                sum += itemStruct.count;//Плюсуем кол-во единиц для конкретного размера одежы
            }
        }
        return sum;//возвр сумму
    }



// Вывод информации


    string Print() {
        string str = "";
        str += "Тип склада - одежда\n";
        str += "Название: " + GetName() + "\n";
        str += "Город: " + GetCity() + "\n";
        str += "Макс. вмесительность: " + to_string(GetMaxVolume()) + "\n";
        for (auto &itemMap : ClothItamMap) {
            str += "Вид товара: " + itemMap.first + "\n";
            for (auto &itemVect : itemMap.second) {
                str += "Высота: " + to_string(itemVect.height) + "  ";
                str += "Размер: " + to_string(itemVect.size) + "  ";
                str += "Кол-во товара: " + to_string(itemVect.count) + "\n";
            }
        }
        return str;
    }



// Нахождение нестандартных размеров

    /// <summary>
    /// Есть ли на складе нестандартные размеры
    /// </summary>
    /// <param name="_big"></param>
    /// <returns>Есть ли на складе нестандартные размеры t/f</returns>
    bool MadSize(bool _big) {
        for (auto &itemVect : ClothItamMap)//перебираем все элементы
        {
            for (auto &itemStruct : itemVect.second)//перебираем сами значения
            {
                if (_big && itemStruct.size > 50)
                    return true;
                if (!_big && itemStruct.size < 40)
                    return true;
            }
        }
        return false;
    }



    const map<string, vector<SizeCl>> &GetMap() { return ClothItamMap; }
};

#endif //HOMEWORK1_CLOTHES_H
