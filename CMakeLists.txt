# SPDX-License-Identifier: Apache-2.0

if(CONFIG_TINYUSB)
	set(TINYUSB_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/tinyusb")
	if(NOT EXISTS "${TINYUSB_SOURCE_DIR}/src/tusb.h")
		message(FATAL_ERROR
			"Could not locate the TinyUSB submodule at ${TINYUSB_SOURCE_DIR}. "
			"Add this project with submodules enabled in the west manifest, then "
			"run 'west update'."
		)
	endif()

	if(NOT TINYUSB_CONFIG_DIR OR NOT EXISTS "${TINYUSB_CONFIG_DIR}/tusb_config.h")
		message(FATAL_ERROR
			"Set TINYUSB_CONFIG_DIR to the application directory containing "
			"tusb_config.h, using -DTINYUSB_CONFIG_DIR=<path-to-config-directory> "
			"or setting it before find_package(Zephyr)."
		)
	endif()

	zephyr_include_directories(
		"${TINYUSB_SOURCE_DIR}/src"
		"${TINYUSB_SOURCE_DIR}/lib/networking"
		"${TINYUSB_CONFIG_DIR}"
	)
	zephyr_compile_definitions(CFG_TUSB_OS=OPT_OS_ZEPHYR)

	# Upstream's source helper excludes controller drivers and BSPs.
	include("${TINYUSB_SOURCE_DIR}/src/CMakeLists.txt")
	if(NOT COMMAND tinyusb_sources_get)
		message(FATAL_ERROR "Upstream TinyUSB does not provide tinyusb_sources_get().")
	endif()
	tinyusb_sources_get(tinyusb_sources)

	zephyr_library()
	zephyr_library_sources(${tinyusb_sources})
endif()
