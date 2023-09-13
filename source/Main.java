package source;

//Import all possible libraries
import java.util.*;
import java.io.*;
public class Main {
    public static final boolean ASCENDING = true;
    public static void main(String[] args) {
        //Make scanner first
        Scanner sc = new Scanner(System.in);
        //Store time
        long timeStart = 0;
        long timeDiff = 0;
        //Create a new random object
        Random random = new Random();
        //Print out the Ui first
        System.out.println("Enter the size of array:");
        int size = sc.nextInt();
        //Create a dynamic array of the input size
        int[] arr = new int[size];
        int[] copyArr = new int[size];
        System.out.println("Input S for testing: ");
        Sort.S = sc.nextInt();
        System.out.println("1. Best Case");
        System.out.println("2. Worst Case");
        System.out.println("3. Populate with random numbers");
        System.out.println("4. Manual input (not recommended for n -> inf)");
        System.out.println("5. Quit");
        int choice = sc.nextInt();
        switch (choice) {
            case 1: {
                //Assuming ascending, we just sort it in decreasing order and treat as worst case
                System.out.println("Populating elements in decreasing order... (worst case)");
                for (int i = 0; i < size; i++) {
                    arr[i] = size - i;
                }
                break;
            }
            case 2: {
                System.out.println("Populating elements in increasing order... (best case)");
                for (int i = 0; i < size; i++) {
                    arr[i] = i;
                }
                break;
            }
            case 3: {
                System.out.println("Populating elements randomly");
                for (int i = 0; i < size; i++) {
                    arr[i] = random.nextInt(size * 2);
                }
                break;
            }
            case 4: {
                System.out.println("Input each element: ");
                for (int i = 0; i < size; i++) {
                    arr[i] = sc.nextInt();
                }
                break;
            }
            case 5: {
                //Return from main and terminate program
                return;
            }
        }

        //Do some UI to test different sorting algorithms
        do {
            System.out.println("1. Reconfigure S, Current S:" + Sort.S);
            System.out.println("2. In Place Insertion Sort");
            System.out.println("3. Auxillary Insertion Sort");
            System.out.println("4. In Place Merge Sort");
            System.out.println("5. Auxillary Merge Sort");
            System.out.println("6. In Place Hybrid Sort");
            System.out.println("7. Auxillary Hybrid Sort");
            System.out.println("8. Print Array [not recommended as n -> inf]");
            System.out.println("9. Continue");
            choice = sc.nextInt();

            //Copy the array into a new variable
            System.arraycopy(arr, 0, copyArr, 0, size);

            //Want to copy an array, so we do not touch the initial random generated arrays
            switch (choice) {
                case 1: {
                    System.out.println("Input new S[" + Sort.S + "]:");
                    Sort.S = sc.nextInt();
                    break;
                }
                case 2: {
                    //Sort.insertionSort(copyArr, ASCENDING);
                    System.out.println("Input both range start end:");
                    int start = sc.nextInt();
                    int end = sc.nextInt();
                    copyArr = InsertionSort.insertionSortInRangeAux(copyArr, start, end);
                    Debug.printArray(copyArr);
                    break;
                }
                case 3: {
                    //Sort.insertionSort(copyArr, ASCENDING);
                    System.out.println("Input both range start end:");
                    int start = sc.nextInt();
                    int end = sc.nextInt();
                    InsertionSort.insertionSortInRangeIP(copyArr, start, end);
                    Debug.printArray(copyArr);
                    break;
                }
                case 4: //in place merge
                {
                    timeStart = System.nanoTime();
                    Sort.mergeSortInPlace(copyArr, 0, size - 1, ASCENDING);
                    timeDiff = System.nanoTime() - timeStart;
                    Debug.printArray(copyArr);
                    System.out.println("Time taken: " + timeDiff * Math.pow(10, -6) + "ms" + "/" + timeDiff * Math.pow(10, -9) + "s");
                    break;
                }
                case 5: //merge aux
                {
                    timeStart = System.nanoTime();
                    copyArr = Sort.mergeSortAuxillary(copyArr, 0, size - 1);
                    timeDiff = System.nanoTime() - timeStart;
                    //Debug.printArray(copyArr);
                    System.out.println("Key Comparisons: " + Sort.keyComparisons);
                    System.out.println("Time taken: " + timeDiff * Math.pow(10, -6) + "ms" + "/" + timeDiff * Math.pow(10, -9) + "s");
                    break;
                }
                case 6: //in place hybrid
                {
                    timeStart = System.nanoTime();
                    Sort.hybridSortInPlace(copyArr, 0, size - 1);
                    timeDiff = System.nanoTime() - timeStart;
                    //Debug.printArray(copyArr);
                    System.out.println("Key Comparisons: " + Sort.keyComparisons);
                    System.out.println("Time taken: " + timeDiff * Math.pow(10, -6) + "ms" + "/" + timeDiff * Math.pow(10, -9) + "s");
                    break;
                }
                case 7: //aux hybrid
                {
                    timeStart = System.nanoTime();
                    copyArr = Sort.hybridSortAuxillary(copyArr, 0, size - 1);
                    timeDiff = System.nanoTime() - timeStart;
                    //Debug.printArray(copyArr);
                    System.out.println("Key Comparisons: " + Sort.keyComparisons);
                    System.out.println("Time taken: " + timeDiff * Math.pow(10, -6) + "ms" + "/" + timeDiff * Math.pow(10, -9) + "s");
                    break;
                }
                case 8: {
                    Debug.printArray(arr);
                    break;
                }
            }

        } while (choice != 9);


        //Actual writing into file (test)
        int ans;
        FileWriter writer;
        //do {
        System.out.println("1. Fixed S but varying N");
        System.out.println("2. Fixed N but varying S");
        ans = sc.nextInt();
        if (ans == 1) {
            System.out.println("Input number of samples:");
            int samples = sc.nextInt();
            int step = 10000000 / samples;
            String line = "Size(n),S,Key Comparisons,Time(ms),Time(s)\n";
            System.out.println("Running Fixed S=" + Sort.S + " with Varying N with step: " + step);
            boolean first = true;
            //Size
            for (int sampleSize = 10; sampleSize <= 10000000; sampleSize += step) {
                int[] newArr = new int[sampleSize];
                // create array up to size(n)
                for (int j = 0; j < sampleSize; j++) {
                    newArr[j] = random.nextInt(sampleSize);
                }
                timeStart = System.nanoTime();
                newArr = Sort.hybridSortAuxillary(newArr, 0, sampleSize - 1);
                timeDiff = System.nanoTime() - timeStart;
                System.out.println("Sample Size: " + sampleSize + " | Key Comparisons: " + Sort.keyComparisons + "  ---  Time taken: "
                        + timeDiff * Math.pow(10, -6) + "ms/ " + timeDiff * Math.pow(10, -9) + "s");
                line += sampleSize + "," + Sort.S + "," + Sort.keyComparisons + "," + timeDiff * Math.pow(10, -9)
                        + "\n";
                //Try writing into a directory
                try {
                    writer = new FileWriter("data/S_" + Sort.S + "_VaryingN.csv");
                    writer.write(line);
                    writer.close();
                } catch (IOException e) {
                    System.out.println(e.getMessage());
                }
                //Ghetto method to start at step
                if(first)
                {
                    sampleSize = 0;
                    first = false;
                }
            }
            //else if (ans == 2)
            {

            }

            //}while (ans != 3);
        }

    }
}