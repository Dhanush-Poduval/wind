if (CONFIG_SAY_HELLO)
	zephyr_include_directories(.)
	zephyr_library_sources(hello.c)
		
endif()
