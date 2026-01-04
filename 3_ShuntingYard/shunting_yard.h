#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

int infix_to_postfix(const char *infix, char *postfix);
int evaluate_postfix(const char *postfix);

#endif
