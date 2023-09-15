package source;

//Import all possible libraries
import java.util.*;
import java.io.*;
public class Main {
    public static final int MAX_SVALUE = 128;
    public static final int MAX_SAMPLES = 10000000;
    public static void main(String[] args) {
        //Make scanner first
        Scanner sc = new Scanner(System.in);
        //Store time
        long timeStart = 0;
        long timeDiff = 0;
        //Create a random object
        Random random = new Random();
        //Actual writing into file (test)
        int ans;
        FileWriter writer;

        System.out.println("1. Fixed S but varying N");
        System.out.println("2. Fixed N but varying S");
        System.out.println("3. Algorithm Comparisons");
        ans = sc.nextInt();
        if (ans == 1) {
            System.out.println("===Fixed S but varying N===");
            //Input S
            System.out.println("Input S: ");
            Sort.S = sc.nextInt();
            System.out.println("Input number of samples:");
            int samples = sc.nextInt();
            int step = 10000000 / samples;
            String line = "Size(n),S,Key Comparisons,Time(ms),Time(s)\n";
            System.out.println("Running Fixed S=" + Sort.S + " with Varying N with step: " + step);
            //Always start with 10 samples, and then run later on
            boolean first = true;
            int sampleSize;
            //Size
            for (sampleSize = step; sampleSize <= 10000000; sampleSize += step) {
                int[] newArr = new int[sampleSize];
                // create array up to size(n)
                for (int j = 0; j < sampleSize; j++) {
                    newArr[j] = random.nextInt(sampleSize);
                }
                timeStart = System.nanoTime();
                newArr = Sort.hybridSortAuxiliary(newArr, 0, sampleSize - 1);
                timeDiff = System.nanoTime() - timeStart;
                System.out.println("Sample Size: " + sampleSize + " | S: " + Sort.S + " | Key Comparisons: " + Sort.keyComparisons + " | Time: "
                        + timeDiff * Math.pow(10, -6) + "ms/" + timeDiff * Math.pow(10, -9) + "s");
                line += sampleSize + "," + Sort.S + "," + Sort.keyComparisons + "," + timeDiff *Math.pow(10,-6) + ","+ timeDiff * Math.pow(10, -9)
                        + "\n";
            }
            //Try writing into a directory
            try {
                writer = new FileWriter("data/FixedS_VaryingN/S_" + Sort.S + "_VaryingN_"+ (sampleSize - step) +".csv");
                writer.write(line);
                writer.close();
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }

        }
        else if (ans == 2)
        {
                String line = "Size(n),S,Key Comparisons,Time(ms),Time(s)\n";
                System.out.println("===Fixed N but varying S===");
                System.out.println("Input size (n) of array:");
                //Input n
                int n = sc.nextInt();
                //Populate an array based on n
                int[] arr = new int[n];
                //Populate with random stuff
                for(int i = 0; i < n; i++)
                {
                    arr[i] = random.nextInt(n * 2);
                }

                //Then for each S we conduct our sort on our n elements and test our S
                for(int i = 1; i <= MAX_SVALUE; i++)
                {
                    //Update our variable
                    Sort.S = i;
                    //Copy the array into a new array
                    int[] copyArr = new int[n];
                    System.arraycopy(arr,0,copyArr,0, n - 1);

                    timeStart = System.nanoTime();
                    //Sort the array
                    copyArr = Sort.hybridSortAuxiliary(copyArr,0,n-1);
                    timeDiff = System.nanoTime() - timeStart;
                    System.out.println("Sample Size: " + n + " | S: " + Sort.S + " | Key Comparisons: " + Sort.keyComparisons + " | Time: "
                            + timeDiff * Math.pow(10, -6) + "ms/" + timeDiff * Math.pow(10, -9) + "s");
                    //Append into our line
                    line += n + "," + Sort.S + "," + Sort.keyComparisons + "," + timeDiff *Math.pow(10,-6) + ","+ timeDiff * Math.pow(10, -9)
                            + "\n";
                }

                //Then write into our file after all is done
                //Try writing into a directory
                try {
                    writer = new FileWriter("data/FixedN_VaryingS/N_" + n + "_S_1to"+ MAX_SVALUE +".csv");
                    writer.write(line);
                    writer.close();
                } catch (IOException e) {
                    System.out.println(e.getMessage());
                }


        }
        else if (ans == 3)
        {
            System.out.println("===Merge Sort In Place, Aux vs Hybrid Aux===");
            //Input S
            System.out.println("Input S: ");
            Sort.S = sc.nextInt();
            System.out.println("Input size (n) of array:");
            //Input n
            int n = sc.nextInt();
            System.out.println("Input Samples to calculate average:");
            int samples = sc.nextInt();

            //Populate an array based on n
            int[] arr = new int[n];
            int[] copyArr = new int[n];

            //Handle initial string
            String line = " ,S = " + Sort.S +",Size(N) = " + n + "\n";
            line += " ,Merge" + ", , ," +"Hybrid" +"\n";
            line += " ,Key Comparisons, Time taken(ms), ,Key Comparisons, Time taken(ms)\n";

            //Make only one object for in place as it takes very long.
            //Make an array of samples for merge aux and hybridaux
            Result[] mergeResults = new Result[samples];
            Result[] hybridResults = new Result[samples];

            //Store average variables
            long averageMergeKey =0;
            double averageMergeTime = 0;
            long averageHybridKey = 0;
            double averageHybridTime = 0;

            //Run up to sample times for merge and hybrid sort
            for(int i = 0; i < samples; i++)
            {
                //Populate with random stuff per sample
                for(int j = 0; j < n; j++)
                {
                    arr[j] = random.nextInt(n * 2);
                }
                //Copy into array
                System.arraycopy(arr,0,copyArr,0,n-1);
                //MERGE
                timeStart = System.nanoTime();
                //Sort the array
                Sort.mergeSortInPlace(copyArr,0,n-1, true);
                timeDiff = System.nanoTime() - timeStart;
                System.out.println("[Merge Sort: " + (i+1) +"] Sample Size: " + n + " | S: " + Sort.S + " | Key Comparisons: " + Sort.keyComparisons + " | Time: "
                        + timeDiff * Math.pow(10, -6) + "ms/" + timeDiff * Math.pow(10, -9) + "s");
                mergeResults[i] = new Result(Sort.keyComparisons,timeDiff * Math.pow(10, -6),timeDiff * Math.pow(10, -9));
                //Add the key comparisons and time
                averageMergeKey += Sort.keyComparisons;
                averageMergeTime += timeDiff * Math.pow(10, -6);

                System.arraycopy(arr,0,copyArr,0,n-1);
                //HYBRID
                timeStart = System.nanoTime();
                //Sort the array
                copyArr = Sort.hybridSortAuxiliary(copyArr,0,n-1);
                timeDiff = System.nanoTime() - timeStart;
                System.out.println("[Hybrid Sort: " + (i+1) +"] Sample Size: " + n + " | S: " + Sort.S + " | Key Comparisons: " + Sort.keyComparisons + " | Time: "
                        + timeDiff * Math.pow(10, -6) + "ms/" + timeDiff * Math.pow(10, -9) + "s");
                hybridResults[i] = new Result(Sort.keyComparisons,timeDiff * Math.pow(10, -6),timeDiff * Math.pow(10, -9));
                averageHybridKey += Sort.keyComparisons;
                averageHybridTime += timeDiff * Math.pow(10, -6);
            }

            //Now append each line up to samples
            for(int i = 0; i < samples; i++)
            {
                line += " ," + mergeResults[i].getKeyComparisons() + "," + mergeResults[i].getTimeMs() + ", ," + hybridResults[i].getKeyComparisons() + "," + hybridResults[i].getTimeMs()+"\n";
            }
            //Make two new lines
            line += "\n";

            //Then write the average
            line +="Average," + (int)averageMergeKey/samples + "," + averageMergeTime/samples + ", ," + (int)averageHybridKey/samples + "," + averageHybridTime/samples +"\n";


            try{
                writer= new FileWriter("data/Sort_Comparisons/S_" + Sort.S+"_N_" + n +".csv");
                writer.write(line);
                writer.close();
            }catch (IOException e)
            {
                System.out.println(e.getMessage());
            }
            //Do aux merge first



        }

    }

}
