#include <stdio.h>

typedef int element;

// 단순 연결 리스트
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// 삽입연산 (첫번째)
ListNode* insert_first(ListNode* head, element value, int *movecount)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// 삽입연산
ListNode* insert(ListNode* head, ListNode* pre, element value,int *movecount)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	(*movecount)++;
	return head;
}

// 삭제연산 (첫번째)
ListNode* delete_first(ListNode* head,int *movecount)
{
	ListNode* removed;
	if (head == NULL) return NULL; // 리스트가 공백일 때 돌아가기
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// 삭제연산
ListNode* delete(ListNode* head, ListNode* pre,int *movecount)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	(*movecount)++;
	return head;
}

// 리스트 출력
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
}

int main()
{
	ListNode *head = NULL;

	do {
		// 입력값 받기
		int enter = 0;

		printf("Menu\n");
		printf("(1) Insert(삽입)\n");
		printf("(2) Delete(삭제)\n");
		printf("(3) Print(출력)\n");
		printf("(0) Exit(종료)\n");

		// haed가 널이면 비어있다는 뜻 위치까지가서 그 값이 널이 아니면 비어있지 않음

		printf("Enter the memu : ");
		scanf_s("%d", &enter);

		element insert_val = 0; // 입력값 저장 변수
		int movecount = 0; // 링크 이동 횟수 저장 변수
		int pos = 0; // 위치 변수

		// 1 이 들어오면 insert 하기
		if (enter == 1)
		{
			printf("Enter the number and position(넣고 싶은 값과 위치 입력) : ");
			scanf_s("%d %d", &insert_val,&pos);

			// pos가 0보다 작은 경우
			if (pos < 0) 
			{
				printf("pos는 0보다가 같거나 큰 값이여야합니다.\n");
			}
			// pos가 0인 경우
			else if (pos == 0)
			{
				head = insert_first(head, insert_val,&movecount);
			}
			// 리스트가 공백일 경우 0번째 자리에 값 저장
			else if (head == NULL)
			{
				head = insert_first(head, insert_val,&movecount);
				printf("리스트 비어있음 / insert at position 0 \n");
			}
			// 나머지
			else
			{
				ListNode* p = head;
				int i = 0;
				int lastIndex = 0; // 마지막 인덱스 변수 추가

				// 연결 리스트의 마지막 인덱스 찾기
				while (p->link != NULL)
				{
					p = p->link;
					lastIndex++;
					movecount++; // ?
				}

				if (pos <= lastIndex) // pos 값이 유효한 범위 내에 있는 경우
				{
					p = head;
					i = 0;

					while (p->link != NULL && i < pos - 1)
					{
						p = p->link;
						movecount++;
						i++;
					}

					head = insert(head, p, insert_val,&movecount);
					printf("Insert at position %d\n", pos);
				}
				else // pos 값이 마지막 인덱스보다 큰 경우
				{
					p = head;
					i = 0;

					while (p->link != NULL && i < lastIndex)
					{
						p = p->link;
						movecount++;
						i++;
					}

					head = insert(head, p, insert_val,&movecount);
					printf("Last index is %d / Insert at the end of list\n", lastIndex);
				}
			}

			printf("Move along the link : %d\n\n", movecount);
		}

		// 2 가 들어오면 delete 하기
		if (enter == 2)
		{
			// 리스트가 공백인 경우
			if (head == NULL)
			{
				printf("현재 리스트는 공백상태입니다.\n");
			}
			//공백 아닌 경우
			else
			{
				printf("Enter the position to delete(삭제하고 싶은 위치 입력) : ");
				scanf_s("%d", &pos);

				// pos 0보다 작은 경우
				if (pos < 0)
				{
					printf("pos는 0보다 같거나 큰 값이여야 합니다.\n");
				}
				// pos가 0인 경우
				else if (pos == 0)
				{
					head = delete_first(head,&movecount);
				}
				// pos가 마지막 index보다 큰 경우에는 삭제 X
				else
				{
					ListNode* p = head;
					int i = 0;
					int lastIndex = 0; // 마지막 인덱스 변수 추가

					// 연결 리스트의 마지막 인덱스 찾기
					while (p->link != NULL)
					{
						p = p->link;
						lastIndex++;
					}

					if (pos <= lastIndex) // pos 값이 유효한 범위 내에 있는 경우
					{
						p = head;
						i = 0;

						while (p->link != NULL && i < pos - 1)
						{
							p = p->link;
							i++;
						}

						head = delete(head, p,&movecount);
						printf("Delete at position %d\n", pos);
					}
					else
					{
						printf("pos값이 유효하지 않아서 삭제할수 없습니다\n");
					}
				}
				printf("Move along the link : %d\n\n", movecount);
			}
		}
		// 3 이 들어오면 리스트 출력하기
		if (enter == 3)
		{
			print_list(head);
			printf("\n");
		}
		// 3 이상 값 들어오면 다시 입력하라고 하기
		if (enter > 3)
		{
			printf("Invalid Memu. Please select again(번호 다시 고르시오)\n");
			printf("\n");
		}
		// 0 이 들어오면 프로그램 종료
		if (enter == 0)
		{
			break;
		}

		getchar();
	} while (1);

	return 0;
}