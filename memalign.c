void **getAlignedAddress(size_t, size_t ,void *);

void *memalign(size_t alignment, size_t size)
{
 void *pointer;

 pointer =(void *) malloc(size + alignment + sizeof(size_t));

 if(pointer==NULL)
 return NULL;

 void **ptr = getAlignedAddress(alignment,size,pointer);
  ptr[-1] = pointer;
  if(!ptr){
  errno=EINVAL;
  return errno;
  }
  return ptr;
}


void **getAlignedAddress(size_t alignment, size_t size,void *pointer){

   return (void**)((uintptr_t)(sizeof(void*)+pointer+alignment) & ~(alignment-1));

}
