#ifndef __CPPUTILS_H__
#define __CPPUTILS_H__

#include <string>
#include <stdint.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

uint16_t server_port(int defaultPort);
std::string make_json_array(int size);

#endif