package Project1_HybridSort.source;

import java.util.*;
public class Debug {

    public static void printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.print(array[i]);
            if(i != array.length -1)
                System.out.print(",");
        }
        System.out.println();
    }

    public static void printArrayInRange(int[] array, int start, int end)
    {
        System.out.print("[");
        for(int i = start; i <= end; i++)
        {
            System.out.print(array[i]);
            if(i != end)
                System.out.print(",");
        }
        System.out.println("]");
    }
}
