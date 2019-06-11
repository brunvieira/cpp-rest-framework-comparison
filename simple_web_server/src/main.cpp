#include <iostream>
#include "simple-web-server/server_http.hpp"
#include "cpputils/cpputils.h"
using namespace std;
using namespace rapidjson;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {
    uint16_t iPort = server_port(18003);

    HttpServer server;
    server.config.port = iPort;

    server.resource["^/json/array/(\\d+)$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        string sizeParameter = request->path_match[1].str();
        uint16_t size = strtouint16(sizeParameter, 0);
        response->write(make_json_array(size));
    };

    cout << "Simple Web Server RUNNING ON PORT = " << iPort << endl;
    server.start();

    return 0;
}