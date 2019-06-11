#include <iostream>
#include <memory>
#include <cstdlib>
#include <restbed>
#include "cpputils.h"

using namespace std;
using namespace restbed;

void get_method_handler(const shared_ptr<Session> session)
{
    const auto& request = session->get_request();
    const string sizeParameter = request->get_path_parameter("size");
    int size = 0;
    try {
        size = stoi(sizeParameter);
    } catch (...) {
        session->close(restbed::BAD_REQUEST);
    }
    if (!size) {
        return;
    }
    string json = make_json_array(size);
    std::multimap<std::string, std::string> headers = {
        {"Content-Length", to_string(json.length())},
        {"Content-Type", "application/json"}
    };
    session->close(OK, json, headers);
}

int main( const int, const char** )
{
    uint16_t port = server_port(18005);
    auto resource = make_shared<Resource>();
    resource->set_path("/json/array/{size: \\d*}");
    resource->set_method_handler("GET", get_method_handler);

    auto settings = make_shared< Settings >();
    settings->set_port(port);
    settings->set_default_header("Connection", "close");

    cout << "Restbed Listening on port: " << port << endl;
    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}