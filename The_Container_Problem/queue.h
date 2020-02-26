//
//  QueueCF.h
//  Queue
//
//  Created by Angela Engelbrecht on 01/05/19.
//  Copyright © 2019 Angela Engelbrecht. All rights reserved.
//

#ifndef QueueCF_h
#define QueueCF_h

#include  <stdlib.h>

using namespace std;

#define MAXELEMENTS 100

struct Queue
{
    int first, last;
    queueElement local[MAXELEMENTS];
};
// Prototipos

void initQueue         (Queue&);
void insertQueue       (Queue&,queueElement);
int isEmptyQueue      (Queue);
queueElement eliminate (Queue&);

void initQueue (Queue& Q)
{
    Q.first = 0;
    Q.last =-1;
}

int isEmptyQueue (Queue Q)
{
    if(Q.first  > Q.last)
        return 1;
    else
        return 0;
}

void insertQueue ( Queue& Q, queueElement V)
{
    if( Q.last == MAXELEMENTS )
        exit(1);
    Q.last++;
    Q.local[Q.last] = V;
}

queueElement eliminate (Queue& Q)
{
    if( isEmptyQueue(Q))
        exit(1);
    return (Q.local [Q.first++ ]);
}

#endif /* queue.h */
