// src/Tool/Info/Building.h - mix info tools
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool { namespace Info {
// @insp https://stackoverflow.com/questions/38530981/output-compiler-version-in-a-c-program
//#define A0S_STRINGIZE_expander(x) #x 
//#define A0S_STRINGIZE(x) A0S_STRINGIZE_expander( x )
#define A0S_SEMVER(major, minor, patch) __STRINGIFY( major ) "." __STRINGIFY( minor ) "." __STRINGIFY( patch )

void Building() {
#ifdef __clang__
	ESP_LOGV( TAGX, "clang verion: %s", A0S_SEMVER( __clang_major__, __clang_minor__, __clang_patchlevel__) );
#else
	ESP_LOGV( TAGX, "g++ verion: %s", A0S_SEMVER( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ ) );
#endif
	ESP_LOGV( TAGX, "__cplusplus: %ld", __cplusplus );
	ESP_LOGV( TAGX, "C++ humanReadable: " );
	if (__cplusplus >= 202101L) 		ESP_LOGV( TAGX, "23" );
	else if (__cplusplus >= 202002L)	ESP_LOGV( TAGX, "20" );
	else if (__cplusplus >= 201703L)	ESP_LOGV( TAGX, "17" );
	else if (__cplusplus >= 201402L)	ESP_LOGV( TAGX, "14" );
	else if (__cplusplus >= 201103L)	ESP_LOGV( TAGX, "11" );
	else if (__cplusplus >= 199711L)	ESP_LOGV( TAGX, "98" );
	else ESP_LOGV( TAGX, "pre-standard C++" );
	ESP_LOGV( TAGX, "ESP-IDF: %d.%d", ESP_IDF_VERSION_MAJOR, ESP_IDF_VERSION_MINOR );
  	
	// @insp examples\ChipID\GetChipID\GetChipID.ino
    uint32_t chipId = 0;
	for(int i=0; i<17; i=i+8) {
		chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}
	ESP_LOGV( TAGX, "ESP32 Chip model/Rev: %s/%d", ESP.getChipModel( ), ESP.getChipRevision( ) );
	ESP_LOGV( TAGX, "%d cores", ESP.getChipCores( ) );
    ESP_LOGV( TAGX, "Chip ID: %d", chipId );

#ifdef LOG_LOCAL_LEVEL
    ESP_LOGV( TAGX, "LOG_LOCAL_LEVEL: %d", LOG_LOCAL_LEVEL );
#endif // LOG_LOCAL_LEVEL
#ifdef CORE_DEBUG_LEVEL
    ESP_LOGV( TAGX, "CORE_DEBUG_LEVEL: %d", CORE_DEBUG_LEVEL);
#endif // LOG_LOCAL_LEVEL
#ifdef BOOTLOADER_BUILD
    ESP_LOGV( TAGX, "BOOTLOADER_BUILD: %d", BOOTLOADER_BUILD);
#endif // BOOTLOADER_BUILD
#ifdef CONFIG_LOG_MASTER_LEVEL
    ESP_LOGV( TAGX, "CONFIG_LOG_MASTER_LEVEL: %d", CONFIG_LOG_MASTER_LEVEL);
#endif // CONFIG_LOG_MASTER_LEVEL
#ifdef CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM
    ESP_LOGV( TAGX, "CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM: %d", CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM);
#endif // CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM
#ifdef CONFIG_LOG_TIMESTAMP_SOURCE_RTOS
    ESP_LOGV( TAGX, "CONFIG_LOG_TIMESTAMP_SOURCE_RTOS: %d", CONFIG_LOG_TIMESTAMP_SOURCE_RTOS);
#endif // CONFIG_LOG_TIMESTAMP_SOURCE_RTOS
}
//#undef A0S_STRINGIZE_expander
//#undef A0S_STRINGIZE
#undef A0S_SEMVER
}} // namespace Tool::Info 
