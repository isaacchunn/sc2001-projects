package Project1_HybridSort.source;

public class Result {
    private long keyComparisons;
    private double timeMs;
    private double timesS;

    public Result(long keyComparisons, double timeMs, double timeS)
    {
        this.keyComparisons = keyComparisons;
        this.timeMs = timeMs;
        this.timesS = timeS;
    }

    public long getKeyComparisons() {
        return keyComparisons;
    }

    public double getTimeMs() {
        return timeMs;
    }

    public double getTimesS() {
        return timesS;
    }
    public void setKeyComparisons(long keyComparisons) {
        this.keyComparisons = keyComparisons;
    }

    public void setTimeMs(double timeMs) {
        this.timeMs = timeMs;
    }

    public void setTimesS(double timesS) {
        this.timesS = timesS;
    }
}
