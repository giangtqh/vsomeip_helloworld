# CommonAPI SomeIP example
Refer to: https://github.com/COVESA/capicxx-someip-tools/wiki/CommonAPI-C---SomeIP-in-10-minutes

## Install libraries
```bash
git clone https://github.com/COVESA/vsomeip.git

# gen tool
git clone https://github.com/COVESA/capicxx-core-tools.git
https://github.com/COVESA/capicxx-core-tools/releases/download/3.2.14/commonapi_core_generator.zip
https://github.com/COVESA/capicxx-someip-tools/releases/download/3.2.14/commonapi_someip_generator.zip

# capicxx-core-runtime
git clone https://github.com/COVESA/capicxx-core-runtime.git
cd capicxx-core-runtime
mkdir build
cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
make install

# capicxx-someip-runtime
git clone https://github.com/COVESA/capicxx-someip-runtime.git
cd capicxx-someip-runtime
mkdir build
cmake -D USE_INSTALLED_COMMONAPI=ON -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
```

## Create your example, lets say vsomeip_helloworld
```bash
mkdir vsomeip_helloworld
cd vsomeip_helloworld
mkdir fidl
touch HelloWorld.fidl
```

```fidl
package commonapi.examples

interface HelloWorld {
    version { major 0 minor 1 }

    method sayHello {
        in {
            String name
        }
        out {
            String message
        }
    }
}
```
`fidl/HelloWorld.fdepl`
```fdepl
import "platform:/plugin/org.genivi.commonapi.someip/deployment/CommonAPI-4-SOMEIP_deployment_spec.fdepl"
import "HelloWorld.fidl"

define org.genivi.commonapi.someip.deployment for interface commonapi.examples.HelloWorld {
    SomeIpServiceID = 4660

    method sayHello {
        SomeIpMethodID = 30000
        SomeIpReliable = true

        in {
            name {
                SomeIpStringEncoding = utf16le
            }
        }
    }
}

define org.genivi.commonapi.someip.deployment for provider as Service {
    instance commonapi.examples.HelloWorld {
        InstanceId = "commonapi.examples.HelloWorld"

        SomeIpInstanceID = 4660

        SomeIpUnicastAddress = "192.168.0.2"
        SomeIpReliableUnicastPort = 30499
        SomeIpUnreliableUnicastPort = 30499
    }
}
```
### Gen source from fidl
```bash
# put the generate tool into tools folder
# Extract commonapi_core_generator.zip
./tools/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -d src-gen/core -sk ./fidl/HelloWorld.fidl

# Extract commonapi_someip_generator.zip
./tools/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 -d src-gen/someip ./fidl/HelloWorld.fdepl
```

### Build

```bash
mkdir build && cd build
cmake ..  -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON
make -j8
# create config file
❯ cat commonapi4someip.ini
[default]
binding=someip

[logging]
console = true
file = ./mylog.log
dlt = true
level = verbose
# run the service and open another terminal export and run the client
export LD_LIBRARY_PATH=.:/usr/local/share/capicxx-core-runtime/lib:/usr/local/share/capicxx-someip-runtime/lib:/usr/local/share/vsomeip/lib

❯ COMMONAPI_CONFIG=commonapi4someip.ini ./HelloWorldService
[70905.310091]~DLT~1813050~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...
[CAPI][INFO] Loading configuration file 'commonapi4someip.ini'
[CAPI][INFO] Using default binding 'someip'
[CAPI][INFO] Using default shared library folder '/usr/local/lib/commonapi'
[CAPI][DEBUG] Loading library for local:commonapi.examples.HelloWorld:v0_1:commonapi.examples.HelloWorld stub.
[CAPI][INFO] Loading configuration file /etc//commonapi-someip.ini
[CAPI][DEBUG] Added address mapping: local:commonapi.examples.HelloWorld:v0_1:commonapi.examples.HelloWorld <--> [1234.1234(0.1)]
[CAPI][VERBOSE] Registering function for creating "commonapi.examples.HelloWorld:v0_1" proxy.
[CAPI][INFO] Registering function for creating "commonapi.examples.HelloWorld:v0_1" stub adapter.
[CAPI][DEBUG] Loading interface library "libHelloWorld-someip.so" succeeded.
[CAPI][INFO] Registering stub for "local:commonapi.examples.HelloWorld:v0_1:commonapi.examples.HelloWorld"
2024-05-02 17:14:51.609727 [info] Parsed vsomeip configuration in 0ms
2024-05-02 17:14:51.610636 [info] Configuration module loaded.
2024-05-02 17:14:51.610770 [info] Security disabled!
2024-05-02 17:14:51.610876 [info] Initializing vsomeip (3.4.10) application "service-sample".
2024-05-02 17:14:51.612036 [info] Instantiating routing manager [Host].
2024-05-02 17:14:51.614128 [info] create_routing_root: Routing root @ /tmp/vsomeip-0
2024-05-02 17:14:51.615723 [info] Service Discovery enabled. Trying to load module.
2024-05-02 17:14:51.640305 [info] Service Discovery module loaded.
2024-05-02 17:14:51.641285 [info] vsomeip tracing not enabled. . vsomeip service discovery tracing not enabled.
2024-05-02 17:14:51.641430 [info] Application(service-sample, 1000) is initialized (11, 100).
2024-05-02 17:14:51.648939 [info] Starting vsomeip application "service-sample" (1000) using 2 threads I/O nice 255
2024-05-02 17:14:51.651002 [info] Client [1000] routes unicast:127.0.0.1, netmask:255.255.255.0
2024-05-02 17:14:51.651735 [info] shutdown thread id from application: 1000 (service-sample) is: 7f3a0579a640 TID: 1813057
2024-05-02 17:14:51.651219 [info] main dispatch thread id from application: 1000 (service-sample) is: 7f3a05f9b640 TID: 1813056
2024-05-02 17:14:51.654431 [info] Watchdog is disabled!
2024-05-02 17:14:51.655008 [info] create_local_server: Listening @ /tmp/vsomeip-1000
2024-05-02 17:14:51.655175 [info] io thread id from application: 1000 (service-sample) is: 7f3a0679c640 TID: 1813055
2024-05-02 17:14:51.655685 [info] OFFER(1000): [1234.1234:0.1] (true)
Successfully Registered Service!
Waiting for calls... (Abort with CTRL+C)
2024-05-02 17:14:51.656212 [info] io thread id from application: 1000 (service-sample) is: 7f39f7fff640 TID: 1813059
2024-05-02 17:14:51.657409 [info] vSomeIP 3.4.10 | (default)
2024-05-02 17:14:51.657945 [info] Network interface "lo" state changed: up
2024-05-02 17:15:01.658904 [info] vSomeIP 3.4.10 | (default)
2024-05-02 17:15:11.660094 [info] vSomeIP 3.4.10 | (default)
2024-05-02 17:15:21.661504 [info] vSomeIP 3.4.10 | (default)
2024-05-02 17:15:30.398274 [info] Application/Client 1001 is registering.
2024-05-02 17:15:30.399901 [info] Client [1000] is connecting to [1001] at /tmp/vsomeip-1001
2024-05-02 17:15:30.402300 [info] REGISTERED_ACK(1001)
2024-05-02 17:15:30.597360 [info] REQUEST(1001): [1234.1234:0.4294967295]
sayHello('World'): 'Hello World!'
sayHello('World'): 'Hello World!'
2024-05-02 17:15:31.662664 [info] vSomeIP 3.4.10 | (default)
sayHello('World'): 'Hello World!'
sayHello('World'): 'Hello World!'
sayHello('World'): 'Hello World!'
sayHello('World'): 'Hello World!'
2024-05-02 17:15:35.521755 [info] Application/Client 1001 is deregistering.
2024-05-02 17:15:35.625629 [info] Client [1000] is closing connection to [1001]
2024-05-02 17:15:35.626252 [info] local_uds_client_endpoint_impl::receive_cbk Error: Operation canceled
^C2024-05-02 17:15:36.791331 [info] Stopping vsomeip application "service-sample" (1000).
2024-05-02 17:15:36.800556 [info] Exiting vsomeip application...
[70960.674348]~DLT~1813050~WARNING  ~Lost log messages in user buffer when exiting: 10
[70960.675244]~DLT~1813050~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...
```