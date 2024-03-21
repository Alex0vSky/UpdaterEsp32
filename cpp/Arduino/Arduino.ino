#include <WiFi.h>
#include <Update.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <driver/uart.h>
#include <lwip/dns.h>
#include <esp_ota_ops.h>
#include <chrono>

#include "src/Configure.h"
#include "src/Tool/HumanReadable.h"
#include "src/Tool/Info/Partition.h"
#include "src/Tool/Info/Building.h"
#include "src/Tool/Info/Memory.h"
#include "src/Tool/Info/Ota.h"
#include "src/Tool/Led.h"
#include "src/Tool/Timer.h"
#include "src/Tool/SemVer.h"
#include "src/OsiDataLink/Wirelesser.h"
#include "src/Updater/Versioner.h"
#include "src/Updater/Updater.h"
#include "src/Application.h"
#include "src/Container.h"

void setup(void) {
#ifdef A0S_DEBUG
	esp_log_level_set( TAGX, ESP_LOG_VERBOSE );
#endif // A0S_DEBUG
	Container::getInstance( ).getApplication( ) ->begin( 
			115200
			, Application::Bytesize::EIGHTBITS
			, Application::Parity::PARITY_NONE
			, Application::Stopbits::STOPBITS_ONE
			, Application::Rtscts::False
			, Application::Dsrdtr::False
		);
	Container::getInstance( ).getNetwork( ) ->begin( );
}

void loop(void) {
	Container::getInstance( ).getApplication( ) ->loop( );
#ifdef A0S_SHOW_LED
	Container::getInstance( ).getLed( ) ->turn( Container::getInstance( ).getNetwork( ) ->isConnected( ) );
#endif // A0S_SHOW_LED
}
