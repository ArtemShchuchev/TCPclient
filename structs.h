#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <QTime>

#define ID 0xFFFE
#define TYPE_REQ 10
#define TYPE_ANS 20

;
#pragma pack(push, 1)

/*
 * Общий формат сообщений
 * Заголовок сообщения -> Данные
 */

// Формат сообщений
enum Messages
{
    GET_TIME   = 100,   // Запрос текущего времени (QDateTime)
    GET_SIZE   = 101,   // Запрос свободного места на сервере (uint32_t)
    GET_STAT   = 102,   // Запрос статистики
    SET_DATA   = 200,   // Передача строки на сервер (QString)
    CLEAR_DATA = 201    // Освободить место на сервере (Ответ заголовком со статусом 1)
};

// Типы ошибок
enum StatusMessages
{
    STATUS_SUCCES = 1,

    ERR_NO_FREE_SPACE = 10, // Недостаточно свободного места
    ERR_CONNECT_TO_HOST = 11,

    ERR_NO_FUNCT = 20       // Функционал не реализован
};

/*!
 * \brief Стрктура описывает служебный заголовок пакета
 */
// Формат заголовка сообщения
struct ServiceHeader
{
    uint16_t id = ID;     // Идентификатор начала пакета
    uint16_t idData = 0;  // Идентификатор типа данных
    uint8_t status = 0;   // Статус обработки сообщения (запрос/ответ)
    uint32_t len = 0;     // Длина пакета далее, байт
};

// Формат ответа статистики сервера
struct StatServer
{
    StatServer()
    {
        memset(this, 0, sizeof(*this));
    }

    uint32_t incBytes;  //принято байт
    uint32_t sendBytes; //передано байт
    uint32_t revPck;    //принто пакетов
    uint32_t sendPck;   //передано пакетов
    uint32_t workTime;  //Время работы сервера секунд
    uint32_t clients;   //Количество подключенных клиентов
};

#pragma pack(pop)
#endif // STRUCTS_H
