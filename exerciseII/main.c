#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    int max_size;
    int* stored_values;
} stack;

stack *create_stack(int max_size) {
    stack *s = (stack *)malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack.\n");
        exit(EXIT_FAILURE);
    }

    s->max_size = max_size;
    s->top = -1;
    s->stored_values = (int*)malloc(s->max_size * sizeof(int));
    if (s->stored_values == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack values.\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    return s;
}

int is_empty(stack *s) {
    return s->top == -1;
}

int is_full(stack *s) {
    return s->top == s->max_size - 1;
}

int resize_stack(stack *s) {
    int new_max_size = s->max_size += s->top;
    int* new_values = (int*)realloc(s->stored_values, new_max_size * sizeof(int));
    if (new_values == NULL) {
        fprintf(stderr, "Failed to reallocate memory for stack values.\n");
        return 1;
    }
    s->stored_values = new_values;
    s->max_size = new_max_size;
    return 0;
}

void free_stack(stack *s) {
    free(s->stored_values);
    free(s);
}

void print_stack(stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("Item:[%d] Value: %d\n", s->top - i, s->stored_values[s->top - i]);
    }
}

int push(stack *s, int value) {
    if (is_full(s)) {
        if (resize_stack(s)) {
            printf("Failed to resize stack.\n");
            return 1;
        }
    }
    s->top++;
    s->stored_values[s->top] = value;
    return 0;
}

int pop(stack *s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        return 1;
    }
    s->top--;
    return 0;
}

int get_top_value(stack *s) {
    return s->stored_values[s->top];
}

int main(void) {
    stack *s = create_stack(3);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);
    push(s, 6);
    print_stack(s);
    printf("%d", get_top_value(s));
    free_stack(s);

    return 0;
}
