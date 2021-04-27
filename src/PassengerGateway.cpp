//
// Created by Evgenii Evlampev on 14.04.2021.
//
#include <iostream>
#include "PassengerGateway.h"


void PassengerGateway::registr(const string &name, const string &surname, int address, const string &login,
                               const string &password) {
    try {
        int users_with_same_login = DataBase::storage.count<Passenger>(where(c(&Passenger::login) == login));
        auto vec = DataBase::storage.get_all<Passenger>(
                where(c(&Passenger::login) == login));
        if (users_with_same_login != 0) {
            cout << users_with_same_login << endl;
            cout << vec[0].login << endl;
            throw LoginIsBusy();
        }
        int tinkoff = 0, sberbank = 0; //by default payment method is set to 1 (it is used)
        Passenger pas{-1, name, surname, address, 0, 0, false, true, "_", login, password, 1, tinkoff, sberbank};
        DataBase::storage.insert(pas);
    } catch(exception e){
        cout << e.what() << endl;
    }
}

Passenger PassengerGateway::login(const string &login, const string &password) {
    try {
        auto vec = DataBase::storage.get_all<Passenger>(
                where(c(&Passenger::login) == login and c(&Passenger::password) == password));
        if (!vec.empty()) {
            cout << "Welcome " << vec[0].name << ". Your rating is " << vec[0].rating << "." << endl;
            return vec[0];
        } else {
            throw IncorrectInputs();
        }
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
}

void PassengerGateway::make_order(Passenger &passenger, int from, int to, CarType carType) {
    try {
        if(passenger.able_to_order) {
            if (!passenger.has_order) {
                int sum = PassengerGateway::CalculatePrice(from, to, carType);
                Order order{-1, from, to, passenger.id, -1, sum, carType, 0}; //makes the order
                DataBase::storage.insert(order);
                passenger.has_order = true;
                DataBase::storage.update(passenger);
            } else throw AlreadyHasOrder(passenger.login);
        } else throw FunctionWasBlocked(passenger.login, passenger.blocked_by);
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}

vector<Order> PassengerGateway::order_history(const Passenger &passenger) {
    return DataBase::storage.get_all<Order>(where(c(&Order::passenger) == passenger.id));
}


int PassengerGateway::CalculatePrice(int from, int to, CarType type) {
    return (abs(from - to) * type);
}

int PassengerGateway::GetDriverCoordinates(Order &o) {
    return DataBase::storage.get<Driver>(o.driver).current_address;
}

void PassengerGateway::UpdatePaymentMethod(Passenger &passenger, string method) {

    passenger.tinkoff = 0;
    passenger.sberbank = 0;
    passenger.cash = 0;
    if (method == "Tinkoff") {

        passenger.tinkoff = 1;
    } else if (method == "Sberbank") {
        passenger.sberbank = 1;

    } else if (method == "Cash") {
        passenger.cash = 1;
    }
    DataBase::storage.update(passenger);
}

string PassengerGateway::SeePaymentMethod(Passenger &passenger) {
    if (passenger.tinkoff == 1) return "Tinkoff";
    if (passenger.sberbank == 1) return "Sberbank";
    if (passenger.cash == 1) return "Cash";
}

void PassengerGateway::PayTheBill(Order &order) {
    order.status = 5;
    DataBase::storage.update(order);
    cout << "The bill is payed" << endl;
}

void PassengerGateway::GiveRating(Driver &driver, int rating) {
    driver.number_of_rates++;
    driver.rating = (driver.rating + rating) / driver.number_of_rates;
    DataBase::storage.update(driver);
}

int PassengerGateway::SeeAddress(Passenger &passenger) {
    return passenger.address;
}

void PassengerGateway::UpdateAddress(Passenger &passenger, int address) {
    passenger.address = address;
    DataBase::storage.update(passenger);
}
