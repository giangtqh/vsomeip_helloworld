// HelloWorldService.cpp
#include <iostream>
#include <thread>

#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"

using namespace std;

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "E01S");
    CommonAPI::Runtime::setProperty("LogApplication", "E01S");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.HelloWorld";
    std::string connection = "service-sample";

    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService, connection);

    while (!successfullyRegistered) {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService, connection);
    }

    std::cout << "Successfully Registered Service!" << std::endl;
    int count{0};
    while (true) {
        ++count;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        myService->fireEvent(count, ::v0::commonapi::examples::HelloWorld::RoutineControlType::START, {0x11*count});
    }

    return 0;
}