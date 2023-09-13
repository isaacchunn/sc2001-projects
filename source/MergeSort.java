package source;
/* NOTES:
- A single element is treated as a small/trivial problem
- Follows divide and conquer hence a recursive algorithm
- Merge is probably the most confusing part with for loops as compared to creating another list
- Space efficient but slower time on this iterative approach

//Time Complexity Analysis: (TODO: Try with Master's Theorem)
// Best case (nlogn)
// Average case (nlogn) - Squeeze Theorem
// Worst Case (nlogn)

- Sample List
-[9,3,7,5,6,4,8,2]
  ^     ^       ^
start  mid     end
*/
public class MergeSort {

    //Main merge sort function
    public static void mergeSort(int[] arr, int start, int end, boolean ascending) {
        //Check if start < end
        //If start == end (single element (one index))
        //If start < end (at least 2 elements, considered a "large problem")
        if (start < end) {
            //Calculate mid
            int mid = (start + end) / 2;
            //Split the list into two halfs and call recursively
            mergeSort(arr, start, mid, ascending);
            mergeSort(arr, mid + 1, end, ascending);

            if (ascending)
                mergeAscending(arr, start, mid, end);
            else
                mergeDescending(arr, start, mid, end);
        }
    }

    public static void mergeAscending(int[] arr, int start, int mid, int end) {
        int i, temp;
        //Settle indexes from each part of the list
        int a = start;
        //Mid + 1 is first element of our list
        int b = mid + 1;

        //Print out what is being merged
        //printInRange(arr,start,mid);
        //printInRange(arr, mid+1,end);

        //Base case is settled outside
        //Do a while loop to check which one finishes first, a or b.
        while(a <=mid && b <=end)
        {
            //Increment our key comparisons as there is a guaranteed check anyway
            Sort.keyComparisons++;

            //Case 1: arr[a] < arr[b] - do nothing as it is in correct slot, so just increment a
            if(arr[a] < arr[b])
            {
                a++;
            }
            //Case 2: arr[a] > arr[b] - have to right shift by one and store temp
            else if (arr[a] > arr[b])
            {
                //Store index at 2nd list as our temp
                temp = arr[b++];
                //Go backwards from mid to a to right shift
                for(i = ++mid; i > a; i--)
                {
                    arr[i] = arr[i-1];
                }
                //Then assign the temp at a
                arr[a++] = temp;
            }
            //Case 3: arr[a] == arr[b], slot[a] in correct position, so move slot[b] beside slot[a]
            else if (arr[a] == arr[b])
            {
                //Since we are incrementing mid each time
                //Assuming a list that was sorted from the front, at the last 2 repetitions, our mid and end will be as follows
                //[x,x,x,x,x,x, 9 , 9]
                //              ^   ^
                //             mid  end
                //Which means we can break as they are already assumed to be sorted and the largest, which in theory saves the time taken to compute everything else in the if statement
                if(a == mid && b == end)
                    break;

                temp = arr[b++];
                //Increment a to make space
                a++;
                //Go backwards from mid to a to right shift
                for(i = ++mid; i > a; i--)
                {
                    arr[i] = arr[i-1];
                }
                //Then assign the temp at a
                arr[a++] = temp;
            }
        }
    }

    private static void mergeDescending(int[] arr, int start, int mid, int end)
    {
        int i, temp;
        //Settle indexes from each part of the list
        int a = start;
        //Mid + 1 is first element of our list
        int b = mid + 1;

        //Print out what is being merged
        //printInRange(arr,start,mid);
        //printInRange(arr, mid+1,end);

        //Base case is settled outside
        //Do a while loop to check which one finishes first, a or b.
        while(a <=mid && b <=end)
        {
            //Increment our key comparisons as there is a guaranteed check anyway
            Sort.keyComparisons++;

            //Case 1: arr[a] > arr[b] - do nothing as it is in correct slot, so just increment a
            if(arr[a] > arr[b])
            {
                a++;
            }
            //Case 2: arr[a] < arr[b] - have to right shift by one and store temp
            else if (arr[a] < arr[b])
            {
                //Store index at 2nd list as our temp
                temp = arr[b++];
                //Go backwards from mid to a to right shift
                for(i = ++mid; i > a; i--)
                {
                    arr[i] = arr[i-1];
                }
                //Then assign the temp at a
                arr[a++] = temp;
            }
            //Case 3: arr[a] == arr[b], slot[a] in correct position, so move slot[b] beside slot[a]
            else if (arr[a] == arr[b])
            {
                //Since we are incrementing mid each time
                //Assuming a list that was sorted from the front, at the last 2 repetitions, our mid and end will be as follows
                //[x,x,x,x,x,x, 9 , 9]
                //              ^   ^
                //             mid  end
                //Which means we can break as they are already assumed to be sorted and the largest, which in theory saves the time taken to compute everything else in the if statement
                if(a == mid && b == end)
                    break;

                temp = arr[b++];
                //Increment a to make space
                a++;
                //Go backwards from mid to a to right shift
                for(i = ++mid; i > a; i--)
                {
                    arr[i] = arr[i-1];
                }
                //Then assign the temp at a
                arr[a++] = temp;
            }
        }
    }
}
