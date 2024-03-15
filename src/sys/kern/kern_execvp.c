#include "syscall.h"
#include <stdarg.h>
int execl(const char *path, const char *arg, ...)
{
    va_list args;
    va_start(args, arg);
    char *argv[10];
    argv[0] = (char *)arg;
    int i = 1;
    const char *nextArg;
    while ((nextArg = va_arg(args, const char *)) != NULL && i < 10)
    {
        argv[i] = (char *)nextArg;
        i++;
    }
    va_end(args);
    argv[i] = NULL;
    return execv(path, argv);
}
int execv(const char *path, const char **argv)
{
    int argc = 0;
    while (argv[argc] != NULL) {
        argc++;
    }

    char **new_argv = (char **)malloc((argc + 1) * sizeof(char *));
    if (new_argv == NULL) {
        return -1;
    }

    /* Copy the program path and arguments into the new array */
    for (int i = 0; i <= argc; i++) {
        new_argv[i] = argv[i];
    }

    /* Execute the new program */
    int result = execvp(path, new_argv);

    /* Free the memory allocated for the new arguments array */
    free(new_argv);

    return result;
}
int execvp(const char *path, const char *argv)
{
    // Count the number of arguments
    int argc = 0;
    while (argv[argc] != NULL) {
        argc++;
    }

    // Create a new array for the arguments including the program path
    char **new_argv = (char **)malloc((argc + 1) * sizeof(char *));
    if (new_argv == NULL) {
        return -1; // Return an error if memory allocation fails
    }

    // Copy the program path and arguments into the new array
    for (int i = 0; i <= argc; i++) {
        new_argv[i] = argv[i];
    }

    // Execute the new program
    int result = -1;
    if (path != NULL && *path != '\0' && new_argv[0] != NULL) {
        result = execv(path, new_argv);
    }

    // Free the memory allocated for the new arguments array
    free(new_argv);

    return result;
}