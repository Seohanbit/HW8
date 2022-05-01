/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;                                         //이중 연결리스트를 동그랗게 해놓은 거랑 비슷함
	struct Node* rlink;                                         //대신에 따로 first가 없고 -9999값이 들어가있는 headnode가 있을 뿐
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

    printf("[-----[Seo han bit]   [2019038043]-----]\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
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
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));                   //메모리를 할당한 후에 
	(*h)->rlink = *h;                                           //따로 NULL값이 아닌 자기 자신을 가리킴
	(*h)->llink = *h;
	(*h)->key = -9999;                                          //headnode의 값에는 -9999를 넣어서 headnode보다 작은 값이 없게끔하는 보여주기식 설정
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	if(h->rlink == h)
	{
		free(h);                                                //headnode가 자기 자신을 가리키고 있으면 노드가 없다는 의미 이므로 headnode만 메모리 해제
		return 1;
	}

	listNode* p = h->rlink;                                     //p가 headnode가 가리키는 곳이 되게 함

	listNode* prev = NULL;                                      //p가 되게 할 포인터 prev를 NULL로 초기화
	while(p != NULL && p != h) {
		prev = p;                                               //prev를 p가 되게 하고 p를 다음 노드로 바꿔주면서 prev 메모리 해제
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));               //새로운 node에 메모리 할당 해주면서 rlink와 llink를 NULL로 초기화
	node->key = key;                                                    //받아온 key값을 node에 넣어줌
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node;                                                //아무 node도 없었을 경우 headnode와 새로운 node가 서로를 가리키게 함
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {            
		h->llink->rlink= node;                                          //headnode의 llink는 마지막 node를 가리키고 있기 때문에 마지막 node의 rlink가 새로운 node를 가리키게 함
		node->llink = h->llink;                                         //node의 llink를 headnode가 가리키던 마지막 node를 가리키게 함
		h->llink = node;                                                //다시 headnode의 llink를 마지막 node가 될 새로운 node를 가리키게 함
		node->rlink = h;                                                //마지막 node의 rlink는 다시 headnode를 가리켜야 함
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {


	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");                                  //전처리기
		return 1;
	}

	listNode* nodetoremove = h->llink;                                   //nodetoremove가 headnode가 가리키던 마지막 node가 되게 함

	/* link 정리 */
	nodetoremove->llink->rlink = h;                                      //마지막 node의 rlink가 headnode를 가리키게 함
	h->llink = nodetoremove->llink;                                      //headnode의 llink가 마지막 node의 전 node를 가리키게 함

	free(nodetoremove);                                                  //마지막 node 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {


	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;                                             //node의 rlink를 원래 headnode의 rlink가 가리키던 곳을 가리키게 함
	h->rlink->llink = node;                                             //headnode가 가리키던 다음 node의 llink가 첫 노드가 될 새로운 node를 가리키게 함
	node->llink = h;                                                    //새로운 node의 llink를 headnode를 가리키게 함
	h->rlink = node;                                                    //headnode의 rlink를 첫 node가 될 새로운 node를 가리키게 함


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");                                 //전처리기
		return 0;
	}

	listNode* nodetoremove = h->rlink;                                  //nodetoremove를 headnode가 가리키던 첫 노드가 되게 함

	/* link 정리 */
	nodetoremove->rlink->llink = h;                                     //첫 node의 다음 node의 llink가 headnode를 가리키게 함
	h->rlink = nodetoremove->rlink;                                     //headnode의 rlink가 첫 node를 건너뛰고 다음 node를 가리키게 함

	free(nodetoremove);                                                 //메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;                        //마지막 node를 가리켰던 llink를 첫 node를 가리키게 함

	while(n != NULL && n != h){
		trail = middle;                         //trail이 middle이 되게 함
		middle = n;                             //middle이 trail이 되게 함
		n = n->rlink;                           //n이 다음 node가 되게 함
		middle->rlink = trail;                  //n과 trail사이의 node의 rlink와 llink의 가리키는 방향을 바꿔 줌
		middle->llink = n;
	}

	h->rlink = middle;                          //n이 headnode가 되었을 때 headnode의 rlink를 첫 노드가 될 middle node를 가리키게 함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)                                                      //node가 아무것도 없을 경우 insertFirst 함수 호출해서 첫 node로 넣어줌
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;                                                 //n을 headnode의 rlink가 가리키던 곳이 되게 함

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {                                             //똑같이 node가 없어서 headnode가 자기 자신을 가리키고 있을 경우 첫 노드로 만듬
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;                                            //n의 바로 전 node가 될 새로운 node의 rlink가 n을 가리키게 함
				node->llink = n->llink;                                     //새로운 node의 llink가 원래 n의 전 node였던 node를 가리키게 함
				n->llink->rlink = node;                                     //n의 전 node였던 node의 rlink가 사이에 들어갈 새로운 node를 가리키게 함
				n->llink = node;                                            //n의 llink가 새로운 node를 가리키게 함
			}
			return 0;
		}

		n = n->rlink;                                                       //조건에 맞지 않을 경우 다음 노드가 되게 함
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
		printf("nothing to delete.\n");                                     //전처리기
		return 0;
	}

	listNode* n = h->rlink;                                                 //n이 headnode가 가리키는 곳이 되게 함

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */                   //첫 노드인 경우 deleteFirst 함수 호출해서 node 삭제
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */              //마지막 node인 경우 deleteLast 함수 호출해서 node 삭제
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;                                 //삭제해야할 node의 전 node의 rlink가 다음 node를 가리키게 함
				n->rlink->llink = n->llink;                                 //삭제해야할 node의 다음 node의 llink가 전 node를 가리키게 함
				free(n);                                                    //node 삭제
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);                     //삭제할 key 값을 찾지 못하면 못찾았다고 출력
	return 0;
}


