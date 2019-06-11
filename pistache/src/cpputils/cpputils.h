#ifndef __CPPUTILS_H__
#define __CPPUTILS_H__

#include <string>
#include <stdint.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace std;

uint16_t server_port(int defaultPort);
string make_json_array(uint16_t size);
uint16_t strtouint16(const char * value, uint16_t defaultValue);
uint16_t strtouint16(string value, uint16_t defaultValue);

#endif