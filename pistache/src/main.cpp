#include <algorithm>
#include <iostream>
#include "pistache/endpoint.h"
#include "pistache/router.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
using namespace Pistache;
using namespace rapidjson;

class HelloHandler : public Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
         response.send(Http::Code::Ok, "Hello, World");
    }
};

class CPPComparisonServer {
    public:
        CPPComparisonServer(Address addr):
            httpEndpoint(std::make_shared<Http::Endpoint>(addr))
        {}

        void init(size_t thr = 2) {
            auto opts = Http::Endpoint::options()
                .threads(thr)
                .flags(Tcp::Options::InstallSignalHandler);
            httpEndpoint->init(opts);
            setupRoutes();
        }

        void start() {
            httpEndpoint->setHandler(router.handler());
            httpEndpoint->serve();
        }

        void shutdown() {
            httpEndpoint->shutdown();
        }
    private:
        void setupRoutes() {
            using namespace Rest;

            Routes::Get(router, "/", Routes::bind(&CPPComparisonServer::getJSON, this));
        }

        void getJSON(const Rest::Request& request, Http::ResponseWriter response) {
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
            response.send(Http::Code::Ok, s.GetString());
        }

        std::shared_ptr<Http::Endpoint> httpEndpoint;
        Rest::Router router;
};

uint16_t server_port() {
    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? std::stoi(port) : 18004);
    return iPort;
}

int main() {

    Address addr(Ipv4::any(), server_port());

    cout << "Cores = " << hardware_concurrency() << endl;
    auto opts = Http::Endpoint::options().threads(1);

    CPPComparisonServer server(addr);

    server.init();
    server.start();

    server.shutdown();
}