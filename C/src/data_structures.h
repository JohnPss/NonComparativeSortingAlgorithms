#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
// ESTRUTURAS DE DADOS DINAMICAS
//  Estrutura para Lista
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} LinkedList;

// Estrutura para Pilha
typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

// Estrutura para Fila
typedef struct
{
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Lista
LinkedList *createList();
void insertList(LinkedList *list, int value);
void destroyList(LinkedList *list);

// Pilha
Stack *createStack(int capacity);
void push(Stack *stack, int value);
int pop(Stack *stack);
void destroyStack(Stack *stack);

// Fila
Queue *createQueue(int capacity);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void destroyQueue(Queue *queue);

// ESTRUTURAS DE DADOS LINEARES

// Lista Linear
typedef struct
{
    int *data;
    int size;
    int capacity;
} LinearList;

// Pilha Linear
typedef struct
{
    int *data;
    int top;
    int capacity;
} LinearStack;

// Fila Linear
typedef struct
{
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} LinearQueue;

// Lista Linear
LinearList *createLinearList(int capacity);
void appendLinearList(LinearList *list, int value);
void destroyLinearList(LinearList *list);
// Pilha Linear
LinearStack *createLinearStack(int capacity);
void pushLinear(LinearStack *stack, int value);
int popLinear(LinearStack *stack);
int isLinearStackEmpty(LinearStack *stack);
void destroyLinearStack(LinearStack *stack);
// Fila Linear
LinearQueue *createLinearQueue(int capacity);
void enqueueLinear(LinearQueue *queue, int value);
int dequeueLinear(LinearQueue *queue);
void destroyLinearQueue(LinearQueue *queue);
#endif