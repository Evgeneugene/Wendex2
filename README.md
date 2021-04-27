# [Evgenii Evlampev B20-01] **Programming Software Systems 2**

## Assignment 4 - **WEndex taxi simulation**

WEndex taxi is a program that is supposed to sumilate the real behaviour between a driver and a passenger

> The main goal is to make the simulation as close to the reality as possible and to consider different activities for different people to make it more complex and real.

***

### **Requirements**

C++17   <br>
Sqlite Lite Orm <br>
sqlite3  <br>
cmake  <br>
gcc  <br>

### **How To Run The Program**

Building:
```bash
1) mkdir build
2) cd build
3) cmake ..
4) make
5) ./Evlampev_Wendex
```
***

### **How it works?**

All the data is stored in 4 tables: drivers, passengers, orders, cars.
 In the main function I register some people as passengers and drivers and further show their functional abilities (You can add any if you want). But once you ran the program and registered the users, you should remove/comment code for registering them, otherwise the LoginIsBusy exception will be thrown, because these users already have an account in the base.
 Passengers can login, see their order history, see and update payment methods(Cash, Tinkoff card, or Sberbank card. By default it is Cash), see and update addresses. Addresses for the whole program are implemented as X coordinates in line for simplicity. Also passenger can select any two addresses and type of car(Economy, Comfort, ComfortPlus, Business), check the price for this ride and order it, check current coordinates of Car during the ride and pay the bill after its ending.
 
 A diver can login, update his current status(offline, free/online, busy), update order status(Waiting for the car, waiting for the passenger, driving, arrived, waiting for the payment, ended), see his order history, see his cars, check available orders and pick one. Also he has current coordinates when driving. Multiple cars supported.
  
 A Car has model, carType, the color and the number. If the type is Comfort it has count of freeBottleOfwater (it randomly decreases during rides). If the type is Business it has the method CoolPark. Firstly car should be validated before the usage.
 
 An admin can register, login through his gateway, see all information, block passengers' and drivers' function to make/take order. Inappropriate cases are handled with exceptions. The passenger's activity with use of multiple devices is supported, and he can't make 2 order from 2 devices.
  
