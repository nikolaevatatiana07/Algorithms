#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vec;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->vec = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack)
    {
        vector_delete(stack->vec);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    if (!stack) return;
    size_t count = vector_size(stack->vec);
    vector_resize(stack->vec, count + 1);
    vector_set(stack->vec, count, data);
}

Data stack_get(const Stack *stack)
{
    if (!stack || stack_empty(stack))
    {
        return (Data)0;
    }
    size_t count = vector_size(stack->vec);
    return vector_get(stack->vec, count - 1);
}

void stack_pop(Stack *stack)
{
    if (!stack || stack_empty(stack)) return;
    size_t count = vector_size(stack->vec);
    vector_resize(stack->vec, count - 1);
}

bool stack_empty(const Stack *stack)
{
    if (!stack) return true;
    return vector_size(stack->vec) == 0;
}
