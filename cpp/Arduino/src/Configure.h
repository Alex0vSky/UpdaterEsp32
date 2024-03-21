// src/Configure.h - preparing environment
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#if __has_include( "Private.h" )
#	include "Private.h"
#endif

#ifdef A0S_DEBUG
const char *g_host = "192.168.0.11";
#else // A0S_DEBUG
const char *g_host = "update-server.ru";
#endif // A0S_DEBUG
const char *g_pathVersion = "/sw/version";
const char *g_pathUpdate = "/sw/update";

#if !defined( A0S_SSID ) || !defined( A0S_PASSWORD ) 
#	error "please define ssid and password for work in wifi network"
#endif

// @from esp-idf-v5.2\examples\storage\partition_api\partition_find\main\main.c
static const char *TAGX = "main";

typedef std::chrono::seconds time_resolution_t;
const std::_Placeholder<1> _1 = std::placeholders::_1;
const std::_Placeholder<2> _2 = std::placeholders::_2;
const std::_Placeholder<3> _3 = std::placeholders::_3;
const std::_Placeholder<4> _4 = std::placeholders::_4;
