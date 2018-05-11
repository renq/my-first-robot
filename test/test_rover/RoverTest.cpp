#include "Joystick.h"
#include "Rover.h"
#include "unity.h"
#include "DummyEngine.h"
#include <stdio.h>

#ifdef UNIT_TEST

Joystick joystick = Joystick();
DummyEngine engineLeft = DummyEngine();
DummyEngine engineRight = DummyEngine();
Rover rover = Rover(&engineLeft, &engineRight, &joystick);

void setUp(void)
{
}

void tearDown(void)
{
}

void test_handle_joystick_at_zeros(void)
{
  joystick.setX(0);
  joystick.setY(0);
  rover.handleJoystick();

  TEST_ASSERT_EQUAL(engineLeft.getPower(), 0);
  TEST_ASSERT_EQUAL(engineRight.getPower(), 0);
}

void test_handle_joystick_full_forward(void)
{
  joystick.setX(0);
  joystick.setY(511);
  rover.handleJoystick();

  TEST_ASSERT_EQUAL(255, engineLeft.getPower());
  TEST_ASSERT_FALSE(engineLeft.isMovingClockwise());

  TEST_ASSERT_EQUAL(255, engineRight.getPower());
  TEST_ASSERT_TRUE(engineRight.isMovingClockwise());
}

void test_handle_joystick_full_reverse(void)
{
  joystick.setX(0);
  joystick.setY(-512);
  rover.handleJoystick();

  TEST_ASSERT_EQUAL(255, engineLeft.getPower());
  TEST_ASSERT_TRUE(engineLeft.isMovingClockwise());

  TEST_ASSERT_EQUAL(255, engineRight.getPower());
  TEST_ASSERT_FALSE(engineRight.isMovingClockwise());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_handle_joystick_at_zeros);
  RUN_TEST(test_handle_joystick_full_forward);
  RUN_TEST(test_handle_joystick_full_reverse);
  UNITY_END();

  return 0;
}

#endif
