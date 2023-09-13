package source;

public class HybridSort {

    public static void hybridSort(int[] arr, int start, int end)
    {
        //This is a trivial case (just 1 element, so no sorting required)
        if(start == end)
        {
            return;
        }
        // 0 indexed size
        int size = end - start + 1;
        //If size < S , we do insertion
        if(size <= Sort.S)
        {
            //We conduct insertion sort from start to end?
            InsertionSort.insertionSortInRange(arr, start, end);

        }
        else // > S, so we do merge
        {
            //We conduct merge sort
            int mid = (start + end) / 2;
            hybridSort(arr, start, mid);
            hybridSort(arr, mid + 1, end);
            MergeSort.mergeAscending(arr, start, mid, end);
        }
    }
}
