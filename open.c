#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvs_t* open() {
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));

    if (kvs) {
        kvs->items = 0;
        kvs->max_level = MAX_LEVEL;
        kvs->current_level = 0;

        // 헤드 노드 초기화
        kvs->head = (node_t*)malloc(sizeof(node_t));
        if (kvs->head == NULL) {
            free(kvs);  // 메모리 할당 실패 시 kvs 해제
            return NULL;
        }

        // 헤드 노드의 필드 초기화
        kvs->head->key[0] = '\0';  // 빈 키로 초기화
        kvs->head->value = NULL;    // Value는 NULL로 초기화
        kvs->head->forward = (node_t**)malloc(kvs->max_level * sizeof(node_t*));
        if (kvs->head->forward == NULL) {
            free(kvs->head);  // 메모리 할당 실패 시 해제
            free(kvs);
            return NULL;
        }

        // 모든 레벨의 forward 포인터를 NULL로 초기화
        for (int i = 0; i < kvs->max_level; ++i) {
            kvs->head->forward[i] = NULL;
        }
        printf("Open: kvs has %d items\n", kvs->items);
    }
    return kvs;
}
