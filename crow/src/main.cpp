#include "crow_all.h"
using namespace std;

int main(int argc, char ** argv) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello, World!";
    });

    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 18001);
    cout << "CROW RUNNING ON PORT = " << iPort << endl;
    app.port(iPort).multithreaded().run();
}