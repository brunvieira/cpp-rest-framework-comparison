#include "cpputils.h"
using namespace rapidjson;

uint16_t server_port(int defaultPort) {
    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? std::stoi(port) : defaultPort);
    return iPort;
}

std::string make_json_array(int size) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    char _id[20];
    writer.StartArray();
    for (int i = 0; i < size; ++i) {
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
    return buffer.GetString();
};
