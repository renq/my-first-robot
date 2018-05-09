#include "TextJoystick.h"
#include "unity.h"

#ifdef UNIT_TEST

TextJoystick textJoystick;

void setUp(void)
{
  textJoystick = TextJoystick();
}

void tearDown(void)
{
}

void test_only_x(void)
{
  char input[] = "x=100";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(100, textJoystick.getX());
  TEST_ASSERT_EQUAL(0, textJoystick.getY());
}

void test_only_y(void)
{
  char input[] = "y=-500";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(0, textJoystick.getX());
  TEST_ASSERT_EQUAL(-500, textJoystick.getY());
}

void test_command(void)
{
  char input[] = "x=100,y=-200";
  textJoystick.command(input);

  TEST_ASSERT_EQUAL(100, textJoystick.getX());
  TEST_ASSERT_EQUAL(-200, textJoystick.getY());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_only_x);
  RUN_TEST(test_only_y);
  RUN_TEST(test_command);
  UNITY_END();

  return 0;
}

#endif
