// src/Tool/Info/Memory.h - memory info tools
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool { namespace Info { namespace Memory {
void all() {
	// @insp https://iotespresso.com/how-to-check-free-memory-in-esp32/
	ESP_LOGI( TAGX, "This Task watermark: %d bytes", uxTaskGetStackHighWaterMark(NULL) );
	ESP_LOGI( TAGX, "esp_get_free_heap_size: %d", esp_get_free_heap_size( ) );

	// @insp https://www.esp32.com/viewtopic.php?t=23609
	ESP_LOGI( TAGX, "esp_get_free_internal_heap_size: %d", esp_get_free_internal_heap_size( ) );
	ESP_LOGI( TAGX, "esp_get_minimum_free_heap_size: %d", esp_get_minimum_free_heap_size( ) );
	multi_heap_info_t info;
	// internal RAM, memory capable to store data or to create new task
	heap_caps_get_info( &info, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT );
	info.total_free_bytes;   // total currently free in all non-continues blocks
	info.minimum_free_bytes;  // minimum free ever
	info.largest_free_block;   // largest continues block to allocate big array
	ESP_LOGI( TAGX, "heap_caps_get_info: %d/%d/%d", info.total_free_bytes, info.minimum_free_bytes, info.largest_free_block );
	heap_caps_print_heap_info( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT );

	// @insp https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/mem_alloc.html
	//heap_caps_get_free_size();
}
}}} // namespace Tool::Info::Memory
