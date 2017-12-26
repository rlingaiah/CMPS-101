//-----------------------------------------------------------------------------
//Rhea Lingaiah
//rlingaia
//pa3
//11/5/17
//  ListTest.java
//  A test client for the List ADT. Use this to test your list module. The
//  correct output is given below.
//-----------------------------------------------------------------------------

public class ListTest {
    public static void main(String[] args) {
        List A = new List();
        List B = new List();

        for (int i = 1; i <= 10; i++) {
            A.append(i);
            B.prepend(i);
        }
        System.out.println(A);
        System.out.println(B);

        for (A.moveFront(); A.index() >= 0; A.moveNext()) {
            System.out.print(A.get() + " ");
        }
        System.out.println();
        for (B.moveBack(); B.index() >= 0; B.movePrev()) {
            System.out.print(B.get() + " ");
        }
        System.out.println();

        List C = B.copy();
        System.out.println(A.equals(B));
        System.out.println(B.equals(C));
        System.out.println(C.equals(A));

        A.moveFront();
        for (int i = 0; i < 5; i++) A.moveNext();
        A.insertBefore(-1);
        for (int i = 0; i < 9; i++) A.moveNext();
        A.insertAfter(-2);
        for (int i = 0; i < 5; i++) A.movePrev();
        B.delete();
        System.out.println(B);
        System.out.println(B.length());
        A.clear();
        System.out.println(A.length());
    }
}