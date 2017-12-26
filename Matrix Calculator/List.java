//Rhea Lingaiah
//rlingaia
//pa3
//11/5/17

public class List {
//----NODE class-------
    private class Node {
        Object data;
        Node next;
        Node prev;

        Node(Object data) {
            this.data = data;
            next = prev = null;
        }

        //to String method
        public String toString() {
            return String.valueOf(data);
        }

        //equals method
        public boolean equals(Object x) {
            boolean eq = false;
            Node that;
            if (x instanceof Node) {
                that = (Node) x;
                eq = (this.data == that.data);
            }
            return eq;
        }
    }
    //--------
    private Node front;
    private Node back;
    private Node cursor;
    private int length;
    private int index;
    List() {
        front = back = cursor = null;
        length = 0;
        index = -1;
    }

    //returns the length
    int length() {
        return length;
    }

    //returns the index of the element if the cursor is not null
    int index() {
        if (cursor != null)
            return index;
        else
            return -1;
    }

    //Returns front element. Pre: length()>0
    Object front() {
        if (length <= 0)
            throw new RuntimeException("called on empty list.");
        return front.data;
    }

    //Returns back element. Pre: length()>0
    Object back() {
        if (length <= 0)
            throw new RuntimeException(" called on empty list.");
        return back.data;
    }


    Object get() {
        //Returns cursor element. Pre: length()>0, index()>=0
        if (length <= 0)
            throw new RuntimeException("called on empty list.");
        if (index < 0)
            throw new RuntimeException("called on invalid index.");
        return cursor.data;
    }


    public boolean equals(List L) {
        // Returns true if and only if this List and L are the same integer sequence
        boolean flag = true; //use flag to break out of the while loop
        Node N = this.front;
        Node M = L.front;
        if (this.length == L.length) {
            while (flag && N != null) { //since the flag is true it goes into the loop
                flag = (N.data == M.data);//check if the data is the same
                N = N.next; //move next in the list
                M = M.next;
            }
            return flag; //if true this will equal true
        } else
            return false;
    }
    //Resets this List to empty state.
    void clear() {
        front = back = cursor = null; //set everything to null
        length = 0;//length gets set to null state
        index = -1; //index gets set to null
    }

    //If List is non-empty, places the cursor under the front element, otherwise does nothing.
    void moveFront() {
        if (length > 0) {
            cursor = front; //move the cursor under the front
            index = 0;
        }
    }

    //If List is non-empty, places the cursor under the back element, otherwise does nothing.
    void moveBack() {
        if (length > 0) {
            cursor = back; //move the cursor under the back
            index = length - 1;
        }
    }

    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void movePrev() {
        if (cursor != null && index != 0) {
            cursor = cursor.prev; //if the cursor is not at the front
            index--; //decrement the index
        } else if (cursor != null && index == 0) {
            cursor = null; //if the cursor is at the front
            index = -1;//stays null
        }
    }
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void moveNext() {
        if (cursor != null && index != length - 1) {
            cursor = cursor.next;//move the cursor to next
            index++; //increase the index
        } else if (cursor != null && index == length - 1) {
            cursor = null; //if at the back of the list
            index = -1; //index stays null
        }
    }

    // Insert new element into this List. If List is non-empty,insertion takes place before front element.
    void prepend(Object data) {
        Node newElement = new Node(data);
        if (length <= 0) {
            front = back = newElement; //new element equals the front and back
            length++;
        } else {
            front.prev = newElement;
            newElement.next = front; //the front moves to the next element
            front = newElement;
            length++;//increase the length
            index++; //increase the index

        }

    }

    // Insert new element into this List. If List is non-empty, insertion takes place after back element.
    void append(Object data) {
        Node N;
        if (back == null) { //if the back is null
            back = new Node(data);
            front = back;
            cursor = back;
        } else if (back!=null){
            N = back;
            N.next = new Node(data);
            back = N.next;
            back.prev = N;
        }
        length++;
    }

    // Insert new element before cursor.
    // Pre: length()>0, index()>=0
    void insertBefore(Object data) {
        if (length <= 0 || index < 0)
            throw new RuntimeException("called on an empty list.");
        else {
            if (index == 0)
                prepend(data); //prepend the element if the index is =0
            else {
                Node N = new Node(data);
                Node before = cursor.prev;
                N.prev = before; //insert the node to before
                N.next = cursor; //the cursor
                before.next = N;
                cursor.prev = N;
                length++; //increment the length
                index++;
            }
        }
    }

    // Inserts new element after cursor.
    // Pre: length()>0, index()>=0
    void insertAfter(Object data) {
        if (length <= 0 || index < 0)
            throw new RuntimeException("called on empty list");
        else {
            if (index == length - 1)
                append(data); //append the element
            else {
                Node N = new Node(data);
                Node after = cursor.next;
                N.next = cursor.next;
                N.prev = after;//set the prev=to after
                after.prev = N;
                cursor.next = N;
                length++; //increase the length
            }
        }
    }

    // Deletes the front element. Pre: length()>0
    void deleteFront() {
        if (length < 1)
            throw new RuntimeException("called on an empty List");
        if (cursor == front) {
            cursor = null; //set the front cursor to null
            index = -1;
        }
        front = front.next;
        front.prev = null; //set the front prev null
        length--; //decrement the length and index because deleted an element
        index--;
    }

    // Deletes the back element.
    // Pre: length() > 0
    void deleteBack() {
        if (length < 1) {
            throw new RuntimeException("called on an empty List");
        } else if (cursor == back) { //if the cursor is in the back
            back = back.prev;
            cursor = null; //set to null
            index = -1;
            length--;
        } else {
            back = back.prev;
            back.next = null; //move the next element to null
            length--;
        }
    }

    // Deletes cursor element, making cursor undefined.
    // Pre: length() > 0, index() >= 0
    void delete() {
        if (index < 0 && length < 1)
            throw new RuntimeException("error since length is less than 1 and index is less than 0");
        if (cursor == back)
            deleteBack(); //if the cursor is in the back delete the back
        else if (cursor == front)
            deleteFront(); //delete front if the cursor is in the front
        else {
            cursor.prev.next = cursor.next;
            cursor.next.prev = cursor.prev;
            cursor = null; //set to null
            index = -1;
            length--;
        }
    }

    // Overrides Object's toString method. Returns a String
    public String toString() {
        String str = "";
        Node N;
        for (N = front; N != null; N = N.next) {
            str += N.toString();
            if (N != back) {
                str += " ";
            }
        }
        return str;
    }



    //copys list to a new List
    List copy() {
        List A = new List();
        Node N = this.front;
        while (N != null) {
            A.append(N.data); //COPY ALL THE DATA VALUES INTO THE NEW LIST
            N = N.next;
        }
        return A;
    }
}