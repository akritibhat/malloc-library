
#define MUL_NO_OVERFLOW (1UL << (sizeof(size_t) * 4))
#define SIZE_MAX  65535

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
   size_t new_size=size * nmemb;
   //checking for multiplication overflow
  if ((size >= MUL_NO_OVERFLOW || nmemb >= MUL_NO_OVERFLOW) &&
            nmemb > 0 && SIZE_MAX / nmemb < size) {
                errno = ENOMEM;
                return NULL;
        }

        return realloc(ptr,new_size);
}
