
/** \file   queue.h
*   \author Alex
*   \date   30.11.2020
*
* ���������� �������
*/

#pragma once

#include <stdint.h>

/** ��� �������� �������
*/
typedef struct {
  uint32_t  val;
} queue_element_t;

/** �������� ���� �������
*/
typedef struct {
  uint32_t          lenght;
  queue_element_t*  pdata;
} queue_t;

/** ������������� �������
* \param  length      - ����� �������
* \param  buffer      - ��������� �� ����� ��� ��������� �������
* \return             - ��������� �� ��������� ������� ���� NULL � ������ ������
*/
queue_t* create_queue( uint32_t length );

void free_queue( queue_t* pqueue );

/** ������ �������� �� �������
* \param  pqueue      - ��������� �� ��������� �������
* \param  index       - ����� ��������
* \return             - ��������� �� ��������� �������� ���� NULL � ������ ������
*/
queue_element_t* get_queue_element( queue_t* pqueue, int32_t index );

/** ������ �������� �������
* \param  pqueue      - ��������� �� ��������� �������
* \param  index       - ����� ��������
* \param  pelement    - ��������� �� �������� ��������
* \return             - ��������� �� ��������� �������� ���� NULL � ������ ������
*/
int32_t set_queue_element(  queue_t* pqueue, int32_t index, queue_element_t* pelement );
