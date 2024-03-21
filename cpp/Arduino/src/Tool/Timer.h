// src/Tool/Timer.h - based on esp32 `millis()` function, initial reseted 
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool {
class Timer { 
	typedef std::chrono::milliseconds millis_t;
	const time_resolution_t m_timeout;
	millis_t m_next;

public:
	explicit Timer(time_resolution_t timeout) : 
		m_timeout( timeout )
		, m_next{ millis_t::min( ) }
	{}
	bool expired() const {
		return m_next <= millis_t{ millis( ) };
	}
	void advance() {
		m_next = millis_t{ millis( ) } + m_timeout;
	}
};
} // namespace Tool
