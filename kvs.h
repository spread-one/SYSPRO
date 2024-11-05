#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//최대 레벨
#define MAX_LEVEL 20

struct node {
	char key[100]; 		// key를 저장할 문자 배열
	char* value; 		//value를 가리키는 포인터
	struct node** forward; 	//Skip List 구현을 위해 다중 레벨 포인터 배열 사용
};	
typedef struct node node_t; //별칭


struct kvs{
	struct node* head; // Key-Value 쌍을 저장하는 linked list의 시작 포인터
	int items; // 저장된 데이터 항목의 개수
	int max_level; //Skip List의 최대 레벨
	int current_level; //현재 사용 중인 최대 레벨
};
typedef struct kvs kvs_t; 


kvs_t* open(); // KVS 초기화
int close(kvs_t* kvs); // 모든 메모리 해제
int put(kvs_t* kvs, const char* key, const char* value); // KVS에 Key-Value 쌍을 저장하는 함수
char* get(kvs_t* kvs, const char* key); // Key에 해당하는 Value를 검색하는 함수
