#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Skip List에서 key에 해당하는 value를 검색하는 함수
char* get(kvs_t* kvs, const char* key) {
    if (kvs == NULL || key == NULL) {
        return NULL;  // KVS나 key가 NULL일 경우 NULL 반환
    }

    node_t* current = kvs->head;  // 헤드 노드에서 시작

    // 상위 레벨부터 시작하여 탐색
    for (int i = kvs->current_level; i >= 0; --i) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];  // 해당 레벨에서 다음 노드로 이동
        }
    }

    // 레벨 0에서 다음 노드를 검사하여 key를 찾음
    current = current->forward[0];
    if (current != NULL && strcmp(current->key, key) == 0) {
        // Key를 찾았을 경우, value를 복사하여 반환
        char* value = (char*)malloc(strlen(current->value) + 1);
        if (value == NULL) {
            printf("Failed to malloc\n");
            return NULL;
        }
        strcpy(value, current->value);
        return value;
    }

    // Key를 찾지 못한 경우 NULL 반환
    return NULL;
}
