// src/Updater/Updater.h - indeed, support chunked HTTP via HTTPClient
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Updater_ {
class Updater {
	const String m_domain, m_pathBinary, m_builtinVersion;
	OsiDataLink::Wirelesser *m_IOsiDataLink;
	Versioner m_versioner;
	Tool::Timer m_timer;
	HTTPClient m_httpClient;
	WiFiClient m_wiFiClient;

	// Without checking "Content-Type: application/octet-stream". To avoid chunked uncomment `useHTTP10` calling
	bool toKnownContentLength_(size_t *contentLength) {
		const char *collect[] = { "Content-Length" };
		size_t std_size = sizeof( collect ) / sizeof( collect[ 0 ] );
		//m_httpClient.useHTTP10( true );
		m_httpClient.collectHeaders( collect, std_size );
		if ( !m_httpClient.begin( m_wiFiClient, m_domain, 80, m_pathBinary ) ) {
			ESP_LOGE( TAGX, "HTTPClient arduino library error" );
			return false;
		}
		// Has been returned after parse all headers
		int httpCode = m_httpClient.GET( );
		String str_contentLength = m_httpClient.header( collect[ 0 ] );
		*contentLength = str_contentLength.toInt( );
		return true;
	}

public:
	Updater(
		time_resolution_t timeout
		, const char *domain
		, const char *path1
		, const char *path2
		, const char *version_
		, OsiDataLink::Wirelesser *IOsiDataLink
	) : 
		m_domain( domain ), m_pathBinary( path2 ), m_builtinVersion( version_ )
		, m_IOsiDataLink( IOsiDataLink )
		, m_versioner( domain, path1 )
		, m_timer( timeout )
	{}
	~Updater() {
		m_httpClient.end( );
	}
	void loop() {
		if ( !m_IOsiDataLink ->isConnected( ) ) 
			return;

		if ( !m_timer.expired( ) )
			return;

		String remoteVersion;
		if ( !m_versioner.getRemoteVersion( &remoteVersion ) )
			return;

		// compare builtin version with remote version
		auto builtinSemVer = Tool::SemVer::create( m_builtinVersion );
		auto remoteSemVer = Tool::SemVer::create( remoteVersion );
		if ( !builtinSemVer || !remoteSemVer ) {
			ESP_LOGE( TAGX, "Fail SemVer parsing" );
			return;
		}

		if ( *builtinSemVer >= *remoteSemVer ) {
			m_timer.advance( );
			return;
		}

		size_t contentLength = 0;
		if ( !toKnownContentLength_( &contentLength ) )
			return;
		// `WiFiClient::flush` and `WiFiClient::stop` done by `HTTPClient::disconnect` in `HTTPClient::end`
		struct Deleter { 
			HTTPClient &x; Deleter(HTTPClient &y) : x( y ) { } ~Deleter() { x.end( ); }
		} unused_( m_httpClient );

		Tool::Info::Ota::all( );
		// Without `esp_efuse_check_secure_version`
		Update.clearError( );
		if ( !Update.begin( contentLength ) ) {
			ESP_LOGE( TAGX, "Not enough space to begin OTA" );
			return;
		}
		ESP_LOGD( TAGX, "Begin OTA. This may take 2 - 5 mins to complete..." );
		const size_t written = Update.writeStream( m_httpClient.getStream( ) );
		if ( written != contentLength ) {
			ESP_LOGE( TAGX, "Fail writeStream: %d", Update.getError( ) );
			return;
		}
		if ( !Update.end( ) ) {
			ESP_LOGE( TAGX, "Occurred error #:  %d", Update.getError( ) );
			return;
		}
        ESP_LOGI( TAGX, "Update successfully completed. Rebooting..." );
		ESP.restart( );
	}
};
} // namespace Updater_
