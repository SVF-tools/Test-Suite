execute_process(
  COMMAND "${EXECUTABLE}" --invalid-state
  RESULT_VARIABLE result
  ERROR_VARIABLE error
  TIMEOUT 30
)
if(result STREQUAL "0" OR result MATCHES "timeout" OR
   NOT error MATCHES "checking invalid initialization state")
  message(FATAL_ERROR "Invalid initialization state was not rejected: ${result} ${error}")
endif()
