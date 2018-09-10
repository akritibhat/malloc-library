

int posix_memalign(void **memptr, size_t alignment, size_t size){
        if(size==0){
          memptr=NULL;
          return 0;
        }
        if(checkAlignment(alignment)){
          void * temp=(memalign(alignment,size));
          memptr=&temp;
          return 0;
        }
        else{
          errno=EINVAL;
          return errno;
        }
}

 int checkAlignment(size_t align){
   int finalAlign=0, power=1;
       if(align==0)
       return 0;

     while(align!=1){
       if(align%2 !=0){
         power= 0;
         break;
       }
         align=align/2;
     }

     if((align%sizeof(void *))==0){
       finalAlign==1;
     }

     return power&&finalAlign;
 }
