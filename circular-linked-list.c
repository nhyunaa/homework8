/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { 
	int key; // 정수형 변수 key
	struct Node* llink; // 구조체 포인터 llink선언
	struct Node* rlink; // 구조체 포인터 rlink선언
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
        printf("[----- [노현아] [2022041065] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 입력받기

		switch(command) { 
		case 'z': case 'Z': // 입력받은 command가 z이거나 Z일때
			initialize(&headnode); // initialize함수 호출
			break;
		case 'p': case 'P': // 입력받은 command가 p이거나 P일때
			printList(headnode);// printList함수 호출
			break;
		case 'i': case 'I': // 입력받은 command가 i이거나 I일때
			printf("Your Key = ");
			scanf("%d", &key); // key값을 입력받기
			insertNode(headnode, key); // insertNode함수 호출
			break;
		case 'd': case 'D': // 입력받은 command가 d이거나 D일때
			printf("Your Key = ");
			scanf("%d", &key); //key값을 입력받기
			deleteNode(headnode, key);//deleteNode함수 호출
			break;
		case 'n': case 'N': // 입력받은 command가 n이거나 N일때
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받기
			insertLast(headnode, key);//insertLast함수 호출
			break;
		case 'e': case 'E': // 입력받은 command가 e이거나 E일때
			deleteLast(headnode);//deleteLast함수 호출
			break;
		case 'f': case 'F': // 입력받은 command가 f이거나 F일때
			printf("Your Key = ");
			scanf("%d", &key);//key 값입력받기
			insertFirst(headnode, key);//insertFirst함수 호출
			break;
		case 't': case 'T': // 입력받은 command가 t이거나 T일때
			deleteFirst(headnode); // deleteFirst함수 호출
			break;
		case 'r': case 'R': // 입력받은 command가 r이거나 R일때
			invertList(headnode); // invertList함수 호출
			break;
		case 'q': case 'Q': // 입력받은 command가 q이거나 Q일때
			freeList(headnode);//freeList함수 호출
			break;
		default: // 이외의 command를 입력받았을때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//>>>>>   Concentration!!   <<<<< 출력
			break;
		}

	}while(command != 'q' && command != 'Q');// 입력받은 command가 q그리고 Q가 아니라면 반복함

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; // headNode를 headNode의 rlink값에 대입
	(*h)->llink = *h;// headNode를 headNode의 llink값에 대입
	(*h)->key = -9999; // headNode의 key값을 -9999로 초기화
	return 1; // 1반환
}

int freeList(listNode* h){

	if(h->rlink == h) // headNode와 headNode의 rlink값이 같을경우
	{
		free(h); // h동적메모리 할당해제
		return 1;//1반환
	}

	listNode* p = h->rlink; //headNode의 rlink값을 구조체 포인터 p에 저장

	listNode* prev = NULL; //구조체포인터 prev를 NULL값으로 초기화
	while(p != NULL && p != h) {// p가 NULL이거나 p가 headNode를 가리키는 경우 반복문종료
		prev = p;//p값을 prev에 대입
		p = p->rlink;//p의 rlink값을 p에 대입한다
		free(prev);//prev동적메모리 할당해제
	}
	free(h);//h동적메모리 할당 해제
	return 0;//0반환
}



void printList(listNode* h) {
	int i = 0; //정수형변수 i선언 및 초기화
	listNode* p; // 구조체포인터 p선언

	printf("\n---PRINT\n");

	if(h == NULL) { // h가 비어있을때
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//h의 rlink값을 p에 대입

	while(p != NULL && p != h) { //p의 값이 NULL이 아니고 p의 값이 h의 값이 아닐때
		printf("[ [%d]=%d ] ", i, p->key); // i와 p의 key값을 출력
		p = p->rlink;//p의 rlink값을 p에 저장
		i++;//i증가
	}
	printf("  items = %d\n", i);//i값출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//h의 llink값과 h,h의 rlink의 주소출력

	i = 0; //i에 0대입
    p = h->rlink;//h의 rlink값을 p에 대입
	while(p != NULL && p != h) { // p가 NULL 이아니고 p가 h가 아닐때
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//i,p의 key,p의 llink,p,p의 rlink출력
		p = p->rlink;//p의 rlink값을 p에 대입
		i++;//i증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // h가 NULL이라면 -1반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node에 대해 동적메모리 할당
	node->key = key; // key값을 node의 key 값에 대입
	node->rlink = NULL; // node의 rlink값을 NULL로 초기화
	node->llink = NULL; // node의 llink값을 NULL로 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{//h와 h의 rlink값이 같을때
		h->rlink = node; // node값을 h의 rlink값에 대입
		h->llink = node; // node값을 h의 llink값에 대입
		node->rlink = h; // h값을 node의 rlink에 대입
		node->llink = h; // h값을 node의 llink에 대입
	} else {//h와 h의 rlink값이 같지않을때
		h->llink->rlink = node; // node값을 h의 llink의 rlink에 대입
		node->llink = h->llink;//h의 llink값을 node의 llink값에 대입
		h->llink = node; // node값을 h의 llink값에 대입
		node->rlink = h;//h값을 node의 rlink값에 대입
	}

	return 1; //1반환
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // h의 llink값이 h와 같거나 h값이 NULL이라면
	{
		printf("nothing to delete.\n"); // 출력후 1반환
		return 1;
	}

	listNode* nodetoremove = h->llink; // h의 llink를 구조체포인터 nodetoremove에 저장

	/* link 정리 */
	nodetoremove->llink->rlink = h; // h를 nodetoremove의 llink의 rlink에 저장
	h->llink = nodetoremove->llink; // nodetoremove의 llink를 h의 llink에 저장

	free(nodetoremove); // nodetoremove동적할당해제

	return 1; // 1 반환
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node동적메모리할당
	node->key = key; // key값을 node의 key 값에 대입
	node->rlink = NULL; // node의 rlink값을 NULL로 초기화
	node->llink = NULL; // node의 llink값을 NULL로 초기화

	node->rlink = h->rlink; // h의 rlink값을 node의 rlink값에 대입
	h->rlink->llink = node; // h의 rlink의 llink값을 node값으로 바꿈
	node->llink = h; // h값을 node의 llink값에 대입
	h->rlink = node; // node를 h의 rlink값에 대입


	return 1; // 1반환
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // h가 NULL이거나 h의 rlink값이 h라면
	{
		printf("nothing to delete.\n");
		return 0; // 0반환
	}

	listNode* nodetoremove = h->rlink;// h의 rlink값을 구조체 포인터 nodetormove에 저장

	/* link 정리 */
	nodetoremove->rlink->llink = h;//첫번째노드의 다음노드 llink와 헤드 노드 연결
	h->rlink = nodetoremove->rlink;//헤드노드의 rlink에 첫번째 노드의 rlink 입력

	free(nodetoremove);// nodetoremove메모리 할당해제

	return 1; // 1반환

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { // h의 rlink값이 h와 동일하거나 h값이 NULL이라면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //h의 rlink값을 구조체 포인터 n에 대입
	listNode *trail = h; // h의 값을 구조체 포인터 trail에 대입
	listNode *middle = h; // h의 값을 구조체 포인터 middle에 대입

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;//헤드노드의 rlink와 llink를 같게해줌

	while(n != NULL && n != h){
		trail = middle;//trail에 middle대입
		middle = n;//middle에 n대입
		n = n->rlink;//n에 n의 다음노드 대입
		middle->rlink = trail;//middle노드의 rlink를 trail을 연결
		middle->llink = n;//middle노드의 llink를 n을 연결
	}

	h->rlink = middle;//헤드노드의rlink를 middle연결

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 노드를 메모리할당해줌
	node->key = key;//노드의 key값에 입력받은 key값 대입
	node->llink = node->rlink = NULL;//새로운 노드의 rlink와 llink는 NULL

	if (h->rlink == h)//헤드노드의 rlink가 헤드노드를 가르키면 //즉 노드가 없으면
	{
		insertFirst(h, key);//노드가 없으므로 첫번째에 노드 삽입
		return 1;
	}

	listNode* n = h->rlink;//n은 첫번째노드 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {//n노드의 key값이 입력받은 key값보다 크거나 같은경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {//n노드가 첫번째 노드인경우
				insertFirst(h, key);//첫번째에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//새로운노드 의 rlink가 n을 가르킴
				node->llink = n->llink;//새로운노드의 llink에 n의llink 대입
				n->llink->rlink = node;//n노드의 이전노드 rlink가 새로운 노드를 가르킴
				n->llink = node;//n노드의 이전노드가 새로운 노드를 가르킴
			}
			return 0;
		}

		n = n->rlink;//n은 n노드의다음노드로 바꿔줌
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}





/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;//n은 첫번째노드 

	while(n != NULL && n != h) {
		if(n->key == key) {//n의 key값이랑 입력받은 key값이랑 같으면
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n노드의 이전노드 rlink가 n노드의 rlink가르킴
				n->rlink->llink = n->llink;//n노드의 다음도느 llink가 n노드의 llink가르킴
				free(n);
			}
			return 0;
		}

		n = n->rlink;//n은 n노드의다음노드로 바꿔줌
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}