// src/Application.h - indeed, mnemonic from PySerial 
// @insp https://pyserial.readthedocs.io/en/latest/pyserial_api.html
// @insp https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/uart.html
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
class Application {
	const String m_version;
	Tool::Timer m_timer;
	// Composition
	Updater_::Updater *m_updater;
	// @from Arduino15\packages\esp32\hardware\esp32\2.0.11\cores\esp32\esp32-hal-uart.c
	uint32_t get_effective_baudrate_(uint32_t baudrate) {
		uint32_t Freq = getApbFrequency( ) / 1000000;
		if ( Freq < 80 ) 
			return 80 / Freq * baudrate;
		else 
			return baudrate;
	}

public:
	Application(Application&) = delete; 
	Application& operator=(Application const&) = delete; 
	Application(const char *version, std::chrono::seconds knock, Updater_::Updater *updater) : 
		m_version( version )
		, m_timer( knock )
		, m_updater( updater )
	{}
	enum class Bytesize {
		FIVEBITS, SIXBITS, SEVENBITS, EIGHTBITS };
	enum class Parity {
		PARITY_NONE, PARITY_EVEN, PARITY_ODD, PARITY_MARK, PARITY_SPACE };
	enum class Stopbits {
		STOPBITS_ONE, STOPBITS_ONE_POINT_FIVE, STOPBITS_TWO };
	enum class Rtscts {
		True, False };
	enum class Dsrdtr {
		True, False };
	void begin(
		uint32_t baudrate
		, Bytesize bytesize
		, Parity parity
		, Stopbits stopbits
		, Rtscts rtscts
		, Dsrdtr dsrdtr
	)
	{
		Serial.begin( baudrate );

		// @from Arduino15\packages\esp32\hardware\esp32\2.0.11\cores\esp32\HardwareSerial.cpp
		const uart_port_t uart_num = 0;

		uart_config_t uart_config = { };
		// @from Arduino15\packages\esp32\hardware\esp32\2.0.11\cores\esp32\HardwareSerial.h#begin()
		uart_config.rx_flow_ctrl_thresh = 112;
		// @from Arduino15\packages\esp32\hardware\esp32\2.0.11\cores\esp32\esp32-hal-uart.c#uartBegin
#if SOC_UART_SUPPORT_XTAL_CLK
		uart_config.source_clk = UART_SCLK_XTAL; // ESP32C3, ESP32S3
	    uart_config.baud_rate = baudrate;
#else
		uart_config.source_clk = UART_SCLK_APB;  // ESP32, ESP32S2
	    uart_config.baud_rate = get_effective_baudrate_( baudrate );
#endif

		// Map from python mnemonic to Espressif mnemonic
		{
		if ( false ) (void)0;
		else if ( Bytesize::EIGHTBITS == bytesize )
			uart_config.data_bits = UART_DATA_8_BITS;
		else if ( Bytesize::FIVEBITS == bytesize )
			uart_config.data_bits = UART_DATA_5_BITS;
		else if ( Bytesize::SEVENBITS == bytesize )
			uart_config.data_bits = UART_DATA_7_BITS;
		else if ( Bytesize::SIXBITS == bytesize )
			uart_config.data_bits = UART_DATA_6_BITS;
		}

		{
		if ( false ) (void)0;
		else if ( Parity::PARITY_NONE == parity )
			uart_config.parity = UART_PARITY_DISABLE;
		else if ( Parity::PARITY_EVEN == parity )
			uart_config.parity = UART_PARITY_EVEN;
		else if ( Parity::PARITY_ODD == parity )
			uart_config.parity = UART_PARITY_ODD;
		}

		{
		if ( false ) (void)0;
		else if ( Stopbits::STOPBITS_ONE == stopbits )
			uart_config.stop_bits = UART_STOP_BITS_1;
		else if ( Stopbits::STOPBITS_ONE_POINT_FIVE == stopbits )
			uart_config.stop_bits = UART_STOP_BITS_1_5;
		else if ( Stopbits::STOPBITS_TWO == stopbits )
			uart_config.stop_bits = UART_STOP_BITS_2;
		}

		// TODO(alex): allow enable "software flow control"
		bool enable_sw_flowctrl = false;
		uint8_t rx_thresh_xon, rx_thresh_xoff;
		rx_thresh_xon = rx_thresh_xoff = 0;
		ESP_ERROR_CHECK( uart_set_sw_flow_ctrl( uart_num, enable_sw_flowctrl, rx_thresh_xon, rx_thresh_xoff ) );

		// Hardware (RTS/CTS) flow control.
		uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
		if ( Rtscts::True == rtscts ) 
			uart_config.flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS;

		// Hardware (DSR/DTR) flow control @from https://esp32.com/viewtopic.php?t=17550
		const int low = 1;
		const int high = 0;
		if ( Dsrdtr::True == dsrdtr ) 
			ESP_ERROR_CHECK( uart_set_dtr( uart_num, high ) );
		else
			ESP_ERROR_CHECK( uart_set_dtr( uart_num, low ) );

		ESP_ERROR_CHECK( uart_param_config( uart_num, &uart_config ) );
		ESP_LOGD( TAGX, "Start Application" );
	}

	void loop() {
		m_updater ->loop( );

		if ( !m_timer.expired( ) )
			return;
		Serial.println( m_version );
		m_timer.advance( );
	}
};
