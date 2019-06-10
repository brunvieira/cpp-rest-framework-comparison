#include "crow_all.h"
using namespace std;

int main(int argc, char ** argv) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/json/array/<int>")
        ([](const crow::request& re, crow::response & res, int size) {
            vector<crow::json::wvalue> items;
            char _id[20];
            for (int i = 0; i < size; ++i) {
                snprintf(_id, size_t(_id), "item-%d", i);
                crow::json::wvalue item;
                item["id"] = static_cast<string>(_id);
                item["name"] = "Hello, world!";
                item["type"] = "application";
                items.emplace_back(std::move(item));
            }
            crow::json::wvalue result;
            result = std::move(items);
            res.write(crow::json::dump(result));
            res.end();
        });

    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 18001);
    cout << "CROW RUNNING ON PORT = " << iPort << endl;
    app.port(iPort).run();
}