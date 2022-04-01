typedef struct _sync_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    bool done;
}sync_t;

void init_sync(sync_t *sync) {
    pthread_mutex_init(&sync->lock, NULL);
    pthread_cond_init(&sync->cond, NULL);
    sync->done = false;
}

void sync_wait(sync_t *sync) {
    pthread_mutex_lock(&sync->lock);
    while (!sync->done)
        pthread_cond_wait(&sync->cond, &sync->lock);
    sync->done = false;
    pthread_mutex_unlock(&sync->lock);
}

void sync_signal(sync_t *sync) {
    pthread_mutex_lock(&sync->lock);
    sync->done = true;
    pthread_cond_signal(&sync->cond);
    pthread_mutex_unlock(&sync->lock);
}

typedef struct {
    sync_t FirstSecond;
    sync_t SecondThird;
} Foo;

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));

    init_sync(&obj->FirstSecond);
    init_sync(&obj->SecondThird);

    return obj;
}

void first(Foo* obj) {
    printFirst();
    sync_signal(&obj->FirstSecond);
}

void second(Foo* obj) {
    sync_wait(&obj->FirstSecond);
    printSecond();
    sync_signal(&obj->SecondThird);
}

void third(Foo* obj) {
    sync_wait(&obj->SecondThird);
    printThird();
}

void fooFree(Foo* obj) {
    free(obj);
}