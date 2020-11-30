
/** \file   queue.h
*   \author Alex
*   \date   30.11.2020
*
* Реализация очереди
*/

#pragma once

#include <stdint.h>

/** Тип элемента очереди
*/
typedef struct {
  uint32_t  val;
} queue_element_t;

/** Описание типа очереди
*/
typedef struct {
  uint32_t          lenght;
  queue_element_t*  pdata;
} queue_t;

/** Инициализация очереди
* \param  length      - длина очереди
* \param  buffer      - указатель на буфер для элементов очереди
* \return             - указатель на экземпляр очереди либо NULL в случае ошибки
*/
queue_t* create_queue( uint32_t length );

void free_queue( queue_t* pqueue );

/** Чтение элемента из очереди
* \param  pqueue      - указатель на экземпляр очереди
* \param  index       - номер элемента
* \return             - указатель на экземпляр элемента либо NULL в случае ошибки
*/
queue_element_t* get_queue_element( queue_t* pqueue, int32_t index );

/** Запись элемента очереди
* \param  pqueue      - указатель на экземпляр очереди
* \param  index       - номер элемента
* \param  pelement    - указатель на значение элемента
* \return             - указатель на экземпляр элемента либо NULL в случае ошибки
*/
int32_t set_queue_element(  queue_t* pqueue, int32_t index, queue_element_t* pelement );
