#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define QUEUE_LENGTH      64

queue_t* pqueue1;
queue_t* pqueue2;

int main( int argc, char *argv[] ) {

  // Создание 1-й очереди
  pqueue1 = create_queue( QUEUE_LENGTH );
  if( pqueue1 == NULL ) {
    printf( "Error create queue1\r\nExit\r\n");
    return 1;
  }

  // Создание 2-й очереди
  pqueue2 = create_queue( QUEUE_LENGTH );
  if( pqueue1 == NULL ) {
    printf( "Error create queue2\r\nExit\r\n");
    return 1;
  }

  // Инициализация очередей
  for( int i = 0; i < QUEUE_LENGTH; i++ ) {
    queue_element_t elem;

    elem.val = i * 2;
    set_queue_element( pqueue1, i, &elem );

    elem.val++;
    set_queue_element( pqueue2, i, &elem );
  }

  printf( "Exit from app\r\n" );
  return 0;
}
