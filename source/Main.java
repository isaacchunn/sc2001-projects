package source;

//Import all possible libraries
import java.util.*;
public class Main {

    public static final boolean ASCENDING = true;


    public static void main(String[] args) {
        //Make scanner first
        Scanner sc = new Scanner(System.in);

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
        switch(choice)
        {
            case 1: {
                //Assuming ascending, we just sort it in decreasing order and treat as worst case
                System.out.println("Populating elements in decreasing order... (worst case)");
                for (int i = 0; i < size; i++)
                {
                    arr[i] = size - i;
                }
                break;
            }
            case 2:
            {
                System.out.println("Populating elements in increasing order... (best case)");
                for (int i = 0; i < size; i++)
                {
                    arr[i] = i;
                }
                break;
            }
            case 3:
            {
                //Create a new random object
                Random random = new Random();
                System.out.println("Populating elements randomly");
                for(int i = 0; i < size; i++)
                {
                    arr[i] = random.nextInt(size);
                }
                break;
            }
            case 4:
            {
                System.out.println("Input each element: ");
                for(int i = 0; i < size; i++)
                {
                    arr[i] = sc.nextInt();
                }
                break;
            }
            case 5:
            {
                //Return from main and terminate program
                return;
            }
        }

        //Do some UI to test different sorting algorithms
        do {
            System.out.println("1. Reconfigure S, Current S:" + Sort.S);
            System.out.println("2. Insertion Sort");
            System.out.println("3. Merge Sort");
            System.out.println("4. Hybrid Sort");
            System.out.println("5. Print Array [not recommended as n -> inf]");
            System.out.println("6. Quit");
            choice = sc.nextInt();

            //Copy the array into a new variable
            System.arraycopy(arr, 0, copyArr, 0, size);

            //Want to copy an array, so we do not touch the initial random generated arrays
            switch(choice)
            {
                case 1:
                {
                    System.out.println("Input new S[" +Sort.S+"]:");
                    Sort.S = sc.nextInt();
                    break;
                }
                case 2:
                {
                    Sort.insertionSort(copyArr, ASCENDING);
                    Debug.printArray(copyArr);
                    break;
                }
                case 3:
                {
                    Sort.mergeSort(copyArr, 0, size -1, ASCENDING);
                    Debug.printArray(copyArr);
                    break;
                }
                case 4:
                {
                    Sort.hybridSort(copyArr);
                    Debug.printArray(copyArr);
                    break;
                }
                case 5:
                {
                    Debug.printArray(arr);
                    break;
                }
            }

        } while(choice != 6);


        /*
        int[] array = new int[]{14,40,31,28,3,15,17,51};

        Debug.printArray(array);
        //Sort.mergeSort(array, 0, array.length-1, true);
        Sort.insertionSort(array,true);
        Debug.printArray(array);
        */
    }


}