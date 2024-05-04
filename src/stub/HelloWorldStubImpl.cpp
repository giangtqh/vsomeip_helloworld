// HelloWorldStubImpl.cpp
#include "HelloWorldStubImpl.hpp"

#include "Utils.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() {
}

HelloWorldStubImpl::~HelloWorldStubImpl() {
}

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) {

    std::stringstream messageStream;

    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};

void HelloWorldStubImpl::routineResult(const std::shared_ptr<CommonAPI::ClientId> _client,
                                       uint16_t _Identifier,
                                       v0_1::commonapi::examples::HelloWorld::RoutineControlType _controlType,
                                       uint8_t _responseCode,
                                       CommonAPI::ByteBuffer _dataOut,
                                       routineResultReply_t _reply)
{
    std::cout << "--> routineResult(" << toHexString(_Identifier) << ", " << routineControlToString(_controlType) << ", " << toHexString(_responseCode) << ", {" << toHexString(_dataOut) << "})" << std::endl;
    _reply();
}

void HelloWorldStubImpl::fireEvent(const uint16_t &_Identifier,
                                   const ::v0::commonapi::examples::HelloWorld::RoutineControlType &_controlType,
                                   const CommonAPI::ByteBuffer &_buffer) {
    std::cout << "<-- fireEvent(" << toHexString(_Identifier) << ", " << routineControlToString(_controlType) << ", {" << toHexString(_buffer) << "})" << std::endl;
    fireOnRoutineControlEvent(_Identifier, _controlType, _buffer);
}