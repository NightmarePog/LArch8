#include "unity.h"

void setUp(void) {}  
void tearDown(void) {}

void compile(void) {
   // TODO int return_val = init("../testdata/test.asm");
   // TEST_ASSERT_EQUAL(0, return_val);
   
}

int main(void) {
   return 0;
   UNITY_BEGIN();
   RUN_TEST(compile);
   return UNITY_END();
}
