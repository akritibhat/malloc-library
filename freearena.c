void free(void *ptr)
{

   if(ptr==NULL)
   {
      return;
   }
   else{
        pthread_mutex_lock(&arrThread->arrlock);
	arrThread->freeReq = arrThread->freeReq+1;
	arrThread->freeBlocks = arrThread->freeBlocks+1;
     MyNode *temp=arrThread->ghead;
     MyNode *final=NULL;
     while(temp!=NULL){
       if(temp->sb_pointer==ptr){
         final=temp;
         break; 
       }
       temp=temp->next;
     }
     if(final==NULL || (final->freeMem==0)){
       pthread_mutex_unlock(&arrThread->arrlock);
       return; 
     }
     else{
       final->freeMem=0;  
       final->occupied=0;
     }
   }
   joinBuddy();   
   pthread_mutex_unlock(&arrThread->arrlock);

}

 void joinBuddy(){

 	MyNode *n,*nnext;
        n=arrThread->ghead;
	nnext=n->next;
            while(n!=NULL){
 		if(n->next!=NULL && n->freeMem==0){
 			
 			MyNode *temp=n->next;
 			long long int val=n->sb_pointer;
			long long int val2=temp->sb_pointer;
				
 			
 			if((temp->freeMem==0) && (n->size==temp->size) && ((val^val2) == temp->size)){ 
 			
 				n->size=n->size*2;
 				n->next=temp->next;
				if(arrThread->endNode==temp){
                         	 arrThread->endNode=n;
                       		 }
 				n=arrThread->ghead;
				continue;
 			}
 		}
 		n = n->next;
 	}
 }

