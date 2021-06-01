//
// Created by Daniil Kolesnik on 14/05/2021.
//all rights and lefts reserved


#ifndef HOMEWORK1_SHOES_H
#define HOMEWORK1_SHOES_H




#include "Abst.h"
#include <map>
#include <vector>
#include <utility>

using namespace std;

/// <summary>
/// Содержит размеры одежды и кол-во для них
/// </summary>
struct SizeSh {
    SizeSh() {
        size = 0;
        count = 0;
    };
    int size;
    int count;

    bool Found(int _s) {
        if (_s == size)
            return true;
        return false;
    }
};

class Shoes : public Abst {
    map<string, vector<SizeSh>> ShoesItamMap;//словарь
public:
// Добавление ключа

    /// <summary>
/// Добавление типа товара
/// </summary>
/// <param name="_str-Тип одежды"></param>
/// <param name="_vect-Вектор структур размеров"></param>
    string AddNewKey(string &_str, vector<SizeSh> *_vect = new vector<SizeSh>()) {
        if (ShoesItamMap.find(_str) == ShoesItamMap.end())//если ключа _str нет, то добавляем
        {
            ShoesItamMap.insert(make_pair(_str, *_vect));
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
    string AddNewMeaning(string &_str, SizeSh &_mean) {

        if (ShoesItamMap.find(_str) == ShoesItamMap.end())//если ключа _str нет, то говорим об ошибке
            return "Такого вида товара не существует\n";
        else//если ключ _str есть, добавляем новое значение в вектор
        {
            if (this->GetMaxVolume() - this->GetVolume() >= _mean.count)//если товар помещается
            {
                ShoesItamMap.find(_str)->second.push_back(_mean);//в значение(в вектор) добавляем структуру
                return "Добавление прошло успешно\n";
            } else
                return "Для товара нет места\n";
        }
    }



// Смена ключа

    string ChangeKey(string &_strOld, string &_strNew) {
        if (ShoesItamMap.find(_strOld) == ShoesItamMap.end())//если ключа _strOld нет
        {
            return "Такого вида одежы нет\n";
        } else//если ключ _strOld есть
        {
            if (ShoesItamMap.find(_strNew) == ShoesItamMap.end())//если ключ _strNew есть
            {
                vector<SizeSh> vec = ShoesItamMap.find(_strOld)->second;//сохраняем значение
                ShoesItamMap.erase(_strOld);//удаляем старое значение
                ShoesItamMap.insert(make_pair(_strNew, vec));//добавляем ключ
                return "Нзвание изменено\n";
            }
            return "Такой вид одежды уже есть\n";
        }
    }



// Смена значения

    string ChangeMeaning(string _str, int _s, SizeSh &_siNew) {
        if (ShoesItamMap.find(_str) == ShoesItamMap.end())//если ключа _str нет
        {
            return "Такого вида одежы нет\n";
        } else//если ключ _str есть
        {
            vector<SizeSh> svec;//создаем вектор
            svec = ShoesItamMap.find(_str)->second;//копируем вектор
            for (int i = 0; i < svec.size(); i++) {
                if (svec[i].Found(_s))//если есть ткое значение
                {
                    ShoesItamMap.find(_str)->second.at(i) = _siNew;
                    return "Изменение прошло успешно\n";
                }
            }
        }
    }



// Удаление значения


    string DeleteMeaning(string _str, int _s) {
        vector<SizeSh> svec;//создаем вектор
        svec = ShoesItamMap.find(_str)->second;//копируем вектор
        for (int i = 0; i < svec.size(); i++) {
            if (svec[i].Found(_s))//если есть ткое значение
            {
                ShoesItamMap.find(_str)->second.erase(ShoesItamMap.find(_str)->second.begin() + i);
                return "Удаление прошло успешно\n";
            }
        }
        return "Такого размера не существует\n";
    }



// Удаление ключа

    /// <summary>
    /// Удаление значения
    /// </summary>
    /// <param name="_str-Тип одежды"></param>
    string DeleteKey(string &_str) {
        if (ShoesItamMap.erase(_str))
            return "Удаление прошло успешно\n";
        else
            return "Такого вида товара не существует\n";
    }



// Подсчет ед. товара

    /// <summary>
    /// Определение кол-ва единиц
    /// </summary>
    /// <returns></returns>
    int Score() {
        int sum = 0;//сумма
        for (auto &itemVect : ShoesItamMap)//перебираем все элементы
        {
            for (auto &itemStruct : itemVect.second)//перебираем сами значения
            {
                sum += itemStruct.count;//Плюсуем кол-во единиц для конкретного размера одежы
            }
        }
        return sum;//возвр сумму
    }



// Вывод информации

    /// <summary>
    /// Вывод информации
    /// </summary>
    /// <returns></returns>
    string Print() {
        string str = "";
        str += "Тип склада - обувь\n";
        str += "Название: " + GetName() + "\n";
        str += "Город: " + GetCity() + "\n";
        str += "Макс. вмесительность: " + to_string(GetMaxVolume()) + "\n";
        for (auto &itemMap : ShoesItamMap) {
            str += "Вид товара: " + itemMap.first + "\n";
            for (auto &itemVect : itemMap.second) {
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
        for (auto &itemVect : ShoesItamMap)//перебираем все элементы
        {
            for (auto &itemStruct : itemVect.second)//перебираем сами значения
            {
                if (_big && itemStruct.size > 45)
                    return true;
                if (!_big && itemStruct.size < 36)
                    return true;
            }
        }
        return false;
    }



    const map<string, vector<SizeSh>> &GetMap() { return ShoesItamMap; }
};


#endif //HOMEWORK1_SHOES_H
