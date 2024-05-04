// HelloWorldStubImpl.hpp
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/examples/HelloWorldStubDefault.hpp>

class HelloWorldStubImpl: public v0_1::commonapi::examples::HelloWorldStubDefault {

public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();

    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);
    virtual void routineResult(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _Identifier, v0_1::commonapi::examples::HelloWorld::RoutineControlType _controlType, uint8_t _responseCode, CommonAPI::ByteBuffer _dataOut, routineResultReply_t _reply);
    virtual void fireEvent(const uint16_t &_Identifier, const ::v0::commonapi::examples::HelloWorld::RoutineControlType &_controlType, const CommonAPI::ByteBuffer &_buffer);
};
#endif /* HELLOWORLDSTUBIMPL_H_ */