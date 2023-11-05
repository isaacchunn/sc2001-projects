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
     * An unbounded knapsack algorithm that calcualtes the max profit given some weights and profit
     * with a known capacity.
     * Unbounded - items can be repicked an infinite amount of times.
     *
     * @param weights  An array of weights
     * @param profits  An array of profits
     * @param capacity The max capacity of our knapsack.
     * @return The max profit of items that we can fit into our knapsack.
     */
    public static int unboundedKnapsack(int[] weights, int[] profits, int capacity) {
        //Create a 1D array with length capacity + 1
        int[] dp = new int[capacity + 1];
        //In this case, newly created int arrays in java are initialized to 0
        //For other languages, initialization may be needed, that takes an order of O(n) time.

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

    public static void main(String[] args) {
        int capacity = 14;
        int[] w1 = {4, 6, 8};
        int[] p1 = {7, 6, 9};

        int max1 = unboundedKnapsack(w1, p1, capacity);
        System.out.println("The max value is " + max1);
    }
}
