#include "TextJoystick.h"
#include <stdlib.h>
#include <string.h>

void TextJoystick::command(char *inputCommand)
{
  char *inputCopy = strdup(inputCommand);
  char *command = strtok(inputCopy, ",");

  x = atoi(command);
  command = strtok(0, ",");
  y = atoi(command);
}
