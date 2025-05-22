#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 30000
#define STACK_SIZE 1000

typedef struct {
    unsigned char memory[MEMORY_SIZE];
    int ptr;
    char *code;
    int code_ptr;
    int code_len;
    int loop_stack[STACK_SIZE];
    int stack_ptr;
} BFInterpreter;

void init_interpreter(BFInterpreter *bf, char *code) {
    memset(bf->memory, 0, MEMORY_SIZE);
    bf->ptr = 0;
    bf->code = code;
    bf->code_ptr = 0;
    bf->code_len = strlen(code);
    bf->stack_ptr = 0;
}

int find_matching_bracket(char *code, int start, int direction) {
    int bracket_count = 1;
    int i = start + direction;
    char open_bracket = (direction > 0) ? '[' : ']';
    char close_bracket = (direction > 0) ? ']' : '[';
    
    while (i >= 0 && i < strlen(code) && bracket_count > 0) {
        if (code[i] == open_bracket) {
            bracket_count++;
        } else if (code[i] == close_bracket) {
            bracket_count--;
        }
        i += direction;
    }
    
    return (bracket_count == 0) ? i - direction : -1;
}

int execute_brainfuck(BFInterpreter *bf) {
    while (bf->code_ptr < bf->code_len) {
        char instruction = bf->code[bf->code_ptr];
        
        switch (instruction) {
            case '>':
                bf->ptr++;
                if (bf->ptr >= MEMORY_SIZE) {
                    fprintf(stderr, "Error: Memory pointer out of bounds (too high)\n");
                    return -1;
                }
                break;
                
            case '<':
                bf->ptr--;
                if (bf->ptr < 0) {
                    fprintf(stderr, "Error: Memory pointer out of bounds (too low)\n");
                    return -1;
                }
                break;
                
            case '+':
                bf->memory[bf->ptr]++;
                break;
                
            case '-':
                bf->memory[bf->ptr]--;
                break;
                
            case '.':
                putchar(bf->memory[bf->ptr]);
                fflush(stdout);
                break;
                
            case ',':
                {
                    int c = getchar();
                    if (c != EOF) {
                        bf->memory[bf->ptr] = (unsigned char)c;
                    }
                }
                break;
                
            case '[':
                if (bf->memory[bf->ptr] == 0) {
                    // Jump to matching ']'
                    int matching = find_matching_bracket(bf->code, bf->code_ptr, 1);
                    if (matching == -1) {
                        fprintf(stderr, "Error: Unmatched '[' at position %d\n", bf->code_ptr);
                        return -1;
                    }
                    bf->code_ptr = matching;
                } else {
                    // Push current position to stack
                    if (bf->stack_ptr >= STACK_SIZE) {
                        fprintf(stderr, "Error: Loop stack overflow\n");
                        return -1;
                    }
                    bf->loop_stack[bf->stack_ptr++] = bf->code_ptr;
                }
                break;
                
            case ']':
                if (bf->stack_ptr == 0) {
                    fprintf(stderr, "Error: Unmatched ']' at position %d\n", bf->code_ptr);
                    return -1;
                }
                
                if (bf->memory[bf->ptr] != 0) {
                    // Jump back to matching '['
                    bf->code_ptr = bf->loop_stack[bf->stack_ptr - 1];
                } else {
                    // Pop from stack
                    bf->stack_ptr--;
                }
                break;
                
            default:
                // Ignore non-Brainfuck characters (comments)
                break;
        }
        
        bf->code_ptr++;
    }
    
    if (bf->stack_ptr != 0) {
        fprintf(stderr, "Error: Unmatched '[' - %d loops left open\n", bf->stack_ptr);
        return -1;
    }
    
    return 0;
}

char* read_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *code = malloc(length + 1);
    if (!code) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    fread(code, 1, length, file);
    code[length] = '\0';
    fclose(file);
    
    return code;
}

void print_usage(const char* program_name) {
    printf("Usage: %s [options] <brainfuck_file>\n", program_name);
    printf("Options:\n");
    printf("  -c <code>    Execute Brainfuck code directly from command line\n");
    printf("  -h, --help   Show this help message\n");
    printf("  -d           Print 'I use Arch btw!'\n");
    printf("\nExamples:\n");
    printf("  %s hello.bf\n", program_name);
    printf("  %s -c \"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.\"\n", program_name);
    printf("  %s -d\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    char *code = NULL;
    int free_code = 0;
    
    // Parse command line arguments
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: -c option requires code argument\n");
            print_usage(argv[0]);
            return 1;
        }
        code = argv[2];
    } else if (strcmp(argv[1], "-d") == 0) {
        // Debug mode - print "I use Arch btw!" directly
        printf("I use Arch btw!\n");
        return 0;
    } else {
        code = read_file(argv[1]);
        if (!code) {
            return 1;
        }
        free_code = 1;
    }
    
    BFInterpreter bf;
    init_interpreter(&bf, code);
    
    int result = execute_brainfuck(&bf);
    
    if (free_code) {
        free(code);
    }
    
    return result;
}