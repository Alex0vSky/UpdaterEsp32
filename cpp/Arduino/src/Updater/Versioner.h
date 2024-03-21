// src/Updater/Versioner.h - get version info from HTTP server on hardcoded port 80
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Updater_ {
class Versioner {
	const String m_domain, m_path;
	AsyncClient m_async;
	String m_GET, m_currentGET, m_response;
	bool m_connectionRun, m_disconnectAfterConnection;

	void init_() {
		m_connectionRun = m_disconnectAfterConnection = false;
		m_currentGET = m_GET;
		m_response.clear( );
	}
	void onConnect_(void*, AsyncClient*) {
		m_connectionRun = true;
	}
	void onDisconnected_(void*, AsyncClient*) {
		if ( m_connectionRun )
			m_disconnectAfterConnection = true;
		m_connectionRun = false;
	}
	// Collect full response to memory!
	void onHandleData_(void*, AsyncClient*client, void *data, size_t len) {
		auto chars = reinterpret_cast< char *>( data );
		m_response += String( chars, len );
	}

public:
	~Versioner() {
		m_async.abort( ), m_async.close( );
	}
	Versioner(const char *domain, const char *path) : 
		m_domain( domain ), m_path( path )
	{
		m_async.onConnect( 
				std::bind( &Versioner::onConnect_, this, _1, _2 )
			);
		m_async.onDisconnect( 
				std::bind( &Versioner::onDisconnected_, this, _1, _2 )
			);
		m_async.onData( 
				std::bind( &Versioner::onHandleData_, this, _1, _2, _3, _4 )
			);
		// To avoid chunked use: m_GET += " HTTP/1.0\r\nHost: ";
		m_GET += "GET ";
		m_GET += m_path;
		m_GET += " HTTP/1.1\r\nHost: ";
		m_GET += m_domain;
		m_GET += "\r\nConnection: close\r\n\r\n";
		init_( );
	}

	bool getRemoteVersion(String *remoteVersion) {
		// Is `m_async.connected( )` not usable
		if ( !m_connectionRun && !m_disconnectAfterConnection ) {
			m_async.connect( m_domain.c_str( ), 80 );
			m_connectionRun = true;
		}

		// Send
		if ( m_currentGET.length( ) ) {
			if ( !m_async.canSend( ) )
				return false;
			size_t sendLength = std::min( m_async.space( ), m_currentGET.length( ) );
			m_async.write( &m_currentGET[ 0 ], sendLength );
			m_currentGET.remove( 0, sendLength );
			if ( m_currentGET.length( ) )
				return false;
		}
		
		// Reaction on closed connection by server
		if ( !m_disconnectAfterConnection )
			return false;

		// Parse Http
		String body;
		const String delimeter = "\r\n";
		const String signatureContentLength = "Content-Length: ";
		const String signatureEnd = "\r\n\r\n";
		do { 
			int posContentLength = m_response.indexOf( signatureContentLength );
			if ( -1 == posContentLength ) 
				break;
			posContentLength += signatureContentLength.length( );
			int endContentLength = m_response.indexOf( delimeter, posContentLength );
			if ( -1 == endContentLength ) 
				break;
			String value = m_response.substring( posContentLength, endContentLength );
			const int contentLength = value.toInt( );
			endContentLength += delimeter.length( );
			int endHeaders = m_response.indexOf( signatureEnd, endContentLength );
			if ( -1 == endHeaders ) 
				break;
			endHeaders += signatureEnd.length( );
			const int bodyLength = ( m_response.length( ) - endHeaders );
			if ( contentLength != bodyLength ) 
				break;
			body = m_response.substring( endHeaders, endHeaders + contentLength );
			ESP_LOGD( TAGX, "body: '%s'", body.c_str( ) );
		} while( false );

		// To avoid web-server ddos
		struct Stopper { 
			AsyncClient &x; Stopper(AsyncClient &y) : x( y ) { } ~Stopper() { x.stop( ); }
		} unused_( m_async );

		// Reinit
		init_( );
		if ( !body.length( ) ) {
			ESP_LOGE( TAGX, "fail parse response" );
			return false;
		}

		// Parse Json
		JsonDocument doc;
		DeserializationError error = deserializeJson( doc, body );
		if ( error ) {
			ESP_LOGE( TAGX, "deserializeJson() failed: ", error.c_str( ) );
			return false;
		}
		*remoteVersion = doc[ "ver" ].as< String >( );
		return true;
	}
};
} // namespace Updater_
