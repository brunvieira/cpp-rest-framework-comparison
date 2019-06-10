#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <sys/time.h>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/json.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"

#include "route.h"

#include <locale>
#include <ctime>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace route;

class Handler
{
    public:
        Handler();
        Handler(utility::string_t url);
        virtual ~Handler();

        pplx::task<void>open(){return m_listener.open();}
        pplx::task<void>close(){return m_listener.close();}

    protected:

    private:
        void handle_get(http_request message);
        void json_array(http_request message, int size);
        void handle_error(pplx::task<void>& t);
        http_listener m_listener;
        Route route;
};

#endif // HANDLER_H
