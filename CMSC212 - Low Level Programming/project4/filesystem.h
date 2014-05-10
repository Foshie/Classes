#include "file-system-internals.h"

void mkfs(Filesystem *files);
void touch(Filesystem *files, const char arg[]);
void mkdir(Filesystem *files, const char arg[]);
void cd(Filesystem *files, const char arg[]);
void ls(Filesystem files, const char arg[]);
void pwd(Filesystem files);
void rmfs(Filesystem *files);
