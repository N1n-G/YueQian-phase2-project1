#include "main.h"

// 初始化任务队列（循环队列）
task_queue_t *task_queue_init(int capacity) {
    task_queue_t *queue = malloc(sizeof(task_queue_t));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    queue->tasks = malloc(sizeof(thread_task_t *) * capacity);
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    return queue;
}

// 向任务队列中添加任务
void add_task_to_queue(task_queue_t *queue, thread_task_t *task) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->size == queue->capacity) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }
    queue->tasks[queue->rear] = task;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);
}

// 从任务队列中取出任务
thread_task_t *task_queue_get(task_queue_t *queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->size == 0) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }
    thread_task_t *task = queue->tasks[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);
    return task;
}
