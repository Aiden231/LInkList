#include <stdio.h>

typedef int element;

// �ܼ� ���� ����Ʈ
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// ���Կ��� (ù��°)
ListNode* insert_first(ListNode* head, element value, int *movecount)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// ���Կ���
ListNode* insert(ListNode* head, ListNode* pre, element value,int *movecount)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	(*movecount)++;
	return head;
}

// �������� (ù��°)
ListNode* delete_first(ListNode* head,int *movecount)
{
	ListNode* removed;
	if (head == NULL) return NULL; // ����Ʈ�� ������ �� ���ư���
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// ��������
ListNode* delete(ListNode* head, ListNode* pre,int *movecount)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	(*movecount)++;
	return head;
}

// ����Ʈ ���
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
		// �Է°� �ޱ�
		int enter = 0;

		printf("Menu\n");
		printf("(1) Insert(����)\n");
		printf("(2) Delete(����)\n");
		printf("(3) Print(���)\n");
		printf("(0) Exit(����)\n");

		// haed�� ���̸� ����ִٴ� �� ��ġ�������� �� ���� ���� �ƴϸ� ������� ����

		printf("Enter the memu : ");
		scanf_s("%d", &enter);

		element insert_val = 0; // �Է°� ���� ����
		int movecount = 0; // ��ũ �̵� Ƚ�� ���� ����
		int pos = 0; // ��ġ ����

		// 1 �� ������ insert �ϱ�
		if (enter == 1)
		{
			printf("Enter the number and position(�ְ� ���� ���� ��ġ �Է�) : ");
			scanf_s("%d %d", &insert_val,&pos);

			// pos�� 0���� ���� ���
			if (pos < 0) 
			{
				printf("pos�� 0���ٰ� ���ų� ū ���̿����մϴ�.\n");
			}
			// pos�� 0�� ���
			else if (pos == 0)
			{
				head = insert_first(head, insert_val,&movecount);
			}
			// ����Ʈ�� ������ ��� 0��° �ڸ��� �� ����
			else if (head == NULL)
			{
				head = insert_first(head, insert_val,&movecount);
				printf("����Ʈ ������� / insert at position 0 \n");
			}
			// ������
			else
			{
				ListNode* p = head;
				int i = 0;
				int lastIndex = 0; // ������ �ε��� ���� �߰�

				// ���� ����Ʈ�� ������ �ε��� ã��
				while (p->link != NULL)
				{
					p = p->link;
					lastIndex++;
					movecount++; // ?
				}

				if (pos <= lastIndex) // pos ���� ��ȿ�� ���� ���� �ִ� ���
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
				else // pos ���� ������ �ε������� ū ���
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

		// 2 �� ������ delete �ϱ�
		if (enter == 2)
		{
			// ����Ʈ�� ������ ���
			if (head == NULL)
			{
				printf("���� ����Ʈ�� ��������Դϴ�.\n");
			}
			//���� �ƴ� ���
			else
			{
				printf("Enter the position to delete(�����ϰ� ���� ��ġ �Է�) : ");
				scanf_s("%d", &pos);

				// pos 0���� ���� ���
				if (pos < 0)
				{
					printf("pos�� 0���� ���ų� ū ���̿��� �մϴ�.\n");
				}
				// pos�� 0�� ���
				else if (pos == 0)
				{
					head = delete_first(head,&movecount);
				}
				// pos�� ������ index���� ū ��쿡�� ���� X
				else
				{
					ListNode* p = head;
					int i = 0;
					int lastIndex = 0; // ������ �ε��� ���� �߰�

					// ���� ����Ʈ�� ������ �ε��� ã��
					while (p->link != NULL)
					{
						p = p->link;
						lastIndex++;
					}

					if (pos <= lastIndex) // pos ���� ��ȿ�� ���� ���� �ִ� ���
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
						printf("pos���� ��ȿ���� �ʾƼ� �����Ҽ� �����ϴ�\n");
					}
				}
				printf("Move along the link : %d\n\n", movecount);
			}
		}
		// 3 �� ������ ����Ʈ ����ϱ�
		if (enter == 3)
		{
			print_list(head);
			printf("\n");
		}
		// 3 �̻� �� ������ �ٽ� �Է��϶�� �ϱ�
		if (enter > 3)
		{
			printf("Invalid Memu. Please select again(��ȣ �ٽ� ���ÿ�)\n");
			printf("\n");
		}
		// 0 �� ������ ���α׷� ����
		if (enter == 0)
		{
			break;
		}

		getchar();
	} while (1);

	return 0;
}