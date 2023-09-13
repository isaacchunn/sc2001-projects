public class Sort {
    public static void mergeSort(int[] arr, int start, int end, boolean ascending)
    {
        int mid = (start + end) / 2;
        if(start < end)
        {
            mergeSort(arr, start, mid , ascending);
            mergeSort(arr, mid + 1, end , ascending);
            merge(arr, start, mid, end);
        }
    }

    private static void merge(int [] arr, int start, int mid, int end)
    {
        
    }
    public static void hybridSort()
    {

    }
}
