#include <stdio.h>
#include <stdlib.h>

/*
 * 이중 원형 연결 리스트 노드 구조체
 *  - data: 노드에 저장할 정수 데이터
 *  - next: 다음 노드를 가리키는 포인터
 *  - prev: 이전 노드를 가리키는 포인터
 */
typedef struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

/*
 * 이중 원형 연결 리스트를 나타내는 구조체
 *  - head: 리스트의 시작 노드를 가리키는 포인터
 */
typedef struct DoublyLinkedList
{
  Node *head;
} DoublyLinkedList;

/*
 * 리스트 초기화 함수
 *  - head 포인터를 NULL로 설정해 리스트가 비었다고 표시
 */
void init(DoublyLinkedList *list)
{
  list->head = NULL;
}

/*
 * 리스트가 비어 있는지 확인하는 함수
 *  - head가 NULL이면 리스트가 비어있는 상태
 */
int is_empty(DoublyLinkedList *list)
{
  return (list->head == NULL);
}

/*
 * 리스트의 끝에 새 노드를 추가하는 함수 (append)
 *  1. 새 노드 동적 할당 및 data 저장
 *  2. 리스트가 비어 있으면, 새 노드를 자기 자신으로 next와 prev 연결 후 head로 지정
 *  3. 비어 있지 않으면, head->prev(현재 마지막 노드) 뒤에 새 노드 삽입
 */
void append(DoublyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (is_empty(list))
  {
    // 리스트가 비어 있을 경우, 자기 자신을 가리키도록 설정
    new_node->next = new_node;
    new_node->prev = new_node;
    list->head = new_node;
  }
  else
  {
    // 리스트가 비어있지 않을 경우
    Node *tail = list->head->prev; // 현재 마지막 노드를 찾음
    // 새 노드의 next는 head를 가리키도록
    new_node->next = list->head;
    // 새 노드의 prev는 tail을 가리키도록
    new_node->prev = tail;
    // 기존 tail의 next는 새 노드를 가리키도록
    tail->next = new_node;
    // head의 prev를 새 노드로 갱신 (마지막 노드를 새 노드로 변경)
    list->head->prev = new_node;
  }
}

/*
 * 리스트의 시작에 새 노드를 추가하는 함수 (prepend)
 *  1. 새 노드 동적 할당 및 data 저장
 *  2. 리스트가 비어 있으면, 자기 자신을 가리키도록 next/prev 설정 후 head로 지정
 *  3. 비어 있지 않으면, head 앞에 새 노드를 삽입하고, head를 새 노드로 변경
 */
void prepend(DoublyLinkedList *list, int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (is_empty(list))
  {
    // 리스트가 비어 있을 경우
    new_node->next = new_node;
    new_node->prev = new_node;
    list->head = new_node;
  }
  else
  {
    // 리스트가 비어있지 않을 경우
    Node *tail = list->head->prev; // 현재 마지막 노드
    // 새 노드의 next는 기존 head
    new_node->next = list->head;
    // 새 노드의 prev는 tail
    new_node->prev = tail;
    // tail의 next를 새 노드로
    tail->next = new_node;
    // 기존 head의 prev를 새 노드로
    list->head->prev = new_node;
    // head를 새 노드로 갱신
    list->head = new_node;
  }
}

/*
 * 지정된 데이터를 가진 첫 번째 노드를 삭제하는 함수 (delete)
 *  1. 리스트가 비어있으면 에러 메시지 출력
 *  2. 비어있지 않으면, head부터 시작하여 한 바퀴를 순회하며 data를 가진 노드를 찾음
 *  3. 찾으면, 해당 노드를 원형 연결에서 제거
 *     - 만약 삭제 대상이 head이고, 그것이 유일한 노드였다면 head = NULL
 *     - 그 외에는 포인터(prev, next) 연결을 재조정
 */
void delete(DoublyLinkedList *list, int data)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다. 삭제할 수 없습니다.\n");
    return;
  }

  Node *current = list->head;
  Node *start = list->head; // 순회를 시작하는 기준점

  while (1)
  {
    if (current->data == data)
    {
      // 노드를 찾았을 때
      // 노드가 딱 하나인 경우 (current->next == current)
      if (current->next == current && current->prev == current)
      {
        list->head = NULL;
      }
      else
      {
        // 여러 노드가 있는 경우
        Node *prev_node = current->prev;
        Node *next_node = current->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        // 만약 삭제하는 노드가 head라면 head를 다음 노드로 변경
        if (current == list->head)
        {
          list->head = next_node;
        }
      }
      free(current);
      return;
    }
    current = current->next;
    if (current == start)
      break; // 한 바퀴 순회 완료
  }

  // 찾는 노드가 없을 경우
  printf("리스트에 해당 데이터가 없습니다.\n");
}

/*
 * 지정된 데이터를 가진 노드를 검색하는 함수 (search)
 *  - 리스트를 한 바퀴 순회하며 데이터를 찾으면 1, 아니면 0 반환
 */
int search(DoublyLinkedList *list, int data)
{
  if (is_empty(list))
    return 0;

  Node *current = list->head;
  Node *start = list->head;

  while (1)
  {
    if (current->data == data)
    {
      return 1;
    }
    current = current->next;
    if (current == start)
      break;
  }

  return 0;
}

/*
 * 리스트의 내용을 출력하는 함수 (show)
 *  - head부터 시작하여 한 바퀴 순회하며 데이터를 출력
 */
void show(DoublyLinkedList *list)
{
  if (is_empty(list))
  {
    printf("리스트가 비어 있습니다.\n");
    return;
  }

  Node *current = list->head;
  Node *start = list->head;

  while (1)
  {
    printf("%d <-> ", current->data);
    current = current->next;
    if (current == start)
      break;
  }
  printf("(다시 head)\n");
}

/*
 * 리스트를 뒤집는 함수 (reverse)
 *  - 각 노드의 next와 prev를 교환
 *  - 마지막에 head를 기존 tail(뒤집기 후의 첫 노드)로 맞춰줘야 함
 */
void reverse(DoublyLinkedList *list)
{
  if (is_empty(list))
    return;

  Node *current = list->head;
  Node *start = list->head;
  Node *temp = NULL;

  while (1)
  {
    // next와 prev를 교체
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    // 뒤집힌 상태에서는 '이전' 노드로 이동
    current = current->prev;

    // 한 바퀴 순회하면 종료
    if (current == start)
      break;
  }

  // temp가 마지막으로 방문한 노드의 prev를 가지고 있으므로
  // 그 노드가 뒤집힌 후의 첫 노드가 됨
  if (temp != NULL)
  {
    list->head = temp->prev;
  }
}

/*
 * 리스트의 노드 수를 계산하는 함수 (length)
 *  - 한 바퀴 순회하며 노드의 개수를 센다
 */
int length(DoublyLinkedList *list)
{
  if (is_empty(list))
    return 0;

  int count = 0;
  Node *current = list->head;
  Node *start = list->head;

  while (1)
  {
    count++;
    current = current->next;
    if (current == start)
      break;
  }

  return count;
}

/*
 * 리스트의 중간 노드를 찾는 함수 (find_middle)
 *  - slow 포인터는 한 칸씩 이동, fast 포인터는 두 칸씩 이동
 *  - fast가 head로 돌아오거나(또는 head 근처에서 멈추면) 순회 종료
 *  - slow가 가리키는 노드의 데이터를 반환 (비어있으면 -1)
 */
int find_middle(DoublyLinkedList *list)
{
  if (is_empty(list))
    return -1;

  Node *slow = list->head;
  Node *fast = list->head;

  // 원형이므로 fast->next, fast->next->next가 head인지 확인하며 이동
  while (fast->next != list->head && fast->next->next != list->head)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  return (slow ? slow->data : -1);
}

/*
 * 리스트에서 N번째 노드 데이터를 찾는 함수 (get_nth)
 *  - head부터 시작하여 n번 인덱스를 만날 때까지 이동
 *  - 만약 리스트 길이를 초과하면 에러 메시지 출력
 */
int get_nth(DoublyLinkedList *list, int n)
{
  if (is_empty(list))
  {
    printf("인덱스가 범위를 벗어났습니다.\n");
    return -1;
  }

  Node *current = list->head;
  Node *start = list->head;
  int count = 0;

  while (1)
  {
    if (count == n)
    {
      return current->data;
    }
    count++;
    current = current->next;
    if (current == start)
      break;
  }

  printf("인덱스가 범위를 벗어났습니다.\n");
  return -1;
}

/*
 * 메모리 해제 함수 (free_list)
 *  - 리스트 내 모든 노드를 한 바퀴 순회하며 free
 *  - head를 NULL로 설정해 리스트 비움
 */
void free_list(DoublyLinkedList *list)
{
  if (is_empty(list))
    return;

  Node *current = list->head;
  Node *start = list->head;
  Node *next_node = NULL;

  while (1)
  {
    next_node = current->next;
    free(current);
    current = next_node;
    if (current == start)
      break;
  }

  list->head = NULL;
}

/*
 * 사용 예제 (테스트 코드)
 *  - 이중 원형 연결 리스트의 각 함수 테스트
 */
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
