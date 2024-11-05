#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 난수를 생성하여 새로운 노드의 레벨을 결정하는 함수
static int random_level(int max_level) {
    int level = 0;
    while ((rand() % 2) && level < max_level - 1) {
        level++;
    }
    return level;
}

// Skip List에 Key-Value 쌍을 삽입하는 함수
int put(kvs_t* kvs, const char* key, const char* value) {
    if (kvs == NULL || key == NULL || value == NULL) {
        return -1;  // 잘못된 인자가 들어오면 실패 반환
    }

    node_t* update[MAX_LEVEL];
    node_t* current = kvs->head;

    // 상위 레벨부터 탐색하여 삽입 위치를 찾음
    for (int i = kvs->current_level; i >= 0; --i) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;  // 삽입 지점을 저장
    }

    // 레벨 0에서 다음 노드 검사
    current = current->forward[0];
    if (current != NULL && strcmp(current->key, key) == 0) {
        // Key가 이미 존재하면 Value를 업데이트
        free(current->value);
        current->value = (char*)malloc(strlen(value) + 1);
        if (current->value == NULL) {
            printf("Failed to malloc\n");
            return -1;
        }
        strcpy(current->value, value);
        return 0;
    }

    // Key가 존재하지 않으면 새로운 노드를 삽입
    int new_level = random_level(kvs->max_level);
    if (new_level > kvs->current_level) {
        for (int i = kvs->current_level + 1; i <= new_level; ++i) {
            update[i] = kvs->head;
        }
        kvs->current_level = new_level;
    }

    // 새로운 노드 생성
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Failed to malloc\n");
        return -1;
    }
    strcpy(new_node->key, key);

    new_node->value = (char*)malloc(strlen(value) + 1);
    if (new_node->value == NULL) {
        free(new_node);
        printf("Failed to malloc\n");
        return -1;
    }
    strcpy(new_node->value, value);

    new_node->forward = (node_t**)malloc(kvs->max_level * sizeof(node_t*));
    if (new_node->forward == NULL) {
        free(new_node->value);
        free(new_node);
        printf("Failed to malloc\n");
        return -1;
    }

    // 새로운 노드를 연결
    for (int i = 0; i <= new_level; ++i) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    // 상위 레벨의 포인터는 NULL로 초기화
    for (int i = new_level + 1; i < kvs->max_level; ++i) {
        new_node->forward[i] = NULL;
    }

    kvs->items++;  // 항목 수 증가
    printf("put: %s, %s\n", key, value);
    return 0;
}
