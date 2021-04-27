#ifndef EVLAMPEV_WENDEX_DRIVERGATEWAY_H
#define EVLAMPEV_WENDEX_DRIVERGATEWAY_H

#include <string>
#include "My_Exceptions.h"
#include "DataBase.h"

class DriverGateway {
public:
    void registr(const string& name, const string &surname, const string& login, const string& password);

    Driver login(const string& login, const string& password);

    void start_job(Driver& driver);

    vector<Order> available_orders(Driver& driver);
    vector<Order> order_history(const Driver& driver);

    void get_order(Driver& driver, Order& order);
    void arrived_to_passenger(Driver& driver, Order& order);
    void ride_with_passenger(Driver& driver, Order &order);
    void end_of_order(Driver& driver, Order &order);
    void arrived_at_location(Driver& driver, Order &order);
    void ChangeStatus(Driver& driver, int status);
    void GiveRating(Passenger& passenger, int rating);
    void ShowCarInfo(Driver &driver);
    void SetCarAsMain(Driver &driver, Car &car);
};


#endif
