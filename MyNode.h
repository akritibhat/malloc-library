typedef struct MyNode{
	int freeMem;
	int size;
	int occupied;
	void *sb_pointer;
	struct Node *next;
}MyNode;


//void traversal();
//int divide_MyNode(struct MyNode* current);
//void * spaceFromKernel(size_t size);
//void* searchspace(size_t memNeeded,MyNode* mnode);
//void joinBuddy();
