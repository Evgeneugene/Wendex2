//
// Created by Женя on 26.04.2021.
//

#ifndef EVLAMPEV_WENDEX_ADMINGATEWAY_H
#define EVLAMPEV_WENDEX_ADMINGATEWAY_H
#include <iostream>
#include "DataBase.h"
using namespace std;

class AdminGateway {
public:
    void registr(const string& name, const string& surname, const string& login, const string& password);
    Admin login(const string& login, const string& pass);
    void SeeAdmins(Admin &admin);
    void SeeCars(Admin &admin);
    void SeeOrders(Admin &admin);
    void SeeDrivers(Admin &admin);
    void SeePassengers(Admin &admin);
    void BlockDriverOrders(Driver& driver, Admin &admin);
    void UnblockDriverOrders(Driver &driver, Admin &admin);
    void BlockPassenger(Passenger& passenger, Admin &admin);
    void UnblockPassenger(Passenger& passenger, Admin &admin);
    void ValidateCar(Car& car, Driver& driver, Admin &admin);
};


#endif //EVLAMPEV_WENDEX_ADMINGATEWAY_H
