import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.lang.Math;

class Main {
    public static void main(String[] args) {
        AddBinary.test();
    }
}

class RemoveDuplicates {
    static int removeDuplicates(int[] nums) {
        int N = nums.length;
        int IsDuplicate = 0;
        int Last = nums[0];
        int K = 1;
        int GarbageCount = 0;
        for (Integer I = 1; I < N - GarbageCount; ++I) {
            if (nums[I] == Last) {
                IsDuplicate = 1;
            } else {
                IsDuplicate = 0;
            }
            if (IsDuplicate == 1) {
                int Temporary = (shiftLeft(nums, I, N) == 0) ? 0: 1;
                GarbageCount += Temporary;
                I -= Temporary;
            } else {
                ++K;
            }
            Last = nums[I];
        } 
        return K;
    }

    static int shiftLeft(int[] Numbers, int Index, int N) {
        for (int I = Index; I < N - 1; ++I) {
            Numbers[I] = Numbers[I + 1];
        }
        return N - 1 - Index;
    }

    public static void test() {
        System.out.print("Testing RemoveDuplicates: ");
        int[] Input = {0,0,1,1,1,2,2,3,3,4};
        int[] ExpectedOutput = {0, 1, 2, 3, 4};
        int ExpectedK = 5;
        assert(removeDuplicates(Input) == ExpectedK);
        for (int I = 0; I < ExpectedK; ++I) {
            assert(Input[I] == ExpectedOutput[I]);
        }
        System.out.println("PASSED");
    }
}

class SieveOfEratosthenes {
    static ArrayList<Integer> generatePrimes(Integer UpperLimit) {
        var LoopLimit = Math.ceil(Math.sqrt(UpperLimit));
        var Primes = new ArrayList<Integer>();
        var CrossArray = new ArrayList<Integer>(
            Collections.nCopies(UpperLimit, 1));
        CrossArray.set(0, 0);
        CrossArray.set(1, 0);
        for (Integer I = 2; I < LoopLimit; ++I) {
            if (CrossArray.get(I) == 1) {
                Integer PrimeValue = I;
                for (Integer J = PrimeValue * 2; J < UpperLimit; J += PrimeValue) {
                    CrossArray.set(J, 0);
                }
            }
        }
        for (Integer I = 2; I < UpperLimit; ++I) {
            if (CrossArray.get(I) == 1) {
                Primes.add(I);
            }
        }
        return Primes;
    }

    public static void test() {
        System.out.print("Testing SieveOfEratosthenes: ");
        ArrayList<Integer> Expected = 
            new ArrayList<Integer>(Arrays.asList(
            2,3,5,7,11,13,17,19,23,29,31,37,41,
            43,47,53,59,61,67,71,73,79,83,89,97
            ));
        Integer UpperLimit = 100;
        ArrayList<Integer> Output = generatePrimes(UpperLimit);
        Integer ExpectedN = Expected.size();
        assert(Output.size() == ExpectedN);
        for (Integer I = 0; I < ExpectedN; ++I) {
            assert(Output.get(I) == Expected.get(I));
        }
        System.out.println("PASSED");
    }
}

class RemoveElement {
    static public void test() {
        System.out.print("Testing RemoveElement: ");
        int[] Input = {0,1,2,2,3,0,4,2};
        int Target = 2, ExpectedN = 5;
        int[] ExpectedOutput = {0, 1, 0, 4, 3};
        assert(removeElement(Input, Target) == ExpectedN);
        for (Integer I = 0; I < ExpectedN; ++I) {
            assert(ExpectedOutput[I] == Input[I]);
        }
        System.out.println("PASSED");
    }

    static public int removeElement(int[] nums, int val) {
        var TargetIndices = new ArrayList<Integer>();
        var N = nums.length;
        for (Integer I = 0; I < N; ++I) {
            if (nums[I] == val) {
                TargetIndices.add(I);
            }
        }        
        int BackwardCounter = 0;
        var TargetIndicesLength = TargetIndices.size();
        for (Integer I = TargetIndicesLength - 1; I >= 0; --I) {
            swap(nums, TargetIndices.get(I),
                N - 1 - BackwardCounter);
            BackwardCounter++;
        }
        return N - TargetIndicesLength;
    }

    static void swap(int[] Array, int Index1, 
        int Index2) {
        int Temporary = Array[Index1];
        Array[Index1] = Array[Index2];
        Array[Index2] = Temporary;
    }
}

class SearchInsert {
    static public void test() {
        System.out.print("Testing SearchInsert: ");
        int[] Input = {1, 3, 5, 6};
        Integer Target = 5;
        Integer ExpectedOutput = 2;
        assert(searchInsert(Input, Target) == ExpectedOutput);
        System.out.println("PASSED");
    }

    static public int searchInsert(int[] nums, int target) {
        var N = nums.length;
        if (N == 1) {
            if (target > nums[0]) {
                return 1;
            } else {return 0;}
        }
        if (target > nums[N - 1]) {
            return N;
        }
        var RightIndex = N - 1;
        var LeftIndex = 0;
        while (RightIndex > LeftIndex + 1) {
            var MiddleIndex = (RightIndex + LeftIndex) / 2;
            var MiddleValue = nums[MiddleIndex];
            if (MiddleValue == target) {
                return MiddleIndex;
            }
            else if (target < MiddleValue) {
                RightIndex = MiddleIndex;
            } else {
                LeftIndex = MiddleIndex;
            }
        }
        if (target <= nums[LeftIndex]) {
            return LeftIndex;
        }
        return RightIndex;
    }
}

class LengthOfLastWord {
    static int lengthOfLastWord(String s) {
        Integer LastWordLength = 0;
        var N = s.length();
        Integer I = N - 1;
        while (s.charAt(I) == ' ') {
            --I;
        }
        while (I >= 0) {
            if (s.charAt(I) == ' ') {
                break;
            }
            --I;
            ++LastWordLength;
        }
        return LastWordLength;
    }

    static public void test() {
        System.out.print("Testing SearchInsert: ");
        var Input = "Hello World";
        var ExpectedOutput = 5;
        assert(lengthOfLastWord(Input) == ExpectedOutput);
        System.out.println("PASSED");
    }
}

class PlusOne {
    static public int[] plusOne(int[] digits) {
        var DigitsAsArrayList = new ArrayList<Integer>();
        for (Integer Value: digits) {
            DigitsAsArrayList.add(Value);
        }
        var N = DigitsAsArrayList.size();
        Integer Carry = 1;
        for (Integer I = N - 1; I >= 0; --I) {
            var Sum = DigitsAsArrayList.get(I) + Carry;
            if (Sum > 9) {
                Carry = 1;
            } else {
                Carry = 0;
            }
            Sum %= 10;
            DigitsAsArrayList.set(I, Sum);
        }
        if (Carry == 1) {
            DigitsAsArrayList.add(0, 1);
        }
        var ResultDigits = new int[DigitsAsArrayList.size()];
        for (Integer I = 0; I < N; ++I) {
            ResultDigits[I] = DigitsAsArrayList.get(I);
        }
        return ResultDigits;
    }

    static public void test() {
        System.out.print("Testing PlusOne: ");
        int[] Input = {1, 9, 9};
        int[] ExpectedOutput = {2, 0, 0};
        int[] Output = plusOne(Input);
        for (Integer I = 0; I < ExpectedOutput.length; ++I) {
            assert(Output[I] == ExpectedOutput[I]);
        }
        System.out.println("PASSED");
    }
}

class AddBinary {
    static public String addBinary(String a, String b) {
        var SumString = "";
        Integer Carry = 0;
        var LengthA = a.length();
        var LengthB = b.length();
        var CounterA = LengthA - 1;
        var CounterB = LengthB - 1;
        while ((CounterA >= 0) && (CounterB >= 0)) {
            Integer ValueA = 
                (a.charAt(CounterA) == '1')? 1: 0;
            Integer ValueB = 
                (b.charAt(CounterB) == '1')? 1: 0;
            var Sum = ValueA + ValueB + Carry;
            if (Sum >= 2) {
                Carry = 1;
            } else {
                Carry = 0;
            }
            Sum %= 2;
            if (Sum == 0) {
                SumString += '0';
            } else {
                SumString += '1';
            }
            --CounterA;
            --CounterB;
        }
        var LongerCounter = 0;
        var LongerString = "";
        if (CounterA >= 0) {
            LongerCounter = CounterA;
            LongerString = a;
        } else {
            LongerCounter = CounterB;
            LongerString = b;
        }
        while (LongerCounter >= 0) {
            Integer Value = 
                (LongerString.charAt(
                LongerCounter) == '1')? 1: 0;
            var Sum = Value + Carry;
            if (Sum >= 2) {
                Carry = 1;
            } else {
                Carry = 0;
            }
            Sum %= 2;
            if (Sum == 0) {
                SumString += '0';
            } else {
                SumString += '1';
            }
            --LongerCounter;
        }
        if (Carry == 1) {
            SumString += '1';
        }
        return new StringBuilder(SumString)
            .reverse().toString();
    }

    static public void test() {
        System.out.print("Testing AddBinary: ");
        String Input1 = "11", Input2 = "1", ExpectedOutput = "100",
            Output = addBinary(Input1, Input2);
        assert(ExpectedOutput.equals(Output));
        System.out.println("PASSED");
    }
}
