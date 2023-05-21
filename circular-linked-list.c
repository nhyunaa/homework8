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
/* �ʿ��� ������� �߰� */

typedef struct Node { 
	int key; // ������ ���� key
	struct Node* llink; // ����ü ������ llink����
	struct Node* rlink; // ����ü ������ rlink����
} listNode;

/* �Լ� ����Ʈ */
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
        printf("[----- [������] [2022041065] -----]\n");
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
		scanf(" %c", &command); // command �Է¹ޱ�

		switch(command) { 
		case 'z': case 'Z': // �Է¹��� command�� z�̰ų� Z�϶�
			initialize(&headnode); // initialize�Լ� ȣ��
			break;
		case 'p': case 'P': // �Է¹��� command�� p�̰ų� P�϶�
			printList(headnode);// printList�Լ� ȣ��
			break;
		case 'i': case 'I': // �Է¹��� command�� i�̰ų� I�϶�
			printf("Your Key = ");
			scanf("%d", &key); // key���� �Է¹ޱ�
			insertNode(headnode, key); // insertNode�Լ� ȣ��
			break;
		case 'd': case 'D': // �Է¹��� command�� d�̰ų� D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //key���� �Է¹ޱ�
			deleteNode(headnode, key);//deleteNode�Լ� ȣ��
			break;
		case 'n': case 'N': // �Է¹��� command�� n�̰ų� N�϶�
			printf("Your Key = ");
			scanf("%d", &key); // key ���� �Է¹ޱ�
			insertLast(headnode, key);//insertLast�Լ� ȣ��
			break;
		case 'e': case 'E': // �Է¹��� command�� e�̰ų� E�϶�
			deleteLast(headnode);//deleteLast�Լ� ȣ��
			break;
		case 'f': case 'F': // �Է¹��� command�� f�̰ų� F�϶�
			printf("Your Key = ");
			scanf("%d", &key);//key ���Է¹ޱ�
			insertFirst(headnode, key);//insertFirst�Լ� ȣ��
			break;
		case 't': case 'T': // �Է¹��� command�� t�̰ų� T�϶�
			deleteFirst(headnode); // deleteFirst�Լ� ȣ��
			break;
		case 'r': case 'R': // �Է¹��� command�� r�̰ų� R�϶�
			invertList(headnode); // invertList�Լ� ȣ��
			break;
		case 'q': case 'Q': // �Է¹��� command�� q�̰ų� Q�϶�
			freeList(headnode);//freeList�Լ� ȣ��
			break;
		default: // �̿��� command�� �Է¹޾�����
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//>>>>>   Concentration!!   <<<<< ���
			break;
		}

	}while(command != 'q' && command != 'Q');// �Է¹��� command�� q�׸��� Q�� �ƴ϶�� �ݺ���

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; // headNode�� headNode�� rlink���� ����
	(*h)->llink = *h;// headNode�� headNode�� llink���� ����
	(*h)->key = -9999; // headNode�� key���� -9999�� �ʱ�ȭ
	return 1; // 1��ȯ
}

int freeList(listNode* h){

	if(h->rlink == h) // headNode�� headNode�� rlink���� �������
	{
		free(h); // h�����޸� �Ҵ�����
		return 1;//1��ȯ
	}

	listNode* p = h->rlink; //headNode�� rlink���� ����ü ������ p�� ����

	listNode* prev = NULL; //����ü������ prev�� NULL������ �ʱ�ȭ
	while(p != NULL && p != h) {// p�� NULL�̰ų� p�� headNode�� ����Ű�� ��� �ݺ�������
		prev = p;//p���� prev�� ����
		p = p->rlink;//p�� rlink���� p�� �����Ѵ�
		free(prev);//prev�����޸� �Ҵ�����
	}
	free(h);//h�����޸� �Ҵ� ����
	return 0;//0��ȯ
}



void printList(listNode* h) {
	int i = 0; //���������� i���� �� �ʱ�ȭ
	listNode* p; // ����ü������ p����

	printf("\n---PRINT\n");

	if(h == NULL) { // h�� ���������
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//h�� rlink���� p�� ����

	while(p != NULL && p != h) { //p�� ���� NULL�� �ƴϰ� p�� ���� h�� ���� �ƴҶ�
		printf("[ [%d]=%d ] ", i, p->key); // i�� p�� key���� ���
		p = p->rlink;//p�� rlink���� p�� ����
		i++;//i����
	}
	printf("  items = %d\n", i);//i�����


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//h�� llink���� h,h�� rlink�� �ּ����

	i = 0; //i�� 0����
    p = h->rlink;//h�� rlink���� p�� ����
	while(p != NULL && p != h) { // p�� NULL �̾ƴϰ� p�� h�� �ƴҶ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//i,p�� key,p�� llink,p,p�� rlink���
		p = p->rlink;//p�� rlink���� p�� ����
		i++;//i����
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // h�� NULL�̶�� -1��ȯ

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node�� ���� �����޸� �Ҵ�
	node->key = key; // key���� node�� key ���� ����
	node->rlink = NULL; // node�� rlink���� NULL�� �ʱ�ȭ
	node->llink = NULL; // node�� llink���� NULL�� �ʱ�ȭ

	if (h->rlink == h) /* ù ���� ���� */
	{//h�� h�� rlink���� ������
		h->rlink = node; // node���� h�� rlink���� ����
		h->llink = node; // node���� h�� llink���� ����
		node->rlink = h; // h���� node�� rlink�� ����
		node->llink = h; // h���� node�� llink�� ����
	} else {//h�� h�� rlink���� ����������
		h->llink->rlink = node; // node���� h�� llink�� rlink�� ����
		node->llink = h->llink;//h�� llink���� node�� llink���� ����
		h->llink = node; // node���� h�� llink���� ����
		node->rlink = h;//h���� node�� rlink���� ����
	}

	return 1; //1��ȯ
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // h�� llink���� h�� ���ų� h���� NULL�̶��
	{
		printf("nothing to delete.\n"); // ����� 1��ȯ
		return 1;
	}

	listNode* nodetoremove = h->llink; // h�� llink�� ����ü������ nodetoremove�� ����

	/* link ���� */
	nodetoremove->llink->rlink = h; // h�� nodetoremove�� llink�� rlink�� ����
	h->llink = nodetoremove->llink; // nodetoremove�� llink�� h�� llink�� ����

	free(nodetoremove); // nodetoremove�����Ҵ�����

	return 1; // 1 ��ȯ
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node�����޸��Ҵ�
	node->key = key; // key���� node�� key ���� ����
	node->rlink = NULL; // node�� rlink���� NULL�� �ʱ�ȭ
	node->llink = NULL; // node�� llink���� NULL�� �ʱ�ȭ

	node->rlink = h->rlink; // h�� rlink���� node�� rlink���� ����
	h->rlink->llink = node; // h�� rlink�� llink���� node������ �ٲ�
	node->llink = h; // h���� node�� llink���� ����
	h->rlink = node; // node�� h�� rlink���� ����


	return 1; // 1��ȯ
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // h�� NULL�̰ų� h�� rlink���� h���
	{
		printf("nothing to delete.\n");
		return 0; // 0��ȯ
	}

	listNode* nodetoremove = h->rlink;// h�� rlink���� ����ü ������ nodetormove�� ����

	/* link ���� */
	nodetoremove->rlink->llink = h;//ù��°����� ������� llink�� ��� ��� ����
	h->rlink = nodetoremove->rlink;//������� rlink�� ù��° ����� rlink �Է�

	free(nodetoremove);// nodetoremove�޸� �Ҵ�����

	return 1; // 1��ȯ

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { // h�� rlink���� h�� �����ϰų� h���� NULL�̶��
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //h�� rlink���� ����ü ������ n�� ����
	listNode *trail = h; // h�� ���� ����ü ������ trail�� ����
	listNode *middle = h; // h�� ���� ����ü ������ middle�� ����

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;//������� rlink�� llink�� ��������

	while(n != NULL && n != h){
		trail = middle;//trail�� middle����
		middle = n;//middle�� n����
		n = n->rlink;//n�� n�� ������� ����
		middle->rlink = trail;//middle����� rlink�� trail�� ����
		middle->llink = n;//middle����� llink�� n�� ����
	}

	h->rlink = middle;//�������rlink�� middle����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));//���ο� ��带 �޸��Ҵ�����
	node->key = key;//����� key���� �Է¹��� key�� ����
	node->llink = node->rlink = NULL;//���ο� ����� rlink�� llink�� NULL

	if (h->rlink == h)//������� rlink�� ����带 ����Ű�� //�� ��尡 ������
	{
		insertFirst(h, key);//��尡 �����Ƿ� ù��°�� ��� ����
		return 1;
	}

	listNode* n = h->rlink;//n�� ù��°��� 

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {
		if(n->key >= key) {//n����� key���� �Է¹��� key������ ũ�ų� �������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {//n��尡 ù��° ����ΰ��
				insertFirst(h, key);//ù��°�� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;//���ο��� �� rlink�� n�� ����Ŵ
				node->llink = n->llink;//���ο����� llink�� n��llink ����
				n->llink->rlink = node;//n����� ������� rlink�� ���ο� ��带 ����Ŵ
				n->llink = node;//n����� ������尡 ���ο� ��带 ����Ŵ
			}
			return 0;
		}

		n = n->rlink;//n�� n����Ǵ������� �ٲ���
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}





/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;//n�� ù��°��� 

	while(n != NULL && n != h) {
		if(n->key == key) {//n�� key���̶� �Է¹��� key���̶� ������
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;//n����� ������� rlink�� n����� rlink����Ŵ
				n->rlink->llink = n->llink;//n����� �������� llink�� n����� llink����Ŵ
				free(n);
			}
			return 0;
		}

		n = n->rlink;//n�� n����Ǵ������� �ٲ���
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}