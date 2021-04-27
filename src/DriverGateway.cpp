
#include "DriverGateway.h"
#include <iostream>
#include "My_Exceptions.h"


/** Registration of Driver*/
void DriverGateway::registr(const string &name, const string &surname, const string &login, const string &password) {
    try {
        int users_with_same_login = DataBase::storage.count<Driver>(where(c(&Driver::login) == login));
        if (users_with_same_login != 0) {
            throw LoginIsBusy();
        } else {
            Driver drv{-1, name, surname,-1, 0, 0, 0, true,
                       "_", rand() % 500, login, password};
            DataBase::storage.insert(drv);
        }
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}

/** Driver logins into the system*/
Driver DriverGateway::login(const string &login, const string &password) {
    try {
        auto st = DataBase::storage.get_all<Driver>(
                where(c(&Driver::login) == login and c(&Driver::password) == password));
        if (!st.empty()) {
            cout << "Welcome " << st[0].name << ". Your rating is " << st[0].rating << "." << endl;
            return st[0];
        } else {
            throw IncorrectInputs(); // handling incorrect input
        }
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}

void DriverGateway::start_job(Driver &driver) { //Driver becomes available for orders
    driver.status = 1;
    DataBase::storage.update(driver);
}

vector<Order> DriverGateway::available_orders(Driver &driver) {
    try {
        if(driver.able_to_take_order) {
            auto car = DataBase::storage.get<Car>(driver.id);
            return DataBase::storage.get_all<Order>(where(c(&Order::status) == 0 and c(&Order::car_type) == car.type));
        } else {
            throw FunctionWasBlocked(driver.login, driver.blocked_by);
        }
    }
    catch(exception& e){
        cout << e.what() << endl;
        vector<Order> empty;
        return empty;
    }
}

vector<Order> DriverGateway::order_history(const Driver &driver) {
    return DataBase::storage.get_all<Order>(where(c(&Order::driver) == driver.id));
}

void DriverGateway::get_order(Driver &driver, Order &order) { //Drivers picks this order
    try {
        if(!driver.able_to_take_order) throw FunctionWasBlocked(driver.login, driver.blocked_by);
        if (driver.status != 1) {
            throw DriverOff();
        }
        if (order.status != 0) {
            throw Order_Busy();
        }
        driver.current_address =
                driver.current_address + (order.to - driver.current_address) / 2; //He moves to location
        driver.status = 2;
        DataBase::storage.update(driver);

        order.began = rand() % 500;
        order.driver = 1; //updating status
        order.status = 1;
        DataBase::storage.update(order);
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}

void DriverGateway::arrived_to_passenger(Driver &driver, Order &order) {
    driver.current_address = order.from;
    order.status = 2;
    vector<Car> vec = DataBase::storage.get_all<Car>(where(c(&Car::driver_id) == driver.id));
    Car car = vec[0];
    if (car.type == 3) car.CoolPark();
    else car.Park();
    DataBase::storage.update(order);
    DataBase::storage.update(driver);
}

void DriverGateway::ride_with_passenger(Driver &driver, Order &order) {
    driver.current_address = order.from + (order.to - order.from) / 2;
    order.status = 3;
    DataBase::storage.update(driver);
    DataBase::storage.update(order);
}

void DriverGateway::arrived_at_location(Driver &driver, Order &order) {
    driver.current_address = order.to;
    order.status = 4;
    DataBase::storage.update(driver);
    DataBase::storage.update(order);
}

void DriverGateway::end_of_order(Driver &driver, Order &order) {
    driver.current_address = order.to;
    driver.status = 1;
    order.status = 6;
    order.ended = order.began + 100;
    vector<Car> vec = DataBase::storage.get_all<Car>(where(c(&Car::driver_id) == driver.id));
    Car car = vec[0];
    if (car.type == 0) car.water = max(0, car.water - rand() % 3);
    DataBase::storage.update(car);
    DataBase::storage.update(driver);
    DataBase::storage.update(order);
}

void DriverGateway::ChangeStatus(Driver &driver, int status) { //Driver can change his status if he wants to
    driver.status = status;
    DataBase::storage.update(driver);
}

void DriverGateway::GiveRating(Passenger &passenger, int rating) { //Driver can estimate passengers behaviour
    passenger.number_of_rates++;
    passenger.rating = (passenger.rating + rating) / passenger.number_of_rates;
    DataBase::storage.update(passenger);
}

void DriverGateway::ShowCarInfo(Driver &driver) {
    vector<Car> vec = DataBase::storage.get_all<Car>(where(c(&Car::driver_id) == driver.id));
    cout << driver.name <<", you have " << vec.size() << " cars with ID: ";
    for(Car i : vec){
        cout << i.id << " ";
    }
    cout << endl << "Your working car's current info:" << endl;
    if(vec.empty()){
        cout << "No car" << endl;
        return;
    }
    Car car = DataBase::storage.get<Car>(driver.car_id);
    cout << "Type: ";
    switch (car.type) {
        case 0: {
            cout << "Economy" << endl;
            break;
        }
        case 1: {
            cout << "Comfort" << endl;
            break;
        }
        case 2: {
            cout << "Comfort Plus" << endl;
            break;
        }
        case 3: {
            cout << "Business" << endl;
            break;
        }
    }
    cout << "ID: " << car.id << endl;
    cout << "Number: " << car.number << endl;
    cout << "Color: ";
    switch (car.color) {
        case 0: {
            cout << "Red" << endl;
            break;
        }
        case 1: {
            cout << "Green" << endl;
            break;
        }
        case 2: {
            cout << "Yellow" << endl;
            break;
        }
        case 3: {
            cout << "White" << endl;
            break;
        }
        case 4: {
            cout << "Black" << endl;
            break;
        }
    }
    cout << "Model: ";
    switch (car.color) {
        case 0: {
            cout << "Mercedes" << endl;
            break;
        }
        case 1: {
            cout << "Audi" << endl;
            break;
        }
        case 2: {
            cout << "Vaz" << endl;
            break;
        }
        case 3: {
            cout << "Kamaz" << endl;
            break;
        }
    }
    if(car.type == 2){
        cout << "Number of bottles left: " << car.water << endl;
    }
}
void DriverGateway::SetCarAsMain(Driver &driver, Car &car) { //choose one car to work on
    driver.car_id = car.id;
    DataBase::storage.update(driver);
}
