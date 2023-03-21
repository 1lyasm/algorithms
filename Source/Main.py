def Main():
    testIsValidParentheses()


def romanToInt(s: str) -> int:
    def checkException(Index, Map, String):
        Result = (0, False)
        if (Index + 1 >= len(String)):
            return Result
        SearchString = String[Index] + String[Index + 1]
        I = 0
        for Key, Value in zip(Map.keys(), Map.values()):
            if Key == SearchString:
                Result = (Value, True)
            I += 1
        return Result
    ExceptionMap = {"IV": 4, "IX": 9, 
        "XL": 40, "XC": 90, "CD": 400, 
        "CM": 900}
    Map = {"I": 1, "V": 5, "X": 10, "L": 50,
        "C": 100, "D": 500, "M": 1000}
    N = len(s)
    I = 0
    Result = 0
    while I < N:
        ExceptionValue, ExceptionResult = \
            checkException(I, ExceptionMap, s)
        if ExceptionResult is True:
            Result += ExceptionValue
            I += 1
        else: 
            Result += Map[str(s[I])]
        I += 1
    return Result


def testRomanToInt():
    print("testRomanToInt: starting\n")
    assert(romanToInt("MCMXCIV") == 1994)
    print("testRomanToInt: OK\n")


def longestCommonPrefix(strs):
    MinimumLength = 201
    for String in strs:
        if len(String) < MinimumLength:
            MinimumLength = len(String)
    Result = ""
    CanContinue = True
    CommonIndex = 0
    while CanContinue and (CommonIndex < MinimumLength):
        if (len(strs[0]) < 1):
            return ""
        ExamplePrefix = strs[0][CommonIndex]
        for String in strs:
            if String[CommonIndex] != ExamplePrefix:
                CanContinue = False
        if CanContinue is True:
            Result += ExamplePrefix
        CommonIndex += 1
    return Result

def testLongestCommonPrefix():
    print("testLongestCommonPrefix: starting\n")
    strs = ["flower","flow","flight"]
    assert(longestCommonPrefix(strs) == "fl")
    print("testLongestCommonPrefix: OK\n")


def isValidParentheses(s: str) -> bool:
    def areSameType(A, B):
        if ((A == '(' and B == ')') or
            (A == '{' and B == '}') or
            (A == '[' and B == ']')):
            return True
        return False

    Stack = []
    N = len(s)
    if (N < 2): return False
    Close = [')', '}', ']']
    Open = ['(', '{', '[']
    if s[0] in Close:
        return False
    else:
        Stack.append(s[0])
    I = 1
    while I < N:
        if len(Stack) < 1:
            Previous = None
        else:
            Previous = Stack[-1]
        Current = s[I]
        if Current in Open:
            Stack.append(Current)
        else:
            if Previous != None and areSameType(Previous, Current):
                Last = Stack.pop()
            elif Current in Open:
                Stack.append(Current)
            elif Current in Close:
                return False
        I += 1
    if (len(Stack) > 0):
        return False
    return True

def testIsValidParentheses():
    print("testIsValidParentheses: starting\n")
    assert(isValidParentheses("([(){}]){[[]]}") == True)
    print("testIsValidParentheses: OK\n")

if __name__ == "__main__":
    Main()
