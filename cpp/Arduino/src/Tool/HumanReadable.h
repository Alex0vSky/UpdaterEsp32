// src/Tool/HumanReadable.h - human readable values
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool { namespace HumanReadable { 
typedef const char * return_t;
struct Partition {
	static return_t type(esp_partition_type_t type) {
		switch ( type ) {
			case ESP_PARTITION_TYPE_APP:
				return "ESP_PARTITION_TYPE_APP";
			case ESP_PARTITION_TYPE_DATA:
				return "ESP_PARTITION_TYPE_DATA";
			default:
				return "UNKNOWN_PARTITION_TYPE"; // type not used in this example
		}
	}
	static return_t subtype(esp_partition_subtype_t subtype) {
		switch ( subtype ) {
			case ESP_PARTITION_SUBTYPE_DATA_NVS:
				return "ESP_PARTITION_SUBTYPE_DATA_NVS";
			case ESP_PARTITION_SUBTYPE_DATA_PHY:
				return "ESP_PARTITION_SUBTYPE_DATA_PHY";
			case ESP_PARTITION_SUBTYPE_APP_FACTORY:
				return "ESP_PARTITION_SUBTYPE_APP_FACTORY";
			case ESP_PARTITION_SUBTYPE_DATA_FAT:
				return "ESP_PARTITION_SUBTYPE_DATA_FAT";
			default:
				return "UNKNOWN_PARTITION_SUBTYPE"; // subtype not used in this example
		}
	}
};
struct Wi_Fi {
	static return_t status(int status){
		switch( status ){
			case WL_IDLE_STATUS:
				return "WL_IDLE_STATUS";
			case WL_SCAN_COMPLETED:
				return "WL_SCAN_COMPLETED";
			case WL_NO_SSID_AVAIL:
				return "WL_NO_SSID_AVAIL";
			case WL_CONNECT_FAILED:
				return "WL_CONNECT_FAILED";
			case WL_CONNECTION_LOST:
				return "WL_CONNECTION_LOST";
			case WL_CONNECTED:
				return "WL_CONNECTED";
			case WL_DISCONNECTED:
				return "WL_DISCONNECTED";
		}
	}
};
struct Ota {
	static return_t img_state(esp_ota_img_states_t state){
		switch( state ){
			case ESP_OTA_IMG_NEW:
				return "ESP_OTA_IMG_NEW";
			case ESP_OTA_IMG_PENDING_VERIFY:
				return "ESP_OTA_IMG_PENDING_VERIFY";
			case ESP_OTA_IMG_VALID:
				return "ESP_OTA_IMG_VALID";
			case ESP_OTA_IMG_INVALID:
				return "ESP_OTA_IMG_INVALID";
			case ESP_OTA_IMG_ABORTED:
				return "ESP_OTA_IMG_ABORTED";
			case ESP_OTA_IMG_UNDEFINED:
				return "ESP_OTA_IMG_UNDEFINED";
		}
	}
};
}} // namespace Tool::HumanReadable
