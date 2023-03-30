#include <cstdio>
#include <cstring>
#include <macros.h>
#include <utils.h>

void utils::getPathToTable(char *dest, const char *title)
{
  char path[MAX_FILENAME_LENGTH]{};
  std::snprintf(path, sizeof(path), "/tables/%s%s", title, ".json");
  std::strncpy(dest, path, MAX_FILENAME_LENGTH);
}

void utils::removeExtension(char *fileName)
{
  *(std::strchr(fileName, '.')) = '\0';
}
