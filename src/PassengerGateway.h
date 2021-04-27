#ifndef EVLAMPEV_WENDEX_PASSENGERGATEWAY_H
#define EVLAMPEV_WENDEX_PASSENGERGATEWAY_H

#include <string>
#include <vector>
#include "My_Exceptions.h"
#include "DataBase.h"

using namespace std;


class PassengerGateway {
public:
    void registr(const string& name, const string& surname, int address, const string& login, const string& password);
    Passenger login(const string& login, const string& password);
    void make_order(Passenger &passenger, int from, int to, CarType carType);
    vector<Order> order_history(const Passenger& passenger);
    int CalculatePrice(int from, int to, CarType type);
    int GetDriverCoordinates(Order &o);
    void UpdatePaymentMethod(Passenger& passenger, string bank);
    string SeePaymentMethod(Passenger& passenger);
    void PayTheBill(Order& order);
    void GiveRating(Driver& driver, int rating);
    int SeeAddress(Passenger& passenger);
    void UpdateAddress(Passenger &passenger, int address);
};


#endif //HOMEWORK_4_PASSENGERGATEWAY_H
