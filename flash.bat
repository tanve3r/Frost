python -m esptool --chip esp32c3 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size=detect --flash_freq 80m 0x0 merged-frost.bin

pause