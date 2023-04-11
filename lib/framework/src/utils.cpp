#include <cstdio>
#include <cstring>
#include <macros.h>
#include <utils.h>

void utils::getPathToTable(char *dest, const char *title)
{
  std::snprintf(dest, MAX_FILENAME_LENGTH, "/tables/%s%s", title, ".json");
}

void utils::getFileName(char *dest, const char *path, size_t size)
{
  char buf[MAX_FILENAME_LENGTH]{};
  std::strncpy(buf, path, sizeof(buf));
  for (char *start = buf, *end = buf; *start != '\0'; ++end)
  {
    if (*end == '\0')
    {
      for (size_t i = 0; i < size && start <= end; ++i, ++start)
      {
        dest[i] = *start;
      }
    }
    else if (*end == '/')
    {
      start = ++end;
    }
  }
}

void utils::removeExtension(char *fileName)
{
  char *extension = std::strchr(fileName, '.');
  while (extension != nullptr && *extension != '\0')
  {
    *(extension++) = '\0';
  }
}
