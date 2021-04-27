add_executable(Evlampev_Wendex main.cpp PassengerGateway.cpp PassengerGateway.h DriverGateway.cpp DriverGateway.h DataBase.h My_Exceptions.h AdminGateway.cpp AdminGateway.h)
target_link_libraries(Evlampev_Wendex PRIVATE sqlite_orm::sqlite_orm)
