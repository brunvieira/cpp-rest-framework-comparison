#include <iostream>
#include "simple-web-server/server_http.hpp"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
using namespace rapidjson;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

uint16_t server_port() {
    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 18003);
    return iPort;
}

int main() {
    uint16_t iPort = server_port();

    HttpServer server;
    server.config.port = iPort;

    server.resource["^/$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        StringBuffer s;
        Writer<StringBuffer> writer(s);
        char _id[20];
        writer.StartArray();
        for (int i = 0; i < 1000; ++i) {
            snprintf(_id, size_t(_id), "item-%d", i);
            writer.StartObject();
            writer.Key("id");
            writer.String(_id);
            writer.Key("name");
            writer.String("Hello, world!");
            writer.Key("type");
            writer.String("application");
            writer.EndObject();
        }
        writer.EndArray();
        response->write(s.GetString());
    };

    cout << "Simple Web Server RUNNING ON PORT = " << iPort << endl;
    server.start();

    return 0;
}