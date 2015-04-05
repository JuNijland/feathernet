# feathernet
A lightweight minimalistic C library for networking. This library is meant for learning networking for myself as well
as providing a fast way to implement networking in your C program.

## Support
Feathernet currently runs on Linux and Windows

## Usage
To use the feathernet library, you first need to pull it from github like so:

`git clone https://github.com/JuNijland/feathernet.git`

Now you can compile the library with make:

`cd feathernet && make build`

This will put the library file `feathernet.a` in the build folder

You can now include `feathernet.h` (located in the headers folder) in your file and use the library.
You do however need to add feathernet.a at the end of your compile command.
The command I used to compile the tests will then look like this:

`gcc -ansi -o build/http_client examples/http_client.c build/feathernet.a`

## Examples
The examples in the `examples` folder can also be compiled with make, but make sure you build the library file first!

`make http_client && make echo_server && make echo_client`

The executables will be placed in the build folder. If you wish you can also compile them without make with the
command shown above.

#### http_client.c
To use this program, simply run it with as a parameter the website you want to pull the html page from.

#### echoclient.c & echoserver.c
To use these programs, first run the echoserver with as a parameter the port (range 0-65535) you want the server to listen on.
When the server is running, you can start the echoclient in a different terminal with as parameter first the 
ip-address where the server is located (probably 127.0.0.1) and the port number you set the server
to listen on.

## Debugging
The library will print all the error messages to stdout if you wish so. Just put `#define FEATHER_DEBUG` at
the top of your file.
