/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.14.v202310241606.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#ifndef V0_COMMONAPI_EXAMPLES_HELLO_WORLD_SOMEIP_PROXY_HPP_
#define V0_COMMONAPI_EXAMPLES_HELLO_WORLD_SOMEIP_PROXY_HPP_

#include <v0/commonapi/examples/HelloWorldProxyBase.hpp>
#include <v0/commonapi/examples/HelloWorldSomeIPDeployment.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Proxy.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Event.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <string>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v0 {
namespace commonapi {
namespace examples {

class HelloWorldSomeIPProxy
    : virtual public HelloWorldProxyBase,
      virtual public CommonAPI::SomeIP::Proxy {
public:
    HelloWorldSomeIPProxy(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection);

    virtual ~HelloWorldSomeIPProxy();

    virtual OnRoutineControlEvent& getOnRoutineControlEvent();

    virtual void sayHello(std::string _name, CommonAPI::CallStatus &_internalCallStatus, std::string &_message, const CommonAPI::CallInfo *_info);

    virtual std::future<CommonAPI::CallStatus> sayHelloAsync(const std::string &_name, SayHelloAsyncCallback _callback, const CommonAPI::CallInfo *_info);

    virtual void routineResult(uint16_t _Identifier, HelloWorld::RoutineControlType _controlType, uint8_t _responseCode, CommonAPI::ByteBuffer _dataOut, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info);

    virtual std::future<CommonAPI::CallStatus> routineResultAsync(const uint16_t &_Identifier, const HelloWorld::RoutineControlType &_controlType, const uint8_t &_responseCode, const CommonAPI::ByteBuffer &_dataOut, RoutineResultAsyncCallback _callback, const CommonAPI::CallInfo *_info);

    virtual void getOwnVersion(uint16_t &_major, uint16_t &_minor) const;

    virtual std::future<void> getCompletionFuture();

private:
    CommonAPI::SomeIP::Event<OnRoutineControlEvent, CommonAPI::Deployable< uint16_t, CommonAPI::SomeIP::IntegerDeployment<uint16_t> >, CommonAPI::Deployable< ::v0::commonapi::examples::HelloWorld::RoutineControlType, ::v0::commonapi::examples::HelloWorld_::RoutineControlTypeDeployment_t >, CommonAPI::Deployable< CommonAPI::ByteBuffer, CommonAPI::SomeIP::ByteBufferDeployment >> onRoutineControl_;

};

} // namespace examples
} // namespace commonapi
} // namespace v0

#endif // V0_COMMONAPI_EXAMPLES_Hello_World_SOMEIP_PROXY_HPP_
