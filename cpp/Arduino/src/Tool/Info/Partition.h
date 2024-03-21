// src/Tool/Info/Partition.h - partition info tools
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
namespace Tool { namespace Info {
// @insp https://github.com/espressif/arduino-esp32/issues/703
class Partition {
	// Find the partition using given parameters
	static void find_partition(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* name) {
		ESP_LOGI(TAGX, "Find partition with type %s, subtype %s, label %s..."
				, Tool::HumanReadable::Partition::type( type )
				, Tool::HumanReadable::Partition::subtype( subtype )
				, name == NULL ? "NULL (unspecified)" : name
			);

		const esp_partition_t * part  = esp_partition_find_first(type, subtype, name);

		if (part != NULL) {
			ESP_LOGI(TAGX, "\tfound partition '%s' at offset 0x%" PRIx32 " with size 0x%" PRIx32, part->label, part->address, part->size);
		} else {
			ESP_LOGE(TAGX, "\tpartition not found!");
		}
	}

public:
	static void all() {
		esp_partition_iterator_t _mypartiterator;
		const esp_partition_t *_mypart;
		ESP_LOGV( TAGX, "Flash chip size: %d", spi_flash_get_chip_size( ) );
		ESP_LOGV( TAGX, "Partiton table: " );
		_mypartiterator = esp_partition_find( ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, nullptr );
		if  ( _mypartiterator ) {
			do {
				_mypart = esp_partition_get(_mypartiterator);
				ESP_LOGV( TAGX, "%x - %x - %x - %x - %s - %i", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->label, _mypart->encrypted);
			} while (_mypartiterator = esp_partition_next(_mypartiterator));
		}
		esp_partition_iterator_release(_mypartiterator);
		_mypartiterator = esp_partition_find( ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, nullptr );
		if (_mypartiterator) {
			do {
				_mypart = esp_partition_get(_mypartiterator);
				ESP_LOGV( TAGX, "%x - %x - %x - %x - %s - %i", _mypart->type, _mypart->subtype, _mypart->address, _mypart->size, _mypart->label, _mypart->encrypted);
			} while (_mypartiterator = esp_partition_next(_mypartiterator));
		}
		esp_partition_iterator_release(_mypartiterator);
	}
};
}} // namespace Tool::Info
