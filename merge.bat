python -m esptool --chip esp32c3 merge_bin -o merged-frost.bin --flash_mode dio --flash_size 2MB 0x0 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\app-frost.bin"

pause