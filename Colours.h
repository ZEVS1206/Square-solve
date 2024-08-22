#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define printfRed(...) printf(ANSI_COLOR_RED __VA_ARGS__); printf(ANSI_COLOR_RESET)
#define printfGreen(...) printf(ANSI_COLOR_GREEN __VA_ARGS__); printf(ANSI_COLOR_RESET)

