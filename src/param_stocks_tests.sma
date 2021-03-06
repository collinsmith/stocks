#include <amxmodx>
#include <logger>

#include "../simple_logger_stocks.inc"
#include "../exception_stocks.inc"
#include "../testing_stocks.inc"
#include "../param_stocks.inc"

static const TEST[][] = {
    "FAILED",
    "PASSED"
};

static val, i, bool: b;
static tests, passed;
static bool: isEqual;

native UnitTest(const function[] = "test", plugin = INVALID_PLUGIN_ID);

public plugin_init() {
  register_plugin("param_stocks tests", "0.0.1", "Tirant");

  log_amx("Testing param_stocks");

  tests = passed = 0;

  UnitTest();

  log_amx("Finished Stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
  isEqual = b;
  tests++;
  if (isEqual) passed++;
}

public test_numParamsInRange_IllegalArgumentException() {
  numParamsInRange(2, 1, 1);
}