macro(add_unit_test TESTNAME)
	add_executable(${TESTNAME} ${TESTNAME}.c)
	target_include_directories(${TESTNAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
	target_link_libraries(${TESTNAME} CCORE)
	add_test(${TESTNAME} ${TESTNAME})
endmacro()

add_unit_test(test-core-array)
