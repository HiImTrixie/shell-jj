#ifndef _READPROCESS_H_
#define _READPROCESS_H_

char *rl_gets();
char *command_generator(const char *text, int state);
char **command_completion(const char *text, int start, int end);
void initialize_readline();

#endif

