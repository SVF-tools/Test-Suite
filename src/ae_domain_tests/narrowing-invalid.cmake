execute_process(
  COMMAND "${EXECUTABLE}" "${CASE}"
  RESULT_VARIABLE result
  ERROR_VARIABLE error
  TIMEOUT 30
)
if(result STREQUAL "0" OR result MATCHES "timeout" OR
   NOT error MATCHES "checking narrowing precondition: ${CASE}")
  message(FATAL_ERROR "Invalid narrowing was not rejected: ${result} ${error}")
endif()
