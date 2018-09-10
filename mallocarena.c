void* arenamalloc(struct ArenaInfo* arena, size_t size);

__thread struct ArenaInfo *arrThread = NULL;


ArenaInfo* getLastassociatedArena(pid_t pidt);
void getArena(struct ArenaInfo* arena);


void * malloc(size_t size)
{
	pthread_mutex_lock(&mutex);
	if(size==0){
 	 pthread_mutex_unlock(&mutex);
 	return NULL;
	}
	int tempArena;
	ArenaInfo* arrTemp;
	
	if(arrThread==NULL){
	//printf("arr null for %d \n", size);

	if(arenaHead==NULL){
	//printf("areana head is null \n");
	cores=get_nprocs();
	initialiseArena(cores);
	arrThread=arenaHead;
	tempArena=arenaNum%cores;
	}

	else
	{
	//	printf("in arena ger");
	arenaNum++;
	int tempArena=arenaNum%cores;
	if(tempArena==0)
	tempArena=cores;
	arrThread=arenaHead;
	for(int i=1;i<=tempArena-1;i++)
	 arrThread=arrThread->next;
	}
	
	}
	//else
	//printf( " arena already initialsed for size %d", size);
	pthread_mutex_unlock(&mutex);

	
	void *ptr= arenamalloc(arrThread, size);
	
	return ptr;
	
}


void* arenamalloc(struct ArenaInfo* arena, size_t size)
{
  	pthread_mutex_lock(&arrThread->arrlock);
	arena->mallocReq = arena->mallocReq+1;
	//printf("\n ***************************** working in arena %d for malloc %d and arena address %p ***************** ", arena->numArena , 		size , arena);
	
	
	if(size==0){
 	 pthread_mutex_unlock(&arena->arrlock);
 	return NULL;
	}
    	void * myPointer;
	arena->usedBlocks= arena->usedBlocks+1;
	arena->freeBlocks = arena->freeBlocks-1;
  	if(arena->ghead==NULL){  //if head node is not initialized, call kernel for space
	//printf("arena head is hull");
   	spaceFromKernel(arena, size);
 	myPointer=searchNodes(arena, size);
	if(myPointer==NULL){
	pthread_mutex_unlock(&arena->arrlock);
	return NULL;
	}
 	}
 	else{
	myPointer=searchNodes(arena, size); //seach for a free node
	if(myPointer==NULL){
		spaceFromKernel(arena, size);
		myPointer=searchNodes(arena,size);
		}
	}


  	pthread_mutex_unlock(&arrThread->arrlock);
   	return myPointer;
}




