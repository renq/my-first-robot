#include "TextJoystick.h"
#include "Rover.h"
#include "unity.h"
#include "DummyEngine.h"

#ifdef UNIT_TEST

TextJoystick textJoystick = TextJoystick();
DummyEngine engineLeft = DummyEngine();
DummyEngine engineRight = DummyEngine();
Rover rover = Rover(&engineLeft, &engineRight, &textJoystick);

void setUp(void)
{
}

void tearDown(void)
{
}

void test_handle_joystick(void)
{
  char input[] = "x=0,y=0";
  textJoystick.command(input);
  rover.handleJoystick();

  TEST_ASSERT_EQUAL(engineLeft.getPower(), 0);
  TEST_ASSERT_EQUAL(engineRight.getPower(), 0);
}


int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_handle_joystick);
  UNITY_END();

  return 0;
}

#endif
