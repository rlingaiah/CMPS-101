//Rhea Lingaiah
//rlingaia
//pa3
//11/5/17

import java.io.*;
import java.util.Scanner;


public class Sparse {
    public static void main(String[] args) throws IOException {
        //Scanner in=null;
        //PrintWriter out=null;
        if (args.length != 2) { //if not given an input and output file
            System.err.println("Use: Sparse InFile OutFile");
            System.exit(1);
        }
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
        Matrix A = null;
        Matrix B = null;
        //String line= in.nextLine()+" ";
        while (in.hasNextInt()) {
            int x = in.nextInt();
            int a = in.nextInt();
            int b = in.nextInt();
            A = new Matrix(x); //size of Matrix is the number of integers in the list
            B = new Matrix(x);//size of the Matrix is equal to the num of integers in the list
            for (int i = 0; i < a; i++) {
                int rowVal = in.nextInt(); //load the row number
                int colVal = in.nextInt(); //load the column number
                double value = in.nextDouble(); //set the value number
                A.changeEntry(rowVal, colVal, value); //set the Matrix to the new row/column/value
            }


            for (int i = 0; i < b; i++) {
                int rowVal2 = in.nextInt(); //set the row number
                int colVal2 = in.nextInt(); //set the column number
                double value2 = in.nextDouble(); //set the value number
                B.changeEntry(rowVal2, colVal2, value2); //set the matrix to the new row/column/value numbers
            }
        }
        // PRINT THE VALUES ACCORDING TO THE PDF-------------------------
        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);
        out.println("B has " + B.getNNZ() + " non-zero entries:");
        out.println(B);
        out.println("(1.5)*A =");
        out.println(A.scalarMult(1.5));
        out.println("A+B =");
        out.println(A.add(B));
        out.println("A+A =");
        out.println(A.add(A));
        out.println("B-A =");
        out.println(B.sub(A));
        out.println("A-A =");
        out.println(A.sub(A));
        out.println("Transpose(A) =");
        out.println(A.transpose());
        out.println("A*B =");
        out.println(A.mult(B));
        out.println("B*B =");
        out.println(B.mult(B));
//END OF PRINTING TO OUT FILE
        in.close(); //CLOSE THE IN AND OUT FILES
        out.close();

    }
}
