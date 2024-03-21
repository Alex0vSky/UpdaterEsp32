// src/Tool/Info/Ota.h - ota info tools
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool { namespace Info { namespace Ota {
// @insp https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/ota.html
void all() {
	typedef const esp_partition_t* partition_t;
	esp_ota_img_states_t ota_state;
	// Not `esp_ota_get_boot_partition`, not affect `esp_ota_set_boot_partition`
	partition_t bootPartition = esp_ota_get_running_partition( );
	if ( bootPartition ) {
		ESP_LOGI( TAGX, "bootPartition.label: %s", bootPartition ->label );
		esp_ota_get_state_partition( bootPartition, &ota_state );
		ESP_LOGI( TAGX, "bootPartition.state: %s", Tool::HumanReadable::Ota::img_state( ota_state ) );
	} else {
		ESP_LOGE( TAGX, "bootPartition failed" );
	}

	// Call this function to find an OTA app partition which can be passed to //esp_ota_begin( );
	partition_t nextPartition = esp_ota_get_next_update_partition( nullptr );
	if ( nextPartition ) {
		ESP_LOGI( TAGX, "nextPartition.label: %s", nextPartition ->label );
		esp_ota_get_state_partition( nextPartition, &ota_state );
		ESP_LOGI( TAGX, "nextPartition.state: %s", Tool::HumanReadable::Ota::img_state( ota_state ) );
	} else {
		ESP_LOGE( TAGX, "nextPartition failed" );
	}

	// Instead `esp_app_get_description`
	const esp_app_desc_t *appDescription = esp_ota_get_app_description( );
	if ( appDescription ) {
		ESP_LOGI( TAGX, "appDescription.version: %s", appDescription ->version );
		ESP_LOGI( TAGX, "appDescription.project_name: %s", appDescription ->project_name );
		ESP_LOGI( TAGX, "appDescription.time: %s", appDescription ->time );
		ESP_LOGI( TAGX, "appDescription.date: %s", appDescription ->date );
		ESP_LOGI( TAGX, "appDescription.idf_ver: %s", appDescription ->idf_ver );
	}
}
}}} // namespace Tool::Info::Memory
