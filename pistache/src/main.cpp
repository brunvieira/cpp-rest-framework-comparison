#include <algorithm>
#include <iostream>
#include "pistache/endpoint.h"
#include "pistache/router.h"
#include "cpputils/cpputils.h"
using namespace std;
using namespace Pistache;

class CPPComparisonServer {
    public:
        CPPComparisonServer(Address addr):
            httpEndpoint(std::make_shared<Http::Endpoint>(addr))
        {
            cout << "Pistache listening for requests at " << addr.host() << ":" << addr.port() << endl;
        }

        void init(size_t thr = 1) {
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

            Routes::Get(router, "/json/array/:size", Routes::bind(&CPPComparisonServer::getJSON, this));
        }

        void getJSON(const Rest::Request& request, Http::ResponseWriter response) {
            if (request.hasParam(":size")) {
                uint16_t size = request.param(":size").as<uint16_t>();
                string json = make_json_array(size);
                response.send(Http::Code::Ok, json);
            }
        }

        std::shared_ptr<Http::Endpoint> httpEndpoint;
        Rest::Router router;
};

int main() {
    Address addr(Ipv4::any(), server_port(18004));
    CPPComparisonServer server(addr);

    server.init();
    server.start();

    server.shutdown();
}