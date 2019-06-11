#include "cpputils.h"
using namespace rapidjson;
using namespace std;

uint16_t server_port(int defaultPort) {
    char * port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL ? std::stoi(port) : defaultPort);
    return iPort;
}

string make_json_array(uint16_t size) {
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

uint16_t strtouint16(const char * value, uint16_t defaultValue) {
    string result{value};
    return strtouint16(result, defaultValue);
}

uint16_t strtouint16(std::string value, uint16_t defaultValue) {
    try {
        std::string::size_type sz;
        int result = stoi(value, &sz, 10);
        return static_cast<uint16_t>(result);
    } catch(...) {};
    return defaultValue;
}

// boohoo