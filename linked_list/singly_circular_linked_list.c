#include <stdio.h>
#include <stdlib.h>

// 단일 원형 연결 리스트의 노드를 나타내는 구조체
typedef struct Node
{
  int data;          // 노드에 저장된 데이터
  struct Node *next; // 다음 노드를 가리키는 포인터 (원형이므로 마지막 노드는 head를 가리킴)
} Node;

// 단일 원형 연결 리스트를 나타내는 구조체
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
  return (list->head == NULL);
}

// 리스트의 끝에 새 노드를 추가하는 함수
void append(SinglyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL; // 일단 NULL로 초기화

  // 빈 리스트이면 새 노드를 스스로 가리키도록(원형) 만든 후 head에 연결
  if (is_empty(list))
  {
    new_node->next = new_node; // 자기 자신을 가리킴
    list->head = new_node;
    return;
  }

  // tail(마지막 노드)를 찾아서 연결
  Node *current = list->head;
  while (current->next != list->head) // 마지막 노드의 next는 head
  {
    current = current->next;
  }
  current->next = new_node;
  new_node->next = list->head; // 새 노드->next가 다시 head를 가리켜 원형 구조
}

// 리스트의 시작에 새 노드를 추가하는 함수
void prepend(SinglyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;

  // 빈 리스트이면 append와 동일한 처리
  if (is_empty(list))
  {
    new_node->next = new_node; // 자기 자신 가리킴
    list->head = new_node;
    return;
  }

  // tail(마지막 노드)를 찾아서 새 노드를 head 앞으로 삽입
  Node *current = list->head;
  while (current->next != list->head)
  {
    current = current->next;
  }
  // current는 tail
  new_node->next = list->head; // 새 노드는 기존 head를 가리킴
  current->next = new_node;    // tail->next = new_node
  list->head = new_node;       // head 갱신
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

  // 노드가 1개만 있는 경우 (head->next == head)
  if (current->next == list->head)
  {
    // 하나뿐인 노드의 data가 일치하면 삭제
    if (current->data == data)
    {
      free(current);
      list->head = NULL;
    }
    else
    {
      printf("리스트에 해당 데이터가 없습니다.\n");
    }
    return;
  }

  // 노드가 2개 이상인 경우
  while (1)
  {
    if (current->data == data)
    {
      // 삭제 노드가 head인 경우
      if (current == list->head)
      {
        // tail(마지막 노드)를 찾아서 tail->next를 head->next로 바꿔야 함
        Node *tail = list->head;
        while (tail->next != list->head)
        {
          tail = tail->next;
        }
        tail->next = list->head->next; // tail->next를 head->next로
        list->head = list->head->next; // head를 한 칸 앞으로
        free(current);
      }
      else
      {
        // 중간/끝 노드 삭제
        prev->next = current->next;
        free(current);
      }
      return;
    }
    prev = current;
    current = current->next;
    // 한 바퀴 다 돌면 종료
    if (current == list->head)
    {
      break;
    }
  }

  // 찾지 못한 경우
  printf("리스트에 해당 데이터가 없습니다.\n");
}

// 지정된 데이터를 가진 노드를 검색하는 함수
int search(SinglyLinkedList *list, int data)
{
  if (is_empty(list))
  {
    return 0;
  }

  Node *current = list->head;
  while (1)
  {
    if (current->data == data)
    {
      return 1; // 데이터가 존재함
    }
    current = current->next;
    if (current == list->head)
    {
      break; // 한 바퀴 순회 완료
    }
  }
  return 0; // 못 찾음
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
  while (1)
  {
    printf("%d -> ", current->data);
    current = current->next;
    if (current == list->head)
    {
      break;
    }
  }
  printf("HEAD(원형)\n");
}

// 리스트를 뒤집는 함수
void reverse(SinglyLinkedList *list)
{
  // 빈 리스트이거나 노드가 하나만 있으면 뒤집을 필요 없음
  if (is_empty(list) || list->head->next == list->head)
  {
    return;
  }

  Node *prev = NULL;
  Node *current = list->head;
  Node *next = NULL;

  // 원형을 끊기 위해 tail을 찾아서 tail->next를 NULL로 만든다.
  Node *tail = list->head;
  while (tail->next != list->head)
  {
    tail = tail->next;
  }
  // tail->next = NULL 로 원을 끊음
  tail->next = NULL;

  // 이제 단일 리스트처럼 뒤집기
  while (current != NULL)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  // prev가 새 head
  list->head = prev;

  // 다시 tail을 찾아서 원형 복원 (마지막 노드->next = head)
  tail = list->head;
  while (tail->next != NULL)
  {
    tail = tail->next;
  }
  tail->next = list->head; // 원형 복원
}

// 리스트의 노드 수를 계산하는 함수
int length(SinglyLinkedList *list)
{
  if (is_empty(list))
  {
    return 0;
  }

  int count = 0;
  Node *current = list->head;
  while (1)
  {
    count++;
    current = current->next;
    if (current == list->head)
    {
      break;
    }
  }
  return count;
}

// 리스트의 중간 노드를 찾는 함수
int find_middle(SinglyLinkedList *list)
{
  if (is_empty(list))
  {
    return -1;
  }

  Node *slow = list->head;
  Node *fast = list->head;

  // fast->next 또는 fast->next->next가 head에 도달하면 중단
  while (fast->next != list->head && fast->next->next != list->head)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow->data;
}

// 리스트에서 N번째 노드 데이터를 찾는 함수
int get_nth(SinglyLinkedList *list, int n)
{
  if (is_empty(list))
  {
    printf("인덱스가 범위를 벗어났습니다.\n");
    return -1;
  }

  Node *current = list->head;
  int count = 0;
  while (1)
  {
    if (count == n)
    {
      return current->data;
    }
    current = current->next;
    count++;
    if (current == list->head)
    {
      break; // 한 바퀴 돌았는데 못 찾음 => 범위 초과
    }
  }

  printf("인덱스가 범위를 벗어났습니다.\n");
  return -1;
}

// 메모리 해제 함수
void free_list(SinglyLinkedList *list)
{
  if (is_empty(list))
  {
    return;
  }

  // 원형을 끊은 뒤 단일 리스트처럼 해제
  Node *tail = list->head;
  while (tail->next != list->head)
  {
    tail = tail->next;
  }
  tail->next = NULL; // 원을 끊음

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

  // 원형 리스트에 데이터 삽입 (append)
  append(&sll, 10);
  append(&sll, 20);
  append(&sll, 30);
  show(&sll);
  // 예: 10 -> 20 -> 30 -> HEAD(원형)

  // 리스트 시작 부분에 삽입 (prepend)
  prepend(&sll, 5);
  show(&sll);
  // 예: 5 -> 10 -> 20 -> 30 -> HEAD(원형)

  // 지정된 데이터를 가진 노드 삭제
  delete (&sll, 20);
  show(&sll);
  // 예: 5 -> 10 -> 30 -> HEAD(원형)

  // 검색 테스트
  printf("10 검색: %d\n", search(&sll, 10));
  printf("40 검색: %d\n", search(&sll, 40));
  // 10 검색: 1, 40 검색: 0

  // 길이
  printf("리스트 길이: %d\n", length(&sll));
  // 예: 3

  // 뒤집기
  reverse(&sll);
  show(&sll);
  // 예: 30 -> 10 -> 5 -> HEAD(원형)

  // 중간 노드
  printf("중간 노드: %d\n", find_middle(&sll));
  // 예) 길이가 3 => 중간 노드는 10

  // N번째 노드
  printf("2번째 노드: %d\n", get_nth(&sll, 2));
  // 인덱스 0=30, 1=10, 2=5 => 5

  // 메모리 해제
  free_list(&sll);

  return 0;
}
