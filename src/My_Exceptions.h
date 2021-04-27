#ifndef EVLAMPEV_WENDEX_MY_EXCEPTIONS_H
#define EVLAMPEV_WENDEX_MY_EXCEPTIONS_H

#include <string>
#include <exception>

using namespace std;


class NoOrders : public exception {
    virtual const char *what() const throw() {
        return "No orders";
    }
};


class DriverOff : public exception {
    virtual const char *what() const throw() {
        return "Driver is offline or busy";
    }
};

class Order_Busy : public exception {
    virtual const char *what() const throw() {
        return "Order is already taken";
    }
};

class IncorrectInputs : public exception {
    virtual const char *what() const throw() {
        return "Login or password is incorrect";
    }
};

class LoginIsBusy : public exception {
    virtual const char *what() const throw() {
        return "This login is already taken";
    }
};

class FunctionWasBlocked : public exception {
    string driver_name;
    string admin_name;

    virtual const char *what() const throw() {
        string answer = "Sorry, " + driver_name + ", your ability to order/take orders was blocked by " + admin_name;
        const char *c = answer.c_str();
        return c;
    }

public:
    explicit FunctionWasBlocked(string &driver_name, string &admin_name) {
        this->driver_name = driver_name;
        this->admin_name = admin_name;
    }
};

class AlreadyHasOrder : public exception {
    string name;
    virtual const char *what() const throw() {
        string answer = "Sorry, " + name + ", you do already have an order in process";
        return answer.c_str();
    }
public:
    explicit AlreadyHasOrder(string &name){
        this->name = name;
    }
};

#endif
