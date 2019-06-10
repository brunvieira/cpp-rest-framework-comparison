#include "handler.h"

Handler::Handler(){}

Handler::Handler(utility::string_t url):
    m_listener(url),
    route{}
{
    m_listener.support(methods::GET, std::bind(&Handler::handle_get, this, std::placeholders::_1));
}

Handler::~Handler(){}

void Handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(exception e)
    {
        cout << "Error: " << e.what() << endl;
        // Ignore the error, Log it if a logger is available
    }
}

void Handler::handle_get(http_request message)
{
    ucout <<  message.to_string() << endl;

    Match match = route.set(message.relative_uri().path());
    if (match.test("/json/array/:size")) {
        string sizeStr = match.get("size");
        try {
            int size = stoi(sizeStr);
            if (size) {
                return this->json_array(message, size);
            }
        } catch(...) {
            message.reply(status_codes::InternalError);
        }

    }

    return;

};

void Handler::json_array(http_request message, int size) {
    vector<json::value> values;
    values.reserve(size);

    vector<pair<utility::string_t, json::value>> fields;
    fields.reserve(3);

    char _id[20];

    for (int i = 0; i < size; ++i) {
        snprintf(_id, sizeof(_id), "item-%d", i);
        fields.push_back(make_pair("id", json::value::string(_id)));
        fields.push_back(make_pair("name", json::value::string("Hello World")));
        fields.push_back(make_pair("type", json::value::string("application")));

        values.push_back(json::value::object(fields));
        fields.clear();
    }

    http_response response(status_codes::OK);
    response.headers().add("Connection", "keep-alive");
    response.set_body(json::value::array(values));

    message.reply(response);
}