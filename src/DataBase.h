//
// Created by Evgenii Evlampev on 14.04.2021.
//

#ifndef EVLAMPEV_WENDEX_DATABASE_H
#define EVLAMPEV_WENDEX_DATABASE_H
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>

using namespace std;
using namespace sqlite_orm;
//const string models[4] = {"Mercedes", "Augi", "Vaz", "Kamaz"};
enum Model {
    Mercedes = 0,
    Audi,
    Vaz,
    Kamaz
};
enum Color {  /** Enums are Just for understanding what different values mean */
    Red = 0,
    Green,
    Yellow,
    White,
    Black
};
enum CarType {
    Economy = 0,
    Comfort,
    ComfortPlus,
    Business
};

class Car {
public:
    int type; //Economy = 0, Comfort = 1, ComfortPlus = 2, Business = 3
    int id;
    int driver_id;
    int number;
    int color;
    int model;
    int water = -1;
    int validated_by_id = -1;
    void Park(){
        std::cout << "Usual boring parking" << endl;
    }
    void CoolPark(){
        std::cout << "Drift veeewwww and park in front of the entrance" << endl;
    }
};
class Passenger {
public:
    int id;
    string name;
    string surname;
    int address; //pinned address
    int rating;
    int number_of_rates;
    bool has_order;
    bool able_to_order;
    string blocked_by;
    string login;
    string password;
    int cash; //To check payment method
    int tinkoff;
    int sberbank;
};

class Driver {
public:
    int id;
    string name;
    string surname;
    int car_id;
    int rating;
    int number_of_rates;
    int status; // offline = 0, free - 1, busy - 2
    bool able_to_take_order;
    string blocked_by;
    int current_address;
    string login;
    string password;
};

class Order {
public:
    int id;
    int from;
    int to;
    int passenger;
    int driver;
    int sum; //price
    int car_type;
    int status;// 0 - Searching for the car; 1 - Waiting for the chosen car; 2 - Waiting for the passenger
    // 3 - Riding 4 - Arrived, waiting for payment 5 - Payed 6 - Ended by Driver
    int began = -1;
    int ended = -1;
};

class Admin{
public:
    int id;
    string name;
    string surname;
    string login;
    string password;
    Admin(int i, string n, string s, string l, string p){
        id = i;
        name = n;
        surname = s;
        login = l;
        password = p;
    }
    Admin() = default;
};

inline auto Storage() { //for storing the data
    return make_storage("DataBase.sqlite",
                        make_table("passengers",
                                   make_column("id", &Passenger::id, autoincrement(), primary_key()),
                                   make_column("name", &Passenger::name),
                                   make_column("surname", &Passenger::surname),
                                   make_column("pinned address, x", &Passenger::address),
                                   make_column("rating, 0-5", &Passenger::rating),
                                   make_column("number of rates", &Passenger::number_of_rates),
                                   make_column("Already has order", &Passenger::has_order),
                                   make_column("Able to order", &Passenger::able_to_order),
                                   make_column("Blocked by admin", &Passenger::blocked_by),
                                   make_column("login", &Passenger::login),
                                   make_column("password", &Passenger::password),
                                   make_column("Cash", &Passenger::cash),
                                   make_column("Tinkoff", &Passenger::tinkoff),
                                   make_column("Sberbank", &Passenger::sberbank)),
                        make_table("drivers",
                                   make_column("id", &Driver::id, autoincrement(), primary_key()),
                                   make_column("name", &Driver::name),
                                   make_column("surname", &Driver::surname),
                                   make_column("Car ID", &Driver::car_id),
                                   make_column("rating, 0-5", &Driver::rating),
                                   make_column("number of rates", &Driver::number_of_rates),
                                   make_column("status", &Driver::status),
                                   make_column("Able to take order", &Driver::able_to_take_order),
                                   make_column("Blocked by", &Driver::blocked_by),
                                   make_column("current address, x", &Driver::current_address),
                                   make_column("login", &Driver::login),
                                   make_column("password", &Driver::password)),
                        make_table("orders",
                                   make_column("id", &Order::id, autoincrement(), primary_key()),
                                   make_column("from, x", &Order::from),
                                   make_column("to, x", &Order::to),
                                   make_column("passenger id", &Order::passenger),
                                   make_column("driver id", &Order::driver),
                                   make_column("sum, rubles", &Order::sum),
                                   make_column("Car type", &Order::car_type),
                                   make_column("status", &Order::status),
                                   make_column("time began", &Order::began),
                                   make_column("time ended", &Order::ended)),
                        make_table("cars",
                                   make_column("ID", &Car::id, autoincrement(), primary_key()),
                                   make_column("Driver ID", &Car::driver_id),
                                   make_column("Type", &Car::type),
                                   make_column("Number", &Car::number),
                                   make_column("Color", &Car::color),
                                   make_column("Model", &Car::model),
                                   make_column("Water Bottles", &Car::water),
                                   make_column("Validated by admin, id", &Car::validated_by_id)),
                        make_table("admins",
                                   make_column("ID", &Admin::id, autoincrement(), primary_key()),
                                   make_column("name", &Admin::name),
                                   make_column("surname", &Admin::surname),
                                   make_column("login", &Admin::login),
                                   make_column("password", &Admin::password)));
}

class DataBase {
public:
    inline static auto storage = Storage(); //store in class for extendibility because there can be several storages
};


#endif
