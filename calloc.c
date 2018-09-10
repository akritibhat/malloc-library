void * calloc(size_t blocks, size_t size) {
  int totalMem = blocks * size;
  if (totalMem == 0) { //checking if size is zero
    return NULL;
  }
  void * temptr = malloc(totalMem); //calling malloc
  if (!temptr) {
    return NULL;
  }
  memset(temptr, 0, totalMem); //setting initial bytes to 0
  return temptr;
}