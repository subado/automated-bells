#pragma once

namespace utils
{
void getPathToTable(char *dest, const char *title);
void getFileName(char *dest, const char *path, size_t size);
void removeExtension(char *fileName);
} // namespace utils
