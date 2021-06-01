//
// Created by Daniil Kolesnik on 14/05/2021.
//all rights and lefts reserved


#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include "Clothes.h"
#include "shoes.h"
#include "BD.h"


using namespace std;
namespace fs = std::filesystem;

const string path = "/Users/daniilkolesnik/Desktop/FORHOMEWORK";//путь, где лежат БД

const BD &OpenBD(string);

const BD &CreateBD();

void UsingBD(BD &);

void SaveBD(BD &);

void UsingSlacd(Clothes &);

void UsingSlacd(Shoes &);

int MainStrCase();

int UsingBDStrCase();

int UsingSlacdStrCase(bool);

int main() {

    string str, str1;//свободная переменная
    BD bd;// БД
    size_t t = 0;
    while (true) {
        t = MainStrCase();
        switch (t) {
            case 1:
// Вывод сущ. БД
                cout << "--------------------------------------\n";
                cout << "Существующие БД:\n\n";
                for (auto &p : fs::directory_iterator(path))//ещем файлы в дериктории
                {
                    str = p.path().filename().string();//берем название пути
                    cout << str.erase(str.length() - 4)
                         << endl;//выводим название, от которого отсекаем последние 4 символа(прасширение)
                }
                break;
            case 2:
// Открытие БД
                cout << "--------------------------------------\n";
                cout << "Введите название:\n\n";
                cin >> str;//вводим название
                bd = OpenBD(str);//возвр класс
                if (bd.GetName() != "")//если открытие прошло удачно
                    UsingBD(bd);//передаем ссылку в функцию использования БД


                break;
            case 3:
                bd = CreateBD();//создание бд
                UsingBD(bd);//передаем ссылку в функцию использования БД
                break;
            case 4:
// Переименовка
                cout << "Введите название БД, которую хотите переименовать:\n";
                cin >> str;
                cout << "Введите новое название для БД:\n";
                cin >> str1;
                try//ловим исключения
                {
                    fs::rename(path + "/" + str + ".txt",
                               path + "/" + str1 + ".txt");//меняем название файла, хранящего бд
                    cout << "БД <" + str + "> переименована на <" + str1 + ">";
                }
                catch (const fs::filesystem_error &)//указан неверный путь
                {
                    cout << "БД названием <" + str + "> не существует";
                }
                break;
            case 5:
// Удаление
                cout << "Введите название БД, которую хотите удалить:\n";
                cin >> str;
                try//ловим исключения
                {
                    if (!fs::remove(path + "/" + str + ".txt"))//удаляем файла, хранящий бд
                        cout << "БД названием <" + str + "> не существует";
                    else
                        cout << "БД <" + str + "> удалена";
                }
                catch (const fs::filesystem_error &)//указан неверный путь
                {

                }

                break;
            case 0:
                return 0;
                break;
            default:
                cout << "Неверный ввод\n";
                break;
        }
    }
    system("pause");

}


void UsingBD(BD &_bd) {
    string str;
    vector<string> strVec;
    int t;
    Clothes *cl = new Clothes();// экземпляр склада одежды
    Shoes *sh = new Shoes();// экземпляр склада Обуви
    BD newBD;

    while (true) {

        t = UsingBDStrCase();
        switch (t) {
            case 1:

                for (auto item : _bd.GetScladName())//выводим названия
                    cout << item << "\n";
                break;
            case 2:
                cout << "Введите название\n\n";
                cin >> str;//вводим название
                str = _bd.GetInfoSclad(str);
                cout << str;//выводим инфу
                break;
            case 3:
                strVec = _bd.GetScladName();//сохраняем вектор названий
                sort(strVec.begin(), strVec.end());//сортируем его
                for (auto item : strVec)//выводим названия
                    cout << item << "\n";
                break;
            case 4:
                strVec = _bd.GetScladVolume();//сохраняем вектор названий
                sort(strVec.begin(), strVec.end());//сортируем его
                for (auto item : strVec)//выводим названия
                    cout << item << "\n";
                break;
            case 5:
// Выборка по нест. размерам
                cout << "Сохранить БД перед выборкой?\n 1-да, 0-нет\n";
                if (cin >> t)
                    SaveBD(_bd);
                cout << "Выборка\n 1-Больших размеров, 0-Маленьких размеров\n";
                cin >> t;
                newBD.SetVectClothes(_bd.GetMadSizeVectCloth(t));
                newBD.SetVectShoes(_bd.GetMadSizeVectShoes(t));
                newBD.SetName(string(t ? "BigSize" : "SmolSize"));
                _bd = newBD;
                cout << "Сохранить выборку как новую БД?\n 1-да, 0-нет\n";
                if (cin >> t)
                    SaveBD(newBD);

                break;
            case 6:
                cout << "Сохранить БД перед выборкой?\n 1-да, 0-нет\n";
                if (cin >> t)
                    SaveBD(_bd);
                cout << "Выборка складов вместительностью меньше чем:\n";
                cin >> t;
                newBD.SetVectClothes(_bd.GetSetMinSizeVectCloth(t));
                newBD.SetVectShoes(_bd.GetSetMinSizeVectShoes(t));
                newBD.SetName(string(t ? "BigSize" : "SmolSize"));
                _bd = newBD;
                cout << "Сохранить выборку как новую БД?\n 1-да, 0-нет\n";
                if (cin >> t)
                    SaveBD(newBD);
                break;
            case 7:
// Добавление склада
                cout << "Склад какого типа вы хотите добавить?\n1-одежда 2-обувь\n";
                cin >> t;
                if (t == 1) {
                    cl = new Clothes();
                    cout << "Введите название\n";
                    cin >> str;
                    cl->SetName(str);
                    cout << "Введите город\n";
                    cin >> str;
                    cl->SetCity(str);
                    cout << "Введите вместительность\n";
                    cin >> t;
                    cl->SetMaxVolume(t);
                    _bd.PushClSclad(*cl);
                }
                if (t == 2) {
                    sh = new Shoes();
                    cout << "Введите название\n";
                    cin >> str;
                    sh->SetName(str);
                    cout << "Введите город\n";
                    cin >> str;
                    sh->SetCity(str);
                    cout << "Введите вместительность\n";
                    cin >> t;
                    sh->SetMaxVolume(t);
                    _bd.PushShSclad(*sh);
                }

                break;
            case 8:
// Перейти к управлению складом
                cout << "Введите название склада\n";
                cin >> str;
                *cl = _bd.GetClothes(str);
                if (cl->GetName() != "")
                    UsingSlacd(*cl);
                else {
                    *sh = _bd.GetShoes(str);
                    if (sh->GetName() != "")
                        UsingSlacd(*sh);
                    else
                        cout << "Такой БД нет\n";
                }

                break;
            case 9:
                SaveBD(_bd);
                cout << "БД сохранена\n";
                break;
            case 0:
                return;
                break;
            default:
                cout << "Неверный ввод\n";
                break;
        }
        //cout << "\n______________________________________\n";
    }

}


void UsingSlacd(Clothes &_clothes) {
    int t, t1, t2;
    string str, str1;
    SizeCl sCl;
    while (true) {
        t = UsingSlacdStrCase(true);
        switch (t) {
            case 1:
                cout << _clothes.Print();
                break;
            case 2:
// Добавление нового ключа
                cout << "Введите вид одежды\n";
                cin >> str;
                cout << _clothes.AddNewKey(str);

                break;
            case 3:
// Добавление нового значения
                cout << "Введите вид одежды\n";
                cin >> str;
                cout << "Введите высоту одежды\n";
                cin >> t;
                sCl.height = t;
                cout << "Введите размер одежды\n";
                cin >> t;
                sCl.size = t;
                cout << "Введите количество товара\n";
                cin >> t;
                sCl.count = t;
                cout << _clothes.AddNewMeaning(str, sCl);

                break;
            case 4:
// Сменить ключ
                cout << "Введите вид одежды, который хотите поменять\n";
                cin >> str;
                cout << "Введите вид одежды, на который хотите поменять\n";
                cin >> str1;
                cout << _clothes.ChangeKey(str, str1);

                break;
            case 5:
// Изменить значение
                cout << "Введите вид одежды, размеры которого хотите поменять\n";
                cin >> str;
                cout << "Введите высоту ожеды, которую хотите поменять\n";
                cin >> t;
                cout << "Введите размер ожеды, который хотите поменять\n";
                cin >> t1;
                cout << "Введите высоту ожеды, на которую хотите поменять\n";
                cin >> t2;
                sCl.height = t2;
                cout << "Введите размер ожеды, на который хотите поменять\n";
                cin >> t2;
                sCl.size = t2;
                cout << "Введите кол-во единиц ожеды, на который хотите поменять\n";
                cin >> t2;
                sCl.count = t2;
                cout << _clothes.ChangeMeaning(str, t, t1, sCl);

                break;
            case 6:
// Удаление вида одежды
                cout << "Введите вид одежды\n";
                cin >> str;
                cout << _clothes.DeleteKey(str);

                break;
            case 7:
//Удаления размера одежды
                cout << "Введите вид одежды\n";
                cin >> str;
                cout << "Введите высоту одежды\n";
                cin >> t;
                cout << "Введите размер одежды\n";
                cin >> t1;
                cout << _clothes.DeleteMeaning(str, t, t1);

                break;
            case 0:
                return;
                break;
            default:
                cout << "Неверный ввод\n";
                break;
        }
    }
}


void UsingSlacd(Shoes &_shoes) {
    int t, t1;
    string str, str1;
    SizeSh sSh;
    while (true) {
        t = UsingSlacdStrCase(true);
        switch (t) {
            case 1:
                cout << _shoes.Print();
                break;
            case 2:
// Добавление нового ключа
                cout << "Введите вид обуви\n";
                cin >> str;
                cout << _shoes.AddNewKey(str);

                break;
            case 3:
// Добавление нового значения
                cout << "Введите вид обуви\n";
                cin >> str;
                cout << "Введите размер обуви\n";
                cin >> t;
                sSh.size = t;
                cout << "Введите количество товара\n";
                cin >> t;
                sSh.count = t;
                cout << _shoes.AddNewMeaning(str, sSh);

                break;
            case 4:
// Сменить ключ
                cout << "Введите вид обуви, который хотите поменять\n";
                cin >> str;
                cout << "Введите вид обуви, на который хотите поменять\n";
                cin >> str1;
                cout << _shoes.ChangeKey(str, str1);

                break;
            case 5:
// Изменить значение
                cout << "Введите вид обуви, размеры которого хотите поменять\n";
                cin >> str;
                cout << "Введите размер обуви, который хотите поменять\n";
                cin >> t;
                cout << "Введите размер обуви, на который хотите поменять\n";
                cin >> t1;
                sSh.size = t1;
                cout << "Введите кол-во единиц обуви, на который хотите поменять\n";
                cin >> t1;
                sSh.count = t1;
                cout << _shoes.ChangeMeaning(str, t, sSh);

                break;
            case 6:
// Удаление вида одежды
                cout << "Введите вид обуви\n";
                cin >> str;
                cout << _shoes.DeleteKey(str);

                break;
            case 7:
// Удаления размера одежды
                cout << "Введите вид обуви\n";
                cin >> str;
                cout << "Введите размер обуви\n";
                cin >> t;
                cout << _shoes.DeleteMeaning(str, t);

                break;
            case 0:
                return;
                break;
            default:
                cout << "Неверный ввод\n";
                break;
        }
    }
}


void SaveBD(BD &_bd) {
    ofstream oFstr;
    oFstr.open(path + "/" + _bd.GetName() + ".txt");//открываем файл
    oFstr << _bd.GetName() + "\n";//гружаем имя БД в 1 строку
//  загрузка скаладов одежды
    for (auto itemCloth : _bd.GetVectClothes())//проходим по вектору скаладов одежды
    {
        oFstr << itemCloth.GetName() << "\n";//загружаем имя
        oFstr << itemCloth.GetCity() << "\n";//загружаем город
        oFstr << to_string(itemCloth.GetMaxVolume()) << "\n";//загружаем max вместительность
        oFstr << to_string(itemCloth.GetVolume()) << "\n";//загружаем вместительность
        for (auto &itemMap : itemCloth.GetMap())//проходим по карте наименований
        {
            oFstr << itemMap.first << " ";//колюч(вид одежды)

            for (auto &itemVect : itemMap.second)//проходим по вектору размеров
            {
                oFstr << itemVect.height << " " << itemVect.size << " " << itemVect.count
                      << "*";//выводим структуру размеров
            }
            oFstr << "; \n";//конец вида товара
        }
        oFstr << "--- \n";//конец склада
    }
    oFstr << "/-----/\n";//конец складов одежды


// Загрузка скаладов обуви


    for (auto itemShues : _bd.GetVectShoes())//проходим по вектору скаладов обуви
    {
        oFstr << itemShues.GetName() << "\n";//загружаем имя
        oFstr << itemShues.GetCity() << "\n";//загружаем город
        oFstr << to_string(itemShues.GetMaxVolume()) << "\n";//загружаем max вместительность
        oFstr << to_string(itemShues.GetVolume()) << "\n";//загружаем вместительность

        for (auto &itemMap : itemShues.GetMap())//проходим по карте наименований
        {
            oFstr << itemMap.first << " ";//колюч(вид обуви)

            for (auto &itemVect : itemMap.second)//проходим по вектору размеров
            {
                oFstr << itemVect.size << " " << itemVect.count << "*";//выводим структуру размеров
            }
            oFstr << "; \n";//конец вида товара
        }
        oFstr << "--- \n";//конец склада
    }
    oFstr << "/-----/\n";//конец складов обуви


    oFstr.close();//закрывам файл
}


const BD &CreateBD() {
    BD *bd = new BD();//создаем экз
    string str;
    cout << "Введте название БД\n";
    cin >> str;//ввод
    bd->SetName(str);//устанавливаем имя
    return *bd;
}


const BD &OpenBD(string _bdName) {
    ifstream iFstr;
    string str;
    Clothes *cl;// экземпляр склада одежды
    Shoes *sh;// экземпляр склада одежды
    BD *bd = new BD();// экземпляр БД

    iFstr.open(path + "/" + _bdName + ".txt");//открываем файл
    if (!iFstr.fail())//Есть ли флаг ошибки при открытии?
    {
        getline(iFstr, str);//получем первую строку, содерж имя БД
        bd->SetName(str);//устанавливаем имя БД

        vector<SizeCl> sizeClothesVect;//Создаем вектор значений размеров
        vector<SizeSh> sizeShoesVect;//Создаем вектор значений размеров

// Заполнение вектора складов одежды в бд
        while (true) {
            cl = new Clothes();//Создаем экземпляр класса склада
            getline(iFstr, str);//берем строку до \n
            if (str != "/-----/")//если не конец складов одежды
                cl->SetName(str);//устанавливаем имя склада
            else
                break;//иначе покидаем цикл
            getline(iFstr, str);//берем строку до \n
            cl->SetCity(str);//устанавливаем город
            getline(iFstr, str);//берем строку до \n
            cl->SetMaxVolume(atoi(str.c_str()));//устанавливаем max значение объема склада
            getline(iFstr, str);//берем строку до \n
            cl->SetVolume(atoi(str.c_str()));//устанавливаем значение заполнености склада

// Проверка на правильность
            if (cl->GetCity() == "" || cl->GetName() == "" ||
                !cl->GetMaxVolume())//если какое-то поле пустое, что-то пошло не так
            {
                cout << "При загрузке БД произошла ошибка (файл поврежден)";
                cl->SetName("");
                return *bd;
            }


// Заполнение карты значений (вид одежды - вектор размеров)
            while (true) {
                string key;

                getline(iFstr, str, ' '); // берем строку до пробела
                if (str != "---")//если конец склада
                    key = str;//сохраняем ключ(вид одежды)
                else {//иначе
                    getline(iFstr, str);//удаляем \n
                    break;//выходим из цикла
                }


// Заполнение вектора структур размеров
                while (true) {
                    SizeCl sCL;//Создаем экземпляр структуры размеров
                    getline(iFstr, str, ' ');// берем строку до пробела
                    if (str != ";")//если не конец описания размеров
                        sCL.height = atoi(str.c_str());//устанавливаем значение роста одежды
                    else {//иначе
                        getline(iFstr, str);//удаляем \n
                        break;//выходим из цикла
                    }

                    getline(iFstr, str, ' ');// берем строку до пробела
                    sCL.size = atoi(str.c_str());//устанавливаем значение размера одежы

                    getline(iFstr, str, '*');// берем строку до *
                    sCL.count = atoi(str.c_str());//устанавливаем значение кол-ва обйектов этого размера

                    sizeClothesVect.push_back(sCL);//Добавляем в вектор структур размеров, структуру размеров
                }


                cl->AddNewKey(key, &sizeClothesVect);//Добавляем в словарь ключ с вектором
                sizeClothesVect.clear();
            }


            bd->PushClSclad(*cl);//добавляем склад
        }



// Заполнение вектора складов Обуви в бд
        while (true) {
            sh = new Shoes();//Создаем экземпляр класса склада
            getline(iFstr, str);//берем строку до \n
            if (str != "/-----/")//если не конец складов
                sh->SetName(str);//устанавливаем имя склада
            else
                break;//иначе покидаем цикл
            getline(iFstr, str);//берем строку до \n
            sh->SetCity(str);//устанавливаем город
            getline(iFstr, str);//берем строку до \n
            sh->SetMaxVolume(atoi(str.c_str()));//устанавливаем max значение объема склада
            getline(iFstr, str);//берем строку до \n
            sh->SetVolume(atoi(str.c_str()));//устанавливаем значение заполнености склада

// Проверка на правильность
            if (sh->GetCity() == "" || sh->GetName() == "" ||
                !sh->GetMaxVolume())//если какое-то поле пустое, что-то пошло не так
            {
                cout << "При загрузке БД произошла ошибка (файл поврежден)";
                sh->SetName("");
                return *bd;
            }


// Заполнение карты значений (вид одежды - вектор размеров)
            while (true) {
                string key;

                getline(iFstr, str, ' '); // берем строку до пробела
                if (str != "---")//если конец склада
                    key = str;//сохраняем ключ(вид одежды)
                else {//иначе
                    getline(iFstr, str);//удаляем \n
                    break;//выходим из цикла
                }
// Заполнение вектора структур размеров
                while (true) {
                    SizeSh sSH;//Создаем экземпляр структуры размеров
                    getline(iFstr, str, ' ');// берем строку до пробела
                    if (str != ";")//если не конец описания размеров
                        sSH.size = atoi(str.c_str());//устанавливаем значение размера обуви
                    else {//иначе
                        getline(iFstr, str);//удаляем \n
                        break;//выходим из цикла
                    }

                    getline(iFstr, str, '*');// берем строку до *
                    sSH.count = atoi(str.c_str());//устанавливаем значение кол-ва объектов этого размера

                    sizeShoesVect.push_back(sSH);//Добавляем в вектор структур размеров, структуру размеров
                }


                sh->AddNewKey(key, &sizeShoesVect);//Добавляем в словарь ключ с вектором
                sizeShoesVect.clear();
            }


            bd->PushShSclad(*sh);//добавляем склад
        }

    } else
        cout << "Такой БД нет\n";//если ошибка открытия

    return *bd;//возвращаем бд
}


int MainStrCase() {
    string str;
    cout << "\n--------------------------------------\n";
    cout << "Выберите действие\n";
    cout << "1-Вывести существующие БД\n";
    cout << "2-Открыть БД\n";
    cout << "3-Добавить БД\n";
    cout << "4-Переименовать БД\n";
    cout << "5-Удалить БД\n";
    cout << "0-Выход\n";
    cout << "--------------------------------------\n";
    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);//переводим в нижний текст
    if (str == "1" || str == "вывести бд" || str == "вывести")
        return 1;
    if (str == "2" || str == "открыть бд" || str == "открыть")
        return 2;
    if (str == "3" || str == "добавить бд" || str == "добавить")
        return 3;
    if (str == "4" || str == "переименовать бд" || str == "переименовать")
        return 4;
    if (str == "5" || str == "удалить бд" || str == "удалить")
        return 5;
    if (str == "0" || str == "выход")
        return 0;
    return 7;
}


/// Распознование ввода для функции UsingBD

int UsingBDStrCase() {
    string str;
    cout << "\n______________________________________\n";
    cout << "Выберите действие\n";
    cout << "1-Вывести список складов\n";
    cout << "2-Вывести информацию о складе\n";
    cout << "3-Сортировка складов по названию\n";
    cout << "4-Сортировка складов по вместительности\n";
    cout << "5-Выборка складов с нестандартными размерами\n";
    cout << "6-Выборка складов с вместимостью меньше чем заданная\n";
    cout << "7-Добавть склад\n";
    cout << "8-Управление складом\n";
    cout << "9-Сохранить БД\n";
    cout << "0-Назад\n";
    cout << "______________________________________\n";
    getline(cin, str);
    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);//переводим в нижний текст
    if (str == "1" || str == "вывести список складов" || str == "список складов" || str == "вывести склады")
        return 1;
    if (str == "2" || str == "вывести информацию о складе" || str == "вывести информацию" ||
        str == "информация о складе" || str == "о складе")
        return 2;
    if (str == "3" || str == "сортировка складов по названию" || str == "склады по названию" || str == "по названию")
        return 3;
    if (str == "4" || str == "сортировка складов по вместительности" || str == "склады по вместительности" ||
        str == "по вместительности")
        return 4;
    if (str == "5" || str == "выборка складов с нестандартными размерами" ||
        str == "склады с нестандартными размерами" || str == "нестандартные размеры")
        return 5;
    if (str == "6" || str == "выборка складов с вместимостью меньше чем заданная" ||
        str == "выборка складов с вместимостью" || str == "вместимость меньше чем заданная")
        return 6;
    if (str == "7" || str == "добавть склад" || str == "добавть" || str == "новый склад")
        return 7;
    if (str == "8" || str == "управление складом" || str == "управлять складом")
        return 8;
    if (str == "9" || str == "сохранить бд" || str == "сохранить")
        return 9;
    if (str == "0" || str == "выход" || str == "назад")
        return 0;
    return -1;
}

int UsingSlacdStrCase(bool _bIsCoth) {
    string nameType;
    if (_bIsCoth)
        nameType = "одежы";
    else
        nameType = "обуви";

    string str;
    cout << "\n****************************************\n";
    cout << "Выберите действие\n";
    cout << "1-Вывести товары склада\n";
    cout << "2-Добавть вид " + nameType + "\n";
    cout << "3-Добавить размер\n";
    cout << "4-Изменить вид" + nameType + "\n";
    cout << "5-Изменить размер\n";
    cout << "6-Удалить вид " + nameType + "\n";
    cout << "7-Удалить размер\n";
    cout << "0-Назад\n";
    cout << "****************************************\n";
    getline(cin, str);
    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::tolower);//переводим в нижний текст
    if (str == "1" || str == "вывести товары склада" || str == "вывести товары" || str == "информация о складе")
        return 1;
    if (str == "2" || str == "добавть вид " + nameType || str == "добавть вид")
        return 2;
    if (str == "3" || str == "добавить размер" || str == "новый размер")
        return 3;
    if (str == "4" || str == "изменить вид " + nameType || str == "изменить вид")
        return 4;
    if (str == "5" || str == "изменить размер" || str == "сменить размер")
        return 5;
    if (str == "6" || str == "удалить вид " + nameType || str == "удалить вид")
        return 6;
    if (str == "7" || str == "удалить размер")
        return 7;
    if (str == "0" || str == "выход" || str == "назад")
        return 0;
    return -1;
}
