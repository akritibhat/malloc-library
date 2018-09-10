typedef struct ArenaInfo {
  int numberOfArena;
  int mallocReq;
  int freeReq;
  int arenaSize;
  int usedBlocks;
  int freeBlocks;
  struct arenaInfo * next;
  pthread_mutex_t arrlock;
  struct MyNode * ghead;
  struct MyNode * endNode;
}
ArenaInfo;

int arenaNum;
struct ArenaInfo * arenaHead;
int cores;
void malloc_stats();
void initialiseArena(int arr) {
  arenaNum = 1;
  pthread_mutex_lock( & sbmutex);
  arenaHead = (ArenaInfo * ) sbrk(sizeof(ArenaInfo));
  pthread_mutex_unlock( & sbmutex);

  arenaHead - > numberOfArena = 1;
  ArenaInfo * arrTemp = arenaHead;
  for (int i = 2; i <= arr; i++) {
    arrTemp - > next = (ArenaInfo * ) sbrk(sizeof(ArenaInfo));
    arrTemp = arrTemp - > next;
    arrTemp - > numberOfArena = i;

  }

}

void malloc_stats() {
  ArenaInfo * arena;
  arena = arenaHead;
  printf("Total arenas : %d \n ", cores);
  while (arena != NULL) {
    printf("\n Arena number: %d", arena - > numberOfArena);
    printf("\n Total size of arena allocated with sbrk/mmap :%d", arena - > arenaSize);
    printf("\n Total number of blocks: %d", arena - > usedBlocks + arena - > freeBlocks);
    printf("\n Used blocks: %d", arena - > usedBlocks);
    printf("\n Free blocks: %d", arena - > freeBlocks);
    printf("\n Total allocation requests: %d", arena - > mallocReq);
    printf("\n Total free requests: %d", arena - > freeReq);
    arena = arena - > next;
    printf("\n\n");

  }
}