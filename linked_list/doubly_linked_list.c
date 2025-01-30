#include <stdio.h>
#include <stdlib.h>

// 이중 연결 리스트의 노드를 나타내는 구조체
typedef struct Node
{
  int data;          // 노드에 저장된 데이터
  struct Node *next; // 다음 노드를 가리키는 포인터
  struct Node *prev; // 이전 노드를 가리키는 포인터
} Node;

// 이중 연결 리스트를 나타내는 구조체
typedef struct DoublyLinkedList
{
  Node *head; // 리스트의 시작(head)
} DoublyLinkedList;

// 리스트 초기화 함수
void init(DoublyLinkedList *list)
{
  list->head = NULL;
}

// 리스트가 비어 있는지 확인하는 함수
int is_empty(DoublyLinkedList *list)
{
  return list->head == NULL;
}

// 리스트의 끝에 새 노드를 추가하는 함수
void append(DoublyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;

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
  new_node->prev = current;
}

// 리스트의 시작에 새 노드를 추가하는 함수
void prepend(DoublyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = list->head;
  new_node->prev = NULL;

  if (!is_empty(list))
  {
    list->head->prev = new_node;
  }

  list->head = new_node;
}

// 지정된 데이터를 가진 첫 번째 노드를 삭제하는 함수
void delete(DoublyLinkedList *list, int data)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다. 삭제할 수 없습니다.\n");
    return;
  }

  Node *current = list->head;

  while (current)
  {
    if (current->data == data)
    {
      if (current->prev)
      {
        current->prev->next = current->next;
      }
      else
      {
        list->head = current->next;
      }

      if (current->next)
      {
        current->next->prev = current->prev;
      }
      free(current);
      return;
    }
    current = current->next;
  }
  printf("리스트에 해당 데이터가 없습니다.\n");
}

// 지정된 데이터를 가진 노드를 검색하는 함수
int search(DoublyLinkedList *list, int data)
{
  Node *current = list->head;
  while (current)
  {
    if (current->data == data)
    {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

// 리스트의 내용을 출력하는 함수
void show(DoublyLinkedList *list)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다.\n");
    return;
  }

  Node *current = list->head;
  while (current)
  {
    printf("%d <-> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

// 리스트를 뒤집는 함수
void reverse(DoublyLinkedList *list)
{
  Node *current = list->head;
  Node *temp = NULL;

  while (current)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp)
  {
    list->head = temp->prev;
  }
}

// 리스트의 노드 수를 계산하는 함수
int length(DoublyLinkedList *list)
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
int find_middle(DoublyLinkedList *list)
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
int get_nth(DoublyLinkedList *list, int n)
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
void free_list(DoublyLinkedList *list)
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
  DoublyLinkedList dll;
  init(&dll);
  append(&dll, 10);
  append(&dll, 20);
  append(&dll, 30);
  show(&dll);
  prepend(&dll, 5);
  show(&dll);
  delete (&dll, 20);
  show(&dll);
  printf("10 검색: %d\n", search(&dll, 10));
  printf("40 검색: %d\n", search(&dll, 40));
  printf("리스트 길이: %d\n", length(&dll));
  reverse(&dll);
  show(&dll);
  printf("중간 노드: %d\n", find_middle(&dll));
  printf("2번째 노드: %d\n", get_nth(&dll, 2));
  free_list(&dll);
  return 0;
}
