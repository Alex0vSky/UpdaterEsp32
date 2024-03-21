// src/OsiDataLink/Wirelesser.h - connect to wi-fi network
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace OsiDataLink { 
class Wirelesser {
	bool m_bConnected;
	const String m_ssid, m_password;
	void disconnected_(WiFiEvent_t event, WiFiEventInfo_t info) {
		ESP_LOGW( TAGX, "Disconnected from the Wi-Fi AP" );
		m_bConnected = false;
	}
	void gotIp_(WiFiEvent_t event, WiFiEventInfo_t info) {
		IPAddress addr( info.got_ip.ip_info.ip.addr );
		ESP_LOGI( TAGX, "Local IP: %s", addr.toString( ).c_str( ) );
		m_bConnected = true;
	}

public:
	Wirelesser(const char *ssid, const char *password) :
		m_bConnected( false )
		, m_ssid( ssid ), m_password( password )
	{}
	~Wirelesser() {
		WiFi.disconnect( true );
	}
	void begin() {
		ESP_LOGD( TAGX, "Start Wirelesser" );
		// delete old config @insp https://randomnerdtutorials.com/solved-reconnect-esp32-to-wifi/
		WiFi.disconnect( true );
		WiFi.mode( WIFI_STA );
		WiFi.onEvent( 
				std::bind( &Wirelesser::disconnected_, this, _1, _2 )
				, ARDUINO_EVENT_WIFI_STA_DISCONNECTED
			);
		// IPv4 only
		WiFi.onEvent( 
				std::bind( &Wirelesser::gotIp_, this, _1, _2 )
				, ARDUINO_EVENT_WIFI_STA_GOT_IP
			);
		WiFi.setAutoReconnect( true );
		WiFi.begin( m_ssid, m_password );
	}
	bool isConnected() const {
		return m_bConnected;
	}
};
} // namespace OsiDataLink
