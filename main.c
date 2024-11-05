#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // KVS 열기
    kvs_t* kvs = open();
    if (!kvs) {
        printf("Failed to open KVS\n");
        return -1;
    }

    // 랜덤 시드 고정 (필요에 따라 삭제 가능)
    srand(42);

    // query.dat 파일 열기
    FILE* query_file = fopen("query.dat", "r");
    if (!query_file) {
        printf("Failed to open query.dat\n");
        close(kvs);
        return -1;
    }

    // answer.dat 파일 생성 및 열기
    FILE* answer_file = fopen("answer.dat", "w");
    if (!answer_file) {
        printf("Failed to open answer.dat\n");
        fclose(query_file);
        close(kvs);
        return -1;
    }

    // query.dat에서 한 줄씩 읽어 처리
    char operation[10];
    char key[100];
    char value[100];
    while (fscanf(query_file, "%[^,],%[^,],%s\n", operation, key, value) != EOF) {
        if (strcmp(operation, "set") == 0) {
            // set 연산 수행
            put(kvs, key, value);  // 값 저장, 성공 여부를 출력하지 않음
        } else if (strcmp(operation, "get") == 0) {
            // get 연산 수행
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "%s\n", result);  // 찾은 값을 기록
                // get 함수에서 메모리 할당을 하지 않으므로 free 불필요
            } else {
                fprintf(answer_file, "-1\n");  // 찾지 못한 경우 -1 기록
            }
        }
    }

    // 파일 닫기
    fclose(query_file);
    fclose(answer_file);

    // KVS 닫기
    close(kvs);

    return 0;
}
