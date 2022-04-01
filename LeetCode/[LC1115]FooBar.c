typedef struct _pc_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int count;
} pc_t;

void init_pc(pc_t *pc) {
    pthread_mutex_init(&pc->lock, NULL);
    pthread_cond_init(&pc->cond, NULL);
    pc->count = 0;
}

void Tproducer_wait(pc_t *pc) {
    pthread_mutex_lock(&pc->lock);
    while (pc->count == 1)
        pthread_cond_wait(&pc->cond, &pc->lock);
    pthread_mutex_unlock(&pc->lock);
    assert(pc->count == 0);
}

void Tproducer_post(pc_t *pc) {
    pthread_mutex_lock(&pc->lock);
    pc->count = 1;
    pthread_cond_broadcast(&pc->cond);
    pthread_mutex_unlock(&pc->lock);
}

void Tconsumer_wait(pc_t *pc) {
    pthread_mutex_lock(&pc->lock);
    while (pc->count == 0)
        pthread_cond_wait(&pc->cond, &pc->lock);
    pthread_mutex_unlock(&pc->lock);
    assert(pc->count > 0);
}

void Tconsumer_post(pc_t *pc) {
    pthread_mutex_lock(&pc->lock);
    pc->count = 0;
    pthread_cond_broadcast(&pc->cond);
    pthread_mutex_unlock(&pc->lock);
}

typedef struct {
    int n;
    pc_t pc;
} FooBar;

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    init_pc(&obj->pc);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        Tproducer_wait(&obj->pc);
        printFoo();
        Tproducer_post(&obj->pc);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        Tconsumer_wait(&obj->pc);
        printBar();
        Tconsumer_post(&obj->pc);
    }
}

void fooBarFree(FooBar* obj) {
    free(obj);
}