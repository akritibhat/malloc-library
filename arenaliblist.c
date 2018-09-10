
void* spaceFromKernel(struct ArenaInfo* arena, size_t size){
	
	void *p;
	size_t psize = 64*sysconf(_SC_PAGESIZE);
	size_t final;
	if (size>(psize)){
		size_t size_sc=sysconf(_SC_PAGESIZE);
		 final=0;
		while(size>final){
			final=final+size_sc; 
		}
           }
	else{
		final=psize;
	}
	pthread_mutex_lock(&sbmutex);
	p=sbrk(final);
	pthread_mutex_unlock(&sbmutex);
	arena->arenaSize = arena->arenaSize+final;
	if(p==-1){
	errno=ENOMEM; 
	return NULL;
	}
	else{
	createNewBlockPage(arena, p,final);
	return p;
	}
	
	return p;
	}


int createNewBlockPage(struct ArenaInfo* arena, void *sbi_pointer,size_t size_stt){
	pthread_mutex_lock(&sbmutex);
        MyNode* new_node =  (MyNode*)sbrk(sizeof(MyNode));
	pthread_mutex_unlock(&sbmutex);

	if(new_node!=NULL){
	arena->freeBlocks = arena->freeBlocks+1;

	new_node->freeMem=0;
	new_node->size=size_stt;
	new_node->sb_pointer=sbi_pointer;
	new_node->next=NULL;
        if(arena->ghead==NULL){
                        arena->ghead=new_node;
                        arena->endNode=new_node;
        }
        else{
		MyNode *nnn=arena->ghead;
		while(nnn->next!=NULL){
		nnn=nnn->next;

		}
                
                nnn->next=new_node;
                arena->endNode=new_node;
        }
	
	return 1;
	}
	
	return 0;
}



void* searchNodes(struct ArenaInfo* arena, size_t memNeeded){

MyNode *n;
        n=arena->ghead;
	MyNode *ntemp=NULL;
	while (n != NULL){
		if(((n->size)>=memNeeded)&& ((n->freeMem)==0)){
			
			if((n->size)==memNeeded){
				
				ntemp=n;
				break;
			}

			if(ntemp!=NULL){
				if(ntemp->size>n->size){
					ntemp=n;
				}
			}
			else{
				ntemp=n;
			}
		}
		 n = n->next;
	}

	if(ntemp!=NULL){
		while(((ntemp->size/2)>=memNeeded) && (ntemp->size>=16)){
		
		divide_MyNode(arena,ntemp);
		
	}
	 ntemp->freeMem=1;
         ntemp->occupied=memNeeded;
         return ntemp->sb_pointer;
	}
	else{

	return NULL;
	}
  }





int divide_MyNode(struct ArenaInfo* arena, struct MyNode* current){
	
				pthread_mutex_lock(&sbmutex);
				MyNode* new_node = (MyNode*)sbrk(sizeof(MyNode));
				pthread_mutex_unlock(&sbmutex);
				if(new_node!=NULL){
				int sizenew=(current->size)/2;
				new_node->freeMem=0;
				arena->freeBlocks = arena->freeBlocks+1;
				new_node->size  = sizenew;
				new_node->next = current->next;
				new_node->sb_pointer=current->sb_pointer+sizenew;
				current->size=sizenew;
				current->next= new_node;
				if(arena->endNode==current){
					arena->endNode->next=new_node;
					arena->endNode=new_node;
				}

				return 1;
				}
				return 0;
			}

