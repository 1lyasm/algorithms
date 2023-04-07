def main():
    arr = [5, 4, 3, 2, 1]
    i = 1
    while i <= len(arr) - 1:
        key = arr[i]
        insert_pos = i
        while (insert_pos > 0) and (key < arr[insert_pos - 1]):
            arr[insert_pos] = arr[insert_pos - 1] 
            insert_pos = insert_pos - 1
        arr[insert_pos] = key
        i = i + 1
    print(arr)
    return

if __name__ == "__main__":
    main()
