package source;
/*
Insertion Sort
    Best Case: O(n)
    Worst Case: O(n^2)
    Average Case: O(n^2)
*/
public class InsertionSort {
    public static void insertionSortAscending(int[] arr) {
        int temp;
        for (int i = 1; i < arr.length; i++) {
            for (int j = i; j > 0; j--) {
                Sort.keyComparisons++;
                //If condition check to see if the previous value is larger
                if (arr[j] < arr[j - 1]) {
                    //Swap between the two
                    temp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = temp;
                } else
                    break;
            }
        }
    }
    public static void insertionSortDescending(int[] arr)
    {
        for (int i = 1; i < arr.length; i++) {
            for (int j = i; j > 0; j--) {
                Sort.keyComparisons++;
                //If condition check to see if the previous value is larger
                if (arr[j] > arr[j - 1]) {
                    //Swap between the two
                    int temp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = temp;
                } else
                    break;
            }
        }
    }

}
