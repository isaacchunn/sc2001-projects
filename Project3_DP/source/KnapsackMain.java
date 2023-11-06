package Project3_DP.source;

/**
 * Problem Definition:
 * We have a knapsack of capacity weight C (a positive integer) and n types of objects.
 * Each object of the ith type has weight wi and profit pi (all wi and all pi are positive
 * integers, i = 0, 1, …, n-1). There are *unlimited* supplies of each type of objects. Find
 * the largest total profit of any set of the objects that fits in the knapsack.
 * <p>
 * <p>
 * Some notes: Profit = 0 when either capacity or number of objects is 0.
 */
public class KnapsackMain {

    /**
     * An unbounded knapsack algorithm that calculates the max profit given some weights and profit
     * with a known capacity.
     * Unbounded - items can be re picked an infinite amount of times.
     *
     * @param weights  An array of weights
     * @param profits  An array of profits
     * @param capacity The max capacity of our knapsack.
     * @return The max profit of items that we can fit into our knapsack.
     */
    public static int unboundedKnapsack(int[] weights, int[] profits, int capacity) {
        //Create a 1D array with length capacity + 1
        int[] dp = new int[capacity + 1];
        //Loop through our dp array starting from index 1, as index 0 means 0 capacity, which is trivial.
        for (int i = 1; i < dp.length; i++) //O(n)
        {
            //At each index, loop through all weights
            for (int j = 0; j < weights.length; j++) //O(n)
            {
                //If the current weight is less than or equals to capacity at index i
                if (weights[j] <= i) {
                    //Update our dp answer array to max of the following cases:
                    //Case 1: Do not include -> dp[i]
                    //Case 2: Include -> Take the profit of current item + previously memorized value at i - weights[j]
                    dp[i] = Math.max(dp[i], dp[i - weights[j]] + profits[j]);
                }
            }
        }
        //Our max value is the last value of the array
        return dp[capacity];
    }

    /**
     * An unbounded knapsack algorithm that calculates the max profit given some weights and profit
     * with a known capacity.
     * Unbounded - items can be re picked an infinite amount of times.
     *
     * @param weights  An array of weights
     * @param profits  An array of profits
     * @param capacity The max capacity of our knapsack.
     * @return The max profit of items that we can fit into our knapsack.
     */
    public static int unboundedKnapsack2(int[] weights, int[] profits, int capacity) {
        //Create a 1D array with length capacity + 1
        int[] dp = new int[capacity + 1];
        //Declare a new array that holds the index of our objects
        int[] idx = new int[capacity + 1];
        //Initialization
        for(int i = 0; i <= capacity; i++)
        {
            idx[i] = -1;
        }
        //Loop through our dp array starting from index 1, as index 0 means 0 capacity, which is trivial.
        for (int i = 1; i < dp.length; i++) //O(n)
        {
            //At each index, loop through all weights
            for (int j = 0; j < weights.length; j++) //O(n)
            {
                //If the current weight is less than or equals to capacity at index i
                if (weights[j] <= i) {
                    //If the current value is lower than if we include the object + profit
                    if (dp[i] < dp[i - weights[j]] + profits[j]) {
                        dp[i] = dp[i - weights[j]] + profits[j];
                        //Update our idx of item chosen (index j)
                        idx[i] = j;
                    }
                }
            }
        }
        System.out.println("The included objects in the knapsack are (weight,profit):");
        int c = capacity;
        int w = 0;
        //Now, we crawl back upwards to find out which object was included.
        while (c > 0 && dp[c] != 0) {
            //Get the item index at this capacity
            int item = idx[c];
            //Minus from our capacity and print out the object put.
            c -= weights[item];
            //Increment our total weight used
            w += weights[item];
            System.out.print("(" + weights[item] + "," + profits[item] + ")");
        }
        System.out.println("\nTotal weight used: " + w + "/" + capacity);
        System.out.println("The max profit is: " + dp[capacity]);
        //Our max value is the last value of the array

        for(int i = 0; i < dp.length; i++)
        {
            System.out.println(i + " : " + dp[i] + " " + idx[i]);
        }
        return dp[capacity];
    }

    public static void main(String[] args) {
        int capacity = 14;
        int[] w1 = {4, 6, 8};
        int[] p1 = {7, 6, 9};

        int max1 = unboundedKnapsack2(w1, p1, capacity);

        int[] w2 = {5, 6, 8};
        int[] p2 = {7, 6, 9};

        int max2 = unboundedKnapsack2(w2, p2, capacity);
    }
}
