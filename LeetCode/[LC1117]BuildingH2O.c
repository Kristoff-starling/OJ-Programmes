typedef struct _h2o_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int state;
}h2o_t;

void init_H2O(h2o_t *cv) {
    pthread_mutex_init(&cv->lock, NULL);
    pthread_cond_init(&cv->cond, NULL);
    cv->state = 1;
}

int NextState(int state, char ch) {
    switch (state) {
        case 1: return ch == 'H' ? 2 : 3;
        case 2: return ch == 'H' ? 4 : 5;
        case 3: return ch == 'H' ? 5 : 0;
        case 4: return ch == 'H' ? 0 : 1;
        case 5: return ch == 'H' ? 1 : 0;
    }
    return 0;
}

void H2O_wait(h2o_t *cv, char ch) {
    pthread_mutex_lock(&cv->lock);
    while (!(NextState(cv->state, ch) != 0))
        pthread_cond_wait(&cv->cond, &cv->lock);
}

void H2O_signal(h2o_t *cv, char ch) {
    cv->state = NextState(cv->state, ch);
    assert(cv->state != 0);
    pthread_cond_broadcast(&cv->cond);
    pthread_mutex_unlock(&cv->lock);
}

typedef struct {
    // User defined data may be declared here.
    h2o_t cv;
} H2O;

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    init_H2O(&obj->cv);
    return obj;
}

void hydrogen(H2O* obj) {
    H2O_wait(&obj->cv, 'H');
    releaseHydrogen();
    H2O_signal(&obj->cv, 'H');
}

void oxygen(H2O* obj) {
    H2O_wait(&obj->cv, 'O');
    releaseOxygen();
    H2O_signal(&obj->cv, 'O');
}

void h2oFree(H2O* obj) {
    free(obj);
}