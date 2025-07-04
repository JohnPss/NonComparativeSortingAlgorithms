#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

// ========== IMPLEMENTAÇÕES - ESTRUTURAS DINÂMICAS ==========
// === IMPLEMENTAÇÕES DA LISTA ===
LinkedList *createList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (!list)
        return NULL;

    list->head = NULL;
    list->size = 0;
    return list;
}

void insertList(LinkedList *list, int value)
{
    if (!list)
        return;

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        return;

    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void destroyList(LinkedList *list)
{
    if (!list)
        return;

    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// === IMPLEMENTAÇÕES DA PILHA ===
Stack *createStack(int capacity)
{
    if (capacity <= 0)
        return NULL;

    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
        return NULL;

    stack->data = (int *)malloc(capacity * sizeof(int));
    if (!stack->data)
    {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, int value)
{
    if (!stack || stack->top >= stack->capacity - 1)
        return;

    stack->data[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (!stack || stack->top < 0)
        return -1;

    return stack->data[stack->top--];
}

int isStackEmpty(Stack *stack)
{
    return (!stack || stack->top < 0);
}

void destroyStack(Stack *stack)
{
    if (!stack)
        return;

    free(stack->data);
    free(stack);
}

// === IMPLEMENTAÇÕES DA FILA ===
Queue *createQueue(int capacity)
{
    if (capacity <= 0)
        return NULL;

    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
        return NULL;

    queue->data = (int *)malloc(capacity * sizeof(int));
    if (!queue->data)
    {
        free(queue);
        return NULL;
    }

    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (!queue || queue->size >= queue->capacity)
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

int dequeue(Queue *queue)
{
    if (!queue || queue->size <= 0)
        return -1;

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int isQueueEmpty(Queue *queue)
{
    return (!queue || queue->size <= 0);
}

void destroyQueue(Queue *queue)
{
    if (!queue)
        return;

    free(queue->data);
    free(queue);
}

// ========== IMPLEMENTAÇÕES - ESTRUTURAS LINEARES ==========

// === LISTA LINEAR ===
LinearList *createLinearList(int capacity)
{
    if (capacity <= 0)
        return NULL;

    LinearList *list = (LinearList *)malloc(sizeof(LinearList));
    if (!list)
        return NULL;

    list->data = (int *)malloc(capacity * sizeof(int));
    if (!list->data)
    {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = capacity;
    return list;
}

void insertLinearList(LinearList *list, int value)
{
    if (!list || list->size >= list->capacity)
        return;

    // Inserir no início (mover todos os elementos para a direita)
    for (int i = list->size; i > 0; i--)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[0] = value;
    list->size++;
}

void appendLinearList(LinearList *list, int value)
{
    if (!list || list->size >= list->capacity)
        return;

    list->data[list->size++] = value;
}

int getLinearList(LinearList *list, int index)
{
    if (!list || index < 0 || index >= list->size)
        return -1;

    return list->data[index];
}

void destroyLinearList(LinearList *list)
{
    if (!list)
        return;

    free(list->data);
    free(list);
}

// === PILHA LINEAR ===
LinearStack *createLinearStack(int capacity)
{
    if (capacity <= 0)
        return NULL;

    LinearStack *stack = (LinearStack *)malloc(sizeof(LinearStack));
    if (!stack)
        return NULL;

    stack->data = (int *)malloc(capacity * sizeof(int));
    if (!stack->data)
    {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void pushLinear(LinearStack *stack, int value)
{
    if (!stack || stack->top >= stack->capacity - 1)
        return;

    stack->data[++stack->top] = value;
}

int popLinear(LinearStack *stack)
{
    if (!stack || stack->top < 0)
        return -1;

    return stack->data[stack->top--];
}

int isLinearStackEmpty(LinearStack *stack)
{
    return (!stack || stack->top < 0);
}

void destroyLinearStack(LinearStack *stack)
{
    if (!stack)
        return;

    free(stack->data);
    free(stack);
}

// === FILA LINEAR ===
LinearQueue *createLinearQueue(int capacity)
{
    if (capacity <= 0)
        return NULL;

    LinearQueue *queue = (LinearQueue *)malloc(sizeof(LinearQueue));
    if (!queue)
        return NULL;

    queue->data = (int *)malloc(capacity * sizeof(int));
    if (!queue->data)
    {
        free(queue);
        return NULL;
    }

    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void enqueueLinear(LinearQueue *queue, int value)
{
    if (!queue || queue->size >= queue->capacity)
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

int dequeueLinear(LinearQueue *queue)
{
    if (!queue || queue->size <= 0)
        return -1;

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int isLinearQueueEmpty(LinearQueue *queue)
{
    return (!queue || queue->size <= 0);
}

void destroyLinearQueue(LinearQueue *queue)
{
    if (!queue)
        return;

    free(queue->data);
    free(queue);
}