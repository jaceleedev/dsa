class Node:
    """
    이중 연결 리스트의 노드를 나타내는 클래스.
    각 노드는 데이터, 이전 노드, 다음 노드에 대한 참조를 포함한다.
    """
    def __init__(self, data):
        self.data = data  # 노드에 저장된 데이터
        self.prev = None  # 이전 노드를 가리키는 참조
        self.next = None  # 다음 노드를 가리키는 참조


class DoublyLinkedList:
    """
    이중 연결 리스트를 나타내는 클래스.
    노드 추가, 삭제, 탐색 등의 메서드를 포함한다.
    """
    def __init__(self):
        self.head = None  # 리스트의 시작(head)

    def is_empty(self):
        """리스트가 비어 있는지 확인."""
        return self.head is None

    def append(self, data):
        """
        리스트의 끝에 새 노드를 추가.
        :param data: 새 노드에 삽입할 데이터
        """
        new_node = Node(data)
        if self.is_empty():
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
            new_node.prev = current

    def prepend(self, data):
        """
        리스트의 시작에 새 노드를 추가.
        :param data: 새 노드에 삽입할 데이터
        """
        new_node = Node(data)
        if self.is_empty():
            self.head = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    def delete(self, data):
        """
        지정된 데이터를 가진 첫 번째 노드를 삭제.
        :param data: 삭제할 노드의 데이터
        """
        if self.is_empty():
            print("리스트가 비어 있습니다. 삭제할 수 없습니다.")
            return

        current = self.head
        while current:
            if current.data == data:
                if current.prev:
                    current.prev.next = current.next
                else:
                    self.head = current.next
                if current.next:
                    current.next.prev = current.prev
                return
            current = current.next

        print("리스트에 해당 데이터가 없습니다.")

    def search(self, data):
        """
        지정된 데이터를 가진 노드를 검색.
        :param data: 검색할 데이터
        :return: 데이터가 발견되면 True, 그렇지 않으면 False
        """
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    def show(self):
        """
        리스트의 내용을 출력.
        """
        if self.is_empty():
            print("리스트가 비어 있습니다.")
            return

        current = self.head
        while current:
            print(current.data, end=" <-> ")
            current = current.next
        print("None")

    def reverse(self):
        """
        리스트를 뒤집음.
        """
        current = self.head
        prev = None
        while current:
            next_node = current.next
            current.next = prev
            current.prev = next_node
            prev = current
            current = next_node
        self.head = prev

    def length(self):
        """
        리스트의 노드 수를 계산.
        :return: 리스트의 길이
        """
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    def insert_at(self, position, data):
        """
        리스트의 특정 위치에 새 노드를 삽입.
        :param position: 삽입할 위치 (0부터 시작)
        :param data: 삽입할 데이터
        """
        if position < 0:
            print("잘못된 위치입니다.")
            return

        new_node = Node(data)
        if position == 0:
            self.prepend(data)
            return

        current = self.head
        for _ in range(position - 1):
            if current is None:
                print("위치가 범위를 벗어났습니다.")
                return
            current = current.next

        new_node.next = current.next
        new_node.prev = current
        if current.next:
            current.next.prev = new_node
        current.next = new_node

    def delete_at(self, position):
        """
        리스트의 특정 위치에 있는 노드를 삭제.
        :param position: 삭제할 위치 (0부터 시작)
        """
        if position < 0 or self.is_empty():
            print("잘못된 위치 또는 리스트가 비어 있습니다.")
            return

        current = self.head
        for _ in range(position):
            if current is None:
                print("위치가 범위를 벗어났습니다.")
                return
            current = current.next

        if current.prev:
            current.prev.next = current.next
        else:
            self.head = current.next
        if current.next:
            current.next.prev = current.prev

    def find_middle(self):
        """
        리스트의 중간 노드 데이터를 반환.
        :return: 중간 노드 데이터
        """
        slow = self.head
        fast = self.head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow.data if slow else None

    def get_nth(self, n):
        """
        리스트에서 N번째 노드의 데이터를 반환.
        :param n: 가져올 노드의 위치 (0부터 시작)
        :return: N번째 노드의 데이터
        """
        current = self.head
        count = 0
        while current:
            if count == n:
                return current.data
            count += 1
            current = current.next
        print("인덱스가 범위를 벗어났습니다.")
        return None

# 사용 예제
if __name__ == "__main__":
    dll = DoublyLinkedList()
    dll.append(10)
    dll.append(20)
    dll.append(30)
    dll.show()
    dll.prepend(5)
    dll.show()
    dll.delete(20)
    dll.show()
    print("10 검색:", dll.search(10))
    print("40 검색:", dll.search(40))
    print("리스트 길이:", dll.length())
    dll.reverse()
    dll.show()
    dll.insert_at(2, 25)
    dll.show()
    dll.delete_at(2)
    dll.show()
    print("중간 노드:", dll.find_middle())
    print("2번째 노드:", dll.get_nth(2))
