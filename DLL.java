public class DLL {

    static DLL head = null;

    int value;
    DLL next;
    DLL prev;

    public DLL(int value) {
        this.value = value;
        this.next = null;
        this.prev = null;
    }

    public DLL(int value, DLL next, DLL prev) {
        this.value = value;
        this.next = next;
        this.prev = prev;
    }

    public static void add(int value) {
        DLL newNode = new DLL(value);
        if (head == null) {
            head = newNode;
            return;
        }

        DLL current = head;

        while (current.next != null) {
            current = current.next;
        }

        current.next = newNode;

    }

    public static void printList() {
        for (DLL current = head; current != null; current = current.next) {
            System.out.println(current.value);
        }
    }

    public static void deleteFirst(int value) {
        DLL current = head;

        while (current != null) {
            if (current.value == value) {
                current.prev.next = current.next;
            }
        }
        System.err.println("Node does not exist");
    }

    public static void insertAt(int index, int value) {
        if (head == null) {
            System.out.println("");
            return;
        }

    }
}
