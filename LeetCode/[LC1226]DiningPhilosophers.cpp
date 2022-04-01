class DiningPhilosophers {
    typedef struct _sync_t {
        pthread_mutex_t lock;
        pthread_cond_t cond;
    }sync_t;
    sync_t sync;
    int forks[5];
    int Left(int p) {return p;}
    int Right(int p) {return (p + 1) % 5;}
    void sync_init() {
        pthread_mutex_init(&sync.lock, NULL);
        pthread_cond_init(&sync.cond, NULL);
        for (int i = 0; i < 5; i++) forks[i] = 1;
    }
    void philosopher_wait(int p,
                          function<void()> pickLeftFork,
                          function<void()> pickRightFork) {
        pthread_mutex_lock(&sync.lock);
        while (!(forks[Left(p)] == 1 && forks[Right(p)] == 1))
            pthread_cond_wait(&sync.cond, &sync.lock);
        forks[Left(p)]  = 0; pickLeftFork();
        forks[Right(p)] = 0; pickRightFork();
        pthread_mutex_unlock(&sync.lock);  
    }
    void philosopher_signal(int p,
                          function<void()> putLeftFork,
                          function<void()> putRightFork) {
        pthread_mutex_lock(&sync.lock);
        forks[Left(p)]  = 1; putLeftFork();
        forks[Right(p)] = 1; putRightFork();
        pthread_cond_broadcast(&sync.cond);
        pthread_mutex_unlock(&sync.lock);  
    }
public:
    DiningPhilosophers() {
        sync_init();
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		philosopher_wait(philosopher, pickLeftFork, pickRightFork);
        eat();
        philosopher_signal(philosopher, putLeftFork, putRightFork);
    }
};