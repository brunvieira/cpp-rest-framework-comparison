#include <iostream>
#include "handler.h"
#include "user_interrupt_handler.h"
using namespace utility;

std::unique_ptr<Handler> g_httpHandler;

string_t make_address() {
    char * envPort = getenv("PORT");
    string_t port = U(envPort ? envPort : "18002");
    string_t address = U("http://0.0.0.0:");
    address.append(port);
    return address;
}

void on_initialize(string_t address)
{
    uri_builder uri(address);


    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<Handler>(new Handler(addr));
    g_httpHandler->open().wait();
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
    return ;
}

void on_shutdown()
{
    cout << "Shuting it down" << endl;
    g_httpHandler->close().wait();
    return;
}

int main(int argc, char *argv[]) {
    string_t address = make_address();
    try {
        cfx::InterruptHandler::hookSIGINT();
        on_initialize(address);
        cfx::InterruptHandler::waitForUserInterrupt();
        on_shutdown();
    }
    catch(std::exception & e) {
        std::cerr << "something wrong happen! :(" << '\n';
    }
    return 0;
}