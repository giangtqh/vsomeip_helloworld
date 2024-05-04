// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <thread>
#ifndef _WIN32
#include <unistd.h>
#endif

#include "Utils.hpp"
#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/examples/HelloWorldProxy.hpp>

using namespace v0::commonapi::examples;

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "E01C");
    CommonAPI::Runtime::setProperty("LogApplication", "E01C");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.HelloWorld";
    std::string connection = "client-sample";

    std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>(domain,
            instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;

    const std::string name = "World";
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    myProxy->getOnRoutineControlEvent().subscribe([&](const uint16_t& did, const ::v0::commonapi::examples::HelloWorld::RoutineControlType& type, const CommonAPI::ByteBuffer& data) {
        std::cout << "--> Received onRoutineControlEvent(" << toHexString(did) << ", " << routineControlToString(type) << ", {" << toHexString(data) << "})" << std::endl;
        CommonAPI::CallStatus status;
        std::cout << "<-- Report result" << std::endl;
        myProxy->routineResult(did, type, 0x22, {data[0]*2}, status, nullptr);
        std::cout << "--> routineResult status: " << (status == CommonAPI::CallStatus::SUCCESS ? "SUCCESS" : "FAILED") << std::endl;
    });
    while (true)
    {
        // myProxy->sayHello(name, callStatus, returnMessage, &info);
        // if (callStatus != CommonAPI::CallStatus::SUCCESS) {
        //     std::cerr << "Remote call failed!\n";
        //     return -1;
        // }
        // info.timeout_ = info.timeout_ + 1000;

        // std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}