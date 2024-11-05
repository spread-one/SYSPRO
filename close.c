#include "kvs.h"
#include <stdlib.h>

// Skip List의 모든 노드와 KVS 구조체의 메모리를 해제하는 함수
int close(kvs_t* kvs) {
    if (kvs == NULL) {
        return -1;  // kvs가 NULL일 경우 실패 코드 반환
    }

    // Skip List의 모든 노드를 해제
    node_t* current = kvs->head;
    while (current != NULL) {
        node_t* next = current->forward[0];  // 다음 노드를 저장
        free(current->value);                // 노드의 value 메모리 해제
        free(current->forward);              // forward 배열 해제
        free(current);                       // 노드 자체 해제
        current = next;                      // 다음 노드로 이동
    }

    // KVS 구조체 해제
    free(kvs);

    return 0;  // 성공적으로 메모리 해제
}
