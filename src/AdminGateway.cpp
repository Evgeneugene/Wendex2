//
// Created by Женя on 26.04.2021.
//

#include "AdminGateway.h"
#include "DataBase.h"
#include "My_Exceptions.h"

void AdminGateway::registr(const string &name, const string &surname, const string &login, const string &password) { //registration
    try {
        auto vec = DataBase::storage.get_all<Admin>(where(c(&Admin::login) == login));
        if (vec.empty()) {
            Admin admin(-1, name, surname, login, password);
            DataBase::storage.insert(admin);
        } else throw LoginIsBusy();
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}

Admin AdminGateway::login(const string &login, const string &pass) { //login
    auto st = DataBase::storage.get_all<Admin>(where(c(&Admin::login) == login and c(&Admin::password) == pass));
    if (!st.empty()) {
        cout << "Welcome " << st[0].name << "." << endl;
        return st[0];
    } else throw IncorrectInputs();
}

void AdminGateway::SeeAdmins(Admin &admin) { //Methods to see the whole information in the base
    cout << "The admins are:" << endl;
    vector<Admin> admins = DataBase::storage.get_all<Admin>();
    for (auto i : admins) {
        cout << DataBase::storage.dump(i) << endl;
    }
}

void AdminGateway::SeeOrders(Admin &admin) {
    cout << "The orders are:" << endl;
    vector<Order> orders = DataBase::storage.get_all<Order>();
    for (auto i : orders) {
        cout << DataBase::storage.dump(i) << endl;
    }
}

void AdminGateway::SeeCars(Admin &admin) {
    cout << "The cars are:" << endl;
    vector<Car> cars = DataBase::storage.get_all<Car>();
    for (auto i : cars) {
        cout << DataBase::storage.dump(i) << endl;
    }
}

void AdminGateway::SeePassengers(Admin &admin) {
    cout << "The passengers are:" << endl;
    vector<Passenger> p = DataBase::storage.get_all<Passenger>();
    for (auto i : p) {
        cout << DataBase::storage.dump(i) << endl;
    }
}

void AdminGateway::SeeDrivers(Admin &admin) {
    cout << "The drivers are:" << endl;
    vector<Driver> d = DataBase::storage.get_all<Driver>();
    for (auto i : d) {
        cout << DataBase::storage.dump(i) << endl;
    }
}

void AdminGateway::BlockDriverOrders(Driver &driver, Admin &admin) { //Block driver's function of taking an order
    driver.able_to_take_order = false;
    driver.blocked_by = admin.login;
    DataBase::storage.update(driver);
}

void AdminGateway::UnblockDriverOrders(Driver &driver, Admin &admin) { //unblock
    driver.able_to_take_order = true;
    driver.blocked_by = "_";
    DataBase::storage.update(driver);
}

void AdminGateway::BlockPassenger(Passenger &passenger, Admin &admin) { //block passenger's ability to make orders
    passenger.able_to_order = false;
    passenger.blocked_by = admin.login;
    DataBase::storage.update(passenger);
}

void AdminGateway::UnblockPassenger(Passenger &passenger, Admin &admin) { //unblock
    passenger.able_to_order = true;
    passenger.blocked_by = "_";
    DataBase::storage.update(passenger);
}

void AdminGateway::ValidateCar(Car &car_temp, Driver &driver_temp, Admin &admin) { //To approve the car chosen by the driver and add it to the base
    Car car =  DataBase::storage.get<Car>(car_temp.id);
    Driver driver =  DataBase::storage.get<Driver>(driver_temp.id);
    car.validated_by_id = admin.id;
    car.driver_id = driver.id;
    driver.car_id = car.id;
    DataBase::storage.update(car);
    DataBase::storage.update(driver);
    driver =  DataBase::storage.get<Driver>(driver.id);
}
