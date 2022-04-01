typedef struct _sync_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int cur;
}sync_t;

void init_sync(sync_t *sync) {
    pthread_mutex_init(&sync->lock, NULL);
    pthread_cond_init(&sync->cond, NULL);
    sync->cur = 1;
}

void sync_wait(sync_t *sync, int num) {
    pthread_mutex_lock(&sync->lock);
    while (!(sync->cur == num))
        pthread_cond_wait(&sync->cond, &sync->lock);
    pthread_mutex_unlock(&sync->lock);
}

void sync_signal(sync_t *sync) {
    pthread_mutex_lock(&sync->lock);
    sync->cur++;
    pthread_cond_broadcast(&sync->cond);
    pthread_mutex_unlock(&sync->lock);
}

typedef struct {
    sync_t sync;
    int n;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    init_sync(&obj->sync);
    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    for (int i = 1; i <= obj->n; i++) {
        if (!(i % 3 == 0 && i % 15 != 0)) continue;
        sync_wait(&obj->sync, i);
        printFizz();
        sync_signal(&obj->sync);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    for (int i = 1; i <= obj->n; i++) {
        if (!(i % 5 == 0 && i % 15 != 0)) continue;
        sync_wait(&obj->sync, i);
        printBuzz();
        sync_signal(&obj->sync);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    for (int i = 1; i <= obj->n; i++) {
        if (!(i % 15 == 0)) continue;
        sync_wait(&obj->sync, i);
        printFizzBuzz();
        sync_signal(&obj->sync);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    for (int i = 1; i <= obj->n; i++) {
        if (!(i % 3 != 0 && i % 5 != 0)) continue;
        sync_wait(&obj->sync, i);
        printNumber(i);
        sync_signal(&obj->sync);
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    free(obj);
}