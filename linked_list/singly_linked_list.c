#include <stdio.h>
#include <stdlib.h>

// 단일 연결 리스트의 노드를 나타내는 구조체
typedef struct Node
{
  int data;          // 노드에 저장된 데이터
  struct Node *next; // 다음 노드를 가리키는 포인터
} Node;

// 단일 연결 리스트를 나타내는 구조체
typedef struct SinglyLinkedList
{
  Node *head; // 리스트의 시작(head)
} SinglyLinkedList;

// 리스트 초기화 함수
void init(SinglyLinkedList *list)
{
  list->head = NULL;
}

// 리스트가 비어 있는지 확인하는 함수
int is_empty(SinglyLinkedList *list)
{
  return list->head == NULL;
}

// 리스트의 끝에 새 노드를 추가하는 함수
void append(SinglyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;

  if (is_empty(list))
  {
    list->head = new_node;
    return;
  }

  Node *current = list->head;
  while (current->next)
  {
    current = current->next;
  }
  current->next = new_node;
}

// 리스트의 시작에 새 노드를 추가하는 함수
void prepend(SinglyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = list->head;
  list->head = new_node;
}

// 지정된 데이터를 가진 첫 번째 노드를 삭제하는 함수
void delete(SinglyLinkedList *list, int data)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다. 삭제할 수 없습니다.\n");
    return;
  }

  Node *current = list->head;
  Node *prev = NULL;

  while (current)
  {
    if (current->data == data)
    {
      if (prev)
      {
        prev->next = current->next;
      }
      else
      {
        list->head = current->next;
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
  printf("리스트에 해당 데이터가 없습니다.\n");
}

// 지정된 데이터를 가진 노드를 검색하는 함수
int search(SinglyLinkedList *list, int data)
{
  Node *current = list->head;
  while (current)
  {
    if (current->data == data)
    {
      return 1; // 데이터가 존재함
    }
    current = current->next;
  }
  return 0; // 데이터가 없음
}

// 리스트의 내용을 출력하는 함수
void show(SinglyLinkedList *list)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다.\n");
    return;
  }

  Node *current = list->head;
  while (current)
  {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

// 리스트를 뒤집는 함수
void reverse(SinglyLinkedList *list)
{
  Node *prev = NULL;
  Node *current = list->head;
  Node *next = NULL;

  while (current)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  list->head = prev;
}

// 리스트의 노드 수를 계산하는 함수
int length(SinglyLinkedList *list)
{
  int count = 0;
  Node *current = list->head;
  while (current)
  {
    count++;
    current = current->next;
  }
  return count;
}

// 리스트의 중간 노드를 찾는 함수
int find_middle(SinglyLinkedList *list)
{
  Node *slow = list->head;
  Node *fast = list->head;

  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow ? slow->data : -1;
}

// 리스트에서 N번째 노드 데이터를 찾는 함수
int get_nth(SinglyLinkedList *list, int n)
{
  Node *current = list->head;
  int count = 0;

  while (current)
  {
    if (count == n)
    {
      return current->data;
    }
    count++;
    current = current->next;
  }
  printf("인덱스가 범위를 벗어났습니다.\n");
  return -1;
}

// 메모리 해제 함수
void free_list(SinglyLinkedList *list)
{
  Node *current = list->head;
  Node *next;
  while (current)
  {
    next = current->next;
    free(current);
    current = next;
  }
  list->head = NULL;
}

// 사용 예제
int main()
{
  SinglyLinkedList sll;
  init(&sll);
  append(&sll, 10);
  append(&sll, 20);
  append(&sll, 30);
  show(&sll);
  prepend(&sll, 5);
  show(&sll);
  delete (&sll, 20);
  show(&sll);
  printf("10 검색: %d\n", search(&sll, 10));
  printf("40 검색: %d\n", search(&sll, 40));
  printf("리스트 길이: %d\n", length(&sll));
  reverse(&sll);
  show(&sll);
  printf("중간 노드: %d\n", find_middle(&sll));
  printf("2번째 노드: %d\n", get_nth(&sll, 2));
  free_list(&sll);
  return 0;
}
