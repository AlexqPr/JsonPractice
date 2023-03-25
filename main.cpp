#include <iostream>
using namespace std;
#include <fstream>
#include <list>
//using namespace nlohmann; спросить
#include "single_include/nlohmann/json.hpp"
using namespace nlohmann;



class Genius{
public:
  string Name;
  int Age;
  int IQ;

};



class Members{
public:
    string Name;
    int id;
    string Appointment;

    void toJson()
    //Данная функция добавляет экземпляры в конец файла в формате JSON
    {
        nlohmann::json j;
        j["Name"] = Name;
        j["id"] = id;
        j["Appointment"] = Appointment;
        string serialized_member = j.dump();
        fstream file2("JsonMember",ios::app);
        file2 << serialized_member;
        cout << "Ваш представитель:" << endl;
        cout << serialized_member << endl;
        file2.close();

    }
    void fromJson()
    {
        fstream file("JsonMember");
        json j;
        string json_des;
        file >> json_des;
        j = nlohmann::json::parse(json_des);
        file.close();

        Name = j["Name"];
        id = j["id"];
        Appointment = j["Appointment"];

        cout << "Ваш представитель из файла:" << endl;
        cout << "Имя:" << Name << endl;
        cout << "ID:" << id << endl;
        cout << "Должность:" << Appointment << endl;

    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Members,Name,id,Appointment);
class SerializeObject{
public:
    void toWrite(Members formember)
    {

        fstream file2("NewJsonFile");
        nlohmann::json j;
        string json_des;
        file2 >> json_des;
        j = nlohmann::json::parse(json_des);
        file2.close();
//        cout << "Пред" << j.size();

//        vector<Members> listmember;
//        listmember.push_back(formember);

        j.push_back(formember);
        file2.open("NewJsonFile");
//        cout << j;
//        cout << "Новая" << j.size() << endl;
        nlohmann::json b = j;
        file2 << b;
        b.clear();
        file2.close();
    }

    void toRead()
    {
        fstream file2("NewJsonFile");
        nlohmann::json j;
        string json_des;
        file2 >> json_des;
        j = nlohmann::json::parse(json_des);
        file2.close();
        for (int i = 0; i < j.size(); ++i) {
            cout << "Имя:" << j[i]["Name"] << endl;
            cout << "ID:" << j[i]["id"] << endl;
            cout << "Должность:" << j[i]["Appointment"] << endl;
            cout << "-------" << endl;
        }
    }
};

//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Genius,Name,Age,IQ);


int main() {
//На 3------------------------
    Genius first;
    first.Age = 15;
    first.Name = "Александр";
    first.IQ = 125;

    fstream file("ForPrimer");
    file << first.Name + "\n";
    file << first.Age;
    file << "\n";
    file << first.IQ;
    file.close();
    //Почему то если сделать функции в классе то тогда идет бесконечный вывод непонятной информации
    file.open("ForPrimer");
    file.unsetf(ios::skipws);
    char ch;
    while (!file.eof())
    {
        file >> ch;
        cout << ch; //Выводит последную цифру 2 раза (
    }
    cout << endl;
    file.close();
    //---------------------------




//Экземпляр класса с методами toJson и fromJson
    Members newmember{"Александр",1,"Руководитель"};

    Members newmember2{"Андрей",2,"Уборщик"};
    Members newmember3{"Иван",3,"Рабочий"};

    //Заполнение листа
    vector<Members> listmember;
    listmember.push_back(newmember);
    listmember.push_back(newmember2);
    listmember.push_back(newmember3);



    //Запись листа в Json файл
    nlohmann::json b = listmember;
    fstream file2("JsonList");
    file2 << b;
    b.clear();
    file2.close();


//Выгрузка информации из Json файла (листа)
    file2.open("JsonList");
    nlohmann::json j;
    string json_des;
    file2 >> json_des;
    j = nlohmann::json::parse(json_des);
    file2.close();
    for (int i = 0; i < j.size(); ++i) {
        cout << "Имя:" << j[i]["Name"] << endl;
        cout << "ID:" << j[i]["id"] << endl;
        cout << "Должность:" << j[i]["Appointment"] << endl;
        cout << "-------" << endl;
    }


    //Реализованные функции toJson и fromJson
    newmember.toJson();
    Members newmember4;
    newmember4.fromJson();

    SerializeObject forser;
    forser.toWrite(newmember);
//    forser.toWrite(newmember2);
    forser.toRead();
    return 0;
}
