#include "TextJoystick.h"
#include "unity.h"

#ifdef UNIT_TEST

TextJoystick textJoystick = TextJoystick();

void setUp(void)
{
  textJoystick = TextJoystick();
}

void tearDown(void)
{
}

void test_both_positive(void)
{
  char input[] = "100,+200";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(100, textJoystick.getX());
  TEST_ASSERT_EQUAL(200, textJoystick.getY());
}

void test_both_negative(void)
{
  char input[] = "-300,-500";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(-300, textJoystick.getX());
  TEST_ASSERT_EQUAL(-500, textJoystick.getY());
}

void test_mixed(void)
{
  char input[] = "100,-200";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(100, textJoystick.getX());
  TEST_ASSERT_EQUAL(-200, textJoystick.getY());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_both_positive);
  RUN_TEST(test_both_negative);
  RUN_TEST(test_mixed);
  UNITY_END();

  return 0;
}

#endif
