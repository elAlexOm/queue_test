
/** \file   queue.c
*   \author Alex
*   \date   30.11.2020
*
* Реализация очереди
*/

#include "queue.h"

#include <stdlib.h>
#include <mem.h>

queue_t* create_queue( uint32_t length ) {
  queue_t* pqueue;

  pqueue = malloc( sizeof( queue_t ) * length );
  if( pqueue ) {
    pqueue->lenght = length;
  }
  return pqueue;
}

void free_queue( queue_t* pqueue ) {
  free( pqueue->pdata );
  free( pqueue );
}

queue_element_t* get_queue_element( queue_t* pqueue, int32_t index ) {
  if( pqueue->lenght > index ) return &pqueue->pdata[index];
  return NULL;
}

int32_t set_queue_element(  queue_t* pqueue, int32_t index, queue_element_t* pelement ) {
  if( pqueue->lenght > index ) {
    memcpy( &pqueue->pdata[index], pelement, sizeof( queue_element_t ));
    return index;
  }
  return -1;
}
