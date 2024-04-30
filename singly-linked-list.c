/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { // Node 구조체 정의
	int key; // key값을 저장할 변수
	struct Node* link; // 다음 노드를 가리킬 포인터
} listNode; // 구조체 이름을 listNode로 정의

typedef struct Head { // Head 구조체 정의
	struct Node* first; // 첫번째 노드를 가리킬 포인터
} headNode; // 구조체 이름을 headNode로 정의


/* 함수 리스트 */
headNode* initialize(headNode* h); 
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; // 사용자로부터 입력받을 명령어를 저장할 변수
	int key; // 사용자로부터 입력받을 key값을 저장할 변수
	headNode* headnode=NULL; // headNode 구조체 포인터 변수를 NULL로 초기화

	printf("-----[HanKangmin] [2023078040]-----\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 사용자로부터 명령어를 입력받음

		switch(command) { 
		case 'z': case 'Z':
			headnode = initialize(headnode); // headnode를 초기화
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트를 출력
			break;
		case 'i': case 'I':
			printf("Your Key = "); // 사용자로부터 key값을 입력받음
			scanf("%d", &key);
			insertNode(headnode, key); // key값을 가진 노드를 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = "); // 사용자로부터 key값을 입력받음
			scanf("%d", &key);
			deleteNode(headnode, key); // key값을 가진 노드를 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = "); // 사용자로부터 key값을 입력받음
			scanf("%d", &key);
			insertLast(headnode, key); // 리스트의 마지막에 key값을 가진 노드를 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 리스트의 마지막 노드를 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = "); // 사용자로부터 key값을 입력받음
			scanf("%d", &key);
			insertFirst(headnode, key); // 리스트의 첫번째에 key값을 가진 노드를 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 리스트의 첫번째 노드를 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 리스트의 링크를 역순으로 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode); // 리스트의 메모리를 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 잘못된 명령어를 입력하면 Concentration!! 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // q나 Q를 입력받으면 종료

	return 1; 
}

// 리스트를 초기화하는 함수
headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

// 리스트의 메모리를 해제하는 함수
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	// 리스트의 모든 노드를 돌면서 메모리 해제
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	// 새로운 노드를 위한 메모리를 동적 할당하여 메모리 주소를 node에 저장
	node->key = key; // node의 key값을 입력받은 key값으로 설정

	node->link = h->first; // node의 link를 headnode의 first가 가리키는 노드로 설정
	// 새 노드는 현재 리스트의 첫 번째 노드 앞에 위치하게 됨
	h->first = node; // headnode의 first가 새로운 노드를 가리키도록 설정

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 위한 메모리 할당
	node->key = key; // 새 노드의 key값 설정
	node->link = NULL; // 새 노드의 link를 NULL로 초기화

	// 리스트가 비어있거나 첫번째 노드의 key값이 입력받은 key값보다 크거나 같으면
	if(h->first == NULL || h->first->key >= key) {
		node->link = h->first; // 새 노드의 link를 headnode의 first가 가리키는 노드로 설정
		h->first = node; // headnode의 first가 새 노드를 가리키도록 설정
		return 0; 
	}

	// 노드를 삽입할 위치 찾기
	listNode* current = h->first; // 현재 노드를 첫 번째 노드로 시작
	listNode* previous = NULL; // 이전 노드 초기화

	// 현재 노드의 key가 입력받은 key보다 작은 동안 반복
	while(current != NULL && current->key < key) {
		previous = current; // 이전 노드를 현재 노드로 업데이트
		current = current->link; // 현재 노드를 다음 노드로 설정
	}

	// 노드 삽입
	node->link = current; // 새 노드의 link를 현재 노드로 설정
	previous->link = node; // 이전 노드의 link를 새 노드로 설정

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 위한 메모리 할당
	node->key = key;
	node->link = NULL;

	if(h->first == NULL) { // 리스트가 비어있으면
		h->first = node; // headnode의 first가 새 노드를 가리키도록 설정
	}
	else {
		listNode* current = h->first; // 현재 노드를 헤드노드로 설정
		// 현재 노드가 마지막 노드가 될 때까지 반복
		// 마지막 노드는 link가 NULL인 노드
		while(current->link != NULL) {
			current = current->link; // 다음 노드로 이동
		}
		current->link = node; // 마지막 노드의 link를 새 노드로 설정
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first == NULL) { // 리스트가 비어있으면
		printf("There is no node to delete.\n"); // 삭제할 노드가 없음
		return -1; // 리스트가 비어있으므로 -1을 반환하여 실패를 나타냄
	}

	listNode* nodeToDelete = h->first; // 삭제할 노드를 가리킬 포인터
	h->first = nodeToDelete->link; // 첫 번째 노드를 다음 노드로 변경

	free(nodeToDelete); // 삭제할 노드의 메모리 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL) { // 리스트가 비어있으면
		printf("There is no node to delete.\n"); // 삭제할 노드가 없음
		return -1; // -1 반환
	}

	// 삭제할 노드 찾기
	listNode* current = h->first; // 현재 노드를 첫 번째 노드로 설정
	listNode* previous = NULL; // 이전 노드 초기화

	// key값이 일치하는 노드를 찾을 때까지 반복
	while(current != NULL && current->key != key) {
        previous = current; // 이전 노드를 현재 노드로 업데이트
        current = current->link; // 다음 노드로 이동
    }

	// key값이 일치하는 노드가 없으면
    if(current == NULL) {
        printf("There is no node to delete with key %d.\n", key); // 삭제할 노드가 없음
        return -1; // -1 반환
    }

	// key값이 일치하는 노드를 찾았을 때(찾은 노드가 리스트의 첫 번째 노드일 경우)
    if(previous == NULL) {
        h->first = current->link; // 첫 번째 노드를 삭제 노드의 다음 노드로 변경
    } 
	else {
        previous->link = current->link; 
		// 이전 노드의 link를 삭제 노드의 다음 노드로 변경하여 리스트에서 현재 노드를 제거

    }

    free(current); // 삭제할 노드의 메모리 해제

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL) { // 리스트가 비어있으면 삭제할 노드가 없다는 메시지 출력
		printf("There is no node to delete.\n");
		return -1;
	}

	// 마지막 노드 찾기
	listNode* current = h->first; 
	listNode* previous = NULL; 

	// 마지막 노드를 찾을 때까지 반복(마지막 노드는 link가 NULL인 노드)
	while(current->link != NULL) {
		previous = current; // 이전 노드를 현재 노드로 업데이트
		current = current->link; // 다음 노드로 이동
	}

	// 마지막 노드 삭제
	if(previous == NULL) { // 리스트에 노드가 하나만 있는 경우
		h->first = NULL; // 헤드 노드를 NULL로 설정하여 리스트를 비움
	} 
	else {
		previous->link = NULL;
		// 마지막 노드의 이전 노드의 link를 NULL로 설정하여 리스트에서 마지막 노드를 제거
	}

	free(current); // 마지막 노드의 메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL) { // 리스트가 비어있으면
		printf("There is no node to invert.\n"); // 역순으로 재배치할 노드가 없음
		return -1;
	}

	// 리스트의 링크를 역순으로 재배치
	listNode* current = h->first; // 현재 노드를 첫 번째 노드로 설정
	listNode* previous = NULL; // 이전 노드 초기화
	listNode* next = NULL; // 다음 노드 초기화

	// 현재 노드가 NULL이 될 때까지 반복(리스트의 링크를 역순으로 재배치)
	while(current != NULL) {
		next = current->link; // 현재 노드의 다음 노드를 next에 저장
		current->link = previous; // 현재 노드의 link를 이전 노드로 설정하여 역순으로 재배치
		previous = current; // 이전 노드를 현재 노드로 업데이트
		current = next; // 다음 노드로 이동
	}

	h->first = previous; 
	// 헤드 노드가 가리키는 노드를 역순으로 재배치된 리스트의 첫 번째 노드로 설정

	return 0;
}

// 리스트를 출력하는 함수
void printList(headNode* h) {
	int i = 0; // 리스트의 노드의 개수를 저장할 변수
	listNode* p; // 리스트의 노드를 가리킬 포인터

	printf("\n---PRINT\n");

	if(h == NULL) { // 리스트가 비어있으면 Nothing to print.... 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p가 리스트의 첫번째 노드를 가리키도록 설정

	// 리스트의 모든 노드 출력
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); // 노드의 key값 출력
		p = p->link; // 다음 노드로 이동
		i++; // 노드의 개수 증가
	}

	printf("  items = %d\n", i); // 리스트의 노드의 개수 출력
}