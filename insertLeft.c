typedef struct thread* threadedPointer;

typedef struct thread {
    threadedPointer leftChild;
    int leftThread;
    threadedPointer rightChild;
    int rightThread;
}

void insertLeft(threadedPointer s, threadedPointer r) {
    threadedPointer temp;

    r->leftChild = s->leftChild;
    r->leftThread = s->leftThread;

    r->rightThread = 1;
    r->rightChild = s;

    s->leftChild = r;
    s->leftThread = 0;

    if (r->leftChild != NULL) {
        temp = insucc(r);
        temp->rightChild = r;
    }
}