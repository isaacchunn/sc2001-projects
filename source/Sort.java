package source;

public class Sort {

    //Stores the key comparisons
    public static long keyComparisons = 0;
    //Stores our given S;
    public static int S = 1;

    //Wrapper function only
    public static void mergeSort(int[] arr, int start, int end, boolean ascending)
    {
        //Reset our key comparisons to be 0
        Sort.keyComparisons = 0;
        MergeSort.mergeSort(arr,start,end, ascending);
        //Print out key comparisons
        String mode = ascending ? "[Ascending Merge Sort] " : "[Descending Merge Sort] ";
        System.out.println(mode + "Key Comparisons: " + keyComparisons);

    }
    public static void hybridSort(int[] arr, int start, int end)
    {
        Sort.keyComparisons = 0;
        HybridSort.hybridSort(arr, start, end);
        //String mode = ascending ? "[Ascending Insertion Sort] " : "[Descending Insertion Sort] ";
        System.out.println("Key Comparisons: " + keyComparisons);

    }

    public static void insertionSort(int[] arr, boolean ascending)
    {
        Sort.keyComparisons = 0;
        if(ascending)
            InsertionSort.insertionSortAscending(arr);
        else
            InsertionSort.insertionSortDescending(arr);

        //Print out key comparisons
        String mode = ascending ? "[Ascending Insertion Sort] " : "[Descending Insertion Sort] ";
        System.out.println(mode + "Key Comparisons: " + keyComparisons);
    }
}
