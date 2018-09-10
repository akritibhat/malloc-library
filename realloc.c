


void *realloc(void *ptr, size_t size) //size_t in bytes
{
// printf("in realloc %d",size);
if(ptr != NULL && size == 0)
{
  free(ptr);
  return;
}
else if(ptr==NULL){
    return malloc(size);
}
else{
      pthread_mutex_lock(&arrThread->arrlock);
    void *newptr= NULL;
    struct MyNode *n=malloc_search_node(ptr);
	pthread_mutex_unlock(&arrThread->arrlock);
    if(n!=NULL){
      if(n->occupied<size){
         //pthread_mutex_lock(&mutex);
         newptr = malloc(size);
         //pthread_mutex_unlock(&mutex);
         newptr= memcpy(newptr, ptr, n->occupied);
        // pthread_mutex_unlock(&mutex);
            free(ptr);
	             //pthread_mutex_unlock(&mutex);
	         return newptr;
          }
            else {
	               return ptr;
                }
            }
     else
	    {
	        return malloc(size);
      }
  }
  //printf("I m here 2:");
  return NULL;
}


int malloc_search_node(void *sbt_pointer){
  struct MyNode *n;
  n=arrThread->ghead;
   while (n != NULL)
   {
     if(n->sb_pointer==sbt_pointer)
     {
       return n;
       break;
     }
      n = n->next;
   }
  return NULL;
 }
