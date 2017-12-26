//Rhea Lingaiah
//rlingaia
//pa3
//11/5/17


public class Matrix {
    //Entry Class:
    private class Entry {
        int column;
        double value;

        Entry(int column, double value) {
            this.column = column;
            this.value = value;
        }

        public String toString() {
            return "(" + column + ", " + value + ")";
        }

        public boolean equals(Object x) {
            boolean eq = false;
            Entry that;
            if (x instanceof Entry) {
                that = (Entry) x;
                eq = (this.column == that.column && this.value == that.value);
            }
            return eq;
        }
    }
    //END of Entry

    List[] row; //List for each row in the matrix
    int size = 0;
    int nnz = 0;

    // Constructor
    Matrix(int n) // Makes a new n x n zero Matrix. pre: n>=1
    {
        if (n >= 1) {
            size = n;
            row = new List[n + 1];
            for (int i = 0; i <= n; i++) {
                row[i] = new List();
            }
        }

    }

    // Access functions
    int getSize() // Returns n, the number of rows and columns of this Matrix
    {
        return size;
    }

    int getNNZ() // Returns the number of non-zero entries in this Matrix
    {

        return nnz;
    }

    public boolean equals(Object x)
    // overrides Object's equals() method
    {
        Matrix that;
        boolean eq = false;
        if (x instanceof Matrix) {
            that = (Matrix) x;
            if (getSize() != that.getSize() || getNNZ() != that.getNNZ()) //if the size or nonzero numbers are not the same then false
            {
                return false;
            }
            if (getSize() == that.getSize()) {
                if (getNNZ() == that.getNNZ()) { //if the size and nonzero numbers are the same then returns true
                    for (int i = 0; i < getSize(); i++) {
                        if (row[i].equals((that.row[i]))) //go through the list to see check each value
                            return true;
                    }
                }
            }
        }
        return eq;
    }

    // Manipulation procedures----------------------------------------
    void makeZero()
    // sets this Matrix to the zero state
    {
        if (nnz == 0) {
            throw new RuntimeException("makeZero() called a list that is already zero");
        }
        for (int i = 0; i < getSize(); i++) {
            row[i].clear();
        }
        nnz = 0;
    }

    Matrix copy()// returns a new Matrix having the same entries as this Matrix
    {
        Matrix M = new Matrix(getSize());
        for (int i = 1; i <= getSize(); i++) {
            row[i].moveFront(); //move to the front of the list
            if (row[i].length() > 0) {
                Entry vals = (Entry) row[i].get();  //get each entry
                while (row[i].index() > -1) {
                    vals = new Entry(vals.column, vals.value);  //set a new val equal to the entry from before
                    M.changeEntry(i, vals.column, vals.value);  //insert the new val into the new matrix
                    row[i].moveNext(); //move onto the next entry
                }
            }
        }
        return M;
    }




    void changeEntry(int i, int j, double x)
    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    {
        if (i > getSize() || j > getSize() || i < 1 || j < 1) {
            throw new RuntimeException("error:can't change row or column with incorrect size");
        } else {
            boolean flag = true; //use this flag to break out of the while loop
            if (row[i].length() <= 0) {// //if there are no entries in the list
                if (x != 0.0) {         //and the value is not equal to 0.0
                    row[i].append(new Entry(j, x)); //append the value into the List
                    nnz++;      //increment the nonzero number
                }
            } else if (row[i].length() > 0) {   //otherwise if the length is not equal to 0
                row[i].moveFront();
                while (row[i].index() > -1 && flag) { //if the index of the list is not null
                    Entry entry = (Entry) row[i].get();
                    if (entry.column >= j) { //if the column is bigger than the column in the other matrix
                        if (j == entry.column && x == 0) {
                            row[i].delete();    //delete since the value is equal to 0.0
                            nnz--;              //decrement the nonzero number

                        }
                        if (j == entry.column && x == entry.value) {//check for when the value is already in the list
                            break;          //do nothing
                        }
                        if (j == entry.column && x != 0) {
                            entry.value = x;        //set the new double as the the entry value
                        } else if (x != 0) {
                            row[i].insertBefore(new Entry(j, x)); //else insert the entry before
                            nnz++;                  //increment nonzero number count
                        }
                        flag = false;               //change the flag to break out of the loop
                    } else if (j > entry.column && x != 0 && row[i].get().equals(row[i].back())) { //edge case to check if the entry is at the back
                        row[i].append(new Entry(j, x));     //insert the entry in the back
                        nnz++;                               //increase the nonzero count
                        flag = false;                       //flag set to false to break out of the loop
                    } else if (j > entry.column) {
                        row[i].moveNext();
                    }
                }

            }
        }

    }

    Matrix scalarMult(double x)
    // returns a new Matrix that is the scalar product of this Matrix with x
    {
        Matrix M = new Matrix(getSize());
        double scaleVal;
        for (int i = 1; i <= getSize(); i++) {

            row[i].moveFront();                             //move to the front of the list
            while (row[i].index() > -1) {
                Entry entry = (Entry) (row[i].get());
                scaleVal = entry.value * x;                 //multiply the x and the entry.value
                M.changeEntry(i, entry.column, scaleVal);   //change the matrix to have the new multiplied value
                row[i].moveNext();                          //move to the next element in the list
            }
        }
        M.nnz = nnz;             //set the new nonzero number to the matrix
        return M;
    }

    Matrix add(Matrix M) {
        Matrix N = new Matrix(getSize());
        if (this.getSize() != M.getSize()) {
            throw new RuntimeException("error:can't add different sizes");
        }
        if (this.equals(M)) {
            return this.scalarMult(2);              //if the matrixs are the same then multiply all the entries by 2
        }
        for (int i = 1; i <= getSize(); i++) {
            this.row[i].moveFront();                //move the matrix to the front
            M.row[i].moveFront();                   //move the other matrix to the front
            while (this.row[i].index() != -1 || M.row[i].index() != -1) {
                if (this.row[i].index() != -1 && M.row[i].index() == -1) //check if one matrix is null and the other is not
                {
                    N.changeEntry(i, ((Entry) this.row[i].get()).column, ((Entry) this.row[i].get()).value);//set the value equal to the matrix that is not null
                    this.row[i].moveNext();
                } else if (this.row[i].index() == -1 && M.row[i].index() != -1) {//check if the other matrix is null
                    N.changeEntry(i, ((Entry) M.row[i].get()).column, ((Entry) M.row[i].get()).value);//set the value equal to the matrix that is not null
                    M.row[i].moveNext();
                } else if (this.row[i].index() != -1 && M.row[i].index() != -1) {
                    Entry entry2 = (Entry) M.row[i].get();
                    Entry entry1 = (Entry) this.row[i].get();
                    if (entry1.column < entry2.column) { //if the entry column for one is greater
                        N.changeEntry(i, entry1.column, entry1.value); //change the column and value to the greater one
                        this.row[i].moveNext();
                    } else if (entry1.column > entry2.column) { //if the entry column is greater
                        N.changeEntry(i, entry2.column, entry2.value);//change the column and value to the other greater one
                        M.row[i].moveNext();
                    } else { //until the two columns are equal
                        double added = entry1.value + entry2.value; //add the entry values together
                        N.changeEntry(i, entry1.column, added); //set the new matrix with the new entry values
                        this.row[i].moveNext();
                        M.row[i].moveNext();
                    }
                }

            }
        }
        return N;
    }

    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M) {
        Matrix N = new Matrix(getSize());
        if (this.getSize() != M.getSize()) {
            throw new RuntimeException("error:can't add different sizes");
        }
        if (this == M) {
            return N; //if the two matrixs are the same return the new empty matrix
        }
        for (int i = 1; i <= getSize(); i++) {
            this.row[i].moveFront(); //move to the front of the matrix
            M.row[i].moveFront(); //move to the front of the matrix
            while (this.row[i].index() != -1 || M.row[i].index() != -1) {
                if (this.row[i].index() != -1 && M.row[i].index() == -1) {//check if one matrix is null and the other is not
                    N.changeEntry(i, ((Entry) this.row[i].get()).column, ((Entry) this.row[i].get()).value);// set the values to the matrix that is not null
                    this.row[i].moveNext(); //go through this.matrix
                } else if (this.row[i].index() == -1 && M.row[i].index() != -1) { //check if one matrix is null and the other is not
                    N.changeEntry(i, ((Entry) M.row[i].get()).column, -((Entry) M.row[i].get()).value);//set the values to the matrix that isn't null
                    M.row[i].moveNext(); //go through M.matrix
                } else if (this.row[i].index() != -1 && M.row[i].index() != -1) {
                    Entry entry2 = (Entry) M.row[i].get();
                    Entry entry1 = (Entry) this.row[i].get();
                    if (entry1.column < entry2.column) {
                        N.changeEntry(i, entry1.column, entry1.value); //change the column and value to the larger column entry
                        this.row[i].moveNext();

                    } else if (entry1.column > entry2.column) {
                        N.changeEntry(i, entry2.column, -entry2.value);//change the column and value to subtract the larger column entry
                        M.row[i].moveNext();
                    } else {
                        if (entry1.value - entry2.value != 0) {
                            N.changeEntry(i, entry1.column, (entry1.value - entry2.value)); // subtract the entry values if it is not equal to 0.0
                        }

                        this.row[i].moveNext();
                        M.row[i].moveNext();
                    }
                }

            }
        }

        return N;
    }

    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix transpose() {
        // returns a new Matrix that is the transpose of this Matrix
        Matrix M = new Matrix(getSize());
        if (getSize() == M.getSize()) { //if the sizes of matrixs are the same
            for (int i = 1; i <= size; i++) {
                row[i].moveFront();
                while (row[i].index() > -1) {
                    Entry entry = (Entry) row[i].get();
                    M.changeEntry(entry.column, i, entry.value); //swap the row and column value to transpose
                    row[i].moveNext();
                }
            }
        }

        M.nnz = nnz; //set the nonzero value to the matrix
        return M;
    }

    public static double dot(List P, List Q) {
        //method created to do the multiplication math
        P.moveFront();
        Q.moveFront();
        double product = 0;
        Entry entry1;
        Entry entry2;
        while (Q.index() > -1 && P.index() > -1) { //check if the indexs are not null
            entry1 = (Entry) P.get();
            entry2 = (Entry) Q.get();
            if (entry1.column > entry2.column) {
                Q.moveNext();
            } else if (entry1.column == entry2.column) {
                product += (entry1.value * entry2.value); //multiply the entry values together
                Q.moveNext(); //move next in the lists
                P.moveNext();
            } else { //(entry1.column<entry2.column)
                P.moveNext();
            }
        }


        return product; //return the multiplies product
    }

    Matrix mult(Matrix M) {
        // returns a new Matrix that is the product of this Matrix with M
        // pre: getSize()==M.getSize()
        Matrix N = new Matrix(getSize());
        if (M.getSize() == getSize()) { //check if the sizes of the Matrixes are the same
            //Matrix N = new Matrix(size);
            M = M.transpose();
            double product;
            for (int i = 1; i <= getSize(); i++) {
                for (int j = 1; j <= getSize(); j++) {

                    product = dot(this.row[i], M.row[j]); //new entry value that has been multiplied
                    N.changeEntry(i, j, product); //new product
                }
            }
        }

        return N;
    }

    // Other functions
    public String toString() {
        String str = "";
        for (int i = 1; i <= getSize(); i++) {
            if (row[i].length() > 0) { //check if the length is not 0
                str = str + (i + ": " + row[i] + "\n"); //print out the matrix
            }
        }
        return str;
    }
}