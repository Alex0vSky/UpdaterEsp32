// src/Container.h - collection global accessible objects
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
class Container {
	OsiDataLink::Wirelesser m_wireless;
	Updater_::Updater m_updater;
	Application m_application;

	Container() :
		m_wireless( A0S_SSID, A0S_PASSWORD )
		, m_updater( 
				std::chrono::seconds{ 5 }
				, g_host
				, g_pathVersion
				, g_pathUpdate
				, A0S_BUILT_VERSION 
				, &m_wireless
			)
		, m_application( A0S_BUILT_VERSION, std::chrono::seconds{ 1 }, &m_updater )
	{}
	
public:
	static Container &getInstance() {
		static Container instance;
		return instance;
	}
	Application *getApplication() {
		return &m_application;
	}
	OsiDataLink::Wirelesser *getNetwork() {
		return &m_wireless;
	}

#ifdef A0S_SHOW_LED
private:
	Tool::Led g_led;

public:
	Tool::Led *getLed() {
		return &g_led;
	}
#endif // A0S_SHOW_LED
};
