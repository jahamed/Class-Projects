package cmsc131Utilities;

import java.util.*;

/**
 * This class allows us to control the generation of random numbers.
 * 
 * @author Nelson Padua-Perez, Fawzi Emad
 */

public class Random131 {
    private static long randomGeneratorSeed = 1234567L;
    private static boolean initialized = false;
    private static Random generator; 
    private static boolean randomSeed = true;
    
    // Allows us to generate a fixed sequence of random values
    public static void setDeterministic() {
        randomSeed = false;
        initialized = false;
    }
    
    // Generate fixed sequence with seed selected by user
    public static void setDeterministic(long seed) {
    	randomSeed = false;
    	initialized = false;
    	randomGeneratorSeed = seed;
    }
    
    // Allow us to generate a traditional sequence of random values
    public static void setNonDeterministic() {
        randomSeed = true;
        initialized = false;
    }
    
    private static void init() {
        if (!initialized) {
            if (randomSeed) {
                generator = new Random();
            }
            else {
                generator = new Random(randomGeneratorSeed);
            }
            initialized = true;
        } 
    }
    
    /**
     * Returns an integer random value between 0 and maxValue - 1
     * (includes 0 and maxValue - 1)
     * 
     * @return random integer value in the specified range
     */
    public static int getRandomInteger(int maxValue) {
        if (!initialized) 
            init();
        return generator.nextInt(maxValue);
    }
}
