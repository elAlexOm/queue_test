
/** \file   main.c
*   \author Alex
*   \date   30.11.2020
*
* Требуется написать консольное приложение на C для работы с двумя очередями фиксированной длинны, состоящими из 32-битных целых беззнаковых чисел.  Консольное приложение должно сопровождаться всеми необходимыми файлами для сборки.
* В качестве аргументов программе передаются:
* - код команды;
* - аргументы для данной команды, если они предусмотрены.
* Программа должна уметь выполнять следующие операции и поддерживать соответствующие команды:
* - запись/чтение элемента из очереди;
* - вывод на экран информации об очереди (размер, содержимое);
* - вывод на экран содержимого очереди;
* - слияние очередей (в шахматном порядке);
* - вывод элементов очереди, у которых задаваемый пользователем бит равен единице.
* Сопроводить код программы комментариями и краткой инструкцией пользователя.
* Остальные детали — на Ваше усмотрение.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "queue.h"
#include "cli.h"

#define QUEUE_LENGTH      64

void cmd_help( int argc, char *argv[] );
void cmd_queue_info( int argc, char *argv[] );
void cmd_queue_set( int argc, char *argv[] );
void cmd_queue_get( int argc, char *argv[] );
void cmd_queue_merge( int argc, char *argv[] );
void cmd_queue_test_bit( int argc, char *argv[] );

command_item_t commands[] = {
  {
    "--help",
    "Help",
    cmd_help
  },
  {
    "--info",
    "Queue X info as --queue_info X",
    cmd_queue_info
  },
  {
    "--set",
    "Set queue X element Y value Z as --set X Y Z",
    cmd_queue_set,
  },
  {
    "--get",
    "Get queue X element Y as --get X Y",
    cmd_queue_get,
  },
  {
    "--merge",
    "Merging queues 1 and 2 in 3",
    cmd_queue_merge
  },
  {
    "--bit",
    "Output queue X element with specific bit Y as --bit X Y",
    cmd_queue_test_bit
  }
};

queue_t* pqueue[2];

void lover_case_string( char* st ) {
  for( int i = 0; st[i]; i++ ){
    st[i] = tolower( st[i] );
  }
}

/** Вывод информации об очереди
* \param  pqueue        - указатель на очередь
* \param  name          - имя очереди
*/
void printf_queue_info( queue_t* pqueue, char* name ) {

  if( NULL == pqueue ) { return; }
  printf( "%s size - %d\r\n", name, pqueue->lenght );
}

/** Вывод содержимого очереди
* \param  pqueue        - указатель на очередь
*/
void printf_queue_data( queue_t* pqueue ) {
  if( NULL == pqueue ) { return; }
  for( uint32_t i = 0; i < pqueue->lenght; i++ ) {
    printf( "Element %4d - %d\r\n", i, get_queue_element( pqueue, i )->val );
  }
}

/** Обработчик команды HELP
*/
void cmd_help( int argc, char *argv[] ) {
  printf( "\r\nCommands help\r\n" );
  for( int i = 0; i < ( sizeof( commands ) / sizeof( commands[0] )); i++ ) {
    printf( "%-12s %s\r\n", commands[i].cmd, commands[i].help );
  }

  printf( "\r\n" );
}

/** Обработчик запроса информации об очереди
*/
void cmd_queue_info( int argc, char *argv[] ) {
  int index;
  char* end;

  if( argc != 3 ) { return; }
  index = strtol( argv[2], &end, 10 );
  if( index < 0 ) { return; }
  if( index >= ( sizeof( pqueue ) ) / sizeof( pqueue[0] )) { return; }

  char name[20];
  sprintf( name, "Queue %d", index );
  printf_queue_info( pqueue[index], name );
  printf_queue_data( pqueue[index] );

  printf( "\r\n" );
}

/** Установка значения элемента очереди
*/
void cmd_queue_set( int argc, char *argv[] ) {
  int index;
  int num;
  int value;
  char* end;

  if( argc != 5 ) { return; }

  index = strtol( argv[2], &end, 10 );
  if( index < 0 ) { return; }
  if( index >= ( sizeof( pqueue ) ) / sizeof( pqueue[0] ) ) { return; }

  num = strtol( argv[3], &end, 10 );
  if( num < 0 ) return;
  if( num >= QUEUE_LENGTH ) return;

  value = strtol( argv[4], &end, 10 );
  if(( value == LONG_MIN  ) || ( value == LONG_MAX  )) return;

  pqueue[index]->pdata[num].val = value;

  char name[20];
  sprintf( name, "Queue %d", index );
  printf_queue_info( pqueue[index], name );
  printf_queue_data( pqueue[index] );

  printf( "\r\n" );
}

/** Вывод значения элемента очереди
*/
void cmd_queue_get( int argc, char *argv[] ) {
  int index;
  int num;
  char* end;

  if( argc != 4 ) { return; }

  index = strtol( argv[2], &end, 10 );
  if( index < 0 ) { return; }
  if( index >= ( sizeof( pqueue ) ) / sizeof( pqueue[0] ) ) { return; }

  num = strtol( argv[3], &end, 10 );
  if( num < 0 ) return;
  if( num >= QUEUE_LENGTH ) return;

  printf( "Queue %d element %d - %d\r\n", index, num, pqueue[index]->pdata[num].val );

  printf( "\r\n" );
}

/** Обработчик запроса слияния очередей
*/
void cmd_queue_merge( int argc, char *argv[] ) {
  if( argc != 2 ) return;

  queue_t* result;
  result = create_queue( QUEUE_LENGTH * 2 );

  if( NULL == result ) {
     printf( "Error create queue\r\n");
     return;
  }

  for( int i = 0; i < QUEUE_LENGTH; i++ ) {
    result->pdata[i*2]    = pqueue[0]->pdata[i];
    result->pdata[i*2+1]  = pqueue[1]->pdata[i];
  }
  printf_queue_info( result, "Combined queue" );
  printf_queue_data( result );

  printf( "\r\n" );
}

/** Обработчик запроса тестирования бита
*/
void cmd_queue_test_bit( int argc, char *argv[] ) {
  int index;
  uint32_t mask;
  char* end;
  int count = 0;

  if( argc != 4 ) return;

  index = strtol( argv[2], &end, 10 );
  if( index < 0 ) { return; }
  if( index >= ( sizeof( pqueue ) ) / sizeof( pqueue[0] ) ) { return; }

  mask = strtol( argv[3], &end, 10 );
  if( mask > 31 ) return;
  mask = ( 1 << mask );

  printf( "Suitable items\r\n" );

  for( int i = 0; i < pqueue[index]->lenght; i++ ) {
    if( pqueue[index]->pdata[i].val & mask ) {
      printf( "element %d - %d\r\n", i, pqueue[index]->pdata[i].val );
      count++;
    }
  }
  printf( "Count of elements - %d\r\n", count );
}

char** str_split( char* a_str, const char a_delim ) {
  char** result    = 0;
  size_t count     = 0;
  char* tmp        = a_str;
  char* last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  /* Count how many elements will be extracted. */
  while ( *tmp ) {
    if ( a_delim == *tmp ) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < ( a_str + strlen( a_str ) - 1 );

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc( sizeof( char* ) * count );

  if ( result ) {
    size_t idx  = 0;
    char* token = strtok( a_str, delim );

    while ( token ) {
      assert( idx < count );
      *( result + idx++ ) = strdup( token );
      token = strtok( 0, delim );
    }
    assert( idx == count - 1 );
    *( result + idx ) = 0;
  }

  return result;
}

int main( int argc, char *argv[] ) {
  // Создание 1-й очереди
  pqueue[0] = create_queue( QUEUE_LENGTH );
  if( pqueue[0] == NULL ) {
    printf( "Error create queue1\r\nExit\r\n" );
    return 1;
  }

  // Создание 2-й очереди
  pqueue[1] = create_queue( QUEUE_LENGTH );
  if( pqueue[1] == NULL ) {
    printf( "Error create queue2\r\nExit\r\n" );
    return 1;
  }

  // Инициализация очередей
  for( int i = 0; i < QUEUE_LENGTH; i++ ) {
    queue_element_t elem;

    elem.val = i * 2;
    set_queue_element( pqueue[0], i, &elem );

    elem.val++;
    set_queue_element( pqueue[1], i, &elem );
  }

  if( argc > 1 ) {

    lover_case_string( argv[1] );

    for( int i = 0; i < ( sizeof( commands ) / sizeof( commands[0] )); i++ ) {
      if( 0 == strcmp( argv[1], commands[i].cmd ) ) {
        if( NULL != commands[i].cmd_fun ) {
          commands[i].cmd_fun( argc, argv );
        }
        break;
      }
    }
  }

//  while( 1 ) {
//    char st[128];
//
//    printf( ">" );
//
//    fgets( st, sizeof( st ), stdin );
//
//    char** tokens;
//    tokens = str_split( st, ',' );
//
//    lover_case_string( tokens[0] );
//
//    if( 0 == strcmp( tokens[0], "exit\n" )) {
//      break;
//    }
//  }

  for( uint32_t i = 0; i < ( sizeof( pqueue ) ) / sizeof( pqueue[0] ); i++ ) {
    if( NULL != pqueue[i] ) { free_queue( pqueue[i] ); }
  }

  printf( "Exit from app\r\n" );
  return 0;
}
