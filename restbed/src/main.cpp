#include <iostream>
#include <memory>
#include <cstdlib>
#include <restbed>
#include "cpputils.h"

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        string json = make_json_array(10000);
        session->close( OK, json, { { "Content-Length", to_string(json.length()) } } );
    } );
}

int main( const int, const char** )
{
    uint16_t port = server_port(18005);
    auto resource = make_shared< Resource >( );
    resource->set_path( "/" );
    resource->set_method_handler("GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port(port);
    settings->set_default_header("Connection", "close");

    cout << "Restbed Listening on port: " << port << endl;
    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}