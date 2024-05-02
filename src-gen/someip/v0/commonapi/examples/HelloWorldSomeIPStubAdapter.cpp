/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.14.v202310241606.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#include <v0/commonapi/examples/HelloWorldSomeIPStubAdapter.hpp>
#include <v0/commonapi/examples/HelloWorld.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v0 {
namespace commonapi {
namespace examples {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createHelloWorldSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< HelloWorldSomeIPStubAdapter<::v0::commonapi::examples::HelloWorldStub>>(_address, _connection, _stub);
}

void initializeHelloWorldSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:commonapi.examples.HelloWorld:v0_1:commonapi.examples.HelloWorld",
         0x1234, 0x1234, 0, 1);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        "commonapi.examples.HelloWorld:v0_1",
        &createHelloWorldSomeIPStubAdapter);
}

INITIALIZER(registerHelloWorldSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeHelloWorldSomeIPStubAdapter);
}

} // namespace examples
} // namespace commonapi
} // namespace v0
