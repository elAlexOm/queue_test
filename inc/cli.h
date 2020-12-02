
#pragma once

typedef struct {
  char* cmd;
  char* help;
  void ( *cmd_fun )( int argc, char *argv[] );
} command_item_t;

extern command_item_t commands[];
