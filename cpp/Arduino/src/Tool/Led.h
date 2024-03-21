// src/Tool/Led.h - just led working
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool {
class Led {
	// @insp examples\ResetReason\ResetReason.ino
#if CONFIG_IDF_TARGET_ESP32
	static const unsigned c_LedBuiltin = 2;
#elif CONFIG_IDF_TARGET_ESP32C3
	static const unsigned c_LedBuiltin = 8;
#else
#	error "unknown led pin"
#endif
public:
	Led() {
		pinMode( c_LedBuiltin, OUTPUT );
	}
	// Turn the LED on (HIGH is the voltage level)
	void turnOn() const {
		digitalWrite( c_LedBuiltin, HIGH );
	}
	// Turn the LED off by making the voltage LOW
	void turnOff() const {
		digitalWrite( c_LedBuiltin, LOW );
	}
	void turn(bool on) const {
		on ?turnOn( ) :turnOff();
	}
};
} // namespace Tool
