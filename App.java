
public class App {
    public static void main(String[] args) {
        // Add elements to the linked list
        SLL.add(10);
        SLL.add(20);
        SLL.add(30);
        SLL.add(40);

        System.out.println("--- Testing printAdd() ---");
        // The printAdd() function will print the memory address of the nodes
        // up to the second-to-last node.
        SLL.printAdd();

        System.out.println("\n--- List Contents (printList()) ---");
        // Use printList() to see the values
        SLL.printList();

        // Example of other methods you could test

        // Insert at a specific index
        SLL.insertAt(1, 15); // Insert 15 at index 1
        System.out.println("\n--- After insertAt(1, 15) ---");
        SLL.printList();

        // Delete the first occurrence of a value
        SLL.deletefirst(30);
        System.out.println("\n--- After deletefirst(30) ---");
        SLL.printList();
    }
}