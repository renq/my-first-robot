#include "TextJoystick.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int TextJoystick::getX()
{
  return x;
}

int TextJoystick::getY()
{
  return y;
}

void TextJoystick::command(char *inputCommand)
{
  char *inputCopy = strdup(inputCommand);
  char commands[2][strlen(inputCopy)+1];
  int numberOfCommands = 0;

  char *command = strtok(inputCopy, ",");

  while (command != 0) {
    strcpy(commands[numberOfCommands], command);
    command = strtok(0, ",");
    numberOfCommands++;
  }

  for (int i = 0; i < numberOfCommands; ++i) {
    char *keyValue = strtok(commands[i], "=");

    if (strcmp(keyValue, "x") == 0) {
        keyValue = strtok(0, "=");
        x = atoi(keyValue);
      } else if (strcmp(keyValue, "y") == 0) {
        keyValue = strtok(0, "=");
        y = atoi(keyValue);
    }
  }
}
